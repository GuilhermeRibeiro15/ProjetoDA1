# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.3.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.3.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DAProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DAProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DAProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DAProject.dir/flags.make

CMakeFiles/DAProject.dir/main.cpp.obj: CMakeFiles/DAProject.dir/flags.make
CMakeFiles/DAProject.dir/main.cpp.obj: C:/Users/ruben/OneDrive/Aulas/DA/ProjetoDA1/main.cpp
CMakeFiles/DAProject.dir/main.cpp.obj: CMakeFiles/DAProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DAProject.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DAProject.dir/main.cpp.obj -MF CMakeFiles\DAProject.dir\main.cpp.obj.d -o CMakeFiles\DAProject.dir\main.cpp.obj -c C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\main.cpp

CMakeFiles/DAProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DAProject.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\main.cpp > CMakeFiles\DAProject.dir\main.cpp.i

CMakeFiles/DAProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DAProject.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\main.cpp -o CMakeFiles\DAProject.dir\main.cpp.s

CMakeFiles/DAProject.dir/src/StationTrack.cpp.obj: CMakeFiles/DAProject.dir/flags.make
CMakeFiles/DAProject.dir/src/StationTrack.cpp.obj: C:/Users/ruben/OneDrive/Aulas/DA/ProjetoDA1/src/StationTrack.cpp
CMakeFiles/DAProject.dir/src/StationTrack.cpp.obj: CMakeFiles/DAProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DAProject.dir/src/StationTrack.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DAProject.dir/src/StationTrack.cpp.obj -MF CMakeFiles\DAProject.dir\src\StationTrack.cpp.obj.d -o CMakeFiles\DAProject.dir\src\StationTrack.cpp.obj -c C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\StationTrack.cpp

CMakeFiles/DAProject.dir/src/StationTrack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DAProject.dir/src/StationTrack.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\StationTrack.cpp > CMakeFiles\DAProject.dir\src\StationTrack.cpp.i

CMakeFiles/DAProject.dir/src/StationTrack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DAProject.dir/src/StationTrack.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\StationTrack.cpp -o CMakeFiles\DAProject.dir\src\StationTrack.cpp.s

CMakeFiles/DAProject.dir/src/graph.cpp.obj: CMakeFiles/DAProject.dir/flags.make
CMakeFiles/DAProject.dir/src/graph.cpp.obj: C:/Users/ruben/OneDrive/Aulas/DA/ProjetoDA1/src/graph.cpp
CMakeFiles/DAProject.dir/src/graph.cpp.obj: CMakeFiles/DAProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DAProject.dir/src/graph.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DAProject.dir/src/graph.cpp.obj -MF CMakeFiles\DAProject.dir\src\graph.cpp.obj.d -o CMakeFiles\DAProject.dir\src\graph.cpp.obj -c C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\graph.cpp

CMakeFiles/DAProject.dir/src/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DAProject.dir/src/graph.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\graph.cpp > CMakeFiles\DAProject.dir\src\graph.cpp.i

CMakeFiles/DAProject.dir/src/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DAProject.dir/src/graph.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\graph.cpp -o CMakeFiles\DAProject.dir\src\graph.cpp.s

CMakeFiles/DAProject.dir/src/TripManager.cpp.obj: CMakeFiles/DAProject.dir/flags.make
CMakeFiles/DAProject.dir/src/TripManager.cpp.obj: C:/Users/ruben/OneDrive/Aulas/DA/ProjetoDA1/src/TripManager.cpp
CMakeFiles/DAProject.dir/src/TripManager.cpp.obj: CMakeFiles/DAProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DAProject.dir/src/TripManager.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DAProject.dir/src/TripManager.cpp.obj -MF CMakeFiles\DAProject.dir\src\TripManager.cpp.obj.d -o CMakeFiles\DAProject.dir\src\TripManager.cpp.obj -c C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\TripManager.cpp

CMakeFiles/DAProject.dir/src/TripManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DAProject.dir/src/TripManager.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\TripManager.cpp > CMakeFiles\DAProject.dir\src\TripManager.cpp.i

CMakeFiles/DAProject.dir/src/TripManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DAProject.dir/src/TripManager.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\src\TripManager.cpp -o CMakeFiles\DAProject.dir\src\TripManager.cpp.s

# Object files for target DAProject
DAProject_OBJECTS = \
"CMakeFiles/DAProject.dir/main.cpp.obj" \
"CMakeFiles/DAProject.dir/src/StationTrack.cpp.obj" \
"CMakeFiles/DAProject.dir/src/graph.cpp.obj" \
"CMakeFiles/DAProject.dir/src/TripManager.cpp.obj"

# External object files for target DAProject
DAProject_EXTERNAL_OBJECTS =

DAProject.exe: CMakeFiles/DAProject.dir/main.cpp.obj
DAProject.exe: CMakeFiles/DAProject.dir/src/StationTrack.cpp.obj
DAProject.exe: CMakeFiles/DAProject.dir/src/graph.cpp.obj
DAProject.exe: CMakeFiles/DAProject.dir/src/TripManager.cpp.obj
DAProject.exe: CMakeFiles/DAProject.dir/build.make
DAProject.exe: CMakeFiles/DAProject.dir/linklibs.rsp
DAProject.exe: CMakeFiles/DAProject.dir/objects1.rsp
DAProject.exe: CMakeFiles/DAProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable DAProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\DAProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DAProject.dir/build: DAProject.exe
.PHONY : CMakeFiles/DAProject.dir/build

CMakeFiles/DAProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DAProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/DAProject.dir/clean

CMakeFiles/DAProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1 C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1 C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug C:\Users\ruben\OneDrive\Aulas\DA\ProjetoDA1\cmake-build-debug\CMakeFiles\DAProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DAProject.dir/depend
