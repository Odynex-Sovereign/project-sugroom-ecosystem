# ==========================================
# STAGE 1: Compilation Tier Workspace
# ==========================================
FROM ubuntu:22.04 AS compilation_tier

# Prevent interactive configuration screens during apt calls
ENV DEBIAN_FRONTEND=noninteractive

# Provision complete toolchain binaries
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    gcc \
    g++ \
    make \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build_context

# Copy structural codebase into build engine context
COPY . .

# Run CMake compilation across 16 core simulation units
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --target all_engines -j$(nproc)

# ==========================================
# STAGE 2: Lightweight Production Execution
# ==========================================
FROM ubuntu:22.04 AS production_tier

RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Safely abstract the binaries from Stage 1 local alias map
COPY --from=compilation_tier /build_context/build/sugroom_core_engine .
COPY --from=compilation_tier /build_context/build/compliance_sentinel .
COPY --from=compilation_tier /build_context/scripts ./scripts

# Configure process authorizations
RUN chmod +x ./scripts/entrypoint.sh ./sugroom_core_engine ./compliance_sentinel

ENTRYPOINT ["./scripts/entrypoint.sh"]
