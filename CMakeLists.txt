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

# Hardware compute microcode targeted to unlock Nvidia Orin Tensor Cores
set(JETSON_COMPUTE_ARCH -arch=sm_87)

# =========================================================================
# UNIFIED ECOSYSTEM OBJECT BUILD PIPELINES (13 CORE PRODUCTION TARGETS)
# =========================================================================

# A. ORIGINAL SUGROOM BASELINE CORE MODULES
add_executable(sugroom_core_engine src/sugroom_core_engine.cpp)
target_compile_options(sugroom_core_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_nystagmus_engine src/project_nystagmus_engine.cpp)
target_link_libraries(project_nystagmus_engine PRIVATE ${GSTREAMER_LIBRARIES} cuda)

add_executable(project_myotonia_engine src/project_myotonia_engine.cpp)
target_compile_options(project_myotonia_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_hypermetria_engine src/project_hypermetria_engine.cpp)
target_compile_options(project_hypermetria_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_synesthesia_engine src/project_synesthesia_engine.cpp)
target_compile_options(project_synesthesia_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# B. CLINICAL PATHOLOGY & INFECTIOUS DISEASE SIMULATION ARCHITECTURES
add_executable(project_parkinson_engine src/project_parkinson_engine.cpp)
target_compile_options(project_parkinson_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_hemophilia_engine src/project_hemophilia_engine.cpp)
target_compile_options(project_hemophilia_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_tetanus_engine src/project_tetanus_engine.cpp)
target_compile_options(project_tetanus_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_phantom_limb_engine src/project_phantom_limb_engine.cpp)
target_compile_options(project_phantom_limb_engine PRIVATE ${JETSON_COMPUTE_ARCH})

# C. HIGH-VALUE ZOOLOGY ADAPTATION & DERMATOLOGICAL DEFENSE SYSTEMS
add_executable(project_laminitis_engine src/project_laminitis_engine.cpp)
target_compile_options(project_laminitis_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_ecdysis_engine src/project_ecdysis_engine.cpp)
target_compile_options(project_ecdysis_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_scab_engine src/project_scab_engine.cpp)
target_compile_options(project_scab_engine PRIVATE ${JETSON_COMPUTE_ARCH})

add_executable(project_melanogenesis_engine src/project_melanogenesis_engine.cpp)
target_compile_options(project_melanogenesis_engine PRIVATE ${JETSON_COMPUTE_ARCH})
