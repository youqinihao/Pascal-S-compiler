// mydebug.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "mydebug.h"
#include "Output.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CMydebugApp

BEGIN_MESSAGE_MAP(CMydebugApp, CWinApp)
	//{{AFX_MSG_MAP(CMydebugApp)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMydebugApp construction

CMydebugApp::CMydebugApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMydebugApp object

CMydebugApp theApp;

extern char f[200]="";//待解释执行的源文件名


extern "C" _declspec(dllexport) void interpret(char *file){
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	strcpy(f,file);
	COutput dlg;
	dlg.DoModal();

}
