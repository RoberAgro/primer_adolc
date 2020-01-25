# Set CMake version
cmake_minimum_required(VERSION 3.14)

# Set project name
project(demo_siso)

# Set path to header files directories
include_directories("$ENV{ADOLC_INCLUDE}")

# Set path to executable directories
link_directories("$ENV{ADOLC_LIB}")

# Add source files to compile to the project
add_executable(PROJECT_NAME main.cpp)

# Add external libraries
target_link_libraries(PROJECT_NAME -ladolc)
