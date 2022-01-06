cmake_minimum_required (VERSION 3.8)
project(neuron_sdf_viewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O2 -Wall")
else()
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3 -Wall")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${neuron_sdf_viewer_SOURCE_DIR}/bin)

set(SOURCES
    src/main.cpp

    # neuron
    src/neuron/SwcNode.cpp      src/neuron/SwcNode.hpp
    src/neuron/SwcLoader.cpp    src/neuron/SwcLoader.hpp
    src/neuron/NeuronScene.cpp  src/neuron/NeuronScene.hpp
    src/neuron/NeuronViewer.cpp src/neuron/NeuronViewer.hpp

    # render
    src/render/Render.cpp       src/render/Render.hpp
    src/render/Ray.cpp          src/render/Ray.hpp
    src/render/Scene.cpp        src/render/Scene.hpp
    src/render/Intersect.hpp    src/render/Intersect.cpp
    
    # camera
    src/render/camera/Camera.cpp                src/render/camera/Camera.hpp
    src/render/camera/OrthographicCamera.cpp    src/render/camera/OrthographicCamera.hpp
    src/render/camera/PerspectiveCamera.cpp     src/render/camera/PerspectiveCamera.hpp

    # object
    src/render/object/Object.hpp
    src/render/object/SdfObject.cpp     src/render/object/SdfObject.hpp
    src/render/object/SdfSphere.cpp     src/render/object/SdfSphere.hpp
    src/render/object/SdfRoundCone.cpp  src/render/object/SdfRoundCone.hpp

    # accelerate
    src/render/accelerate/Bound3.hpp            src/render/accelerate/Bound3.cpp
    src/render/accelerate/Bound3Intersect.hpp   src/render/accelerate/Bound3Intersect.cpp
    src/render/accelerate/BVH.hpp               src/render/accelerate/BVH.cpp
)

# Executable
add_executable(NueronSdfViewer ${SOURCES})

# Eigen3
find_package (Eigen3 REQUIRED)
target_link_libraries(NueronSdfViewer Eigen3::Eigen)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(NueronSdfViewer ${OpenCV_LIBS})

# Threads
if(WIN32)
    set(CMAKE_USE_WIN32_THREADS_INIT ON)
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()
find_package(Threads REQUIRED)
target_link_libraries(NueronSdfViewer Threads::Threads)
