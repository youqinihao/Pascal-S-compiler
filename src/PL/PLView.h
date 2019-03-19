// PLView.h : interface of the CPLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLVIEW_H__F5A36CD2_FB88_4A89_9AE1_44B0B3F23874__INCLUDED_)
#define AFX_PLVIEW_H__F5A36CD2_FB88_4A89_9AE1_44B0B3F23874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PLDoc.h"

class CPLCntrItem;

class CPLView : public CRichEditView
{
protected: // create from serialization only
	CPLView();
	DECLARE_DYNCREATE(CPLView)

// Attributes
public:
	CPLDoc* GetDocument();
  
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CHARFORMAT cfm1;
	void ShowKey();
	CHARFORMAT cfm;
	CHARFORMAT cf;
	void ShowLine();
	virtual ~CPLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPLView)
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMenuitemcom();
	afx_msg void OnMenuitemexe();
	afx_msg void OnMenuitemdebug();
	afx_msg void OnUpdateMenuitemexe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuitemdebug(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	bool canexe;
};

#ifndef _DEBUG  // debug version in PLView.cpp
inline CPLDoc* CPLView::GetDocument()
   { return (CPLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLVIEW_H__F5A36CD2_FB88_4A89_9AE1_44B0B3F23874__INCLUDED_)
