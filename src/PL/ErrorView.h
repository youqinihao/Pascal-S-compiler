#if !defined(AFX_ERRORVIEW_H__00AE3303_AB73_4E03_BF20_265FA901EC12__INCLUDED_)
#define AFX_ERRORVIEW_H__00AE3303_AB73_4E03_BF20_265FA901EC12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorView.h : header file
//´íÎóÊä³ö´°¿Ú

/////////////////////////////////////////////////////////////////////////////
// CErrorView view

class CErrorView : public CEditView
{
protected:
	CErrorView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CErrorView)

// Attributes
public:

// Operations
public:
	void ShowError(FILE *fp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CErrorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CErrorView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORVIEW_H__00AE3303_AB73_4E03_BF20_265FA901EC12__INCLUDED_)
