# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/158/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/158/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rasl/ITMO_Projects/Rubik

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rasl/ITMO_Projects/Rubik/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/Rubik.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Rubik.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Rubik.dir/flags.make

CMakeFiles/Rubik.dir/main.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Rubik.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/main.cpp.o -c /home/rasl/ITMO_Projects/Rubik/main.cpp

CMakeFiles/Rubik.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/main.cpp > CMakeFiles/Rubik.dir/main.cpp.i

CMakeFiles/Rubik.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/main.cpp -o CMakeFiles/Rubik.dir/main.cpp.s

CMakeFiles/Rubik.dir/Cube/Side.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Side.cpp.o: ../Cube/Side.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Rubik.dir/Cube/Side.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Side.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Side.cpp

CMakeFiles/Rubik.dir/Cube/Side.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Side.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Side.cpp > CMakeFiles/Rubik.dir/Cube/Side.cpp.i

CMakeFiles/Rubik.dir/Cube/Side.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Side.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Side.cpp -o CMakeFiles/Rubik.dir/Cube/Side.cpp.s

CMakeFiles/Rubik.dir/Cube/Cube.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Cube.cpp.o: ../Cube/Cube.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Rubik.dir/Cube/Cube.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Cube.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Cube.cpp

CMakeFiles/Rubik.dir/Cube/Cube.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Cube.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Cube.cpp > CMakeFiles/Rubik.dir/Cube/Cube.cpp.i

CMakeFiles/Rubik.dir/Cube/Cube.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Cube.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Cube.cpp -o CMakeFiles/Rubik.dir/Cube/Cube.cpp.s

CMakeFiles/Rubik.dir/Random.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Random.cpp.o: ../Random.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Rubik.dir/Random.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Random.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Random.cpp

CMakeFiles/Rubik.dir/Random.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Random.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Random.cpp > CMakeFiles/Rubik.dir/Random.cpp.i

CMakeFiles/Rubik.dir/Random.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Random.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Random.cpp -o CMakeFiles/Rubik.dir/Random.cpp.s

CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.o: ../genetic_algorithm/genetic_algorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.o -c /home/rasl/ITMO_Projects/Rubik/genetic_algorithm/genetic_algorithm.cpp

CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/genetic_algorithm/genetic_algorithm.cpp > CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.i

CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/genetic_algorithm/genetic_algorithm.cpp -o CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.s

CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.o: ../Cube/Action/IAction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Action/IAction.cpp

CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Action/IAction.cpp > CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.i

CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Action/IAction.cpp -o CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.s

CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.o: ../Cube/Action/Move.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Action/Move.cpp

CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Action/Move.cpp > CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.i

CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Action/Move.cpp -o CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.s

CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.o: ../Cube/Action/Scramble.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Action/Scramble.cpp

CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Action/Scramble.cpp > CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.i

CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Action/Scramble.cpp -o CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.s

CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.o: ../Cube/Action/Rotate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Action/Rotate.cpp

CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Action/Rotate.cpp > CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.i

CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Action/Rotate.cpp -o CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.s

CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.o: ../Cube/Action/Skip.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Action/Skip.cpp

CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Action/Skip.cpp > CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.i

CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Action/Skip.cpp -o CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.s

CMakeFiles/Rubik.dir/Cube/Model3D.cpp.o: CMakeFiles/Rubik.dir/flags.make
CMakeFiles/Rubik.dir/Cube/Model3D.cpp.o: ../Cube/Model3D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Rubik.dir/Cube/Model3D.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rubik.dir/Cube/Model3D.cpp.o -c /home/rasl/ITMO_Projects/Rubik/Cube/Model3D.cpp

CMakeFiles/Rubik.dir/Cube/Model3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rubik.dir/Cube/Model3D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rasl/ITMO_Projects/Rubik/Cube/Model3D.cpp > CMakeFiles/Rubik.dir/Cube/Model3D.cpp.i

CMakeFiles/Rubik.dir/Cube/Model3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rubik.dir/Cube/Model3D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rasl/ITMO_Projects/Rubik/Cube/Model3D.cpp -o CMakeFiles/Rubik.dir/Cube/Model3D.cpp.s

# Object files for target Rubik
Rubik_OBJECTS = \
"CMakeFiles/Rubik.dir/main.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Side.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Cube.cpp.o" \
"CMakeFiles/Rubik.dir/Random.cpp.o" \
"CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.o" \
"CMakeFiles/Rubik.dir/Cube/Model3D.cpp.o"

# External object files for target Rubik
Rubik_EXTERNAL_OBJECTS =

Rubik: CMakeFiles/Rubik.dir/main.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Side.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Cube.cpp.o
Rubik: CMakeFiles/Rubik.dir/Random.cpp.o
Rubik: CMakeFiles/Rubik.dir/genetic_algorithm/genetic_algorithm.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Action/IAction.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Action/Move.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Action/Scramble.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Action/Rotate.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Action/Skip.cpp.o
Rubik: CMakeFiles/Rubik.dir/Cube/Model3D.cpp.o
Rubik: CMakeFiles/Rubik.dir/build.make
Rubik: CMakeFiles/Rubik.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable Rubik"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Rubik.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Rubik.dir/build: Rubik

.PHONY : CMakeFiles/Rubik.dir/build

CMakeFiles/Rubik.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Rubik.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Rubik.dir/clean

CMakeFiles/Rubik.dir/depend:
	cd /home/rasl/ITMO_Projects/Rubik/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rasl/ITMO_Projects/Rubik /home/rasl/ITMO_Projects/Rubik /home/rasl/ITMO_Projects/Rubik/cmake-build-release /home/rasl/ITMO_Projects/Rubik/cmake-build-release /home/rasl/ITMO_Projects/Rubik/cmake-build-release/CMakeFiles/Rubik.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Rubik.dir/depend

