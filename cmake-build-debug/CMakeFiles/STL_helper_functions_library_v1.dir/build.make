# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/STL_helper_functions_library_v1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/STL_helper_functions_library_v1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/STL_helper_functions_library_v1.dir/flags.make

CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.obj: CMakeFiles/STL_helper_functions_library_v1.dir/flags.make
CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.obj: ../src/stl_helper_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\STL_helper_functions_library_v1.dir\src\stl_helper_functions.cpp.obj -c C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\src\stl_helper_functions.cpp

CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\src\stl_helper_functions.cpp > CMakeFiles\STL_helper_functions_library_v1.dir\src\stl_helper_functions.cpp.i

CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\src\stl_helper_functions.cpp -o CMakeFiles\STL_helper_functions_library_v1.dir\src\stl_helper_functions.cpp.s

CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.obj: CMakeFiles/STL_helper_functions_library_v1.dir/flags.make
CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.obj: ../tests/test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\STL_helper_functions_library_v1.dir\tests\test_main.cpp.obj -c C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\tests\test_main.cpp

CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\tests\test_main.cpp > CMakeFiles\STL_helper_functions_library_v1.dir\tests\test_main.cpp.i

CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\tests\test_main.cpp -o CMakeFiles\STL_helper_functions_library_v1.dir\tests\test_main.cpp.s

# Object files for target STL_helper_functions_library_v1
STL_helper_functions_library_v1_OBJECTS = \
"CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.obj" \
"CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.obj"

# External object files for target STL_helper_functions_library_v1
STL_helper_functions_library_v1_EXTERNAL_OBJECTS =

STL_helper_functions_library_v1.exe: CMakeFiles/STL_helper_functions_library_v1.dir/src/stl_helper_functions.cpp.obj
STL_helper_functions_library_v1.exe: CMakeFiles/STL_helper_functions_library_v1.dir/tests/test_main.cpp.obj
STL_helper_functions_library_v1.exe: CMakeFiles/STL_helper_functions_library_v1.dir/build.make
STL_helper_functions_library_v1.exe: CMakeFiles/STL_helper_functions_library_v1.dir/linklibs.rsp
STL_helper_functions_library_v1.exe: CMakeFiles/STL_helper_functions_library_v1.dir/objects1.rsp
STL_helper_functions_library_v1.exe: CMakeFiles/STL_helper_functions_library_v1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable STL_helper_functions_library_v1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\STL_helper_functions_library_v1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/STL_helper_functions_library_v1.dir/build: STL_helper_functions_library_v1.exe

.PHONY : CMakeFiles/STL_helper_functions_library_v1.dir/build

CMakeFiles/STL_helper_functions_library_v1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\STL_helper_functions_library_v1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/STL_helper_functions_library_v1.dir/clean

CMakeFiles/STL_helper_functions_library_v1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1 C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1 C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\cmake-build-debug C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\cmake-build-debug C:\Users\atib1\CLionProjects\STL_helper_functions_library_v1\cmake-build-debug\CMakeFiles\STL_helper_functions_library_v1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/STL_helper_functions_library_v1.dir/depend

