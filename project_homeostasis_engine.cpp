/**
 * Project Homeostasis – Decentralized Traffic Self-Regulation
 * Biological Blueprint: Physiological homeostasis / local feedback loops.
 */
#include "odynex_common.hpp"
#include <iostream>
#include <vector>

struct TrafficNode {
    float local_load;
    float capacity;
    float throttle; // 0..1
};

class HomeostasisEngine {
public:
    HomeostasisEngine() {
        std::cout << "[INIT] Project Homeostasis Traffic Self-Regulation Engine online.\n";
    }

    void Regulate(std::vector<TrafficNode>& nodes) {
        for (auto& n : nodes) {
            float util = n.capacity > 0.f ? n.local_load / n.capacity : 1.f;
            if (util > 0.9f) n.throttle = odynex::clampf(n.throttle - 0.15f, 0.2f, 1.f);
            else if (util < 0.5f) n.throttle = odynex::clampf(n.throttle + 0.1f, 0.2f, 1.f);
        }
    }
};

int main() {
    HomeostasisEngine engine;
    std::vector<TrafficNode> mesh = {
        {80.f, 100.f, 1.0f}, {95.f, 100.f, 1.0f}, {30.f, 100.f, 0.7f}
    };
    std::cout << "[RUNNING] Self-regulating decentralized traffic mesh...\n";
    engine.Regulate(mesh);
    for (size_t i = 0; i < mesh.size(); ++i) {
        std::cout << "  Node " << i << " throttle=" << mesh[i].throttle << "\n";
    }
    std::cout << "[SUCCESS] Homeostasis regulation pass complete.\n";
    return 0;
}
