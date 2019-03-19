// PL.h : main header file for the PL application
//

#if !defined(AFX_PL_H__386FC436_4BC6_49FF_B650_3480DCEDB81D__INCLUDED_)
#define AFX_PL_H__386FC436_4BC6_49FF_B650_3480DCEDB81D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPLApp:
// See PL.cpp for the implementation of this class
//

class CPLApp : public CWinApp
{
public:
	CPLApp();
public:
	CString GetPtPath(int CSIDL);
	CString ExePath();
	bool CreatLink(LPSTR szPath,LPSTR szLink);
	void SetPLBkColor();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPLApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PL_H__386FC436_4BC6_49FF_B650_3480DCEDB81D__INCLUDED_)
