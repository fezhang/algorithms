# Microsoft Developer Studio Project File - Name="book_in_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=book_in_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "book_in_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "book_in_cpp.mak" CFG="book_in_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "book_in_cpp - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "book_in_cpp - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "book_in_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "book_in_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "book_in_cpp - Win32 Release"
# Name "book_in_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Test Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\adt_test.cpp
# End Source File
# Begin Source File

SOURCE=.\adt_test.h
# End Source File
# Begin Source File

SOURCE=.\algorithm_analysis_test.cpp
# End Source File
# Begin Source File

SOURCE=.\algorithm_analysis_test.h
# End Source File
# Begin Source File

SOURCE=.\connectivity_test.cpp
# End Source File
# Begin Source File

SOURCE=.\connectivity_test.h
# End Source File
# Begin Source File

SOURCE=.\elementary_data_structure_test.cpp
# End Source File
# Begin Source File

SOURCE=.\elementary_data_structure_test.h
# End Source File
# Begin Source File

SOURCE=.\sort_test.cpp
# End Source File
# Begin Source File

SOURCE=.\sort_test.h
# End Source File
# Begin Source File

SOURCE=.\test_entry.h
# End Source File
# Begin Source File

SOURCE=.\testframe.cpp
# End Source File
# Begin Source File

SOURCE=.\testframe.h
# End Source File
# End Group
# Begin Group "Common Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ds_comm.h
# End Source File
# Begin Source File

SOURCE=.\platform.h
# End Source File
# Begin Source File

SOURCE=.\typedef.h
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# End Group
# Begin Group "Fundamentals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\algorithm_analysis.cpp
# End Source File
# Begin Source File

SOURCE=.\algorithm_analysis.h
# End Source File
# Begin Source File

SOURCE=.\connectivity.cpp
# End Source File
# Begin Source File

SOURCE=.\connectivity.h
# End Source File
# Begin Source File

SOURCE=.\union_find.cpp
# End Source File
# Begin Source File

SOURCE=.\union_find.h
# End Source File
# End Group
# Begin Group "DataStructures"

# PROP Default_Filter ""
# Begin Group "Recursive"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\simple_recursive_example.cpp
# End Source File
# Begin Source File

SOURCE=.\simple_recursive_example.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\container.hpp
# End Source File
# Begin Source File

SOURCE=.\datastructure_exercise.cpp
# End Source File
# Begin Source File

SOURCE=.\datastructure_exercise.h
# End Source File
# Begin Source File

SOURCE=.\elementary.cpp
# End Source File
# Begin Source File

SOURCE=.\elementary.h
# End Source File
# Begin Source File

SOURCE=.\josephus_problem.cpp
# End Source File
# Begin Source File

SOURCE=.\josephus_problem.h
# End Source File
# Begin Source File

SOURCE=.\list.hpp
# End Source File
# Begin Source File

SOURCE=.\obj_interface.hpp
# End Source File
# Begin Source File

SOURCE=.\polynomial.hpp
# End Source File
# Begin Source File

SOURCE=.\polynomial_use.cpp
# End Source File
# Begin Source File

SOURCE=.\polynomial_use.h
# End Source File
# Begin Source File

SOURCE=.\queue.hpp
# End Source File
# Begin Source File

SOURCE=.\queue_use.cpp
# End Source File
# Begin Source File

SOURCE=.\queue_use.h
# End Source File
# Begin Source File

SOURCE=.\stack.hpp
# End Source File
# Begin Source File

SOURCE=.\stack_use.cpp
# End Source File
# Begin Source File

SOURCE=.\stack_use.h
# End Source File
# Begin Source File

SOURCE=.\tree.hpp
# End Source File
# Begin Source File

SOURCE=.\tree_use.cpp
# End Source File
# Begin Source File

SOURCE=.\tree_use.h
# End Source File
# Begin Source File

SOURCE=.\vector.hpp
# End Source File
# End Group
# Begin Group "Sorting"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\basic_sort.hpp
# End Source File
# Begin Source File

SOURCE=.\elementary_sort_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\elementary_sort_frame.h
# End Source File
# End Group
# Begin Group "Searching"

# PROP Default_Filter ""
# End Group
# End Target
# End Project
