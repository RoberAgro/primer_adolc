# Set CMake version
cmake_minimum_required(VERSION 3.14)

# Set project name
project(tapeless_vector)

# Set C++ standard
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11 standard

# Set path to header files directories (Adol-C, OpenCascade, etc)
include_directories("$ENV{ADOLC_INCLUDE}")

# Set path to executable directories (Adol-C, OpenCascade, etc)
link_directories("$ENV{ADOLC_LIB}")

# Add source files to compile to the project
add_executable(PROJECT_NAME tapeless_vector.cpp)

# Add external libraries (Adol-C, OpenCascade, etc)
target_link_libraries(PROJECT_NAME -ladolc)


