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
include external/Unity/CMakeFiles/Unity.dir/depend.make

# Include the progress variables for this target.
include external/Unity/CMakeFiles/Unity.dir/progress.make

# Include the compile flags for this target's objects.
include external/Unity/CMakeFiles/Unity.dir/flags.make

external/Unity/CMakeFiles/Unity.dir/src/unity.c.o: external/Unity/CMakeFiles/Unity.dir/flags.make
external/Unity/CMakeFiles/Unity.dir/src/unity.c.o: ../external/Unity/src/unity.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/Unity/CMakeFiles/Unity.dir/src/unity.c.o"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Unity.dir/src/unity.c.o   -c /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/external/Unity/src/unity.c

external/Unity/CMakeFiles/Unity.dir/src/unity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Unity.dir/src/unity.c.i"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/external/Unity/src/unity.c > CMakeFiles/Unity.dir/src/unity.c.i

external/Unity/CMakeFiles/Unity.dir/src/unity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Unity.dir/src/unity.c.s"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/external/Unity/src/unity.c -o CMakeFiles/Unity.dir/src/unity.c.s

# Object files for target Unity
Unity_OBJECTS = \
"CMakeFiles/Unity.dir/src/unity.c.o"

# External object files for target Unity
Unity_EXTERNAL_OBJECTS =

external/Unity/libUnity.a: external/Unity/CMakeFiles/Unity.dir/src/unity.c.o
external/Unity/libUnity.a: external/Unity/CMakeFiles/Unity.dir/build.make
external/Unity/libUnity.a: external/Unity/CMakeFiles/Unity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libUnity.a"
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity && $(CMAKE_COMMAND) -P CMakeFiles/Unity.dir/cmake_clean_target.cmake
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Unity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/Unity/CMakeFiles/Unity.dir/build: external/Unity/libUnity.a

.PHONY : external/Unity/CMakeFiles/Unity.dir/build

external/Unity/CMakeFiles/Unity.dir/clean:
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity && $(CMAKE_COMMAND) -P CMakeFiles/Unity.dir/cmake_clean.cmake
.PHONY : external/Unity/CMakeFiles/Unity.dir/clean

external/Unity/CMakeFiles/Unity.dir/depend:
	cd /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/external/Unity /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity /home/emanuelezanoni/lab_informatica/assegnamento-finale-crypto_alpaca/build/external/Unity/CMakeFiles/Unity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/Unity/CMakeFiles/Unity.dir/depend

