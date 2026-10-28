# Project SuGROOM Ecosystem

**Pathological Biomimicry Ecosystem** — Edge AI that transforms mechanical noise, structural jitter, and tremors into millimeter precision using the NVIDIA Physical AI stack.

Developed by **Odynex Axis Logistics LLC** (Founder: David Fabian Cadelinia). SuGROOM decouples systemic structural intent from high-frequency mechanical tremors, allowing low-cost, high-tolerance hardware to execute hyper-precise trajectories entirely via software.

---

## Ecosystem Modules

| Module | Biological Blueprint | Application |
|--------|----------------------|-------------|
| **SuGROOM** | Feline Cerebellar Hypoplasia | Inverse-tremor attenuation for AMR / factory floors |
| **Nystagmus** | Rhythmic eye oscillation | Visual / optical path stabilization (drones, LEO) |
| **Myotonia** | Startle-induced muscle stiffness | Sub-ms adaptive rigid locking |
| **Hypermetria** | Dysmetric over-shoot | Predictive trajectory damping |
| **Synesthesia** | Sensory cross-wiring | Cross-modal fallback navigation |
| **Parkinson** | Intermittent pathway degradation | Signal dropout resilience |
| **Hemophilia** | Rapid clotting | Hydraulic leak isolation |
| **Tetanus** | Inhibitory interneurons | Motor current spasm dampening |
| **Phantom-Limb** | Cortical remapping | Kinematic loss rebalancing |
| **Laminitis** | Equine load shedding | Quadruped weight redistribution |
| **Ecdysis** | Gecko adhesion cycles | Dynamic clamping friction control |
| **Scab** | Wound sealing | Self-healing resin boundaries |
| **Melanogenesis** | Melanin UV response | Active radiation shielding |
| **Malunion** | Bone angle compensation | Warped geometry calibration |
| **Homeostasis** | Physiological feedback | Decentralized traffic self-regulation |
| **Compliance Sentinel** | — | ECCN / geofence export-control interlock |

---

## Repository Layout

```
├── include/odynex_common.hpp   # Shared host-side types
├── src/                       # 16 engine executables (CPU-portable)
├── scripts/                   # Isaac Lab chaos seeds + Jetson setup
├── deploy/                    # Secure docker-compose + boot script
├── docs/                      # Executive briefs
├── CMakeLists.txt             # Host build (optional CUDA later)
├── Dockerfile                 # Multi-stage: compilation_tier → production_tier
└── .github/workflows/         # CI: build all engines + ctest + docker
```

---

## Quick Start (host / CI)

```bash
# Configure & build all 16 engines
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --target all_engines -j$(nproc)

# Run every engine as a smoke test
ctest --test-dir build --output-on-failure

# Single engine
./build/sugroom_core_engine
./build/compliance_sentinel

# Python chaos seed (NumPy or PyTorch)
python3 scripts/isaac_lab_chaos_seed.py
```

### Docker

```bash
docker build --target compilation_tier -t odynex-sugroom:build .
docker build --target production_tier -t odynex-sugroom:run .
docker run --rm odynex-sugroom:run
```

### Jetson / CUDA note

Default builds are **CPU-portable** so CI and laptops work without the NVIDIA toolchain.  
CUDA/TensorRT/DeepStream paths can be re-enabled later with `-DENABLE_CUDA=ON` and the corresponding Jetson base images (see `scripts/setup_jetson_env.sh`).

---

## License

See [LICENSE](LICENSE) and [LICENSE.md](LICENSE.md).  
Trade-secret and defensive-publication notices apply to proprietary biological matrix coefficients not present in this public tree.
