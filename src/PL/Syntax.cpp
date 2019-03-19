// Syntax.cpp : implementation file
//

#include "stdafx.h"
#include "pl.h"
#include "Syntax.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyntax dialog


CSyntax::CSyntax(CWnd* pParent /*=NULL*/)
	: CDialog(CSyntax::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSyntax)
	//}}AFX_DATA_INIT
}


void CSyntax::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSyntax)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSyntax, CDialog)
	//{{AFX_MSG_MAP(CSyntax)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyntax message handlers

void CSyntax::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	int nHeight=rect.Height();
	int nWidth=rect.Width();
	int i;
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(100,100,25));
	CPen *pOldPen=dc.SelectObject(&pen);
	for(i=15;i<20;i++){
      	dc.MoveTo(0+i,0+i);
		dc.LineTo(i,nHeight-i);
		dc.LineTo(nWidth-i,nHeight-i);
		dc.LineTo(nWidth-i,i);
		dc.LineTo(i,i);
	}
	dc.SelectObject(pOldPen);
	pen.DeleteObject();

	// Do not call CDialog::OnPaint() for painting messages
}
