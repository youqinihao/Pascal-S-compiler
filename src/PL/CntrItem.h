// CntrItem.h : interface of the CPLCntrItem class
//

#if !defined(AFX_CNTRITEM_H__DF13EB25_55A2_437B_93F6_5306622BFF94__INCLUDED_)
#define AFX_CNTRITEM_H__DF13EB25_55A2_437B_93F6_5306622BFF94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPLDoc;
class CPLView;

class CPLCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CPLCntrItem)

// Constructors
public:
	CPLCntrItem(REOBJECT* preo = NULL, CPLDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CPLDoc* GetDocument()
		{ return (CPLDoc*)CRichEditCntrItem::GetDocument(); }
	CPLView* GetActiveView()
		{ return (CPLView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CPLCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__DF13EB25_55A2_437B_93F6_5306622BFF94__INCLUDED_)
