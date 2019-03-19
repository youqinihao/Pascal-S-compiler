// PLDoc.h : interface of the CPLDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLDOC_H__64D97981_39D2_4702_86AD_6A16C7A93552__INCLUDED_)
#define AFX_PLDOC_H__64D97981_39D2_4702_86AD_6A16C7A93552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPLDoc : public CRichEditDoc
{
protected: // create from serialization only
	CPLDoc();
	DECLARE_DYNCREATE(CPLDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CPLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPLDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLDOC_H__64D97981_39D2_4702_86AD_6A16C7A93552__INCLUDED_)
