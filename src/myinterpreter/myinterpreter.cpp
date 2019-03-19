// myinterpreter.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "myinterpreter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "datastructure.h"
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
// CMyinterpreterApp

BEGIN_MESSAGE_MAP(CMyinterpreterApp, CWinApp)
	//{{AFX_MSG_MAP(CMyinterpreterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyinterpreterApp construction

CMyinterpreterApp::CMyinterpreterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyinterpreterApp object

CMyinterpreterApp theApp;
int t,a,b,sx,c1,c2,lc;    //各种表格的索引
bool canexe;           //是否可以解释执行p代码
int display[lmax];     //分程序索引表
table tab[tmax+1];     //符号表   
btable btab[bmax+1];   //分程序表
char stab[smax+1];     //字符串常量数组
double rconst[c2max];  //实常量数组
order code[cmax+1];    //p代码数组
atable atab[amax+1];   //数组信息向量表
bool readbinary(char *file){
    char bfile[200];
	strcpy(bfile,file);
	FILE *fp=fopen(bfile,"rb");
	if(!fp){
		printf("文件名不对!\n");
		system("pause");
		return false;
	}
	fread(&t,sizeof(int),1,fp);
	
//	fscanf(fp,"%d",&t);
	fread(tab,sizeof(table),t+1,fp);
	fread(&b,sizeof(int),1,fp);
//	fscanf(fp,"%d",&b);
	fread(btab,sizeof(btable),b+1,fp);
	fread(&sx,sizeof(int),1,fp);
//	fscanf(fp,"%d",&sx);
	fread(stab,sizeof(char),sx+1,fp);
	fread(&c2,sizeof(int),1,fp);
//	fscanf(fp,"%d",&c2);
	fread(rconst,sizeof(double),c2+1,fp);
	fread(&lc,sizeof(int),1,fp);
//	fscanf(fp,"%d",&lc);
	fread(code,sizeof(order),lc+1,fp);
	fread(&a,sizeof(int),1,fp);
	fread(atab,sizeof(atable),a+1,fp);
	fclose(fp);
	return true;

}
extern "C" _declspec(dllexport) void interpreter(char *file){
   	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!readbinary(file)){
		printf("加载文件出错!\n");
		return;
	}
	order ir;
	int pc;
	int t;
	int b;
	int h1,h2,h3,h4;
	int lncnt,ocnt;
	enum p {run,fin,divchk,inxchk,stkchk,linchk,};
	int display[lmax];
    char temp;
	struct datastack{
		int i;
		double r;
	};
	datastack s[stacksize+1];
	p ps;

	s[1].i=0; s[2].i=0;
	s[3].i=-1;s[4].i=btab[1].last;
	display[1]=0;t=btab[2].vsize-1;
	b=0;         pc=tab[s[4].i].adr;
	lncnt=0;ocnt=0;
	ps=run;
	do{
		ir=code[pc];
		pc++;ocnt++;
		switch(ir.f){
		case 0:
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t].i=display[ir.x]+ir.y;
			break;
		case 1:
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t]=s[display[ir.x]+ir.y];
			break;
		case 2:;
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t]=s[s[display[ir.x]+ir.y].i];
			break;
		case 3:
			h1=ir.y;h2=ir.x;h3=b;
			do{
				display[h1]=h3;h1--;h3=s[h3+2].i;
			}while(h1!=h2);
			break;
		case 9:
			s[t].i=s[t].i+ir.y;
			break;
		case 10:
			pc=ir.y;
			break;
		case 11:
			if(!s[t].i)
				pc=ir.y;
			t--;
			break;
    	case 12:
			if(s[t].i)
				pc=ir.y;
			t--;
			break;
		case 14:
			h1=s[t-1].i;
			if(h1<=s[t].i){
				s[s[t-2].i].i=h1;
			}
			else
			{
				
				t=t-3;
				pc=ir.y;
			}
			break;
		case 15:
			h2=s[t-2].i;
			h1=s[h2].i+1;
			if(h1<=s[t].i)
			{
				s[h2].i=h1;pc=ir.y;
			}
			else
			{
				t=t-3;
			
			}
			break;
		case 16:
			h1=s[t-1].i;
			if(h1>=s[t].i)
			{
				s[s[t-2].i].i=h1;
			}
			else 
			{
				pc=ir.y;t=t-3;
			
			}
			break;
		case 17:
			h2=s[t-2].i;
			h1=s[h2].i-1;
			if(h1>=s[t].i)
			{
				s[h2].i=h1;pc=ir.y;
			}
			else
			{
				t=t-3;
			}
			break;
		case 18:
			h1=btab[tab[ir.y].ref].vsize;
			if(t+h1>stacksize)
				ps=stkchk;
			else
			{
				t=t+5;
				s[t-1].i=h1-1;s[t].i=ir.y;
			}
			break;
		case 19:
			h1=t-ir.y;
			h2=s[h1+4].i;
			h3=tab[h2].lev;
			display[h3+1]=h1;
			h4=s[h1+3].i+h1;
			s[h1+1].i=pc;
			s[h1+3].i=b;
			for(h3=t+1;h3<=h4;++h3)
				s[h3].i=0;
			b=h1;t=h4;
			pc=tab[h2].adr;
			break;
		case 20:
			h1=ir.y;
			h2=atab[h1].low;
			h3=s[t].i;
			if(h3<h2)
				ps=inxchk;
			else if(h3>atab[h1].high)
				ps=inxchk;
			else
			{
				--t;
				s[t].i+=h3-h2;
			}
			break;
		case 21:
        	h1=ir.y;
			h2=atab[h1].low;
			h3=s[t].i;
			if(h3<h2)
				ps=inxchk;
			else if(h3>atab[h1].high)
				ps=inxchk;
			else
			{
				--t;
				s[t].i+=(h3-h2)*atab[h1].elsize;
			}
			break;
		case 22:
			h1=s[t].i;t--;
			h2=ir.y+t;
			if(h2>stacksize)
				ps=stkchk;
			else
				while(t<h2){
					t++;
					s[t]=s[h1];h1++;
				}
				break;
		case 23:
			h1=s[t-1].i;
			h2=s[t].i;
			h3=h1+ir.y;
			while(h1<h3){
				s[h1]=s[h2];
				h1++;
				h2++;
			}
			t=t-2;
			break;
		case 24:
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t].i=ir.y;
			break;
		case 25:
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t].r=rconst[ir.y];
			break;
		case 26:
			h1=t-ir.y;
			s[h1].r=s[h1].i;
			break;
		case 27:
			switch(ir.y){
			case 1:
				scanf("%d",&s[s[t].i].i);
				break;
			case 2:
				scanf("%lf",&s[s[t].i].r);
				break;
			case 3:
				do{
					temp=getchar();
				}while(temp=='\n');
                s[s[t].i].i=(int)temp;
				break;

			}
			--t;
			break;
		case 28:
			h1=s[t].i;
			h2=ir.y;t--;
			if(h1!=0)
			do{
				printf("%c",(char)stab[h2]);
				h1--;
				h2++;
			}while(h1!=0);
			break;
		case 29:
			switch(ir.y){
			case 1:
				printf("%d",s[t].i);
				break;
			case 2:
				printf("%lf",s[t].r);
				break;
			case 3:
				printf("%c",(char)s[t].i);
				break;
			}
			t--;
			break;
		case 31:
			ps=fin;
			break;
		case 32:
			t=b-1;
			pc=s[b+1].i;b=s[b+3].i;
			break;
		case 33:
			t=b;
			pc=s[b+1].i;b=s[b+3].i;
			break;
		case 34:
			s[t]=s[s[t].i];
			break;
		case 36:
			s[t].i=-s[t].i;
			s[t].r=-s[t].r;
			break;
		case 38:
			s[s[t-1].i]=s[t];
			t=t-2;
			break;
		case 39:
			t--;
			if(s[t].r==s[t+1].r)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 40:
			t--;
			if(s[t].r!=s[t+1].r)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 41:
			t--;
			if(s[t].r<s[t+1].r)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 42:
			t--;
			if(s[t].r<=s[t+1].r)
				s[t].i=1;
			else
				s[t].i=0;
        	break;
		case 43:
			t--;
			if(s[t].r>s[t+1].r)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 44:
			t--;
			if(s[t].r>=s[t+1].r)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 45:
			t--;
			if(s[t].i==s[t+1].i)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 46:
			t--;
			if(s[t].i!=s[t+1].i)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 47:
			t--;
			if(s[t].i<s[t+1].i)
				s[t].i=1;
			else
				s[t].i=0;
			break;

		case 48:
			t--;
			if(s[t].i<=s[t+1].i)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 49:
			t--;
			if(s[t].i>s[t+1].i)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 50:
			t--;
			if(s[t].i>=s[t+1].i)
				s[t].i=1;
			else
				s[t].i=0;
			break;
		case 52:
			t--;
			s[t].i=s[t].i+s[t+1].i;
			break;
		case 53:
			t--;
			s[t].i=s[t].i-s[t+1].i;
			break;
		case 54:
			t--;
			s[t].r=s[t].r+s[t+1].r;
			break;
		case 55:
			t--;
			s[t].r=s[t].r-s[t+1].r;
			break;
		case 57:
			t--;
			s[t].i=s[t].i*s[t+1].i;
			break;
		case 58:
			t--;
			if(s[t+1].i==0)
				ps=divchk;
			else
				s[t].i=s[t].i/s[t+1].i;
			break;
		case 60:
			t--;
			s[t].r=s[t].r*s[t+1].r;
			break;
		case 61:
			t--;
			if(s[t+1].r==0)
				ps=divchk;
			else
			    s[t].r=s[t].r/s[t+1].r;
			break;
		case 63:
			printf("\n");
			break;
		}
	}while(ps==run);
	if(ps!=fin){
		printf("halt at %5d because of",pc-1);
		switch(ps){
		case divchk:
			printf("\ndivision by 0!\n");
			break;
		case inxchk:
			printf("\ninvalid index!\n");
			break;
		case stkchk:
			printf("\nstorage overflow!\n");
			break;
		case linchk:
			printf("\ntoo much output!\n");
			break;
		}
	}
	else
		printf("\nThe program has executed successfully!\n");
	system("pause");

}
