#if !defined(AFX_ERROR_H__0E826805_B395_4550_A3DE_9A9D7724FB72__INCLUDED_)
#define AFX_ERROR_H__0E826805_B395_4550_A3DE_9A9D7724FB72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Error.h : header file
//错误信息管理类

#include<stdio.h>
#define errmax 59

/////////////////////////////////////////////////////////////////////////////
// CError command target

class CError : public CCmdTarget
{
	DECLARE_DYNCREATE(CError)

	CError();           // protected constructor used by dynamic creation

// Attributes
public:
	void error(int line,int err);  //登陆错误信息
	int Number() {
		return num;
		}
	void Disp(){                   //打印错误信息到文件
		FILE *fp=fopen("error.txt","w");
		fprintf(fp,"\n------------------------- Welcome to PL! -------------------------\n");
		printf("\n------------------------- Welcome to PL! -------------------------\n");
		if(num==0){
            fprintf(fp,"\n**********No Error!**********\n");
			 printf("\n**********No Error!**********\n");
		}
		else
		{
			fprintf(fp,"\nThere are %d errors!\n",num);
			printf("\nThere are %d errors!\n",num);
			for(int i=0;i<num;i++){
	    fprintf(fp,"Line No. %d: Error No. %d: %s\n",lines[i],errors[i],err[errors[i]]);
		 printf("Line No. %d: Error No. %d: %s\n",lines[i],errors[i],err[errors[i]]);
			}
		}
		if(fp)
		  fclose(fp);
	}
private:
	int errors[errmax]; //错误编号
	char *err[errmax];  //错误信息
	int lines[errmax];  //记录出现错误的行号
public:   int num;      //当前错误数
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CError)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CError();

	// Generated message map functions
	//{{AFX_MSG(CError)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERROR_H__0E826805_B395_4550_A3DE_9A9D7724FB72__INCLUDED_)
