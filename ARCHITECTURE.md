# Architecture — Project SuGROOM Ecosystem

**Status:** Reflects the verified current state of the repository plus recommended target architecture for an industrial MVP.

---

## 1. Current Architecture (verified)

```mermaid
flowchart TB
    subgraph Host["Host / CI / Laptop"]
        CMake[CMake 3.22+] --> Engines["16 C++ Executables<br/>(CPU-portable)"]
        Engines --> Smoke["ctest smoke tests"]
    end

    subgraph Docker["Docker Multi-stage"]
        Compile["compilation_tier<br/>Ubuntu + gcc/cmake"] --> Prod["production_tier<br/>minimal runtime"]
        Prod --> Core["sugroom_core_engine"]
        Prod --> Sentinel["compliance_sentinel"]
    end

    subgraph Optional["Future / Stub"]
        CUDA["CUDA / TensorRT stubs"]
        Jetson["setup_jetson_env.sh"]
        Isaac["isaac_lab_chaos_seed.py"]
    end

    Engines --> Docker
    CUDA -.-> Engines
```

### Component inventory (current)

| Layer | Status |
|-------|--------|
| Frontend / UI | None |
| Backend / API | None (console only) |
| Data layer | None (in-memory mock vectors) |
| Authentication | None |
| Billing | None |
| Notifications | None |
| Analytics | None |
| Background jobs | None |
| Object storage | None |
| Real-time | None |
| Observability | Console `std::cout` only |
| Backups / DR | None |

### Deployment options present

- Local CMake + ctest  
- Docker multi-stage  
- Fly.io (`fly.toml`)  
- Multiple cloud CI starters (AWS, Azure, Google, IBM, Docker publish, CodeQL)

---

## 2. Target Architecture for Industrial MVP

```mermaid
flowchart TB
    subgraph Client["Consumer of the library"]
        App["Customer application<br/>or ROS 2 / MQTT node"]
    end

    subgraph Library["SuGROOM SDK"]
        API["Stable C / C++ API<br/>+ optional pybind11"]
        Kernels["16 biomimetic kernels<br/>(header + implementation)"]
        Config["Runtime configuration<br/>+ compliance policy"]
        API --> Kernels
        API --> Config
    end

    subgraph Runtime["Deployment artifacts"]
        Lib["Shared / static library"]
        CLI["Optional CLI for offline analysis"]
        Container["Production container<br/>(CPU or Jetson)"]
    end

    subgraph Observability["Minimal observability"]
        Log["Structured logging"]
        Metrics["Optional Prometheus endpoint"]
    end

    App --> API
    Kernels --> Lib
    Kernels --> CLI
    Lib --> Container
    CLI --> Container
    Container --> Log
    Container --> Metrics
```

### Build-vs-buy decisions

| Capability | Decision | Rationale |
|------------|----------|-----------|
| Core kernels | Build (keep pure C++) | Domain IP; already present |
| Packaging / SDK | Build (CMake install + Conan/vcpkg) | Standard industrial practice |
| Container base | Buy (official Ubuntu / NVIDIA Jetson images) | Security & maintenance |
| Telemetry transport | Buy / adopt (ROS 2, MQTT, OPC UA) | Do not invent a new protocol |
| Auth / multi-tenant | Out of scope for this repo | Belongs to a future control-plane product |
| Billing / Stripe | Out of scope for this repo | Quote-based commercial model only |
| Secrets management | Use platform secrets (Fly, cloud KMS) | Never hard-code |

---

## 3. Data flow (current simulation path)

1. Host process constructs a `std::vector` of mock actuator telemetry.  
2. Kernel function (sin/cos-based attenuation or equivalent) transforms the vector in-place or into an output buffer.  
3. Result is printed or returned; process exits.  

No persistence, no network, no multi-process coordination.

---

## 4. Security & compliance posture (current + required for MVP)

- **Current:** Console-only, no network surface, root Docker containers.  
- **MVP requirements:**
  - Non-root container user  
  - Explicit export-control / geofence policy evaluation before any real actuation path is enabled  
  - Clear documentation that proprietary coefficients are not in the public tree  
  - SBOM generation in CI  
  - Dependency and container scanning  

---

## 5. Future optional layers (explicitly non-goals for current MVP)

- Multi-tenant SaaS control plane  
- Web dashboard  
- Children’s learning portal  
- Market-data or industrial telemetry SaaS integrations  

These would live in separate repositories that *consume* the SuGROOM library.
