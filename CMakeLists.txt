cmake_minimum_required(VERSION 3.18)
project(OdynexPathologicalBiomimicryEcosystem LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

find_package(CUDA REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

include_directories(
    ${GSTREAMER_INCLUDE_DIRS}
    /opt/nvidia/deepstream/deepstream/sources/includes
)

# Optimize compilation architectures across the entire Jetson Orin Core footprint
set(JETSON_COMPUTE_ARCH -arch=sm_87)

# =========================================================================
# UNIFIED ECOSYSTEM EXECUTABLE TARGETS
# =========================================================================

# 1. Project SuGROOM Core Engine (Feline CH Compensation)
add_executable(sugroom_core_engine src/sugroom_core_engine.cpp)
target_compile_options(sugroom_core_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# 2. Project Nystagmus Engine (Visual Jitter DeepStream Stabilization)
add_executable(project_nystagmus_engine src/project_nystagmus_engine.cpp)
target_link_libraries(project_nystagmus_engine PRIVATE ${GSTREAMER_LIBRARIES} cuda)

# 3. Project Myotonia Engine (Adaptive Rigidity Lockdown)
add_executable(project_myotonia_engine src/project_myotonia_engine.cpp)
target_compile_options(project_myotonia_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# 4. Project Hypermetria Engine (Predictive Target Over-Shoot Damping)
add_executable(project_hypermetria_engine src/project_hypermetria_engine.cpp)
target_compile_options(project_hypermetria_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# 5. Project Synesthesia Engine (Cross-Modal Fallback Navigation)
add_executable(project_synesthesia_engine src/project_synesthesia_engine.cpp)
target_compile_options(project_synesthesia_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# 6. Project Parkinson Engine (Signal Dropout Resilience Layer)
add_executable(project_parkinson_engine src/project_parkinson_engine.cpp)
target_compile_options(project_parkinson_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# 7. Project Hemophilia Engine (Vascular Coagulation Leak Isolation)
add_executable(project_hemophilia_engine src/project_hemophilia_engine.cpp)
target_compile_options(project_hemophilia_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# 8. Project Tetanus Engine (Inhibitory Motor Current Dampening)
add_executable(project_tetanus_engine src/project_tetanus_engine.cpp)
target_compile_options(project_tetanus_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# 9. Project Phantom-Limb Engine (Kinematic Loss Trajectory Rebalancer)
add_executable(project_phantom_limb_engine src/project_phantom_limb_engine.cpp)
target_compile_options(project_phantom_limb_engine PRIVATE ${JETSON_COMPUTE_ARCH})
