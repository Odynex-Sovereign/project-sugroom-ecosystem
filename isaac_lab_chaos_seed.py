#!/usr/bin/env python3
"""
Pathological Chaos Seed Manager for Isaac Lab / digital-twin validation.
Injects SuGROOM tremor, nystagmus camera jitter, and phantom-limb detachment.
Works with or without PyTorch (falls back to NumPy).
"""
from __future__ import annotations

import math
import sys

try:
    import torch
    HAS_TORCH = True
except ImportError:
    HAS_TORCH = False
    import numpy as np


class PathologicalChaosSeedManager:
    def __init__(self, num_envs: int = 512, device: str = "cpu"):
        self.num_envs = num_envs
        self.device = device
        print(f"[INIT] PathologicalChaosSeedManager envs={num_envs} device={device} torch={HAS_TORCH}")

    def inject_sugroom_tremor(self, joint_torques, frame_count: int, amplitude: float = 0.8):
        """High-frequency tremor perturbation on joint torque tensors."""
        if HAS_TORCH:
            noise = (
                torch.sin(torch.linspace(0, 2.0 * math.pi, joint_torques.shape[-1], device=self.device))
                * amplitude
                * math.sin(frame_count * 0.37)
            )
            return joint_torques + noise
        # NumPy fallback
        n = joint_torques.shape[-1]
        noise = np.sin(np.linspace(0, 2.0 * math.pi, n)) * amplitude * math.sin(frame_count * 0.37)
        return joint_torques + noise

    def inject_nystagmus_camera_jitter(self, camera_rgb_tensor, frame_count: int, intensity: int = 15):
        """Rhythmic visual frame displacement."""
        if frame_count % 2 != 0:
            return camera_rgb_tensor
        if HAS_TORCH:
            return torch.roll(camera_rgb_tensor, shifts=(intensity, -intensity), dims=(1, 2))
        return np.roll(camera_rgb_tensor, shift=(intensity, -intensity), axis=(1, 2))

    def assert_phantom_limb_detachment(self, root_states, env_ids, joint_index_to_sever: int):
        """Simulate catastrophic component loss."""
        if HAS_TORCH:
            root_states[env_ids, joint_index_to_sever, :] = 0.0
        else:
            root_states[env_ids, joint_index_to_sever, :] = 0.0
        print(f"[CHAOS ACTION] Node {joint_index_to_sever} severed. Tracking Phantom Limb adaptation response.")
        return root_states


if __name__ == "__main__":
    chaos_manager = PathologicalChaosSeedManager(num_envs=512, device="cpu")
    if HAS_TORCH:
        dummy_torques = torch.ones((512, 6)) * 12.0
    else:
        dummy_torques = np.ones((512, 6)) * 12.0

    print("[RUNNING] Testing SuGROOM high-frequency noise injection loop...")
    perturbed = chaos_manager.inject_sugroom_tremor(dummy_torques, frame_count=45)
    sample = perturbed[0, 0].item() if HAS_TORCH else float(perturbed[0, 0])
    print(f"[SUCCESS] Tensors modified. Sample baseline torque altered from 12.0 to: {sample:.4f}")
    sys.exit(0)
