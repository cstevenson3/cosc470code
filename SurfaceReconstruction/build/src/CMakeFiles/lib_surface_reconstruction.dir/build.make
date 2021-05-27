# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build

# Include any dependencies generated for this target.
include src/CMakeFiles/lib_surface_reconstruction.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/lib_surface_reconstruction.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/lib_surface_reconstruction.dir/flags.make

src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o: ../src/main.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/main.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/main.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/main.cpp > CMakeFiles/lib_surface_reconstruction.dir/main.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/main.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/main.cpp -o CMakeFiles/lib_surface_reconstruction.dir/main.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o: ../src/ReconstructionConfig.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ReconstructionConfig.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ReconstructionConfig.cpp > CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ReconstructionConfig.cpp -o CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o: ../src/Timer.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Timer.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Timer.cpp > CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Timer.cpp -o CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o: ../src/Statistics.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Statistics.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Statistics.cpp > CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Statistics.cpp -o CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o: ../src/ContourStatistics.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ContourStatistics.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ContourStatistics.cpp > CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ContourStatistics.cpp -o CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o: ../src/PointCloud.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointCloud.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointCloud.cpp > CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointCloud.cpp -o CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o: ../src/DTW.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/DTW.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/DTW.cpp > CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/DTW.cpp -o CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o: ../src/PointCorrespondence.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointCorrespondence.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointCorrespondence.cpp > CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointCorrespondence.cpp -o CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o: ../src/Contours.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Contours.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Contours.cpp > CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Contours.cpp -o CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o: ../src/PointUtil.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointUtil.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointUtil.cpp > CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/PointUtil.cpp -o CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o: ../src/MeshUtil.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/MeshUtil.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/MeshUtil.cpp > CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/MeshUtil.cpp -o CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o: ../src/Surface.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Surface.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Surface.cpp > CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/Surface.cpp -o CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.s

src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/flags.make
src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o: ../src/ContourCorrespondence.cpp
src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o: src/CMakeFiles/lib_surface_reconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o -MF CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o.d -o CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o -c /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ContourCorrespondence.cpp

src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.i"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ContourCorrespondence.cpp > CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.i

src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.s"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src/ContourCorrespondence.cpp -o CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.s

# Object files for target lib_surface_reconstruction
lib_surface_reconstruction_OBJECTS = \
"CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o" \
"CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o"

# External object files for target lib_surface_reconstruction
lib_surface_reconstruction_EXTERNAL_OBJECTS =

src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/main.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/ReconstructionConfig.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/Timer.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/Statistics.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/ContourStatistics.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/PointCloud.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/DTW.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/PointCorrespondence.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/Contours.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/PointUtil.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/MeshUtil.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/Surface.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/ContourCorrespondence.cpp.o
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/build.make
src/liblib_surface_reconstruction.a: src/CMakeFiles/lib_surface_reconstruction.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX static library liblib_surface_reconstruction.a"
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lib_surface_reconstruction.dir/cmake_clean_target.cmake
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib_surface_reconstruction.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/lib_surface_reconstruction.dir/build: src/liblib_surface_reconstruction.a
.PHONY : src/CMakeFiles/lib_surface_reconstruction.dir/build

src/CMakeFiles/lib_surface_reconstruction.dir/clean:
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lib_surface_reconstruction.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/lib_surface_reconstruction.dir/clean

src/CMakeFiles/lib_surface_reconstruction.dir/depend:
	cd /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/src /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src /Users/cameron/Desktop/Development/cosc470code/SurfaceReconstruction/build/src/CMakeFiles/lib_surface_reconstruction.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/lib_surface_reconstruction.dir/depend
