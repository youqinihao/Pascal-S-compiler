#if !defined(AFX_PLTREEVIEW_H__69612D9C_A039_4AE2_8F26_4705535DD903__INCLUDED_)
#define AFX_PLTREEVIEW_H__69612D9C_A039_4AE2_8F26_4705535DD903__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PLTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPLTreeView view

class CPLTreeView : public CView
{
protected:
	CPLTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPLTreeView)

// Attributes
public:

// Operations
public:
	bool isInit;
	CImageList m_ImgList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPLTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPLTreeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
private:
	CTreeCtrl m_tree;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLTREEVIEW_H__69612D9C_A039_4AE2_8F26_4705535DD903__INCLUDED_)
