# SuGROOM — production deploy fix

## Why previous deploys failed

1. **Old image reused** — `fly deploy --image registry.fly.io/...:deployment-b5e0...` never rebuilt the fixed Dockerfile.
2. **Process exited** — engines are one-shot; PID 1 must be a long-running server.
3. **No listener on 8080** — Fly Proxy / health checks need something bound to `internal_port`.
4. **IP allocation race** — first deploy sometimes fails allocating IPv6; remediable with `fly ips`.

## This package

- Python HTTP server is **PID 1** (always listens on `$PORT`).
- Engines run once at boot + optional background tick; failures never kill the container.
- `auto_stop_machines = "off"` so the machine stays up for production demos.
- `DEPLOY.sh` destroys stuck machines, allocates IPs, and **forces a Dockerfile rebuild**.

## Deploy on Fly.io (required steps)

```bash
unzip project-sugroom-ecosystem-fly-fix.zip
cd sugroom-fly-fix

# Login if needed
fly auth login

# One-shot helper (recommended)
./DEPLOY.sh

# OR manually — NEVER pass --image on first successful deploy
fly deploy -a project-sugroom-ecosystem --config fly.toml --wait-timeout 10m
```

If IP errors persist:
```bash
fly ips allocate-v4 --shared -a project-sugroom-ecosystem
fly ips allocate-v6 -a project-sugroom-ecosystem
fly deploy -a project-sugroom-ecosystem --config fly.toml --wait-timeout 10m
```

Verify:
```bash
fly status -a project-sugroom-ecosystem
fly logs -a project-sugroom-ecosystem
curl -s https://project-sugroom-ecosystem.fly.dev/
```

## Any other cloud / local

```bash
docker compose up --build -d
curl -s http://127.0.0.1:8080/
```

Same image works on Railway, Render, AWS ECS, GCP Cloud Run, K8s — expose container port 8080.
