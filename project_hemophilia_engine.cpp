/**
 * Project Hemophilia – Vascular Coagulation / Leak Isolation
 * Biological Blueprint: Rapid isolation of fluid path breaches.
 */
#include "odynex_common.hpp"
#include <iostream>
#include <vector>

struct HydraulicNode {
    float node_pressure;
    float flow_rate;
    float expected_flow;
};

class HemophiliaEngine {
public:
    HemophiliaEngine() {
        std::cout << "[INIT] Project Hemophilia Leak Isolation Engine online.\n";
    }

    bool DetectLeak(const HydraulicNode& n, float tolerance = 0.15f) {
        if (n.expected_flow <= 0.f) return false;
        float ratio = std::fabs(n.flow_rate - n.expected_flow) / n.expected_flow;
        return ratio > tolerance || n.node_pressure < 0.5f;
    }
};

int main() {
    HemophiliaEngine engine;
    std::vector<HydraulicNode> nodes = {
        {12.0f, 3.1f, 3.0f},
        {2.0f, 0.4f, 3.0f},
        {11.5f, 2.9f, 3.0f}
    };
    std::cout << "[RUNNING] Scanning hydraulic mesh for breaches...\n";
    for (size_t i = 0; i < nodes.size(); ++i) {
        bool leak = engine.DetectLeak(nodes[i]);
        std::cout << "  Node " << i << (leak ? " <-- LEAK ISOLATE" : " OK") << "\n";
    }
    std::cout << "[SUCCESS] Coagulation / isolation pass complete.\n";
    return 0;
}
