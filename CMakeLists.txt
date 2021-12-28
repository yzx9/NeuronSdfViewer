cmake_minimum_required (VERSION 3.8)
project(neuron_sdf_viewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${neuron_sdf_viewer_SOURCE_DIR}/bin)
set(SOURCES
	# sources
	src/main.cpp
	src/Rasterizer.cpp src/Rasterizer.hpp
	src/Ray.cpp src/Ray.hpp
	src/Scene.cpp src/Scene.hpp
	src/Viewer.cpp src/Viewer.hpp
	src/object/Object.hpp
	src/object/SdfSphere.cpp src/object/SdfSphere.hpp
	src/object/SdfObject.cpp src/object/SdfObject.hpp
	src/swc/SwcLoader.hpp src/swc/SwcLoader.cpp)

# Executable
add_executable(main ${SOURCES})

# Eigen3
find_package (Eigen3 REQUIRED)
target_link_libraries(main Eigen3::Eigen)

# GLFW3
find_package(glfw3 REQUIRED)
target_link_libraries(main glfw)

# Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(main Vulkan::Vulkan)
