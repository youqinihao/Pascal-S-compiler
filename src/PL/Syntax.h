#if !defined(AFX_SYNTAX_H__A5C3EB81_D720_44C8_A7DD_473DE8419909__INCLUDED_)
#define AFX_SYNTAX_H__A5C3EB81_D720_44C8_A7DD_473DE8419909__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Syntax.h : header file
// 新增加文法显示对话框

/////////////////////////////////////////////////////////////////////////////
// CSyntax dialog

class CSyntax : public CDialog
{
// Construction
public:
	CSyntax(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSyntax)
	enum { IDD = IDD_DIALOG3 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSyntax)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSyntax)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNTAX_H__A5C3EB81_D720_44C8_A7DD_473DE8419909__INCLUDED_)
