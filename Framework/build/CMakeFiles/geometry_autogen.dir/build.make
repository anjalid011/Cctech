# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\build"

# Utility rule file for geometry_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/geometry_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/geometry_autogen.dir/progress.make

CMakeFiles/geometry_autogen: geometry_autogen/timestamp

geometry_autogen/timestamp: C:/Qt/6.9.0/mingw_64/bin/moc.exe
geometry_autogen/timestamp: C:/Qt/6.9.0/mingw_64/bin/uic.exe
geometry_autogen/timestamp: CMakeFiles/geometry_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target geometry"
	"C:\Program Files\CMake\bin\cmake.exe" -E cmake_autogen "C:/Users/Anjali Dongare/Desktop/Project/Cctech/Framework/build/CMakeFiles/geometry_autogen.dir/AutogenInfo.json" ""
	"C:\Program Files\CMake\bin\cmake.exe" -E touch "C:/Users/Anjali Dongare/Desktop/Project/Cctech/Framework/build/geometry_autogen/timestamp"

CMakeFiles/geometry_autogen.dir/codegen:
.PHONY : CMakeFiles/geometry_autogen.dir/codegen

geometry_autogen: CMakeFiles/geometry_autogen
geometry_autogen: geometry_autogen/timestamp
geometry_autogen: CMakeFiles/geometry_autogen.dir/build.make
.PHONY : geometry_autogen

# Rule to build all files generated by this target.
CMakeFiles/geometry_autogen.dir/build: geometry_autogen
.PHONY : CMakeFiles/geometry_autogen.dir/build

CMakeFiles/geometry_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\geometry_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/geometry_autogen.dir/clean

CMakeFiles/geometry_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework" "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework" "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\build" "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\build" "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\build\CMakeFiles\geometry_autogen.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/geometry_autogen.dir/depend

