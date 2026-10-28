cmake_minimum_required(VERSION 3.14)
project(OdynexPathologicalBiomimicryEcosystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Host-side portable build (no CUDA / GStreamer / DeepStream required).
# Optional CUDA acceleration can be re-enabled later with -DENABLE_CUDA=ON.
option(ENABLE_CUDA "Build CUDA-accelerated kernels (requires NVIDIA toolchain)" OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(ENGINE_SOURCES
    src/sugroom_core_engine.cpp
    src/project_nystagmus_engine.cpp
    src/project_myotonia_engine.cpp
    src/project_hypermetria_engine.cpp
    src/project_synesthesia_engine.cpp
    src/project_parkinson_engine.cpp
    src/project_hemophilia_engine.cpp
    src/project_tetanus_engine.cpp
    src/project_phantom_limb_engine.cpp
    src/project_laminitis_engine.cpp
    src/project_ecdysis_engine.cpp
    src/project_scab_engine.cpp
    src/project_melanogenesis_engine.cpp
    src/project_malunion_engine.cpp
    src/project_homeostasis_engine.cpp
    src/compliance_sentinel.cpp
)

foreach(src ${ENGINE_SOURCES})
    get_filename_component(target_name ${src} NAME_WE)
    add_executable(${target_name} ${src})
    target_include_directories(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endforeach()

# Convenience meta-target: build everything
add_custom_target(all_engines DEPENDS
    sugroom_core_engine
    project_nystagmus_engine
    project_myotonia_engine
    project_hypermetria_engine
    project_synesthesia_engine
    project_parkinson_engine
    project_hemophilia_engine
    project_tetanus_engine
    project_phantom_limb_engine
    project_laminitis_engine
    project_ecdysis_engine
    project_scab_engine
    project_melanogenesis_engine
    project_malunion_engine
    project_homeostasis_engine
    compliance_sentinel
)

enable_testing()
foreach(src ${ENGINE_SOURCES})
    get_filename_component(target_name ${src} NAME_WE)
    add_test(NAME run_${target_name} COMMAND ${target_name})
endforeach()

message(STATUS "Odynex SuGROOM ecosystem configured (host/CPU mode). Targets: ${ENGINE_SOURCES}")
