// mycompiler.h : main header file for the MYCOMPILER DLL
//

#if !defined(AFX_MYCOMPILER_H__EE085EA5_D17D_4BA8_BAE5_B4301D126750__INCLUDED_)
#define AFX_MYCOMPILER_H__EE085EA5_D17D_4BA8_BAE5_B4301D126750__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "datastructure.h"
#include "resource.h"		// main symbols
#define MyExport   _declspec(dllexport)

/////////////////////////////////////////////////////////////////////////////
// CMycompilerApp
// See mycompiler.cpp for the implementation of this class
//
extern "C" MyExport bool canexe;           //是否可以解释执行p代码
/*extern "C" MyExport int lc;                //指令数组的当前索引
extern "C" MyExport int t,a,b,sx,c1,c2;    //各种表格的索引
extern "C" MyExport int display[lmax];     //分程序索引表
extern "C" MyExport table tab[tmax+1];     //符号表   
extern "C" MyExport btable btab[bmax+1];   //分程序表
extern "C" MyExport char stab[smax+1];     //字符串常量数组
extern "C" MyExport double rconst[c2max];  //实常量数组
extern "C" MyExport order code[cmax+1];    //p代码数组*/
extern "C" _declspec(dllexport)  int compiler(char *file);
class CMycompilerApp : public CWinApp
{
public:
	CMycompilerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMycompilerApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMycompilerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOMPILER_H__EE085EA5_D17D_4BA8_BAE5_B4301D126750__INCLUDED_)
