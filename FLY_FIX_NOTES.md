# Fly.io crash fix

## Root causes
1. **Process exited immediately** — `sugroom_core_engine` and friends are one-shot smoke binaries (`return 0`). Fly.io marks the machine dead when the main process exits.
2. **Nothing listened on port 8080** — `fly.toml` declares `http_service.internal_port = 8080` but the image never opened a socket.
3. **CMakeLists was incomplete** — only one `add_executable` was real; the rest were comments, so Docker build of `all_engines` failed or was incomplete.
4. **`src/*.cpp` required CUDA/TensorRT** — those headers are not present on stock Ubuntu, so the image could not compile the CUDA path.

## What this package changes
- Complete portable `CMakeLists.txt` building all engines from root `*.cpp` (CPU-only).
- Fixed `sugroom_core_engine.cpp` so it compiles without the broken CUDA kernel interceptor.
- New `scripts/entrypoint.sh` that:
  - runs compliance + core smoke once
  - starts a long-lived HTTP health server on `$PORT` (8080)
  - keeps a background tick so the machine stays useful
- Production image installs `python3` + `netcat-openbsd` for the health server.
- `fly.toml` adds a health check and sets `PORT` / license env.

## Deploy
```bash
cd sugroom-fly-fix
fly apps create project-sugroom-ecosystem   # if not already created
fly deploy
fly status
fly logs
curl https://project-sugroom-ecosystem.fly.dev/
```
