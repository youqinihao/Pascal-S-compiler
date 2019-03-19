// CntrItem.cpp : implementation of the CPLCntrItem class
//

#include "stdafx.h"
#include "PL.h"

#include "PLDoc.h"
#include "PLView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPLCntrItem implementation

IMPLEMENT_SERIAL(CPLCntrItem, CRichEditCntrItem, 0)

CPLCntrItem::CPLCntrItem(REOBJECT* preo, CPLDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CPLCntrItem::~CPLCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CPLCntrItem diagnostics

#ifdef _DEBUG
void CPLCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CPLCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
