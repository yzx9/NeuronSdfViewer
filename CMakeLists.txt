cmake_minimum_required (VERSION 3.15)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

# WORKAROUND
# This is added so that CMake can recognize the .ixx extension as a module interface.
set(CMAKE_CXX_SYSROOT_FLAG_CODE "list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS ixx)")

project(
    "neuron_sdf_viewer"
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${neuron_sdf_viewer_SOURCE_DIR}/bin)

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message("CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")

set(SOURCE_FILE

    # Neuron
    modules/neuron/NeuronScene.ixx
    modules/neuron/NeuronViewer.ixx
    modules/neuron/SwcLoader.ixx
    modules/neuron/SwcNode.ixx

    # Render
    modules/render/Camera.ixx
    modules/render/Intersect.ixx
    modules/render/Object.ixx
    modules/render/Ray.ixx
    modules/render/Render.ixx
    modules/render/Scene.ixx

    # Render.Accelerate
    modules/render/accelerate/Bound3.ixx
    modules/render/accelerate/Bound3Intersect.ixx
    modules/render/accelerate/BVH.ixx

    # Render.Camera
    modules/render/cameras/OrthographicCamera.ixx
    modules/render/cameras/PerspectiveCamera.ixx

    # Render.Object.Sdf
    modules/render/objects/SdfObject.ixx
    modules/render/objects/SdfCombinedObject.ixx
    modules/render/objects/SdfSphere.ixx
    modules/render/objects/SdfRoundCone.ixx

    # Utils
    modules/utils/debug.ixx
    modules/utils/partion.ixx
)

# Executable
add_executable(neuron_sdf_viewer src/main.cpp ${SOURCE_FILE})

# Only support statically linking for now.
target_compile_definitions(neuron_sdf_viewer PRIVATE
                            SEQUENTIAL_PROCESSING=0)

# Require c++20, this is better than setting CMAKE_CXX_STANDARD since it won't pollute other targets
# note : cxx_std_* features were added in CMake 3.8.2
target_compile_features(neuron_sdf_viewer PRIVATE cxx_std_20)

target_compile_options(neuron_sdf_viewer PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX /permissive- /Z7 /MT /MP /Bt+>)

set_target_properties(neuron_sdf_viewer PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)

# Eigen3
find_package (Eigen3 REQUIRED)
target_link_libraries(neuron_sdf_viewer Eigen3::Eigen)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(neuron_sdf_viewer ${OpenCV_LIBS})

# Threads
if(WIN32)
    set(CMAKE_USE_WIN32_THREADS_INIT ON)
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()
find_package(Threads REQUIRED)
target_link_libraries(neuron_sdf_viewer Threads::Threads)
