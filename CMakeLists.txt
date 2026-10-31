cmake_minimum_required(VERSION 3.22)
project(ProjectSugroomEcosystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
include_directories(include)

# 16 Core Pathological Biomimicry Engine Targets (Configure add_executable for all 16 modules)
add_executable(sugroom_core_engine src/sugroom_core_engine.cpp)
# ... define remaining 15 executables and custom target dependencies ...
