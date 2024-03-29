# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/kasper/prg/fun/fluidsim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kasper/prg/fun/fluidsim

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kasper/prg/fun/fluidsim/CMakeFiles /home/kasper/prg/fun/fluidsim/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kasper/prg/fun/fluidsim/CMakeFiles 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Fluid

# Build rule for target.
Fluid: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Fluid
.PHONY : Fluid

# fast build rule for target.
Fluid/fast:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/build
.PHONY : Fluid/fast

# target to build an object file
src/framebuffer.o:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/framebuffer.o
.PHONY : src/framebuffer.o

# target to preprocess a source file
src/framebuffer.i:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/framebuffer.i
.PHONY : src/framebuffer.i

# target to generate assembly for a file
src/framebuffer.s:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/framebuffer.s
.PHONY : src/framebuffer.s

# target to build an object file
src/loadshaders.o:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/loadshaders.o
.PHONY : src/loadshaders.o

# target to preprocess a source file
src/loadshaders.i:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/loadshaders.i
.PHONY : src/loadshaders.i

# target to generate assembly for a file
src/loadshaders.s:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/loadshaders.s
.PHONY : src/loadshaders.s

# target to build an object file
src/main.o:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/main.o
.PHONY : src/main.o

# target to preprocess a source file
src/main.i:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/main.i
.PHONY : src/main.i

# target to generate assembly for a file
src/main.s:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/main.s
.PHONY : src/main.s

# target to build an object file
src/simulator.o:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/simulator.o
.PHONY : src/simulator.o

# target to preprocess a source file
src/simulator.i:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/simulator.i
.PHONY : src/simulator.i

# target to generate assembly for a file
src/simulator.s:
	$(MAKE) -f CMakeFiles/Fluid.dir/build.make CMakeFiles/Fluid.dir/src/simulator.s
.PHONY : src/simulator.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... Fluid"
	@echo "... src/framebuffer.o"
	@echo "... src/framebuffer.i"
	@echo "... src/framebuffer.s"
	@echo "... src/loadshaders.o"
	@echo "... src/loadshaders.i"
	@echo "... src/loadshaders.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/simulator.o"
	@echo "... src/simulator.i"
	@echo "... src/simulator.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

