# Microsoft Developer Studio Project File - Name="AxisGCom" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AxisGCom - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AxisGCom.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AxisGCom.mak" CFG="AxisGCom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AxisGCom - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AxisGCom - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AxisGCom - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Imm32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../../../Release/AXISGCOM.DLL"

!ELSEIF  "$(CFG)" == "AxisGCom - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Imm32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../../../exe/AXISGCOM.DLL" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AxisGCom - Win32 Release"
# Name "AxisGCom - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AxisGCom.cpp
# End Source File
# Begin Source File

SOURCE=.\AxisGCom.def
# End Source File
# Begin Source File

SOURCE=.\AxisGCom.rc
# End Source File
# Begin Source File

SOURCE=.\CellRange.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckBox.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\MxTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\NewMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\PnAid.cpp
# End Source File
# Begin Source File

SOURCE=.\PnAidInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PnBaseWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\PnCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PnInput.cpp
# End Source File
# Begin Source File

SOURCE=.\PnSise.cpp
# End Source File
# Begin Source File

SOURCE=.\PnTable.cpp
# End Source File
# Begin Source File

SOURCE=.\PnTool.cpp
# End Source File
# Begin Source File

SOURCE=.\PnToolInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PnToolTip.cpp
# End Source File
# Begin Source File

SOURCE=.\PnWndCalendar.cpp
# End Source File
# Begin Source File

SOURCE=.\PnWndCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\PnWndCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PnWndEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PnWndGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\SavedHead.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AxisGCom.h
# End Source File
# Begin Source File

SOURCE=.\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\CheckBox.h
# End Source File
# Begin Source File

SOURCE=.\CodeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\defInfo.h
# End Source File
# Begin Source File

SOURCE=.\memDc.h
# End Source File
# Begin Source File

SOURCE=.\NewMenu.h
# End Source File
# Begin Source File

SOURCE=.\PnAid.h
# End Source File
# Begin Source File

SOURCE=.\PnAidInfo.h
# End Source File
# Begin Source File

SOURCE=.\PnBaseWnd.h
# End Source File
# Begin Source File

SOURCE=.\PnCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PnInput.h
# End Source File
# Begin Source File

SOURCE=.\PnSise.h
# End Source File
# Begin Source File

SOURCE=.\PnTable.h
# End Source File
# Begin Source File

SOURCE=.\PnTool.h
# End Source File
# Begin Source File

SOURCE=.\PnToolInfo.h
# End Source File
# Begin Source File

SOURCE=.\PnToolTip.h
# End Source File
# Begin Source File

SOURCE=.\PnWndCalendar.h
# End Source File
# Begin Source File

SOURCE=.\PnWndCombo.h
# End Source File
# Begin Source File

SOURCE=.\PnWndCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PnWndEdit.h
# End Source File
# Begin Source File

SOURCE=.\PnWndGrid.h
# End Source File
# Begin Source File

SOURCE=.\qsort.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\Common\SavedHead.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AxisGCom.rc2
# End Source File
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\folder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tabimg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_ctrl2.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
