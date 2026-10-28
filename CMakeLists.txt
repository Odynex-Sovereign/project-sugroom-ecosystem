cmake_minimum_required(VERSION 3.18)
project(SuGROOMEcosystem LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

# Identify system CUDA references automatically across host hardware maps
find_package(CUDA REQUIRED)

add_executable(sugroom_core_engine src/sugroom_core_engine.cpp)

# Optimize execution parameters specifically targeting Orin Core compute profiles
target_compile_options(sugroom_core_engine PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -arch=sm_87>)
