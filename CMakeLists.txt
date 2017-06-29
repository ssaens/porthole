cmake_minimum_required(VERSION 2.8)
project(porthole)

set(CMAKE_CXX_STANDARD 11)

#-------------------------------------------------------------------------------
# Find dependencies
#-------------------------------------------------------------------------------

# Required packages
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(OpenCV REQUIRED)

add_subdirectory(deps/glew)
set_property(TARGET glew APPEND_STRING PROPERTY COMPILE_FLAGS -w)

add_subdirectory(deps/glfw)
set_property(TARGET glfw APPEND_STRING PROPERTY COMPILE_FLAGS -w)

include_directories(
        deps/include
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)

link_directories(
        ${GLEW_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
)


add_subdirectory(src)

set(CMAKE_INSTALL_PREFIX "${porthole_SOURCE_DIR}/")

