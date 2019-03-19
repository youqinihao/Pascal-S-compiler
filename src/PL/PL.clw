; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PL.h"
LastPage=0

ClassCount=8
Class1=CPLApp
Class2=CPLDoc
Class3=CPLView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_CNTR_INPLACE
Resource2=IDD_DIALOG3
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Class6=CPLTree
Class7=CContainView
Class8=CPLTreeView
Resource4=IDD_ABOUTBOX

[CLS:CPLApp]
Type=0
HeaderFile=PL.h
ImplementationFile=PL.cpp
Filter=N

[CLS:CPLDoc]
Type=0
HeaderFile=PLDoc.h
ImplementationFile=PLDoc.cpp
Filter=N

[CLS:CPLView]
Type=0
HeaderFile=PLView.h
ImplementationFile=PLView.cpp
Filter=C
BaseClass=CRichEditView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=PL.cpp
ImplementationFile=PL.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_PASTE_SPECIAL
Command15=ID_EDIT_SELECT_ALL
Command16=ID_EDIT_FIND
Command17=ID_EDIT_REPEAT
Command18=ID_EDIT_REPLACE
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_APP_ABOUT
Command22=ID_MENUITEM32785
Command23=ID_MENUITEMCOM
Command24=ID_MENUITEMEXE
Command25=ID_MENUITEMDEBUG
Command26=ID_MENUITEM32789
CommandCount=26

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=CPLView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_SELECT_ALL
Command10=ID_EDIT_FIND
Command11=ID_EDIT_REPEAT
Command12=ID_EDIT_REPLACE
Command13=ID_OLE_EDIT_PROPERTIES
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_NEXT_PANE
Command19=ID_PREV_PANE
Command20=ID_CANCEL_EDIT_CNTR
CommandCount=20

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=CPLView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_MENUITEMCOM
Command10=ID_MENUITEMEXE
Command11=ID_MENUITEMDEBUG
CommandCount=11

[DLG:IDD_DIALOG3]
Type=1
Class=?
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308864
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308864

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[CLS:CPLTree]
Type=0
HeaderFile=PLTree.h
ImplementationFile=PLTree.cpp
BaseClass=CTreeView
Filter=C
VirtualFilter=VWC

[CLS:CContainView]
Type=0
HeaderFile=ContainView.h
ImplementationFile=ContainView.cpp
BaseClass=CView
Filter=C

[CLS:CPLTreeView]
Type=0
HeaderFile=PLTreeView.h
ImplementationFile=PLTreeView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC

