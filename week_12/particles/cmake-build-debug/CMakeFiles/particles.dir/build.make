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
CMAKE_COMMAND = /snap/clion/151/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/151/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vladlen/Testik/week_12/particles

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vladlen/Testik/week_12/particles/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/particles.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/particles.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/particles.dir/flags.make

CMakeFiles/particles.dir/main.cpp.o: CMakeFiles/particles.dir/flags.make
CMakeFiles/particles.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladlen/Testik/week_12/particles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/particles.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particles.dir/main.cpp.o -c /home/vladlen/Testik/week_12/particles/main.cpp

CMakeFiles/particles.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particles.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladlen/Testik/week_12/particles/main.cpp > CMakeFiles/particles.dir/main.cpp.i

CMakeFiles/particles.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particles.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladlen/Testik/week_12/particles/main.cpp -o CMakeFiles/particles.dir/main.cpp.s

CMakeFiles/particles.dir/link.cpp.o: CMakeFiles/particles.dir/flags.make
CMakeFiles/particles.dir/link.cpp.o: ../link.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladlen/Testik/week_12/particles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/particles.dir/link.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particles.dir/link.cpp.o -c /home/vladlen/Testik/week_12/particles/link.cpp

CMakeFiles/particles.dir/link.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particles.dir/link.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladlen/Testik/week_12/particles/link.cpp > CMakeFiles/particles.dir/link.cpp.i

CMakeFiles/particles.dir/link.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particles.dir/link.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladlen/Testik/week_12/particles/link.cpp -o CMakeFiles/particles.dir/link.cpp.s

CMakeFiles/particles.dir/particle.cpp.o: CMakeFiles/particles.dir/flags.make
CMakeFiles/particles.dir/particle.cpp.o: ../particle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladlen/Testik/week_12/particles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/particles.dir/particle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particles.dir/particle.cpp.o -c /home/vladlen/Testik/week_12/particles/particle.cpp

CMakeFiles/particles.dir/particle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particles.dir/particle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladlen/Testik/week_12/particles/particle.cpp > CMakeFiles/particles.dir/particle.cpp.i

CMakeFiles/particles.dir/particle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particles.dir/particle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladlen/Testik/week_12/particles/particle.cpp -o CMakeFiles/particles.dir/particle.cpp.s

CMakeFiles/particles.dir/pressure.cpp.o: CMakeFiles/particles.dir/flags.make
CMakeFiles/particles.dir/pressure.cpp.o: ../pressure.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladlen/Testik/week_12/particles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/particles.dir/pressure.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particles.dir/pressure.cpp.o -c /home/vladlen/Testik/week_12/particles/pressure.cpp

CMakeFiles/particles.dir/pressure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particles.dir/pressure.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladlen/Testik/week_12/particles/pressure.cpp > CMakeFiles/particles.dir/pressure.cpp.i

CMakeFiles/particles.dir/pressure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particles.dir/pressure.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladlen/Testik/week_12/particles/pressure.cpp -o CMakeFiles/particles.dir/pressure.cpp.s

CMakeFiles/particles.dir/system.cpp.o: CMakeFiles/particles.dir/flags.make
CMakeFiles/particles.dir/system.cpp.o: ../system.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladlen/Testik/week_12/particles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/particles.dir/system.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particles.dir/system.cpp.o -c /home/vladlen/Testik/week_12/particles/system.cpp

CMakeFiles/particles.dir/system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particles.dir/system.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladlen/Testik/week_12/particles/system.cpp > CMakeFiles/particles.dir/system.cpp.i

CMakeFiles/particles.dir/system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particles.dir/system.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladlen/Testik/week_12/particles/system.cpp -o CMakeFiles/particles.dir/system.cpp.s

# Object files for target particles
particles_OBJECTS = \
"CMakeFiles/particles.dir/main.cpp.o" \
"CMakeFiles/particles.dir/link.cpp.o" \
"CMakeFiles/particles.dir/particle.cpp.o" \
"CMakeFiles/particles.dir/pressure.cpp.o" \
"CMakeFiles/particles.dir/system.cpp.o"

# External object files for target particles
particles_EXTERNAL_OBJECTS =

particles: CMakeFiles/particles.dir/main.cpp.o
particles: CMakeFiles/particles.dir/link.cpp.o
particles: CMakeFiles/particles.dir/particle.cpp.o
particles: CMakeFiles/particles.dir/pressure.cpp.o
particles: CMakeFiles/particles.dir/system.cpp.o
particles: CMakeFiles/particles.dir/build.make
particles: /home/vladlen/Загрузки/SFML-2.5.1/lib/libsfml-graphics.so.2.5.1
particles: /home/vladlen/Загрузки/SFML-2.5.1/lib/libsfml-window.so.2.5.1
particles: /home/vladlen/Загрузки/SFML-2.5.1/lib/libsfml-system.so.2.5.1
particles: CMakeFiles/particles.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vladlen/Testik/week_12/particles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable particles"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/particles.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/particles.dir/build: particles

.PHONY : CMakeFiles/particles.dir/build

CMakeFiles/particles.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/particles.dir/cmake_clean.cmake
.PHONY : CMakeFiles/particles.dir/clean

CMakeFiles/particles.dir/depend:
	cd /home/vladlen/Testik/week_12/particles/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vladlen/Testik/week_12/particles /home/vladlen/Testik/week_12/particles /home/vladlen/Testik/week_12/particles/cmake-build-debug /home/vladlen/Testik/week_12/particles/cmake-build-debug /home/vladlen/Testik/week_12/particles/cmake-build-debug/CMakeFiles/particles.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/particles.dir/depend
