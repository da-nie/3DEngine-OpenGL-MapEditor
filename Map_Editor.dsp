# Microsoft Developer Studio Project File - Name="Map_Editor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Map_Editor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Map_Editor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Map_Editor.mak" CFG="Map_Editor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Map_Editor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Map_Editor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Map_Editor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Map_Editor - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Map_Editor - Win32 Release"
# Name "Map_Editor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\button.cpp
# End Source File
# Begin Source File

SOURCE=.\colorset.cpp
# End Source File
# Begin Source File

SOURCE=.\common.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_createlightingform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_createpolygonform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_createsegmentform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_createsimplydoorform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_createsimplysectorform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_createstarform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_selecttextureform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_settexturefollowform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_settingrenderform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_showtextureform.cpp
# End Source File
# Begin Source File

SOURCE=.\dl_startposform.cpp
# End Source File
# Begin Source File

SOURCE=.\FileProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\formats.cpp
# End Source File
# Begin Source File

SOURCE=.\gdi.cpp
# End Source File
# Begin Source File

SOURCE=.\lighting.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\mapeditor.rc
# End Source File
# Begin Source File

SOURCE=.\menu.cpp
# End Source File
# Begin Source File

SOURCE=.\Polygon.cpp
# End Source File
# Begin Source File

SOURCE=.\render.cpp
# End Source File
# Begin Source File

SOURCE=.\shadow.cpp
# End Source File
# Begin Source File

SOURCE=.\static.cpp
# End Source File
# Begin Source File

SOURCE=.\surface.cpp
# End Source File
# Begin Source File

SOURCE=.\vector.cpp
# End Source File
# Begin Source File

SOURCE=.\wc_form.cpp
# End Source File
# Begin Source File

SOURCE=.\wc_menuform.cpp
# End Source File
# Begin Source File

SOURCE=.\wc_progress.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\button.h
# End Source File
# Begin Source File

SOURCE=.\colorset.h
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\dl_createlightingform.h
# End Source File
# Begin Source File

SOURCE=.\dl_createpolygonform.h
# End Source File
# Begin Source File

SOURCE=.\dl_createsegmentform.h
# End Source File
# Begin Source File

SOURCE=.\dl_createsimplydoorform.h
# End Source File
# Begin Source File

SOURCE=.\dl_createsimplysectorform.h
# End Source File
# Begin Source File

SOURCE=.\dl_createstarform.h
# End Source File
# Begin Source File

SOURCE=.\dl_selecttextureform.h
# End Source File
# Begin Source File

SOURCE=.\dl_settexturefollowform.h
# End Source File
# Begin Source File

SOURCE=.\dl_settingrenderform.h
# End Source File
# Begin Source File

SOURCE=.\dl_showtextureform.h
# End Source File
# Begin Source File

SOURCE=.\dl_startposform.h
# End Source File
# Begin Source File

SOURCE=.\FileProcess.h
# End Source File
# Begin Source File

SOURCE=.\formats.h
# End Source File
# Begin Source File

SOURCE=.\gdi.h
# End Source File
# Begin Source File

SOURCE=.\lighting.h
# End Source File
# Begin Source File

SOURCE=.\menu.h
# End Source File
# Begin Source File

SOURCE=.\Polygon.h
# End Source File
# Begin Source File

SOURCE=.\render.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\shadow.h
# End Source File
# Begin Source File

SOURCE=.\static.h
# End Source File
# Begin Source File

SOURCE=.\surface.h
# End Source File
# Begin Source File

SOURCE=.\vector.h
# End Source File
# Begin Source File

SOURCE=.\wc_form.h
# End Source File
# Begin Source File

SOURCE=.\wc_menuform.h
# End Source File
# Begin Source File

SOURCE=.\wc_progress.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
