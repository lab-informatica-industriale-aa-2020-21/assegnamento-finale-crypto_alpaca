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
include lib/transaction/CMakeFiles/transaction.dir/depend.make

# Include the progress variables for this target.
include lib/transaction/CMakeFiles/transaction.dir/progress.make

# Include the compile flags for this target's objects.
include lib/transaction/CMakeFiles/transaction.dir/flags.make

lib/transaction/CMakeFiles/transaction.dir/src/transaction.c.o: lib/transaction/CMakeFiles/transaction.dir/flags.make
lib/transaction/CMakeFiles/transaction.dir/src/transaction.c.o: ../lib/transaction/src/transaction.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/transaction/CMakeFiles/transaction.dir/src/transaction.c.o"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/transaction.dir/src/transaction.c.o -c /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/lib/transaction/src/transaction.c

lib/transaction/CMakeFiles/transaction.dir/src/transaction.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/transaction.dir/src/transaction.c.i"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/lib/transaction/src/transaction.c > CMakeFiles/transaction.dir/src/transaction.c.i

lib/transaction/CMakeFiles/transaction.dir/src/transaction.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/transaction.dir/src/transaction.c.s"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/lib/transaction/src/transaction.c -o CMakeFiles/transaction.dir/src/transaction.c.s

# Object files for target transaction
transaction_OBJECTS = \
"CMakeFiles/transaction.dir/src/transaction.c.o"

# External object files for target transaction
transaction_EXTERNAL_OBJECTS =

lib/transaction/libtransaction.a: lib/transaction/CMakeFiles/transaction.dir/src/transaction.c.o
lib/transaction/libtransaction.a: lib/transaction/CMakeFiles/transaction.dir/build.make
lib/transaction/libtransaction.a: lib/transaction/CMakeFiles/transaction.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libtransaction.a"
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction && $(CMAKE_COMMAND) -P CMakeFiles/transaction.dir/cmake_clean_target.cmake
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/transaction.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/transaction/CMakeFiles/transaction.dir/build: lib/transaction/libtransaction.a

.PHONY : lib/transaction/CMakeFiles/transaction.dir/build

lib/transaction/CMakeFiles/transaction.dir/clean:
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction && $(CMAKE_COMMAND) -P CMakeFiles/transaction.dir/cmake_clean.cmake
.PHONY : lib/transaction/CMakeFiles/transaction.dir/clean

lib/transaction/CMakeFiles/transaction.dir/depend:
	cd /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/lib/transaction /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction /home/alberto/lab_informatica/assegnamento-finale-crypto_alpaca/build/lib/transaction/CMakeFiles/transaction.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/transaction/CMakeFiles/transaction.dir/depend
