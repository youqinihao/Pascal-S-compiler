// showkw.h : main header file for the SHOWKW DLL
//

#if !defined(AFX_SHOWKW_H__201CE42B_8E27_4521_8DF7_D271D9B20584__INCLUDED_)
#define AFX_SHOWKW_H__201CE42B_8E27_4521_8DF7_D271D9B20584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowkwApp
// See showkw.cpp for the implementation of this class
//
extern "C" _declspec(dllexport) void ShowKeyword(CRichEditCtrl &richedit,CHARFORMAT &cf,CHARFORMAT &cfm,CHARFORMAT &cfm1);
class CShowkwApp : public CWinApp
{
public:
	CShowkwApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowkwApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CShowkwApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWKW_H__201CE42B_8E27_4521_8DF7_D271D9B20584__INCLUDED_)
