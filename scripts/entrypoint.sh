#!/usr/bin/env bash
# =====================================================================
# Odynex Axis Logistics LLC — Project SuGROOM Ecosystem
# Production Runtime Edge Infrastructure Entrypoint Bootstrapper
# =====================================================================

set -e

echo "====================================================================="
echo " awakening project-sugroom-ecosystem edge node infrastructure"
echo "====================================================================="

# 1. Enforce Infrastructure Identity Diagnostics Verification
echo "[*] Auditing node allocation environment variables..."
if [ -z "$SUGROOM_LICENSE_TIER" ]; then
    echo "[!] WARNING: SUGROOM_LICENSE_TIER is unset. Defaulting to isolated SANDBOX parameters."
    export SUGROOM_LICENSE_TIER="SANDBOX_MOCK"
else
    echo "[+] Active License Tier Token Detected: $SUGROOM_LICENSE_TIER"
fi

# 2. Run Pre-Flight Compliance Registry Diagnostics
if [ -f "./compliance_sentinel" ]; then
    echo "[*] Triggering internal Compliance Sentinel structural audit..."
    ./compliance_sentinel
else
    echo "[!] WARNING: Compliance Sentinel validation binary missing from app space."
fi

# 3. Hand over process control seamlessly to the main processing engine loop
echo "[*] Launching high-frequency core telemetry attenuation loops..."
echo "---------------------------------------------------------------------"
exec ./sugroom_core_engine
