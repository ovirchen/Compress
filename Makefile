# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/olga/compress

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olga/compress

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/snap/clion/32/bin/cmake/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/olga/compress/CMakeFiles /home/olga/compress/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/olga/compress/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named compress

# Build rule for target.
compress: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 compress
.PHONY : compress

# fast build rule for target.
compress/fast:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/build
.PHONY : compress/fast

src/Server.o: src/Server.cpp.o

.PHONY : src/Server.o

# target to build an object file
src/Server.cpp.o:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/Server.cpp.o
.PHONY : src/Server.cpp.o

src/Server.i: src/Server.cpp.i

.PHONY : src/Server.i

# target to preprocess a source file
src/Server.cpp.i:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/Server.cpp.i
.PHONY : src/Server.cpp.i

src/Server.s: src/Server.cpp.s

.PHONY : src/Server.s

# target to generate assembly for a file
src/Server.cpp.s:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/Server.cpp.s
.PHONY : src/Server.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/response.o: src/response.cpp.o

.PHONY : src/response.o

# target to build an object file
src/response.cpp.o:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/response.cpp.o
.PHONY : src/response.cpp.o

src/response.i: src/response.cpp.i

.PHONY : src/response.i

# target to preprocess a source file
src/response.cpp.i:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/response.cpp.i
.PHONY : src/response.cpp.i

src/response.s: src/response.cpp.s

.PHONY : src/response.s

# target to generate assembly for a file
src/response.cpp.s:
	$(MAKE) -f CMakeFiles/compress.dir/build.make CMakeFiles/compress.dir/src/response.cpp.s
.PHONY : src/response.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... compress"
	@echo "... edit_cache"
	@echo "... src/Server.o"
	@echo "... src/Server.i"
	@echo "... src/Server.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/response.o"
	@echo "... src/response.i"
	@echo "... src/response.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

