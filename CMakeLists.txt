cmake_minimum_required (VERSION 3.8)
project(neuron_sdf_viewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${neuron_sdf_viewer_SOURCE_DIR}/bin)
set(SOURCES
	# 3rd Libary
	lib/glad/src

	# source
	src/main.cpp
	src/Object.hpp
	src/Rasterizer.cpp src/Rasterizer.hpp
	src/Ray.cpp src/Ray.hpp
	src/Scene.cpp src/Scene.hpp
	src/Viewer.hpp src/Viewer.cpp
	src/SdfSphere.hpp src/SdfSphere.cpp)

# Executable
add_executable(main ${SOURCES})

# Glad
target_include_directories(main PUBLIC lib/glad/include)

# Eigen3
find_package (Eigen3 REQUIRED)
target_link_libraries(main Eigen3::Eigen)

# GLFW3
find_package(glfw3 REQUIRED)
target_link_libraries(main glfw)
