# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build

# Include any dependencies generated for this target.
include test/test_block/CMakeFiles/block_app_test.dir/depend.make

# Include the progress variables for this target.
include test/test_block/CMakeFiles/block_app_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/test_block/CMakeFiles/block_app_test.dir/flags.make

test/test_block/CMakeFiles/block_app_test.dir/src/test_block.c.o: test/test_block/CMakeFiles/block_app_test.dir/flags.make
test/test_block/CMakeFiles/block_app_test.dir/src/test_block.c.o: ../test/test_block/src/test_block.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/test_block/CMakeFiles/block_app_test.dir/src/test_block.c.o"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/test/test_block && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/block_app_test.dir/src/test_block.c.o -c /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/test/test_block/src/test_block.c

test/test_block/CMakeFiles/block_app_test.dir/src/test_block.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/block_app_test.dir/src/test_block.c.i"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/test/test_block && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/test/test_block/src/test_block.c > CMakeFiles/block_app_test.dir/src/test_block.c.i

test/test_block/CMakeFiles/block_app_test.dir/src/test_block.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/block_app_test.dir/src/test_block.c.s"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/test/test_block && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/test/test_block/src/test_block.c -o CMakeFiles/block_app_test.dir/src/test_block.c.s

# Object files for target block_app_test
block_app_test_OBJECTS = \
"CMakeFiles/block_app_test.dir/src/test_block.c.o"

# External object files for target block_app_test
block_app_test_EXTERNAL_OBJECTS =

test/test_block/block_app_test: test/test_block/CMakeFiles/block_app_test.dir/src/test_block.c.o
test/test_block/block_app_test: test/test_block/CMakeFiles/block_app_test.dir/build.make
test/test_block/block_app_test: lib/block/libblock.a
test/test_block/block_app_test: external/Unity/libUnity.a
test/test_block/block_app_test: lib/transaction/libtransaction.a
test/test_block/block_app_test: lib/hash/libhash.a
test/test_block/block_app_test: test/test_block/CMakeFiles/block_app_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable block_app_test"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/test/test_block && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/block_app_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/test_block/CMakeFiles/block_app_test.dir/build: test/test_block/block_app_test

.PHONY : test/test_block/CMakeFiles/block_app_test.dir/build

test/test_block/CMakeFiles/block_app_test.dir/clean:
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/test/test_block && $(CMAKE_COMMAND) -P CMakeFiles/block_app_test.dir/cmake_clean.cmake
.PHONY : test/test_block/CMakeFiles/block_app_test.dir/clean

test/test_block/CMakeFiles/block_app_test.dir/depend:
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/test/test_block /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/test/test_block /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/test/test_block/CMakeFiles/block_app_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/test_block/CMakeFiles/block_app_test.dir/depend

