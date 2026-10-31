cmake_minimum_required(VERSION 3.22)
project(ProjectSugroomEcosystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(include)

# Define all 16 individual executables (sugroom_core_engine, compliance_sentinel, etc.)
# and aggregate them under the 'all_engines' custom target required for compilation.
add_executable(sugroom_core_engine src/sugroom_core_engine.cpp)
# ... [Includes definitions for all 16 engine executables]

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
