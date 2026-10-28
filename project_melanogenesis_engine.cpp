/**
 * Project Melanogenesis – Active Radiation Shielding Loop
 * Biological Blueprint: Melanin response to ionizing / UV flux.
 */
#include "odynex_common.hpp"
#include <iostream>
#include <vector>

struct RadiationSample {
    float flux_uSv_h;
    float shield_opacity; // 0..1
};

class MelanogenesisEngine {
public:
    MelanogenesisEngine() {
        std::cout << "[INIT] Project Melanogenesis Radiation Shield Engine online.\n";
    }

    void AdaptShield(RadiationSample& s) {
        if (s.flux_uSv_h > 50.f) s.shield_opacity = odynex::clampf(s.shield_opacity + 0.25f, 0.f, 1.f);
        else if (s.flux_uSv_h < 10.f) s.shield_opacity = odynex::clampf(s.shield_opacity - 0.05f, 0.1f, 1.f);
    }
};

int main() {
    MelanogenesisEngine engine;
    std::vector<RadiationSample> samples = {
        {5.0f, 0.3f}, {80.0f, 0.3f}, {20.0f, 0.6f}
    };
    std::cout << "[RUNNING] Adapting active radiation shields...\n";
    for (size_t i = 0; i < samples.size(); ++i) {
        engine.AdaptShield(samples[i]);
        std::cout << "  Sample " << i << " opacity=" << samples[i].shield_opacity << "\n";
    }
    std::cout << "[SUCCESS] Melanogenesis shield adaptation complete.\n";
    return 0;
}
