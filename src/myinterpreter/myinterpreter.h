// myinterpreter.h : main header file for the MYINTERPRETER DLL
//

#if !defined(AFX_MYINTERPRETER_H__C4CE3D45_63FE_4E28_A742_F1C3DC3EBBF2__INCLUDED_)
#define AFX_MYINTERPRETER_H__C4CE3D45_63FE_4E28_A742_F1C3DC3EBBF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyinterpreterApp
// See myinterpreter.cpp for the implementation of this class
//
extern "C" _declspec(dllexport)  void interpreter(char *file);
class CMyinterpreterApp : public CWinApp
{
public:
	CMyinterpreterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyinterpreterApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMyinterpreterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYINTERPRETER_H__C4CE3D45_63FE_4E28_A742_F1C3DC3EBBF2__INCLUDED_)
