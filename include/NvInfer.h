/**
 * Odynex Axis Logistics LLC — Project SuGROOM Ecosystem
 * Virtualized NVIDIA TensorRT (NvInfer) Emulation Stub Header
 * Allows compilation of physical AI loops on non-CUDA architectures.
 */

#ifndef NV_INFER_H_EMULATION
#define NV_INFER_H_EMULATION

#include <iostream>
#include <memory>
#include <string>

namespace nvinfer1 {

class ILogger {
public:
    enum class Severity : int {
        kINTERNAL_ERROR = 0,
        kERROR = 1,
        kWARNING = 2,
        kINFO = 3,
        kVERBOSE = 4
    };
    virtual void log(Severity severity, const char* msg) noexcept = 0;
    virtual ~ILogger() = default;
};

class IExecutionContext {
public:
    virtual bool enqueueV2(void** buffers, void* stream, void** inputTensorAddress) noexcept {
        return true;
    }
    virtual ~IExecutionContext() = default;
};

class ICudaEngine {
public:
    virtual IExecutionContext* createExecutionContext() noexcept {
        return new IExecutionContext();
    }
    virtual ~ICudaEngine() = default;
};

class IRuntime {
public:
    virtual ICudaEngine* deserializeCudaEngine(const void* blob, size_t size) noexcept {
        return new ICudaEngine();
    }
    virtual ~IRuntime() = default;
};

inline IRuntime* createInferRuntime(ILogger& logger) noexcept {
    return new IRuntime();
}

} // namespace nvinfer1

#endif // NV_INFER_H_EMULATION
