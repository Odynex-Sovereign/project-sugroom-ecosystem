# ==========================================
# STAGE 1: Compilation Tier
# ==========================================
FROM ubuntu:22.04 AS compilation_tier

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install core build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    gcc \
    g++ \
    make \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build_context

# Copy the entire workspace into the compilation tier
COPY . .

# Configure and build all 16 ecosystem modules using CMake
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --target all_engines -j$(nproc)

# ==========================================
# STAGE 2: Production Run Tier
# ==========================================
FROM ubuntu:22.04 AS production_tier

# Install minimal runtime shared libraries (libstdc++, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Pull only the compiled operational engine binaries from the compilation tier
COPY --from=compilation_tier /build_context/build/sugroom_core_engine .
COPY --from=compilation_tier /build_context/build/compliance_sentinel .
# Copy scripts or configurations if your application runtime requires them
COPY --from=compilation_tier /build_context/scripts ./scripts

# Set default entrypoint execution target to the core biomimicry controller
CMD ["./sugroom_core_engine"]
