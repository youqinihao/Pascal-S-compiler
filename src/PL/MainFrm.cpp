// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PL.h"

#include "MainFrm.h"
#include "PLView.h"
#include "ErrorView.h"
#include "PLTreeView.h"
#include "Syntax.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM32789, OnMenuitemBk)
	ON_COMMAND(ID_MENUITEM32785, OnMenuitem32785)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_YOUQI,OnYOUQI)  
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOTOR_LINE,
	ID_INDICATOR_CLOCK,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
   //	HICON m_ico;   
   // m_ico=AfxGetApp()->LoadIcon(IDI_ICON11);	
	m_wndToolBar.SetButtonText(0,"�½�");
	m_wndToolBar.SetButtonText(1,"��");
	m_wndToolBar.SetButtonText(3,"����");
	m_wndToolBar.SetButtonText(5,"����");
	m_wndToolBar.SetButtonText(7,"����");
	m_wndToolBar.SetButtonText(8,"ճ��");
	m_wndToolBar.SetButtonText(10,"��ӡ");
	m_wndToolBar.SetButtonText(12,"����");
	m_wndToolBar.SetButtonText(14,"����");
	m_wndToolBar.SetButtonText(16,"ִ��");
	m_wndToolBar.SetButtonText(18,"����");
	m_wndToolBar.SetSizes(CSize(48,42),CSize(36,18));
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

  

	SetTimer(1,1000,NULL);    //����״̬��ʱ����ʾ
    
	//�����������ͼ��
	 NOTIFYICONDATA   tnd;     
     tnd.cbSize=sizeof(NOTIFYICONDATA);   
     tnd.hWnd=this->m_hWnd;   
     tnd.uID=IDR_MAINFRAME;   
     tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;   
     tnd.uCallbackMessage=WM_YOUQI;   
     tnd.hIcon=LoadIcon(AfxGetInstanceHandle(),   
       MAKEINTRESOURCE(IDR_MAINFRAME));     
     strcpy(tnd.szTip,"��ӭʹ����չPL/0������");   
     Shell_NotifyIcon(NIM_ADD,&tnd);   


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
		// create splitter window//����Ӵ���
   	CRect rect;
	GetClientRect(rect);

     if (!m_wndSplitter.CreateStatic(this, 2, 1))
             return FALSE;
      if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CErrorView),
		       CSize(0, 0), pContext))
	  {


	  }

      if(!m_wndSplitter2.CreateStatic(&m_wndSplitter, 1, 2,
	      WS_CHILD | WS_VISIBLE | WS_BORDER,m_wndSplitter.IdFromRowCol(0, 0)))
	  {

	  }

      if(!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CPLTreeView), 
		  CSize(150, 0), pContext))
	  {
 
	  }

      if(!m_wndSplitter2.CreateView(0, 1, RUNTIME_CLASS(CPLView),
		  CSize(0, 0), pContext))
	  {

	  }
      m_wndSplitter.SetRowInfo(0,rect.bottom,0 );
	  m_wndSplitter.RecalcLayout(); 
	 return true; 
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
		//�ر�״̬��ͼ�����ʾ
	KillTimer(1);
	NOTIFYICONDATA   tnid;   
    tnid.cbSize=sizeof(NOTIFYICONDATA);   
    tnid.hWnd=this->m_hWnd;   
    tnid.uID=IDR_MAINFRAME;//��֤ɾ���������ǵ�ͼ��   
    Shell_NotifyIcon(NIM_DELETE,&tnid);     
	CFrameWnd::OnClose();
}
//Ϊ��ʾ������ͼ����Զ������Ϣ��Ӧ����
void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	 //��״̬����ʾ��ǰʱ��
	CTime time;
	time=CTime::GetCurrentTime();
	CString s=time.Format("%H:%M:%S");
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_CLOCK),s);
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnYOUQI(WPARAM wParam, LPARAM lParam)
{
            UINT   uID;//��������Ϣ��ͼ���ID   
            UINT   uMouseMsg;//��궯��   
            uID=(UINT)wParam;   
            uMouseMsg=(UINT)lParam; 
            if(uMouseMsg==WM_RBUTTONDOWN)//����ǵ����Ҽ�   
            {   
                 switch(uID)   
                {   
                    case   IDR_MAINFRAME://��������ǵ�ͼ��  
					     	
						   ShowWindow(SW_SHOWMAXIMIZED); 

				    break;    
                }   
            }   
            return;     
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message==WM_SYSCOMMAND&&wParam==SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
		//�ػ���С����Ϣ�������ش���
	    return true;
	}
	
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnMenuitemBk() 
{
	// TODO: Add your command handler code here
	((CPLApp*)AfxGetApp())->SetPLBkColor();
}

void CMainFrame::OnMenuitem32785() 
{
	// TODO: Add your command handler code here
	//�������ķ���Ϣ��ʾ�Ի���
	CSyntax dlg;
	dlg.DoModal();
}
