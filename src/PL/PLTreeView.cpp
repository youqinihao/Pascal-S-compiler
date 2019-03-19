// PLTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "PL.h"
#include "PLTreeView.h"
#include "PLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPLTreeView

IMPLEMENT_DYNCREATE(CPLTreeView, CView)

CPLTreeView::CPLTreeView()
{
	isInit=false;
	
}

CPLTreeView::~CPLTreeView()
{
}


BEGIN_MESSAGE_MAP(CPLTreeView, CView)
	//{{AFX_MSG_MAP(CPLTreeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLTreeView drawing

void CPLTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	CRect rect;
	GetClientRect(&rect);
	m_tree.MoveWindow(&rect);
}

/////////////////////////////////////////////////////////////////////////////
// CPLTreeView diagnostics

#ifdef _DEBUG
void CPLTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CPLTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPLTreeView message handlers

void CPLTreeView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	if(!isInit){
	CRect rect;
	GetClientRect(rect);
	m_ImgList.Create(IDB_BITMAP1,20,1,RGB(0,0,0));
    m_tree.Create(TVS_LINESATROOT |TVS_HASBUTTONS|TVS_HASLINES|TVS_SHOWSELALWAYS ,rect,this,IDC_TREE1);
	m_tree.SetImageList(&m_ImgList,TVSIL_NORMAL);
	//m_tree.SetTextColor(RGB(200,0,60));
	HTREEITEM hItem,hSubItem;
    hItem = m_tree.InsertItem("Sort",TVI_ROOT);
    hSubItem = m_tree.InsertItem("bubblesort",hItem);
    hSubItem = m_tree.InsertItem("insertionsort",hItem,hSubItem);
    hSubItem = m_tree.InsertItem("selectsort",hItem,hSubItem);
	hSubItem = m_tree.InsertItem("shellsort",hItem,hSubItem);
	hSubItem = m_tree.InsertItem("quicksort",hItem,hSubItem);
	hSubItem = m_tree.InsertItem("stringsort",hItem,hSubItem);
    hItem = m_tree.InsertItem("Example",TVI_ROOT,hItem);  
	hSubItem = m_tree.InsertItem("magic",hItem);
    hSubItem = m_tree.InsertItem("queen",hItem,hSubItem);
    hSubItem = m_tree.InsertItem("reccurresive",hItem,hSubItem);
	hSubItem = m_tree.InsertItem("multi",hItem,hSubItem);
    hSubItem = m_tree.InsertItem("record",hItem,hSubItem);
    hItem = m_tree.InsertItem("ErrorExample",TVI_ROOT,hItem); 
	hSubItem = m_tree.InsertItem("errortest_1",hItem);
    hSubItem = m_tree.InsertItem("errortest_2",hItem,hSubItem);
    hSubItem = m_tree.InsertItem("errortest_3",hItem,hSubItem);
	hSubItem = m_tree.InsertItem("errortest_4",hItem,hSubItem);
    hSubItem = m_tree.InsertItem("errortest_5",hItem,hSubItem);
	isInit=true;
	m_tree.ShowWindow(SW_SHOW);
	}
}
void CPLTreeView::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{

	// TODO: Add your control notification handler code here
    NM_TREEVIEW *pNMTreeView=(NM_TREEVIEW*)pNMHDR;
	CString root=((CPLApp*)AfxGetApp())->ExePath();
	HTREEITEM m_hSelect=m_tree.GetSelectedItem( );
	CString name=m_tree.GetItemText(m_hSelect);
	if(strcmp(name,"Example")==NULL)
		return;
	if(strcmp(name,"Sort")==NULL)
		return;
	if(strcmp(name,"ErrorExample")==NULL)
		return;
	CString code="\\code\\";
	root=root+code+name;
	code=".p";
	root=root+code;
	CDocument *doc=this->GetDocument();
	doc->OnOpenDocument(root);
	POSITION p=doc->GetFirstViewPosition();
	doc->GetNextView(p);
	doc->GetNextView(p);
	CPLView *rich=(CPLView*)doc->GetNextView(p);
	CRichEditCtrl &richedit=rich->GetRichEditCtrl();
	richedit.HideSelection(true,false);
    rich->ShowKey();
	*pResult = 0;
}
