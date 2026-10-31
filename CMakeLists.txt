cmake_minimum_required(VERSION 3.22)
project(ProjectSugroomEcosystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
include_directories(include)

# Register all 16 source engines and the custom all_engines meta-target.
# Please reference the full CMakeLists.txt configuration script to add all add_executable and add_custom_target commands for the 16 engines.
