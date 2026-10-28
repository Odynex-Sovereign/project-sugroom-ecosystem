cmake_minimum_required(VERSION 3.18)
project(OdynexPathologicalBiomimicryEcosystem LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

# Identify required hardware rendering toolchains and platform libraries
find_package(CUDA REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

include_directories(
    ${GSTREAMER_INCLUDE_DIRS}
    /opt/nvidia/deepstream/deepstream/sources/includes
)

# =========================================================================
# ECOSYSTEM COMPILATION OBJECT TARGETS
# =========================================================================

# 1. Core SuGROOM Inverse-Tremor Engine
add_executable(sugroom_core_engine src/sugroom_core_engine.cpp)
target_compile_options(sugroom_core_engine PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -arch=sm_87>)

# 2. Project Nystagmus Visual Jitter DeepStream Stabilization pipeline
add_executable(project_nystagmus_engine src/project_nystagmus_engine.cpp)
target_link_libraries(project_nystagmus_engine PRIVATE ${GSTREAMER_LIBRARIES} cuda)

# 3. Project Myotonia Adaptive Shock Lockdown Engine
add_executable(project_myotonia_engine src/project_myotonia_engine.cpp)
target_compile_options(project_myotonia_engine PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -arch=sm_87>)

# 4. Project Hypermetria Predictive Actuator Braking Engine
add_executable(project_hypermetria_engine src/project_hypermetria_engine.cpp)
target_compile_options(project_hypermetria_engine PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -arch=sm_87>)

# 5. Project Synesthesia Cross-Modal Fallback Navigation Engine
add_executable(project_synesthesia_engine src/project_synesthesia_engine.cpp)
target_compile_options(project_synesthesia_engine PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -arch=sm_87>)
