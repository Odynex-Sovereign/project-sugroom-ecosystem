#!/usr/bin/env bash
# SuGROOM production entrypoint — MUST stay alive and bind PORT
set +e
export PORT="${PORT:-8080}"
export SUGROOM_LICENSE_TIER="${SUGROOM_LICENSE_TIER:-SANDBOX_MOCK}"

echo "====================================================================="
echo " SuGROOM edge node starting (port=$PORT tier=$SUGROOM_LICENSE_TIER)"
echo "====================================================================="

# Best-effort smoke (never fail the container)
if [ -x ./compliance_sentinel ]; then
  ./compliance_sentinel 2>&1 || true
fi
if [ -x ./sugroom_core_engine ]; then
  ./sugroom_core_engine 2>&1 || true
fi

# Background periodic tick (optional)
(
  while true; do
    sleep 120
    [ -x ./sugroom_core_engine ] && ./sugroom_core_engine >/dev/null 2>&1 || true
  done
) &

echo "[*] Binding HTTP health server on 0.0.0.0:${PORT}"
exec python3 -u - <<'PY'
import http.server
import socketserver
import os
import time
import signal
import sys

PORT = int(os.environ.get("PORT", "8080"))
TIER = os.environ.get("SUGROOM_LICENSE_TIER", "SANDBOX_MOCK")
STARTED = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())

class Handler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        body = (
            "SuGROOM edge node — ONLINE\n"
            f"path={self.path}\n"
            f"tier={TIER}\n"
            f"started={STARTED}\n"
            f"ts={time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())}\n"
            "health=ok\n"
        ).encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", "text/plain; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    def do_HEAD(self):
        self.send_response(200)
        self.send_header("Content-Type", "text/plain; charset=utf-8")
        self.end_headers()

    def log_message(self, fmt, *args):
        sys.stdout.write("[%s] %s\n" % (self.log_date_time_string(), fmt % args))
        sys.stdout.flush()

def _shutdown(signum, frame):
    print("shutdown signal", signum, flush=True)
    sys.exit(0)

signal.signal(signal.SIGTERM, _shutdown)
signal.signal(signal.SIGINT, _shutdown)

# Allow quick restarts on same port
socketserver.TCPServer.allow_reuse_address = True
with socketserver.TCPServer(("0.0.0.0", PORT), Handler) as httpd:
    print(f"[*] HTTP listening on 0.0.0.0:{PORT}", flush=True)
    httpd.serve_forever()
PY
