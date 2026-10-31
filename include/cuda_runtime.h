/**
 * Odynex Axis Logistics LLC — Project SuGROOM Ecosystem
 * Virtualized CUDA Runtime Emulation Stub Header
 * Prevents build-time compilation blocks on standard CPU environments.
 */

#ifndef CUDA_RUNTIME_H_EMULATION
#define CUDA_RUNTIME_H_EMULATION

#include <iostream>

// Standard CUDA platform abstraction type definitions
typedef int cudaError_t;
#define cudaSuccess 0

// Standard stream allocations
typedef struct CUstream_st* cudaStream_t;

// Structural mock definitions for memory management flags
enum cudaMemcpyKind {
    cudaMemcpyHostToDevice = 1,
    cudaMemcpyDeviceToHost = 2
};

// Inline emulation stubs to ensure seamless CPU execution fallbacks
inline cudaError_t cudaMalloc(void** devPtr, size_t size) {
    *devPtr = malloc(size);
    return cudaSuccess;
}

inline cudaError_t cudaFree(void* devPtr) {
    if (devPtr) free(devPtr);
    return cudaSuccess;
}

inline cudaError_t cudaMemcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind) {
    memcpy(dst, src, count);
    return cudaSuccess;
}

inline const char* cudaGetErrorString(cudaError_t error) {
    return "CUDA_SUCCESS_VIRTUAL_EMULATION";
}

#endif // CUDA_RUNTIME_H_EMULATION
