#!/usr/bin/env bash
# Force a clean rebuild + deploy on Fly.io (do NOT reuse old images)
set -euo pipefail
cd "$(dirname "$0")"

echo "==> Cleaning any stuck machines (ignore errors)..."
fly machines list -a project-sugroom-ecosystem 2>/dev/null || true
fly machines list -a project-sugroom-ecosystem -q 2>/dev/null | awk '{print $1}' | while read -r id; do
  [ -n "$id" ] && fly machines destroy "$id" -a project-sugroom-ecosystem --force || true
done

echo "==> Ensure public IPs exist..."
fly ips list -a project-sugroom-ecosystem 2>/dev/null || true
fly ips allocate-v4 --shared -a project-sugroom-ecosystem 2>/dev/null || true
fly ips allocate-v6 -a project-sugroom-ecosystem 2>/dev/null || true

echo "==> Building FROM Dockerfile (no --image) and deploying..."
fly deploy -a project-sugroom-ecosystem \
  --config fly.toml \
  --build-only=false \
  --wait-timeout 10m \
  --strategy immediate \
  --ha=false

echo "==> Status"
fly status -a project-sugroom-ecosystem
echo "==> Recent logs"
fly logs -a project-sugroom-ecosystem --no-tail | tail -40
echo
echo "Open: https://project-sugroom-ecosystem.fly.dev/"
