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
CMAKE_SOURCE_DIR = D:\5sem\OSISP\OSISP\Kyrs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Kyrs.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Kyrs.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Kyrs.dir\flags.make

CMakeFiles\Kyrs.dir\main.cpp.obj: CMakeFiles\Kyrs.dir\flags.make
CMakeFiles\Kyrs.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Kyrs.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Kyrs.dir\main.cpp.obj /FdCMakeFiles\Kyrs.dir\ /FS -c D:\5sem\OSISP\OSISP\Kyrs\main.cpp
<<

CMakeFiles\Kyrs.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kyrs.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\Kyrs.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\5sem\OSISP\OSISP\Kyrs\main.cpp
<<

CMakeFiles\Kyrs.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kyrs.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Kyrs.dir\main.cpp.s /c D:\5sem\OSISP\OSISP\Kyrs\main.cpp
<<

CMakeFiles\Kyrs.dir\atom\Atom.cpp.obj: CMakeFiles\Kyrs.dir\flags.make
CMakeFiles\Kyrs.dir\atom\Atom.cpp.obj: ..\atom\Atom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Kyrs.dir/atom/Atom.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Kyrs.dir\atom\Atom.cpp.obj /FdCMakeFiles\Kyrs.dir\ /FS -c D:\5sem\OSISP\OSISP\Kyrs\atom\Atom.cpp
<<

CMakeFiles\Kyrs.dir\atom\Atom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kyrs.dir/atom/Atom.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\Kyrs.dir\atom\Atom.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\5sem\OSISP\OSISP\Kyrs\atom\Atom.cpp
<<

CMakeFiles\Kyrs.dir\atom\Atom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kyrs.dir/atom/Atom.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Kyrs.dir\atom\Atom.cpp.s /c D:\5sem\OSISP\OSISP\Kyrs\atom\Atom.cpp
<<

# Object files for target Kyrs
Kyrs_OBJECTS = \
"CMakeFiles\Kyrs.dir\main.cpp.obj" \
"CMakeFiles\Kyrs.dir\atom\Atom.cpp.obj"

# External object files for target Kyrs
Kyrs_EXTERNAL_OBJECTS =

Kyrs.exe: CMakeFiles\Kyrs.dir\main.cpp.obj
Kyrs.exe: CMakeFiles\Kyrs.dir\atom\Atom.cpp.obj
Kyrs.exe: CMakeFiles\Kyrs.dir\build.make
Kyrs.exe: CMakeFiles\Kyrs.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Kyrs.exe"
	"D:\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Kyrs.dir --rc="D:\Embarcadero Studio 19.0\Windows Kits 10\bin\10.0.19041.0\x86\rc.exe" --mt="D:\Embarcadero Studio 19.0\Windows Kits 10\bin\10.0.19041.0\x86\mt.exe" --manifests  -- C:\PROGRA~2\MICROS~4\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Kyrs.dir\objects1.rsp @<<
 /out:Kyrs.exe /implib:Kyrs.lib /pdb:D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug\Kyrs.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:windows  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Kyrs.dir\build: Kyrs.exe

.PHONY : CMakeFiles\Kyrs.dir\build

CMakeFiles\Kyrs.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Kyrs.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Kyrs.dir\clean

CMakeFiles\Kyrs.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\5sem\OSISP\OSISP\Kyrs D:\5sem\OSISP\OSISP\Kyrs D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug D:\5sem\OSISP\OSISP\Kyrs\cmake-build-debug\CMakeFiles\Kyrs.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Kyrs.dir\depend
