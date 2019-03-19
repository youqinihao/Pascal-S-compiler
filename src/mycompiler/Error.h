#if !defined(AFX_ERROR_H__0E826805_B395_4550_A3DE_9A9D7724FB72__INCLUDED_)
#define AFX_ERROR_H__0E826805_B395_4550_A3DE_9A9D7724FB72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Error.h : header file
//������Ϣ������

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
	void error(int line,int err);  //��½������Ϣ
	int Number() {
		return num;
		}
	void Disp(){                   //��ӡ������Ϣ���ļ�
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
	int errors[errmax]; //������
	char *err[errmax];  //������Ϣ
	int lines[errmax];  //��¼���ִ�����к�
public:   int num;      //��ǰ������
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
