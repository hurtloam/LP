# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo

# Include any dependencies generated for this target.
include CMakeFiles/AppGimpactTestDemo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AppGimpactTestDemo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AppGimpactTestDemo.dir/flags.make

CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o: CMakeFiles/AppGimpactTestDemo.dir/flags.make
CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o: GimpactTestDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o -c /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/GimpactTestDemo.cpp

CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/GimpactTestDemo.cpp > CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.i

CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/GimpactTestDemo.cpp -o CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.s

CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.requires:
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.requires

CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.provides: CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.requires
	$(MAKE) -f CMakeFiles/AppGimpactTestDemo.dir/build.make CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.provides.build
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.provides

CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.provides.build: CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o

CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o: CMakeFiles/AppGimpactTestDemo.dir/flags.make
CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o: /home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o -c /home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.cpp

CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.cpp > CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.i

CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.cpp -o CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.s

CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.requires:
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.requires

CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.provides: CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.requires
	$(MAKE) -f CMakeFiles/AppGimpactTestDemo.dir/build.make CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.provides.build
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.provides

CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.provides.build: CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o

CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o: CMakeFiles/AppGimpactTestDemo.dir/flags.make
CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o: Win32GimpactDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o -c /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/Win32GimpactDemo.cpp

CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/Win32GimpactDemo.cpp > CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.i

CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/Win32GimpactDemo.cpp -o CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.s

CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.requires:
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.requires

CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.provides: CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.requires
	$(MAKE) -f CMakeFiles/AppGimpactTestDemo.dir/build.make CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.provides.build
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.provides

CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.provides.build: CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o

# Object files for target AppGimpactTestDemo
AppGimpactTestDemo_OBJECTS = \
"CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o" \
"CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o" \
"CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o"

# External object files for target AppGimpactTestDemo
AppGimpactTestDemo_EXTERNAL_OBJECTS =

AppGimpactTestDemo: CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o
AppGimpactTestDemo: CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o
AppGimpactTestDemo: CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o
AppGimpactTestDemo: CMakeFiles/AppGimpactTestDemo.dir/build.make
AppGimpactTestDemo: CMakeFiles/AppGimpactTestDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppGimpactTestDemo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppGimpactTestDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AppGimpactTestDemo.dir/build: AppGimpactTestDemo
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/build

CMakeFiles/AppGimpactTestDemo.dir/requires: CMakeFiles/AppGimpactTestDemo.dir/GimpactTestDemo.o.requires
CMakeFiles/AppGimpactTestDemo.dir/requires: CMakeFiles/AppGimpactTestDemo.dir/home/peter/projects/bullet-2.82-r2704/Demos/OpenGL/Win32AppMain.o.requires
CMakeFiles/AppGimpactTestDemo.dir/requires: CMakeFiles/AppGimpactTestDemo.dir/Win32GimpactDemo.o.requires
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/requires

CMakeFiles/AppGimpactTestDemo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AppGimpactTestDemo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/clean

CMakeFiles/AppGimpactTestDemo.dir/depend:
	cd /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo /home/peter/projects/bullet-2.82-r2704/Demos/GimpactTestDemo/CMakeFiles/AppGimpactTestDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AppGimpactTestDemo.dir/depend

