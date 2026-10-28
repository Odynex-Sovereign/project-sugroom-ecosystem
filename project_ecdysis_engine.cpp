/**
 * Project Gecko-Ecdysis – Dynamic Clamping Friction Control
 * Biological Blueprint: Gecko adhesion / shedding phase grip adaptation.
 */
#include "odynex_common.hpp"
#include <iostream>
#include <vector>

struct ContactPadTelemetry {
    float static_friction_coefficient;
    float micro_slip_velocity;
    float normal_clamping_force;
};

struct OptimizedGripCommand {
    float adjusted_clamping_pressure;
    float target_contact_angle_degrees;
};

class EcdysisEngine {
public:
    EcdysisEngine() {
        std::cout << "[INIT] Project Ecdysis Tactile Friction Engine online.\n";
    }

    OptimizedGripCommand Optimize(const ContactPadTelemetry& p) {
        OptimizedGripCommand c;
        c.adjusted_clamping_pressure = p.normal_clamping_force;
        c.target_contact_angle_degrees = 0.f;
        if (p.micro_slip_velocity > 0.05f || p.static_friction_coefficient < 0.4f) {
            c.adjusted_clamping_pressure *= 1.35f;
            c.target_contact_angle_degrees = 12.0f;
        }
        return c;
    }
};

int main() {
    EcdysisEngine engine;
    std::vector<ContactPadTelemetry> pads = {
        {0.8f, 0.01f, 40.f}, {0.3f, 0.12f, 40.f}, {0.6f, 0.02f, 35.f}
    };
    std::cout << "[RUNNING] Sampling tactile surface tension...\n";
    for (size_t i = 0; i < pads.size(); ++i) {
        auto c = engine.Optimize(pads[i]);
        std::cout << "  Pad " << i << " pressure=" << c.adjusted_clamping_pressure << " N";
        if (c.target_contact_angle_degrees > 0.f)
            std::cout << " [SLIP COMPENSATED " << c.target_contact_angle_degrees << " deg]";
        std::cout << "\n";
    }
    std::cout << "[SUCCESS] Grip optimization complete.\n";
    return 0;
}
