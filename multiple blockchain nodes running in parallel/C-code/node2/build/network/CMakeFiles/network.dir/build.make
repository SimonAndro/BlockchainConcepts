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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build"

# Include any dependencies generated for this target.
include network/CMakeFiles/network.dir/depend.make

# Include the progress variables for this target.
include network/CMakeFiles/network.dir/progress.make

# Include the compile flags for this target's objects.
include network/CMakeFiles/network.dir/flags.make

network/CMakeFiles/network.dir/src/network.c.obj: network/CMakeFiles/network.dir/flags.make
network/CMakeFiles/network.dir/src/network.c.obj: network/CMakeFiles/network.dir/includes_C.rsp
network/CMakeFiles/network.dir/src/network.c.obj: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/BTCmining_parallel_nodes/network/src/network.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object network/CMakeFiles/network.dir/src/network.c.obj"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/network.dir/src/network.c.obj -c "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/network/src/network.c"

network/CMakeFiles/network.dir/src/network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/network.dir/src/network.c.i"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/network/src/network.c" > CMakeFiles/network.dir/src/network.c.i

network/CMakeFiles/network.dir/src/network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/network.dir/src/network.c.s"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/network/src/network.c" -o CMakeFiles/network.dir/src/network.c.s

# Object files for target network
network_OBJECTS = \
"CMakeFiles/network.dir/src/network.c.obj"

# External object files for target network
network_EXTERNAL_OBJECTS =

network/libnetwork.a: network/CMakeFiles/network.dir/src/network.c.obj
network/libnetwork.a: network/CMakeFiles/network.dir/build.make
network/libnetwork.a: network/CMakeFiles/network.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libnetwork.a"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network" && $(CMAKE_COMMAND) -P CMakeFiles/network.dir/cmake_clean_target.cmake
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/network.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
network/CMakeFiles/network.dir/build: network/libnetwork.a

.PHONY : network/CMakeFiles/network.dir/build

network/CMakeFiles/network.dir/clean:
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network" && $(CMAKE_COMMAND) -P CMakeFiles/network.dir/cmake_clean.cmake
.PHONY : network/CMakeFiles/network.dir/clean

network/CMakeFiles/network.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/network" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/network/CMakeFiles/network.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : network/CMakeFiles/network.dir/depend

