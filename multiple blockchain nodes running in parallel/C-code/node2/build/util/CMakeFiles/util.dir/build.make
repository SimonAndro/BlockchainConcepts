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
include util/CMakeFiles/util.dir/depend.make

# Include the progress variables for this target.
include util/CMakeFiles/util.dir/progress.make

# Include the compile flags for this target's objects.
include util/CMakeFiles/util.dir/flags.make

util/CMakeFiles/util.dir/src/util.c.obj: util/CMakeFiles/util.dir/flags.make
util/CMakeFiles/util.dir/src/util.c.obj: util/CMakeFiles/util.dir/includes_C.rsp
util/CMakeFiles/util.dir/src/util.c.obj: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/BTCmining_parallel_nodes/util/src/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object util/CMakeFiles/util.dir/src/util.c.obj"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/util.dir/src/util.c.obj -c "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/util/src/util.c"

util/CMakeFiles/util.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/util.dir/src/util.c.i"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/util/src/util.c" > CMakeFiles/util.dir/src/util.c.i

util/CMakeFiles/util.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/util.dir/src/util.c.s"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/util/src/util.c" -o CMakeFiles/util.dir/src/util.c.s

# Object files for target util
util_OBJECTS = \
"CMakeFiles/util.dir/src/util.c.obj"

# External object files for target util
util_EXTERNAL_OBJECTS =

F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libutil.dll: util/CMakeFiles/util.dir/src/util.c.obj
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libutil.dll: util/CMakeFiles/util.dir/build.make
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libutil.dll: util/CMakeFiles/util.dir/linklibs.rsp
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libutil.dll: util/CMakeFiles/util.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library \"F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/bin/libutil.dll\""
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" && "C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/util.dir/objects.a
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" && E:/msys64/mingw64/bin/ar.exe cr CMakeFiles/util.dir/objects.a @CMakeFiles/util.dir/objects1.rsp
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" && E:/msys64/mingw64/bin/cc.exe -shared -o "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/bin/libutil.dll" -Wl,--out-implib,libutil.dll.a -Wl,--major-image-version,0,--minor-image-version,0 -Wl,--whole-archive CMakeFiles/util.dir/objects.a -Wl,--no-whole-archive @CMakeFiles/util.dir/linklibs.rsp

# Rule to build all files generated by this target.
util/CMakeFiles/util.dir/build: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libutil.dll

.PHONY : util/CMakeFiles/util.dir/build

util/CMakeFiles/util.dir/clean:
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" && $(CMAKE_COMMAND) -P CMakeFiles/util.dir/cmake_clean.cmake
.PHONY : util/CMakeFiles/util.dir/clean

util/CMakeFiles/util.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/util" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/util/CMakeFiles/util.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : util/CMakeFiles/util.dir/depend

