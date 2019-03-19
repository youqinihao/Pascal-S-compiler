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
extern "C" MyExport bool canexe;           //�Ƿ���Խ���ִ��p����
/*extern "C" MyExport int lc;                //ָ������ĵ�ǰ����
extern "C" MyExport int t,a,b,sx,c1,c2;    //���ֱ�������
extern "C" MyExport int display[lmax];     //�ֳ���������
extern "C" MyExport table tab[tmax+1];     //���ű�   
extern "C" MyExport btable btab[bmax+1];   //�ֳ����
extern "C" MyExport char stab[smax+1];     //�ַ�����������
extern "C" MyExport double rconst[c2max];  //ʵ��������
extern "C" MyExport order code[cmax+1];    //p��������*/
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
