#!/usr/bin/env bash
# =====================================================================
# Odynex Axis Logistics LLC — Project SuGROOM Ecosystem
# Production Runtime Edge Infrastructure Entrypoint (Fly.io compatible)
# =====================================================================
set -euo pipefail

PORT="${PORT:-8080}"
INTERNAL_PORT="${INTERNAL_PORT:-8080}"

echo "====================================================================="
echo " awakening project-sugroom-ecosystem edge node infrastructure"
echo "====================================================================="

echo "[*] Auditing node allocation environment variables..."
if [ -z "${SUGROOM_LICENSE_TIER:-}" ]; then
    echo "[!] WARNING: SUGROOM_LICENSE_TIER is unset. Defaulting to isolated SANDBOX parameters."
    export SUGROOM_LICENSE_TIER="SANDBOX_MOCK"
else
    echo "[+] Active License Tier Token Detected: $SUGROOM_LICENSE_TIER"
fi

# Pre-flight compliance
if [ -x "./compliance_sentinel" ]; then
    echo "[*] Triggering internal Compliance Sentinel structural audit..."
    ./compliance_sentinel || echo "[!] Compliance sentinel returned non-zero (continuing in sandbox)"
else
    echo "[!] WARNING: Compliance Sentinel validation binary missing from app space."
fi

# One-shot smoke of the core engine
if [ -x "./sugroom_core_engine" ]; then
    echo "[*] Running core engine smoke pass..."
    ./sugroom_core_engine || true
fi

echo "[*] Starting long-running health / status HTTP server on 0.0.0.0:${PORT}"
echo "---------------------------------------------------------------------"

# Minimal HTTP server in pure bash + /dev/tcp (no python required).
# Fly.io health checks and http_service need something listening on internal_port.
STATUS_DIR="/tmp/sugroom_status"
mkdir -p "$STATUS_DIR"
echo "ok" > "$STATUS_DIR/health"
date -u +%Y-%m-%dT%H:%M:%SZ > "$STATUS_DIR/started_at"
echo "$SUGROOM_LICENSE_TIER" > "$STATUS_DIR/tier"

# Background loop that periodically re-runs a light engine tick so logs stay alive
(
  while true; do
    sleep 60
    if [ -x "./sugroom_core_engine" ]; then
      ./sugroom_core_engine >/dev/null 2>&1 || true
      date -u +%Y-%m-%dT%H:%M:%SZ > "$STATUS_DIR/last_tick"
    fi
  done
) &

# Serve a tiny static response forever using bash /dev/tcp
# Compatible with Fly.io http_service + health checks.
while true; do
  # Accept one connection at a time (good enough for health + status)
  { echo -ne "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\nConnection: close\r\n\r\n";
    echo "SuGROOM edge node — ONLINE";
    echo "tier=${SUGROOM_LICENSE_TIER}";
    echo "started=$(cat $STATUS_DIR/started_at 2>/dev/null || echo unknown)";
    echo "last_tick=$(cat $STATUS_DIR/last_tick 2>/dev/null || echo none)";
    echo "health=ok";
  } | nc -l -p "$PORT" -q 1 2>/dev/null \
    || { # fallback if nc is missing: pure bash listener is harder; use python if present
         if command -v python3 >/dev/null 2>&1; then
           python3 - <<'PY'
import http.server, socketserver, os, time
PORT = int(os.environ.get("PORT", "8080"))
class H(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        body = (
            "SuGROOM edge node — ONLINE\n"
            f"tier={os.environ.get('SUGROOM_LICENSE_TIER','SANDBOX_MOCK')}\n"
            f"health=ok\n"
            f"ts={time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())}\n"
        ).encode()
        self.send_response(200)
        self.send_header("Content-Type", "text/plain; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)
    def log_message(self, *a): pass
with socketserver.TCPServer(("0.0.0.0", PORT), H) as httpd:
    print(f"[*] Python HTTP health server listening on 0.0.0.0:{PORT}", flush=True)
    httpd.serve_forever()
PY
           break
         else
           echo "[!] Neither nc nor python3 available; sleeping to keep machine alive"
           sleep 3600
         fi
       }
done
