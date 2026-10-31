# ==========================================
# STAGE 2: Production Run Tier
# ==========================================
FROM ubuntu:22.04 AS production_tier

RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Pull binaries from compilation tier cleanly
COPY --from=compilation_tier /build_context/build/sugroom_core_engine .
COPY --from=compilation_tier /build_context/build/compliance_sentinel .
COPY --from=compilation_tier /build_context/scripts ./scripts

# CRITICAL SECURITY SETUPS: Enforce script execution parameters
RUN chmod +x ./scripts/entrypoint.sh ./sugroom_core_engine ./compliance_sentinel

# Execute via the standardized production bootstrap wrapper
ENTRYPOINT ["./scripts/entrypoint.sh"]
