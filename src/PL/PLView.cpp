// PLView.cpp : implementation of the CPLView class
//

#include "stdafx.h"
#include "PL.h"

#include "PLDoc.h"
#include "CntrItem.h"
#include "PLView.h"
#include "MainFrm.h"
#include "RichEdit.h"
#include "ErrorView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPLView

IMPLEMENT_DYNCREATE(CPLView, CRichEditView)

BEGIN_MESSAGE_MAP(CPLView, CRichEditView)
	//{{AFX_MSG_MAP(CPLView)
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MENUITEMCOM, OnMenuitemcom)
	ON_COMMAND(ID_MENUITEMEXE, OnMenuitemexe)
	ON_COMMAND(ID_MENUITEMDEBUG, OnMenuitemdebug)
	ON_UPDATE_COMMAND_UI(ID_MENUITEMEXE, OnUpdateMenuitemexe)
	ON_UPDATE_COMMAND_UI(ID_MENUITEMDEBUG, OnUpdateMenuitemdebug)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLView construction/destruction

CPLView::CPLView()
{
	// TODO: add construction code here
    canexe=false;
	cf.cbSize=sizeof(CHARFORMAT);   
    cf.dwMask=CFM_COLOR;   
    cf.dwEffects=~(CFE_AUTOCOLOR);  
    cf.crTextColor=RGB(0,0,255);
	cfm.cbSize=sizeof(CHARFORMAT);   
    cfm.dwMask=CFM_COLOR;   
    cfm.dwEffects=~(CFE_AUTOCOLOR);  
    cfm.crTextColor=RGB(0,0,0);
	cfm1.cbSize=sizeof(CHARFORMAT);   
    cfm1.dwMask=CFM_COLOR;   
    cfm1.dwEffects=~(CFE_AUTOCOLOR);  
    cfm1.crTextColor=RGB(42,163,60);
}

CPLView::~CPLView()
{
}

BOOL CPLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CPLView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();
	CRichEditCtrl &richedit=this->GetRichEditCtrl();
	richedit.HideSelection(true,false);
    ShowKey();
	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
	
}

/////////////////////////////////////////////////////////////////////////////
// CPLView printing

BOOL CPLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CPLView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CPLView diagnostics

#ifdef _DEBUG
void CPLView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CPLView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CPLDoc* CPLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPLDoc)));
	return (CPLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPLView message handlers

void CPLView::ShowLine()
{
	long  nStartChar,nEndChar,lineNo;
	CString line;
	CMainFrame*pFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CRichEditCtrl &edit=this->GetRichEditCtrl();
	edit.GetSel(nStartChar,nEndChar);
	lineNo=edit.LineFromChar(nEndChar);
	line.Format("当前为第%d行",lineNo+1);
	
	pFrame->m_wndStatusBar.SetPaneText(pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOTOR_LINE),line);

}

void CPLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//显示当前插入的行号
	ShowLine();
	CRichEditView::OnMouseMove(nFlags, point);
}

void CPLView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//显示当前插入的行号
	ShowLine();  
	CRichEditView::OnChar(nChar, nRepCnt, nFlags);
	CRichEditCtrl &richedit=this->GetRichEditCtrl();
	richedit.HideSelection(true,false);
	ShowKey();	
	
	//以下为无用代码
	/*CToolBar  &toolBar=((CMainFrame*)AfxGetMainWnd())->m_wndToolBar;
    CRect rect;
	toolBar.GetClientRect(&rect);
	CStatic s;
	s.Create("youqi",WS_CHILD|WS_VISIBLE,rect,&toolBar,0);
	toolBar.SetBorders(&rect);
	CDC *dc=toolBar.GetDC();
	dc->TextOut(10,10,"youqinihao");
	CRect rect;CBrush *pOldBrush,NewBrush(RGB(0,0,255));
	pOldBrush=dc->SelectObject(&NewBrush);
	toolBar.GetClientRect(&rect);
	dc->FillRect(rect,&NewBrush);
	dc->SelectObject(pOldBrush);
	NewBrush.DeleteObject();*/
}

void CPLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//显示当前插入的行号
	ShowLine();
	CRichEditCtrl &richedit=this->GetRichEditCtrl();
	richedit.HideSelection(false,false);
	CRichEditView::OnLButtonDown(nFlags, point);

}

void CPLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//显示当前插入的行号
	ShowLine();
	CRichEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPLView::OnMenuitemcom() 
{
	// TODO: Add your command handler code here

	//响应用户的编译命令
	CPLDoc *doc=this->GetDocument();
	CString FilePath=doc->GetPathName();
	canexe=false;
	if(FilePath.IsEmpty())
	{
		AfxMessageBox("文件未保存!");
		canexe=false;
		return;
		//FilePath=((CPLApp*)AfxGetApp())->ExePath()+"\\"+doc->GetTitle();
		
	}
	
	doc->OnSaveDocument(FilePath);
	char filepath[200];
	sprintf(filepath,"%s",FilePath);

	typedef int (*pMyFun)(char *file);
	HINSTANCE hDll;
	pMyFun compiler;
	hDll=::LoadLibrary("mycompiler.dll");
    compiler=(pMyFun)GetProcAddress(hDll,"compiler");
	if(compiler==NULL)
		return;
    if(!compiler(filepath))
		canexe=true;
	FreeLibrary(hDll);
	POSITION p=doc->GetFirstViewPosition();

    CErrorView *err=(CErrorView *)doc->GetNextView(p);
    FILE *fp=fopen("error.txt","r");
   	err->ShowError(fp);
    if(fp)
	 	fclose(fp);
	doc->SetModifiedFlag(false);
}
void CPLView::OnMenuitemexe() 
{
	// TODO: Add your command handler code here
	//解释执行用户程序
	CPLDoc *doc=this->GetDocument();

    if(doc->IsModified())
	{
		int value=AfxMessageBox("文档有改动,是否编译后再执行?",MB_YESNOCANCEL,0);
		if(value==IDYES)
		{
			OnMenuitemcom();
		}
		else if(value==IDCANCEL)
			return ;
	}
	if(!canexe)
		return;
	CString FilePath=doc->GetPathName();
	char filepath[200];
	char cmdline[300];
	sprintf(filepath,"%s",FilePath);
	strcat(filepath,".bpl\"");
	strcpy(cmdline,"startinterpret.exe  ");
	strcat(cmdline,"\"");
	strcat(cmdline,filepath);
    WinExec(cmdline,SW_SHOW);
	
}


void CPLView::OnMenuitemdebug() 
{
	// TODO: Add your command handler code here
		//调试执行用户程序
	
	CPLDoc *doc=this->GetDocument();
	
    if(doc->IsModified())
	{
		int value=AfxMessageBox("文档有改动,是否编译后再执行?",MB_YESNOCANCEL,0);
		if(value==IDYES)
		{
			OnMenuitemcom();
		}
		else if(value==IDCANCEL)
			return ;
	}
	if(!canexe)
		return;
	CString FilePath=doc->GetPathName();
	if(FilePath.IsEmpty())
	{
		AfxMessageBox("文件未保存!");
	//	FilePath=((CPLApp*)AfxGetApp())->ExePath()+"\\"+doc->GetTitle();
		return;
	}
	doc->OnSaveDocument(FilePath);
	char filepath[200];
	sprintf(filepath,"%s",FilePath);
//	strcat(filepath,".bpl");
	typedef void (*pMyFun)(char *file);
	HINSTANCE hDll;
	pMyFun interpret;
	hDll=::LoadLibrary("mydebug.dll");
    interpret=(pMyFun)GetProcAddress(hDll,"interpret");
	if(interpret==NULL)
		return;
    interpret(filepath);
	FreeLibrary(hDll);
	POSITION p=doc->GetFirstViewPosition();
    doc->GetNextView(p);
    CErrorView *err=(CErrorView *)doc->GetNextView(p);
    FILE *fp=fopen("error.txt","r");
   	err->ShowError(fp);
    if(fp)
	 	fclose(fp);
}

void CPLView::OnUpdateMenuitemexe(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable(canexe);
}

void CPLView::OnUpdateMenuitemdebug(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable(canexe);
}



void CPLView::ShowKey()
{
    CRichEditCtrl &richedit=this->GetRichEditCtrl();
	typedef int (*pMyFun)(CRichEditCtrl &richeidt,CHARFORMAT &cf,CHARFORMAT &cfm,CHARFORMAT &cfm1);
	HINSTANCE hDll;
	pMyFun ShowKeyword;
	hDll=::LoadLibrary("showkw.dll");
    ShowKeyword=(pMyFun)GetProcAddress(hDll,"ShowKeyword");
	if(ShowKeyword==NULL)
		return;
    ShowKeyword(richedit,cf,cfm,cfm1);
	FreeLibrary(hDll);
}

void CPLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CRichEditView::OnLButtonUp(nFlags, point);
}
