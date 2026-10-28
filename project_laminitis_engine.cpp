/**
 * Project Equine-Laminitis – Quadruped Weight Redistribution
 * Biological Blueprint: Load shedding away from compromised support structures.
 */
#include "odynex_common.hpp"
#include <iostream>
#include <array>

struct LegLoad {
    float normal_force_n;
    float temperature_c;
    bool compromised;
};

class LaminitisEngine {
public:
    LaminitisEngine() {
        std::cout << "[INIT] Project Laminitis Weight Redistribution Engine online.\n";
    }

    void Redistribute(std::array<LegLoad, 4>& legs) {
        float total = 0.f;
        int healthy = 0;
        for (auto& l : legs) {
            if (l.temperature_c > 42.0f) l.compromised = true;
            if (!l.compromised) { total += l.normal_force_n; ++healthy; }
        }
        if (healthy == 0) return;
        float target_each = total / static_cast<float>(healthy);
        for (auto& l : legs) {
            if (l.compromised) l.normal_force_n *= 0.25f;
            else l.normal_force_n = target_each;
        }
    }
};

int main() {
    LaminitisEngine engine;
    std::array<LegLoad, 4> legs = {{
        {250.f, 38.f, false}, {250.f, 45.f, false}, {250.f, 37.f, false}, {250.f, 38.f, false}
    }};
    std::cout << "[RUNNING] Redistributing quadruped loads...\n";
    engine.Redistribute(legs);
    for (size_t i = 0; i < legs.size(); ++i) {
        std::cout << "  Leg " << i << " force=" << legs[i].normal_force_n
                  << (legs[i].compromised ? " [COMPROMISED]" : "") << "\n";
    }
    std::cout << "[SUCCESS] Load redistribution complete.\n";
    return 0;
}
