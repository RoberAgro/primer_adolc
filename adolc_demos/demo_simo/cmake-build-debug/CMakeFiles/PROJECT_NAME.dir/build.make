# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/robertoa/my_software/jet_brains/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/robertoa/my_software/jet_brains/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PROJECT_NAME.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PROJECT_NAME.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PROJECT_NAME.dir/flags.make

CMakeFiles/PROJECT_NAME.dir/main.cpp.o: CMakeFiles/PROJECT_NAME.dir/flags.make
CMakeFiles/PROJECT_NAME.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PROJECT_NAME.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PROJECT_NAME.dir/main.cpp.o -c /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/main.cpp

CMakeFiles/PROJECT_NAME.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROJECT_NAME.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/main.cpp > CMakeFiles/PROJECT_NAME.dir/main.cpp.i

CMakeFiles/PROJECT_NAME.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROJECT_NAME.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/main.cpp -o CMakeFiles/PROJECT_NAME.dir/main.cpp.s

# Object files for target PROJECT_NAME
PROJECT_NAME_OBJECTS = \
"CMakeFiles/PROJECT_NAME.dir/main.cpp.o"

# External object files for target PROJECT_NAME
PROJECT_NAME_EXTERNAL_OBJECTS =

PROJECT_NAME: CMakeFiles/PROJECT_NAME.dir/main.cpp.o
PROJECT_NAME: CMakeFiles/PROJECT_NAME.dir/build.make
PROJECT_NAME: CMakeFiles/PROJECT_NAME.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PROJECT_NAME"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PROJECT_NAME.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PROJECT_NAME.dir/build: PROJECT_NAME

.PHONY : CMakeFiles/PROJECT_NAME.dir/build

CMakeFiles/PROJECT_NAME.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PROJECT_NAME.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PROJECT_NAME.dir/clean

CMakeFiles/PROJECT_NAME.dir/depend:
	cd /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/cmake-build-debug /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/cmake-build-debug /home/robertoa/my_GIT/primer_adolc/adolc_demos/demo_simo/cmake-build-debug/CMakeFiles/PROJECT_NAME.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PROJECT_NAME.dir/depend

