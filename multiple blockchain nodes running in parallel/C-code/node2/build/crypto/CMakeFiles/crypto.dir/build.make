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
include crypto/CMakeFiles/crypto.dir/depend.make

# Include the progress variables for this target.
include crypto/CMakeFiles/crypto.dir/progress.make

# Include the compile flags for this target's objects.
include crypto/CMakeFiles/crypto.dir/flags.make

crypto/CMakeFiles/crypto.dir/hash.c.obj: crypto/CMakeFiles/crypto.dir/flags.make
crypto/CMakeFiles/crypto.dir/hash.c.obj: crypto/CMakeFiles/crypto.dir/includes_C.rsp
crypto/CMakeFiles/crypto.dir/hash.c.obj: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/BTCmining_parallel_nodes/crypto/hash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object crypto/CMakeFiles/crypto.dir/hash.c.obj"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/crypto.dir/hash.c.obj -c "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/hash.c"

crypto/CMakeFiles/crypto.dir/hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crypto.dir/hash.c.i"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/hash.c" > CMakeFiles/crypto.dir/hash.c.i

crypto/CMakeFiles/crypto.dir/hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crypto.dir/hash.c.s"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/hash.c" -o CMakeFiles/crypto.dir/hash.c.s

crypto/CMakeFiles/crypto.dir/blake3_dispatch.c.obj: crypto/CMakeFiles/crypto.dir/flags.make
crypto/CMakeFiles/crypto.dir/blake3_dispatch.c.obj: crypto/CMakeFiles/crypto.dir/includes_C.rsp
crypto/CMakeFiles/crypto.dir/blake3_dispatch.c.obj: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_dispatch.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object crypto/CMakeFiles/crypto.dir/blake3_dispatch.c.obj"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/crypto.dir/blake3_dispatch.c.obj -c "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_dispatch.c"

crypto/CMakeFiles/crypto.dir/blake3_dispatch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crypto.dir/blake3_dispatch.c.i"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_dispatch.c" > CMakeFiles/crypto.dir/blake3_dispatch.c.i

crypto/CMakeFiles/crypto.dir/blake3_dispatch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crypto.dir/blake3_dispatch.c.s"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_dispatch.c" -o CMakeFiles/crypto.dir/blake3_dispatch.c.s

crypto/CMakeFiles/crypto.dir/blake3_portable.c.obj: crypto/CMakeFiles/crypto.dir/flags.make
crypto/CMakeFiles/crypto.dir/blake3_portable.c.obj: crypto/CMakeFiles/crypto.dir/includes_C.rsp
crypto/CMakeFiles/crypto.dir/blake3_portable.c.obj: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_portable.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object crypto/CMakeFiles/crypto.dir/blake3_portable.c.obj"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/crypto.dir/blake3_portable.c.obj -c "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_portable.c"

crypto/CMakeFiles/crypto.dir/blake3_portable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crypto.dir/blake3_portable.c.i"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_portable.c" > CMakeFiles/crypto.dir/blake3_portable.c.i

crypto/CMakeFiles/crypto.dir/blake3_portable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crypto.dir/blake3_portable.c.s"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/blake3_portable.c" -o CMakeFiles/crypto.dir/blake3_portable.c.s

crypto/CMakeFiles/crypto.dir/memzero.c.obj: crypto/CMakeFiles/crypto.dir/flags.make
crypto/CMakeFiles/crypto.dir/memzero.c.obj: crypto/CMakeFiles/crypto.dir/includes_C.rsp
crypto/CMakeFiles/crypto.dir/memzero.c.obj: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/BTCmining_parallel_nodes/crypto/memzero.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object crypto/CMakeFiles/crypto.dir/memzero.c.obj"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/crypto.dir/memzero.c.obj -c "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/memzero.c"

crypto/CMakeFiles/crypto.dir/memzero.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crypto.dir/memzero.c.i"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/memzero.c" > CMakeFiles/crypto.dir/memzero.c.i

crypto/CMakeFiles/crypto.dir/memzero.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crypto.dir/memzero.c.s"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/memzero.c" -o CMakeFiles/crypto.dir/memzero.c.s

crypto/CMakeFiles/crypto.dir/ripemd160.c.obj: crypto/CMakeFiles/crypto.dir/flags.make
crypto/CMakeFiles/crypto.dir/ripemd160.c.obj: crypto/CMakeFiles/crypto.dir/includes_C.rsp
crypto/CMakeFiles/crypto.dir/ripemd160.c.obj: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/BTCmining_parallel_nodes/crypto/ripemd160.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object crypto/CMakeFiles/crypto.dir/ripemd160.c.obj"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/crypto.dir/ripemd160.c.obj -c "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/ripemd160.c"

crypto/CMakeFiles/crypto.dir/ripemd160.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crypto.dir/ripemd160.c.i"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/ripemd160.c" > CMakeFiles/crypto.dir/ripemd160.c.i

crypto/CMakeFiles/crypto.dir/ripemd160.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crypto.dir/ripemd160.c.s"
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto/ripemd160.c" -o CMakeFiles/crypto.dir/ripemd160.c.s

# Object files for target crypto
crypto_OBJECTS = \
"CMakeFiles/crypto.dir/hash.c.obj" \
"CMakeFiles/crypto.dir/blake3_dispatch.c.obj" \
"CMakeFiles/crypto.dir/blake3_portable.c.obj" \
"CMakeFiles/crypto.dir/memzero.c.obj" \
"CMakeFiles/crypto.dir/ripemd160.c.obj"

# External object files for target crypto
crypto_EXTERNAL_OBJECTS =

F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/hash.c.obj
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/blake3_dispatch.c.obj
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/blake3_portable.c.obj
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/memzero.c.obj
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/ripemd160.c.obj
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/build.make
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/linklibs.rsp
F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll: crypto/CMakeFiles/crypto.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C shared library \"F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/bin/libcrypto.dll\""
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && "C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/crypto.dir/objects.a
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/ar.exe cr CMakeFiles/crypto.dir/objects.a @CMakeFiles/crypto.dir/objects1.rsp
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && E:/msys64/mingw64/bin/cc.exe -shared -o "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/bin/libcrypto.dll" -Wl,--out-implib,libcrypto.dll.a -Wl,--major-image-version,0,--minor-image-version,0 -Wl,--whole-archive CMakeFiles/crypto.dir/objects.a -Wl,--no-whole-archive @CMakeFiles/crypto.dir/linklibs.rsp

# Rule to build all files generated by this target.
crypto/CMakeFiles/crypto.dir/build: F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple\ blockchain\ nodes\ running\ in\ parallel/C-code/node2/bin/libcrypto.dll

.PHONY : crypto/CMakeFiles/crypto.dir/build

crypto/CMakeFiles/crypto.dir/clean:
	cd "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" && $(CMAKE_COMMAND) -P CMakeFiles/crypto.dir/cmake_clean.cmake
.PHONY : crypto/CMakeFiles/crypto.dir/clean

crypto/CMakeFiles/crypto.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/BTCmining_parallel_nodes/crypto" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto" "F:/C-projects/Blockchain/BlockchainConcepts-repo/multiple blockchain nodes running in parallel/C-code/node2/build/crypto/CMakeFiles/crypto.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : crypto/CMakeFiles/crypto.dir/depend

