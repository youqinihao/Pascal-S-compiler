#if !defined(AFX_INPUT_H__A294D541_F6D3_4083_B72D_69EA950D5755__INCLUDED_)
#define AFX_INPUT_H__A294D541_F6D3_4083_B72D_69EA950D5755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
// Input.h : header file
//用户程序数据输入窗口

/////////////////////////////////////////////////////////////////////////////
// CInput dialog

class CInput : public CDialog
{
// Construction
public:
	CInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInput)
	enum { IDD = IDD_DIALOG1 };
	CString	m_szData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUT_H__A294D541_F6D3_4083_B72D_69EA950D5755__INCLUDED_)
