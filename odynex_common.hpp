#pragma once
/**
 * Odynex Axis Logistics LLC – Shared types for Pathological Biomimicry engines.
 * Host-side (CPU) portable definitions. CUDA paths can be layered on top later.
 */
#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace odynex {

struct Vec3 {
    float x = 0.f, y = 0.f, z = 0.f;
};

inline float clampf(float v, float lo, float hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

inline float high_freq_noise(float signal, float scale = 0.12f) {
    return std::sin(signal * 1000.0f) * scale;
}

} // namespace odynex
