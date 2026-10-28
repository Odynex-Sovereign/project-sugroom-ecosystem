cmake_minimum_required(VERSION 3.18)
project(SuGROOMEcosystem LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

# Identify system CUDA references automatically across host hardware maps
find_package(CUDA REQUIRED)

add_executable(sugroom_core_engine src/sugroom_core_engine.cpp)

# Optimize execution parameters specifically targeting Orin Core compute profiles
target_compile_options(sugroom_core_engine PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -arch=sm_87>)
git add .
git commit -m "feat: integrate Project Nystagmus edge stabilization DeepStream pipeline"
git push origin main
# Add compilation targets for Project Myotonia's structural shock engine
add_executable(project_myotonia_engine src/project_myotonia_engine.cpp)

# Align GPU compiler profiles with optimized Jetson Orin streaming capabilities
target_compile_options(project_myotonia_engine PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -arch=sm_87>
)
