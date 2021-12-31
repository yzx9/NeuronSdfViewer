cmake_minimum_required (VERSION 3.8)
project(neuron_sdf_viewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${neuron_sdf_viewer_SOURCE_DIR}/bin)
set(SOURCES
    src/main.cpp

    # neuron
    src/neuron/SwcLoader.cpp    src/neuron/SwcLoader.hpp
    src/neuron/NeuronScene.cpp  src/neuron/NeuronScene.hpp

    # render
    src/render/Render.cpp       src/render/Render.hpp
    src/render/Ray.cpp          src/render/Ray.hpp
    src/render/Scene.cpp        src/render/Scene.hpp
    
    # camera
    src/render/camera/Camera.hpp
    src/render/camera/OrthographicCamera.cpp   src/render/camera/OrthographicCamera.hpp

    # object
    src/render/object/Object.hpp
    src/render/object/SdfSphere.cpp    src/render/object/SdfSphere.hpp
    src/render/object/SdfObject.cpp    src/render/object/SdfObject.hpp
)

# Executable
add_executable(main ${SOURCES})

# Eigen3
find_package (Eigen3 REQUIRED)
target_link_libraries(main Eigen3::Eigen)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})
