# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build

# Include any dependencies generated for this target.
include lib/hash/CMakeFiles/hash.dir/depend.make

# Include the progress variables for this target.
include lib/hash/CMakeFiles/hash.dir/progress.make

# Include the compile flags for this target's objects.
include lib/hash/CMakeFiles/hash.dir/flags.make

lib/hash/CMakeFiles/hash.dir/src/hash.c.o: lib/hash/CMakeFiles/hash.dir/flags.make
lib/hash/CMakeFiles/hash.dir/src/hash.c.o: ../lib/hash/src/hash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/hash/CMakeFiles/hash.dir/src/hash.c.o"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hash.dir/src/hash.c.o   -c /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/lib/hash/src/hash.c

lib/hash/CMakeFiles/hash.dir/src/hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hash.dir/src/hash.c.i"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/lib/hash/src/hash.c > CMakeFiles/hash.dir/src/hash.c.i

lib/hash/CMakeFiles/hash.dir/src/hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hash.dir/src/hash.c.s"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/lib/hash/src/hash.c -o CMakeFiles/hash.dir/src/hash.c.s

# Object files for target hash
hash_OBJECTS = \
"CMakeFiles/hash.dir/src/hash.c.o"

# External object files for target hash
hash_EXTERNAL_OBJECTS =

lib/hash/libhash.a: lib/hash/CMakeFiles/hash.dir/src/hash.c.o
lib/hash/libhash.a: lib/hash/CMakeFiles/hash.dir/build.make
lib/hash/libhash.a: lib/hash/CMakeFiles/hash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libhash.a"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash && $(CMAKE_COMMAND) -P CMakeFiles/hash.dir/cmake_clean_target.cmake
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/hash/CMakeFiles/hash.dir/build: lib/hash/libhash.a

.PHONY : lib/hash/CMakeFiles/hash.dir/build

lib/hash/CMakeFiles/hash.dir/clean:
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash && $(CMAKE_COMMAND) -P CMakeFiles/hash.dir/cmake_clean.cmake
.PHONY : lib/hash/CMakeFiles/hash.dir/clean

lib/hash/CMakeFiles/hash.dir/depend:
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/lib/hash /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/hash/CMakeFiles/hash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/hash/CMakeFiles/hash.dir/depend

