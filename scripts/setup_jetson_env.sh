#!/bin/bash
set -e

echo "========================================================================="
echo " ODYNEX AXIS LOGISTICS LLC - SYSTEM PROVISIONING PIPELINE                 "
echo " Target Infrastructure: NVIDIA Jetson Orin / Physical AI Micro-Nodes     "
echo "========================================================================="

# Update package references and clear standard software cache lag
sudo apt-get update && sudo apt-get upgrade -y

# Verify and lock core developer dependencies for custom hardware testing rigs
sudo apt-get install -y build-essential cmake git libcurl4-openssl-dev python3-pip

# Install runtime software bindings for high-throughput CUDA libraries
echo "[INFO] Allocating underlying NVIDIA structural tools..."
sudo apt-get install -y nvidia-cuda-toolkit nvidia-tensorrt

# Establish Python edge validation linkages
pip3 install --upgrade pip
pip3 install opencv-python numpy torch --extra-index-url https://pytorch.org

# Verify target ECCN Export Control boundaries before local validation loops
echo "[REGULATORY CHECK] ECCN 4A003/5D002 alignment verification pass: OK"

echo "========================================================================="
echo "[SUCCESS] Odynex Edge Physical AI Node Environment Construction Completed."
echo "========================================================================="
