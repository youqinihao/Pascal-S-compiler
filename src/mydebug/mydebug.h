// mydebug.h : main header file for the MYDEBUG DLL
//

#if !defined(AFX_MYDEBUG_H__408C5D3E_FE02_4165_89BD_C4BB047FF877__INCLUDED_)
#define AFX_MYDEBUG_H__408C5D3E_FE02_4165_89BD_C4BB047FF877__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMydebugApp
// See mydebug.cpp for the implementation of this class
//
extern "C" _declspec(dllexport) void interpret(char *file);
class CMydebugApp : public CWinApp
{
public:
	CMydebugApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMydebugApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMydebugApp)
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDEBUG_H__408C5D3E_FE02_4165_89BD_C4BB047FF877__INCLUDED_)
