#include <iostream>
#include <vector>
#include <cuda_runtime.h>

struct ContactPadTelemetry {
    float static_friction_coefficient;
    float micro_slip_velocity;
    float normal_clamping_force;
};

struct OptimizedGripCommand {
    float adjusted_clamping_pressure;
    float target_contact_angle_degrees;
};

// CUDA Kernel to optimize tactile contact matrices (Emulating Gecko mechanical adaptation during skin shedding phases)
__global__ void TactileFrictionCompensationKernel(const ContactPadTelemetry* pads,
                                                   OptimizedGripCommand* commands,
                                                   int configuration_nodes) {
    int idx = blockIdx.x * blockIdx.y + threadIdx.x;
    if (idx < configuration_nodes) {
        ContactPadTelemetry current_pad = pads[idx];
        
        if (current_pad.micro_slip_velocity > 0.02f || current_pad.static_friction_coefficient < 0.25f) {
            // High slippage risk detected: Instantly scale clamping force and roll angle inward to lock hold
            commands[idx].adjusted_clamping_pressure = current_pad.normal_clamping_force * 2.45f;
            commands[idx].target_contact_angle_degrees = 14.5f; // Structural wedge angle change
        } else {
            // Normal operating friction window
            commands[idx].adjusted_clamping_pressure = current_pad.normal_clamping_force;
            commands[idx].target_contact_angle_degrees = 0.0f;
        }
    }
}

class EcdysisEngine {
private:
    cudaStream_t grip_stream;

public:
    EcdysisEngine() {
        cudaStreamCreate(&grip_stream);
        std::cout << "[INIT] Project Gecko-Ecdysis Tactile Adhesion Engine Initialized." << std::endl;
    }

    void OptimizeClawHold(const std::vector<ContactPadTelemetry>& inputs, std::vector<OptimizedGripCommand>& outputs) {
        int count = inputs.size();
        ContactPadTelemetry* d_in;
        OptimizedGripCommand* d_out;

        cudaMalloc(&d_in, count * sizeof(ContactPadTelemetry));
        cudaMalloc(&d_out, count * sizeof(OptimizedGripCommand));

        cudaMemcpyAsync(d_in, inputs.data(), count * sizeof(ContactPadTelemetry), cudaMemcpyHostToDevice, grip_stream);

        int threads = 32;
        int blocks = (count + threads - 1) / threads;

        TactileFrictionCompensationKernel<<<blocks, threads, 0, grip_stream>>>(d_in, d_out, count);

        cudaMemcpyAsync(outputs.data(), d_out, count * sizeof(OptimizedGripCommand), cudaMemcpyDeviceToHost, grip_stream);
        cudaStreamSynchronize(grip_stream);

        cudaFree(d_in);
        cudaFree(d_out);
    }

    ~EcdysisEngine() {
        cudaStreamDestroy(grip_stream);
    }
};

int main() {
    EcdysisEngine engine;
    // Pad 1 slips while grabbing smooth or oily surface layers
    std::vector<ContactPadTelemetry> claw_pads = {
        {0.65f, 0.00f, 15.0f}, {0.12f, 0.45f, 15.0f}, {0.62f, 0.00f, 15.0f}
    };
    std::vector<OptimizedGripCommand> commands(3);

    std::cout << "[RUNNING] Sampling tactile claw surface tension matrix..." << std::endl;
    engine.OptimizeClawHold(claw_pads, commands);

    for (size_t i = 0; i < commands.size(); ++i) {
        std::cout << "[TACTILE NODE " << i << "] Assigned Clamping Pressure: " << commands[i].adjusted_clamping_pressure << " N";
        if (commands[i].target_contact_angle_degrees > 0.0f) {
            std::cout << " <-- [SLIP WARNING: CONTACT ANGLE COMPENSATED TO " << commands[i].target_contact_angle_degrees << "°]";
        }
        std::cout << std::endl;
    }
    return 0;
}
