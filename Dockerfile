# Stage 1: Build & Compilation Environment utilizing the authoritative Nvidia container baseline
FROM nvcr.io/nvidia/cuda:12.2.0-devel-ubuntu22.04 AS compilation_tier

LABEL maintainer="Odynex Axis Logistics LLC"
LABEL engineer="David Fabian Cadelinia"

WORKDIR /app_compile

# Install structural packages for build generation
RUN apt-get update && apt-get install -y cmake build-essential

# Copy source abstraction layer code
COPY src/sugroom_core_engine.cpp .
COPY CMakeLists.txt .

# Compile optimized execution binaries
RUN cmake . && make

# Stage 2: Hardened Edge Execution Tier to enforce TUTSA Trade Secret isolation
FROM nvcr.io/nvidia/cuda:12.2.0-runtime-ubuntu22.04 AS production_tier

WORKDIR /opt/odynex/sugroom

# Port runtime artifacts from build workspace while throwing away compilation histories
COPY --from=compilation_tier /app_compile/sugroom_core_engine .

# Enforce secure user isolation parameters inside industrial automation zones
RUN useradd -m odynex_operator && chown -R odynex_operator:odynex_operator /opt/odynex
USER odynex_operator

# Standard edge communication tracking indicators
EXPOSE 8080

ENTRYPOINT ["./sugroom_core_engine"]
