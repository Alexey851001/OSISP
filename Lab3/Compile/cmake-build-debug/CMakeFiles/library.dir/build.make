# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\5sem\OSISP\Lab3\Compile

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\5sem\OSISP\Lab3\Compile\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\library.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\library.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\library.dir\flags.make

CMakeFiles\library.dir\library\library.cpp.obj: CMakeFiles\library.dir\flags.make
CMakeFiles\library.dir\library\library.cpp.obj: ..\library\library.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\5sem\OSISP\Lab3\Compile\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/library.dir/library/library.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\library.dir\library\library.cpp.obj /FdCMakeFiles\library.dir\ /FS -c D:\5sem\OSISP\Lab3\Compile\library\library.cpp
<<

CMakeFiles\library.dir\library\library.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.dir/library/library.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\library.dir\library\library.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\5sem\OSISP\Lab3\Compile\library\library.cpp
<<

CMakeFiles\library.dir\library\library.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.dir/library/library.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\library.dir\library\library.cpp.s /c D:\5sem\OSISP\Lab3\Compile\library\library.cpp
<<

# Object files for target library
library_OBJECTS = \
"CMakeFiles\library.dir\library\library.cpp.obj"

# External object files for target library
library_EXTERNAL_OBJECTS =

library.dll: CMakeFiles\library.dir\library\library.cpp.obj
library.dll: CMakeFiles\library.dir\build.make
library.dll: CMakeFiles\library.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\5sem\OSISP\Lab3\Compile\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library library.dll"
	"D:\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_dll --intdir=CMakeFiles\library.dir --rc="D:\Embarcadero Studio 19.0\Windows Kits 10\bin\10.0.18362.0\x86\rc.exe" --mt="D:\Embarcadero Studio 19.0\Windows Kits 10\bin\10.0.18362.0\x86\mt.exe" --manifests  -- C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\library.dir\objects1.rsp @<<
 /out:library.dll /implib:library.lib /pdb:D:\5sem\OSISP\Lab3\Compile\cmake-build-debug\library.pdb /dll /version:0.0 /machine:X86 /debug /INCREMENTAL  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib  
<<

# Rule to build all files generated by this target.
CMakeFiles\library.dir\build: library.dll

.PHONY : CMakeFiles\library.dir\build

CMakeFiles\library.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\library.dir\cmake_clean.cmake
.PHONY : CMakeFiles\library.dir\clean

CMakeFiles\library.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\5sem\OSISP\Lab3\Compile D:\5sem\OSISP\Lab3\Compile D:\5sem\OSISP\Lab3\Compile\cmake-build-debug D:\5sem\OSISP\Lab3\Compile\cmake-build-debug D:\5sem\OSISP\Lab3\Compile\cmake-build-debug\CMakeFiles\library.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\library.dir\depend
