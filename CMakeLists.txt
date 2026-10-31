cmake_minimum_required(VERSION 3.22)
project(ProjectSugroomEcosystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Prefer the portable host-side headers
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# ---------------------------------------------------------------------------
# Portable CPU engines (root .cpp files). These do NOT require CUDA/TensorRT
# and are the ones that actually build in CI / Fly.io / laptops.
# ---------------------------------------------------------------------------
add_executable(sugroom_core_engine        sugroom_core_engine.cpp)
add_executable(compliance_sentinel        compliance_sentinel.cpp)
add_executable(project_nystagmus_engine   project_nystagmus_engine.cpp)
add_executable(project_myotonia_engine    project_myotonia_engine.cpp)
add_executable(project_hypermetria_engine project_hypermetria_engine.cpp)
add_executable(project_synesthesia_engine project_synesthesia_engine.cpp)
add_executable(project_parkinson_engine   project_parkinson_engine.cpp)
add_executable(project_hemophilia_engine  project_hemophilia_engine.cpp)
add_executable(project_tetanus_engine     project_tetanus_engine.cpp)
add_executable(project_phantom_limb_engine project_phantom_limb_engine.cpp)
add_executable(project_laminitis_engine   project_laminitis_engine.cpp)
add_executable(project_ecdysis_engine     project_ecdysis_engine.cpp)
add_executable(project_scab_engine        project_scab_engine.cpp)
add_executable(project_melanogenesis_engine project_melanogenesis_engine.cpp)
add_executable(project_malunion_engine    project_malunion_engine.cpp)
add_executable(project_homeostasis_engine project_homeostasis_engine.cpp)

# Aggregate target used by Dockerfile / CI
add_custom_target(all_engines DEPENDS
    sugroom_core_engine
    compliance_sentinel
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
)

# Smoke tests (ctest)
enable_testing()
foreach(eng
    sugroom_core_engine
    compliance_sentinel
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
)
  add_test(NAME run_${eng} COMMAND ${eng})
endforeach()
