// PLDoc.cpp : implementation of the CPLDoc class
//

#include "stdafx.h"
#include "PL.h"

#include "PLDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPLDoc

IMPLEMENT_DYNCREATE(CPLDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CPLDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CPLDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLDoc construction/destruction

CPLDoc::CPLDoc()
{
	// TODO: add one-time construction code here

}

CPLDoc::~CPLDoc()
{
}

BOOL CPLDoc::OnNewDocument()
{
	//设置新建文档的默认标题
	this->SetTitle("mypl.p");
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;
    //设定新建源程序的默认代码
    //CString init="const x=999999.8888,y=3333333.333;\r\nvar i:real;j:integer;\r\nfunction add(x,y:integer):integer;\r\nbegin\r\nadd:=x+y;\r\nend;\r\nbegin\r\n  read(i,j);\r\n  write(i);\r\n  write(add(j,j));\r\n  write(x);\r\n  j:=0;\r\n  do\r\n  begin\r\n   write(\"hello,world!\");\r\n   j:=j+1;\r\n end while j<5;\r\n if j=5\r\n then  write(\"youqi\",i);\r\nend.";
	CString init="//This is a program framework.\r\nconst c=9999.9999;//常量定义\r\ntype t=array [0:100] of integer;//数组类型定义\r\n        r=record r:integer end;//记录类型定义\r\nvar v:integer;//变量定义\r\nprocedure p(i:integer);//过程定义\r\nbegin\r\nend;\r\nfunction f(p:integer):integer;//函数定义\r\nbegin\r\n  f:=0;\r\nend;\r\nbegin       //主程序\r\n  write(\"hello,world!\");\r\nend.\r\n";
	GetView()->GetRichEditCtrl().SetWindowText(init); 

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
    
	return TRUE;
}

CRichEditCntrItem* CPLDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CPLCntrItem(preo, (CPLDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CPLDoc serialization

void CPLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::m_bRTF = FALSE;
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPLDoc diagnostics

#ifdef _DEBUG
void CPLDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CPLDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPLDoc commands
