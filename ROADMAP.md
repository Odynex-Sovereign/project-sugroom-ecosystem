# Roadmap — Project SuGROOM Ecosystem

Prioritize the **smallest credible paid / licensed industrial product** first.

---

## Milestone 0 — Repository hygiene (1 week)

**Acceptance criteria**
- Single source tree (eliminate root / `src/` duplication).  
- Clean CMake that installs headers + library targets.  
- All existing engines still build and pass smoke tests.  
- LICENSE and trade-secret notices remain intact.  

**Estimate:** 3–5 engineer-days.

---

## Milestone 1 — Industrial MVP (4–6 weeks)

**Goal:** A usable control library that an engineer can embed.

**Acceptance criteria**
- Stable C API (and thin C++ wrapper) for every engine.  
- Deterministic unit tests with golden vectors for all 16 kernels.  
- Documented latency and memory characteristics.  
- Production Docker image (non-root) that exposes a simple CLI or gRPC/REST analysis surface.  
- CMake package config + optional Conan/vcpkg recipes.  
- README that lets a new engineer build and run in < 15 minutes.  
- Clear “Request commercial license / support” path (no online buyout price).  
- SBOM + basic container scanning in CI.  

**Out of scope for MVP**
- Web UI, multi-tenancy, Stripe, children’s portal, school/sports modules.

---

## Milestone 2 — Beta (hardware path)

**Acceptance criteria**
- Real Jetson / CUDA path behind a feature flag (`-DENABLE_CUDA=ON`).  
- Example ROS 2 node and MQTT adapter.  
- Structured logging + optional metrics endpoint.  
- Compliance Sentinel becomes a real, configurable policy engine.  
- Hardware-in-the-loop test harness outline.  

**Estimate:** 6–10 weeks after MVP.

---

## Milestone 3 — v1 (SDK + commercial readiness)

**Acceptance criteria**
- Official packages: deb, pip wheel (pybind11), Conan, vcpkg.  
- Private deployment / air-gapped installation guide.  
- Commercial support contract language and SLA outline.  
- Full threat model and export-control documentation.  
- Optional managed control-plane discussion only if industrial customers demand multi-site fleet management.  

---

## Later phases (explicitly separate products)

- Education / “WhyDream”-style materials that teach the *mathematical ideas* behind compensatory control, published in a different repository with strict age-appropriate and privacy design.  
- Multi-tenant SaaS control plane that *consumes* the SuGROOM library.  
- White-label or private-deployment offerings handled via quote and contract, never via self-serve checkout for source-code or IP buyout.

---

## Guiding principles

1. Prefer a small, complete industrial product over an enormous incomplete platform.  
2. Never claim the software automatically acquires clients.  
3. All external publishing, outreach, and commercial terms require human approval.  
4. Children’s or school-facing surfaces, if ever built, live in a separate codebase with independent safety review.
