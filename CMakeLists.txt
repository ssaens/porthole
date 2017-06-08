cmake_minimum_required(VERSION 2.8)
project(porthole)

set(CMAKE_CXX_STANDARD 11)

#-------------------------------------------------------------------------------
# Find dependencies
#-------------------------------------------------------------------------------

# Required packages
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(OpenCV REQUIRED)

add_subdirectory(src)

set(CMAKE_INSTALL_PREFIX "${porthole_SOURCE_DIR}/")

