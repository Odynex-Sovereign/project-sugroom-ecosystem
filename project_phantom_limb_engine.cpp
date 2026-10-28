/**
 * Project Phantom-Limb – Kinematic Loss Trajectory Rebalancer
 * Biological Blueprint: Cortical remapping after limb loss.
 */
#include "odynex_common.hpp"
#include <iostream>
#include <vector>

struct JointState {
    float position;
    float velocity;
    bool active;
};

class PhantomLimbEngine {
public:
    PhantomLimbEngine() {
        std::cout << "[INIT] Project Phantom-Limb Rebalancer online.\n";
    }

    void Rebalance(std::vector<JointState>& joints, size_t severed_idx) {
        if (severed_idx >= joints.size()) return;
        joints[severed_idx].position = 0.f;
        joints[severed_idx].velocity = 0.f;
        joints[severed_idx].active = false;
        // Redistribute residual effort to remaining active joints
        int active = 0;
        for (const auto& j : joints) if (j.active) ++active;
        if (active == 0) return;
        float share = 1.0f / static_cast<float>(active);
        for (auto& j : joints) {
            if (j.active) j.velocity *= (1.0f + share * 0.15f);
        }
    }
};

int main() {
    PhantomLimbEngine engine;
    std::vector<JointState> chain = {
        {0.1f, 1.0f, true}, {0.2f, 1.1f, true}, {0.3f, 0.9f, true}, {0.4f, 1.0f, true}
    };
    std::cout << "[RUNNING] Simulating component loss at joint 2...\n";
    engine.Rebalance(chain, 2);
    for (size_t i = 0; i < chain.size(); ++i) {
        std::cout << "  Joint " << i << " active=" << chain[i].active
                  << " vel=" << chain[i].velocity << "\n";
    }
    std::cout << "[SUCCESS] Phantom-limb rebalance complete.\n";
    return 0;
}
