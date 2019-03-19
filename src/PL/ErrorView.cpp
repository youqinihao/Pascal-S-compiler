// ErrorView.cpp : implementation file
//

#include "stdafx.h"
#include "PL.h"
#include "ErrorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorView

IMPLEMENT_DYNCREATE(CErrorView, CEditView)

CErrorView::CErrorView()
{
}

CErrorView::~CErrorView()
{
}


BEGIN_MESSAGE_MAP(CErrorView, CEditView)
	//{{AFX_MSG_MAP(CErrorView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorView drawing

void CErrorView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CErrorView diagnostics

#ifdef _DEBUG
void CErrorView::AssertValid() const
{
	CEditView::AssertValid();
}

void CErrorView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CErrorView message handlers

void CErrorView::ShowError(FILE *fp)
{
	   int i;
	   if(!fp)
		   return;
	    char buffer[200];
        CEdit & error=GetEditCtrl();
		SetWindowText("");
		error.SetFocus();
		error.SetSel(0,0);
		while(fgets(buffer,200,fp)!=NULL)
		{   
			for(i=0;buffer[i]!='\0';++i)
				if(buffer[i]=='\r'||buffer[i]=='\n')
					buffer[i]='\0';
			error.ReplaceSel((LPCTSTR)buffer);
			error.ReplaceSel("\r\n");
		}
}
