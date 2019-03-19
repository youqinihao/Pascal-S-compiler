// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mydebug.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	ON_WM_CANCELMODE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

BOOL CInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_Info.SetWindowText(info);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInfoDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CInfoDlg::OnPaint() 
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
