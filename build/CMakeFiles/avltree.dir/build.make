# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build

# Include any dependencies generated for this target.
include CMakeFiles/avltree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/avltree.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/avltree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/avltree.dir/flags.make

CMakeFiles/avltree.dir/src/main.cpp.o: CMakeFiles/avltree.dir/flags.make
CMakeFiles/avltree.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/avltree.dir/src/main.cpp.o: CMakeFiles/avltree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/avltree.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/avltree.dir/src/main.cpp.o -MF CMakeFiles/avltree.dir/src/main.cpp.o.d -o CMakeFiles/avltree.dir/src/main.cpp.o -c /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/main.cpp

CMakeFiles/avltree.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/avltree.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/main.cpp > CMakeFiles/avltree.dir/src/main.cpp.i

CMakeFiles/avltree.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/avltree.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/main.cpp -o CMakeFiles/avltree.dir/src/main.cpp.s

CMakeFiles/avltree.dir/src/AvlTree.cpp.o: CMakeFiles/avltree.dir/flags.make
CMakeFiles/avltree.dir/src/AvlTree.cpp.o: ../src/AvlTree.cpp
CMakeFiles/avltree.dir/src/AvlTree.cpp.o: CMakeFiles/avltree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/avltree.dir/src/AvlTree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/avltree.dir/src/AvlTree.cpp.o -MF CMakeFiles/avltree.dir/src/AvlTree.cpp.o.d -o CMakeFiles/avltree.dir/src/AvlTree.cpp.o -c /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/AvlTree.cpp

CMakeFiles/avltree.dir/src/AvlTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/avltree.dir/src/AvlTree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/AvlTree.cpp > CMakeFiles/avltree.dir/src/AvlTree.cpp.i

CMakeFiles/avltree.dir/src/AvlTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/avltree.dir/src/AvlTree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/AvlTree.cpp -o CMakeFiles/avltree.dir/src/AvlTree.cpp.s

CMakeFiles/avltree.dir/src/Util.cpp.o: CMakeFiles/avltree.dir/flags.make
CMakeFiles/avltree.dir/src/Util.cpp.o: ../src/Util.cpp
CMakeFiles/avltree.dir/src/Util.cpp.o: CMakeFiles/avltree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/avltree.dir/src/Util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/avltree.dir/src/Util.cpp.o -MF CMakeFiles/avltree.dir/src/Util.cpp.o.d -o CMakeFiles/avltree.dir/src/Util.cpp.o -c /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/Util.cpp

CMakeFiles/avltree.dir/src/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/avltree.dir/src/Util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/Util.cpp > CMakeFiles/avltree.dir/src/Util.cpp.i

CMakeFiles/avltree.dir/src/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/avltree.dir/src/Util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/Util.cpp -o CMakeFiles/avltree.dir/src/Util.cpp.s

CMakeFiles/avltree.dir/src/Command.cpp.o: CMakeFiles/avltree.dir/flags.make
CMakeFiles/avltree.dir/src/Command.cpp.o: ../src/Command.cpp
CMakeFiles/avltree.dir/src/Command.cpp.o: CMakeFiles/avltree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/avltree.dir/src/Command.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/avltree.dir/src/Command.cpp.o -MF CMakeFiles/avltree.dir/src/Command.cpp.o.d -o CMakeFiles/avltree.dir/src/Command.cpp.o -c /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/Command.cpp

CMakeFiles/avltree.dir/src/Command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/avltree.dir/src/Command.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/Command.cpp > CMakeFiles/avltree.dir/src/Command.cpp.i

CMakeFiles/avltree.dir/src/Command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/avltree.dir/src/Command.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/src/Command.cpp -o CMakeFiles/avltree.dir/src/Command.cpp.s

# Object files for target avltree
avltree_OBJECTS = \
"CMakeFiles/avltree.dir/src/main.cpp.o" \
"CMakeFiles/avltree.dir/src/AvlTree.cpp.o" \
"CMakeFiles/avltree.dir/src/Util.cpp.o" \
"CMakeFiles/avltree.dir/src/Command.cpp.o"

# External object files for target avltree
avltree_EXTERNAL_OBJECTS =

avltree: CMakeFiles/avltree.dir/src/main.cpp.o
avltree: CMakeFiles/avltree.dir/src/AvlTree.cpp.o
avltree: CMakeFiles/avltree.dir/src/Util.cpp.o
avltree: CMakeFiles/avltree.dir/src/Command.cpp.o
avltree: CMakeFiles/avltree.dir/build.make
avltree: CMakeFiles/avltree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable avltree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/avltree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/avltree.dir/build: avltree
.PHONY : CMakeFiles/avltree.dir/build

CMakeFiles/avltree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/avltree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/avltree.dir/clean

CMakeFiles/avltree.dir/depend:
	cd /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build /home/tales/Documents/bti/2022.1/EDB2/unity-3/EDBII-Trab3U/build/CMakeFiles/avltree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/avltree.dir/depend

