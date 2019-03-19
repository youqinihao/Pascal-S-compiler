// showkw.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "showkw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CShowkwApp

BEGIN_MESSAGE_MAP(CShowkwApp, CWinApp)
	//{{AFX_MSG_MAP(CShowkwApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowkwApp construction

CShowkwApp::CShowkwApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShowkwApp object

CShowkwApp theApp;
extern "C" _declspec(dllexport) void ShowKeyword(CRichEditCtrl &richedit,CHARFORMAT &cf,CHARFORMAT &cfm,CHARFORMAT &cfm1){
	CString str;
	CString key[22]={"integer","real","char","begin","end","const","div","do","downto","else","for","function","if","procedure","then","to","var","while","of","record","array","type"};
    long len;
	short n;	
	long nStartChar,nEndChar;
	richedit.GetSel(nStartChar,nEndChar);
	richedit.GetWindowText(str);
	len=str.GetLength();
	richedit.SetSel(0,len);
	richedit.SetSelectionCharFormat(cfm);
	richedit.HideSelection(true,false);
	int i=0,j=0;
	while(j<22){
		n=key[j].GetLength();
		i=0;
	do{
	
		i=str.Find(key[j],i);
		
		if(i==-1)
			break;
		if(len==n)
		{
		richedit.SetSel(i,i+ n);
		richedit.SetSelectionCharFormat(cf);
			}
		else if(len>n)
		{
		if(i==0&&!isalnum(str.GetAt(n))||i+n==len&&!isalnum(str.GetAt(i-1)))
		{
		richedit.SetSel(i,i+n);
		richedit.SetSelectionCharFormat(cf);
		}
	    else if(!isalnum(str.GetAt(i-1))&&!isalnum(str.GetAt(i+n))){
		richedit.SetSel(i,i+n);
		richedit.SetSelectionCharFormat(cf);
		}
		}
		i=i+n;
	}while(i<len);	
     ++j;
	}
	i=0; j=0;              //¸ßÁÁÏÔÊ¾×¢ÊÍÐÐ
	do{
		i=str.Find("//",i);
		if(i!=-1){
		j=str.Find("\n",i);
		if(j==-1){
			j=len;
		}
		richedit.SetSel(i,j);
		richedit.SetSelectionCharFormat(cfm1);
		}
		else
			break;
		i=j;
	}while(i<len);
	richedit.HideSelection(false,true);
	richedit.SetSel(nStartChar,nEndChar);
    
	richedit.SetSelectionCharFormat(cfm);

}