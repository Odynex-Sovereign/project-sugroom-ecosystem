# Product Requirements — Project SuGROOM Ecosystem

**Derived strictly from the verified contents of the repository.**  
External product briefs that describe consumer SaaS, children’s portals, or multi-tenant education platforms are treated as out-of-scope for this codebase.

---

## 1. Product Mission

SuGROOM is an edge control library and simulation suite that applies biomimetic algorithms (inspired by compensatory neurological and physiological mechanisms) to stabilize mechanical systems under high-frequency noise and structural jitter, enabling higher precision from lower-cost hardware.

---

## 2. Primary Users

- Robotics and mechatronics engineers and researchers  
- Autonomous mobile robot (AMR) and factory-automation teams  
- Drone / UAV and space (LEO) guidance teams  
- Industrial OEMs evaluating software-defined precision  
- Advanced university robotics and controls laboratories  

---

## 3. Jobs-to-be-Done

- Ingest high-frequency actuator or structural telemetry  
- Apply domain-specific attenuation, locking, damping, or fallback kernels  
- Output stabilized trajectories at millimeter-class tolerance (simulation today; real hardware later)  
- Run the same kernels on CPU (laptop / CI) and optionally on Jetson / CUDA later  
- Satisfy basic export-control / geofence checks  

---

## 4. Value Propositions

- Software-only precision improvement on high-tolerance mechanical hardware  
- Modular “engine” architecture (one biological blueprint per failure mode)  
- CPU-portable for development and continuous integration; NVIDIA path as an optional future accelerator  
- Clear separation between open simulation kernels and proprietary coefficients (trade-secret notice)  

---

## 5. User Roles (current reality)

Only “operator / developer” who builds and runs the console binaries.  

No multi-user, parent/guardian, student, educator, billing, or organization model exists in the repository.

---

## 6. Core Workflows (verified)

1. Configure and build all engines with CMake.  
2. Run individual engine or the `all_engines` target.  
3. Feed mock telemetry vectors; receive stabilized output.  
4. Package via Docker multi-stage build or deploy via Fly.io.  
5. (Optional) Run the Isaac Lab chaos-seed script for synthetic disturbance generation.  

---

## 7. Non-Goals

- Consumer-facing web application  
- Children’s learning portal (“WhyDream”) or any product surface targeting minors  
- School, sports-club, nonprofit, or municipality multi-tenant SaaS  
- Stripe billing, free/paid tiers, white-label, or online IP-buyout checkout  
- Any claim that the software “automatically gains clients”  
- Medical or healthcare claims  

---

## 8. Measurable KPIs (realistic for this codebase)

| KPI | Target |
|-----|--------|
| Binary build success rate across platforms | ≥ 99 % on CI matrix |
| Smoke-test pass rate | 100 % of engines exit 0 |
| Latency of attenuation kernel on representative vector lengths | Documented and reproducible |
| Memory footprint of production Docker image | Minimized and tracked |
| Number of distinct biological control modes with deterministic, reproducible output | 16 (current set) |
| Time for a new engineer to build and run locally | < 15 minutes |

---

## 9. Assumption Log

- Any expansion into education, multi-tenant SaaS, or consumer pricing would be a **separate product** that may later reference or embed SuGROOM kernels; it is not a transformation of this repository.
- Commercial licensing discussions remain quote-based and contract-driven; no self-serve buyout price will be published without legal review.
