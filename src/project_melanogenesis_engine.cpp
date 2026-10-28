#include <iostream>
#include <vector>
#include <cuda_runtime.h>

struct RadiationSensorNode {
    float ultra_violet_index;   // UV Index rating (0.0 to 15.0+)
    float structural_core_temp; // Measured in Celsius (°C)
    int array_channel_id;
};

struct ShieldingActuatorOutput {
    float optoelectronic_attenuation_db; // Filter density scaling factor
    int thermal_cooling_relay_state;     // 1 = Active cooling loop engagement
};

// CUDA Kernel implementing active structural shielding (Emulating skin layer Melanogenesis protection arrays)
__global__ void MelanocyteRadiationShieldKernel(const RadiationSensorNode* arrays,
                                                 ShieldingActuatorOutput* controls,
                                                 float critical_temp_ceiling,
                                                 int sensor_nodes) {
    int idx = blockIdx.x * blockIdx.y + threadIdx.x;
    if (idx < sensor_nodes) {
        RadiationSensorNode sensor = arrays[idx];
        
        if (sensor.ultra_violet_index > 10.0f || sensor.structural_core_temp > critical_temp_ceiling) {
            // Apply aggressive optical filtering and activate internal fluid circulation systems
            controls[idx].optoelectronic_attenuation_db = sensor.ultra_violet_index * 4.2f;
            controls[idx].thermal_cooling_relay_state = 1;
        } else {
            controls[idx].optoelectronic_attenuation_db = 0.0f;
            controls[idx].thermal_cooling_relay_state = 0;
        }
    }
}

class MelanogenesisEngine {
private:
    cudaStream_t thermal_stream;

public:
    MelanogenesisEngine() {
        cudaStreamCreate(&thermal_stream);
        std::cout << "[INIT] Project Melanogenesis Environmental Shielding Loop Operational." << std::endl;
    }

    void ExecuteRadiationMitigation(const std::vector<RadiationSensorNode>& matrix, std::vector<ShieldingActuatorOutput>& routing) {
        int nodes = matrix.size();
        RadiationSensorNode* d_mat;
        ShieldingActuatorOutput* d_rot;

        cudaMalloc(&d_mat, nodes * sizeof(RadiationSensorNode));
        cudaMalloc(&d_rot, nodes * sizeof(ShieldingActuatorOutput));

        cudaMemcpyAsync(d_mat, matrix.data(), nodes * sizeof(RadiationSensorNode), cudaMemcpyHostToDevice, thermal_stream);

        int threads = 32;
        int blocks = (nodes + threads - 1) / threads;

        MelanocyteRadiationShieldKernel<<<blocks, threads, 0, thermal_stream>>>(d_mat, d_rot, 65.0f, nodes);

        cudaMemcpyAsync(routing.data(), d_rot, nodes * sizeof(ShieldingActuatorOutput), cudaMemcpyDeviceToHost, thermal_stream);
        cudaStreamSynchronize(thermal_stream);

        cudaFree(d_mat);
        cudaFree(d_rot);
    }

    ~MelanogenesisEngine() {
        cudaStreamDestroy(thermal_stream);
    }
};

int main() {
    MelanogenesisEngine engine;
    // Node 0 under clear intense high-altitude sunlight exposure parameters
    std::vector<RadiationSensorNode> array_nodes = {
        {12.4f, 72.5f, 0}, {2.1f, 32.0f, 1}, {1.8f, 30.5f, 2}
    };
    std::vector<ShieldingActuatorOutput> controllers(3);

    std::cout << "[RUNNING] Sampling environmental solar radiation sensor networks..." << std::endl;
    engine.ExecuteRadiationMitigation(array_nodes, controllers);

    for (size_t i = 0; i < controllers.size(); ++i) {
        std::cout << "[CHASSIS PLANE " << i << "] Lens Attenuation Command: " << controllers[i].optoelectronic_attenuation_db << " dB";
        if (controllers[i].thermal_cooling_relay_state) {
            std::cout << " <-- [RADIATION INDEX CEILING BREACHED: INTERNAL FLUID THERMAL RELAYS ON]";
        }
        std::cout << std::endl;
    }
    return 0;
}
