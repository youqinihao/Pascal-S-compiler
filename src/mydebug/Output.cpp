// output->cpp : implementation file
//

#include "stdafx.h"
#include "output.h"
#include "Resource.h"
#include "Input.h"
#include "InfoDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutput dialog

//解释执行时各种信息的输出窗口类
extern char f[200];
bool isShow=false; //是否显示静态符号表



#define MyImport extern "C" _declspec(dllimport)
//#pragma comment(lib,"mycompiler.lib")
int lc;                //指令数组的当前索引
int t,a,b,sx,c1,c2;    //各种表格的索引
bool canexe=false;           //是否可以解释执行p代码
int display[lmax];     //分程序索引表
table tab[tmax+1];     //符号表   
btable btab[bmax+1];   //分程序表
char stab[smax+1];     //字符串常量数组
double rconst[c2max];  //实常量数组
order code[cmax+1];    //p代码数组
atable atab[amax+1];   //数组信息向量表
//MyImport int compiler(char *file);

CString szout;          //程序输出窗口将显示的信息  
datastack s[stacksize+1];//运行栈数组

    order ir;
	conrec in;
	int pc;	
	int h1,h2,h3,h4;
	int lncnt,ocnt;
	CString Base,lineNum;
	enum p {run,fin,divchk,inxchk,stkchk,linchk,};
	int disp[lmax];
	p ps;
	int t1,b1;

//从二进制文件中解析各数据结构
bool readbinary(char *file){
    char bfile[200];
	strcpy(bfile,file);
	strcat(bfile,".bpl");
	FILE *fp=fopen(bfile,"rb");
	if(!fp){
		printf("文件名不对!\n");
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
//用户程序的数据输入
conrec COutput::inputdata(int kind){
	CInput dlg;
	conrec data;
	data.i=0;data.r=0;
	CString temp;	
	
	if(IDOK==dlg.DoModal()){
		temp=dlg.m_szData;
		switch(kind){
		case 1:
		    data.i=atoi(temp);
			break;
		case 2:
			data.i=(int)temp.GetAt(0);
			break;
		case 3:
			data.r=(double)atof(temp);
			break;
        default:
			data.i=0;data.r=0;
    		break;
			
		}
	}
	return data;
}

//输出用户程序中的整数
void COutput::outputi(int i){
	CString temp;
	temp.Empty();
	temp.Format("%d",i);
	 UpdateData();
	szout= m_szOutput;
	 m_szOutput=szout+temp;
     UpdateData(false);
}
//输出用户程序中的实数
void COutput::outputf(double f){
	
	CString temp;
	temp.Empty();
	temp.Format("%f",f);
	 UpdateData();
	szout= m_szOutput;
	 m_szOutput=szout+temp;
     UpdateData(false);
}
//输出用户程序的字符和字符串
void COutput::outputc(char c){
	CString temp;
	temp.Empty();
	temp.Format("%c",c);
	 UpdateData();
	szout= m_szOutput;
	 m_szOutput=szout+temp;
     UpdateData(false);
}
//输出用户程序的字符串常量表
void COutput::ouptputStab(int sx){
	stab[sx]='\0';
    m_stab.SetWindowText(stab);

}
//输出用户程序的实数常量表
void COutput::outputRconst(int c2){
	CString constant;
	m_Rconst.ResetContent();
	for(int i=1;i<=c2;++i){
        constant.Format("%f",rconst[i]);
	 m_Rconst.AddString(constant);
	}

}
//输出用户程序的分程序表信息
void COutput::outputBtab(int b){
	 m_BtabList.SetExtendedStyle( m_BtabList.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	 m_BtabList.DeleteAllItems();
	 CString last,lastpar,psize,vsize,no,line;
	 m_BtabList.InsertColumn(0,"No.",LVCFMT_CENTER,50,0);
	 m_BtabList.InsertColumn(1,"last",LVCFMT_CENTER,50,0);
	 m_BtabList.InsertColumn(2,"lastpar",LVCFMT_CENTER,80,0);
	 m_BtabList.InsertColumn(3,"psize",LVCFMT_CENTER,50,0);
	 m_BtabList.InsertColumn(4,"vsize",LVCFMT_CENTER,50,0);
	 m_BtabList.InsertColumn(5,"line",LVCFMT_CENTER,50,0);
	for(int i=0;i<=b;i++){
    last.Format("%d",btab[i].last);
	lastpar.Format("%d",btab[i].lastpar);
	psize.Format("%d",btab[i].psize);
	vsize.Format("%d",btab[i].vsize);
	line.Format("%d",btab[i].line);
	no.Format("%d",i);
	 m_BtabList.InsertItem(i,no);
	 m_BtabList.SetItemText(i,1,last);
	 m_BtabList.SetItemText(i,2,lastpar);
	 m_BtabList.SetItemText(i,3,psize);
	 m_BtabList.SetItemText(i,4,vsize);	
	 m_BtabList.SetItemText(i,5,line);	
	}
}
//输出用户程序的符号表信息
void COutput::outputTab(int t){
	char *object[5];
	char *type[6];
	type[0]="notyp";  type[1]="ints";
	type[2]="reals";    type[3]="chars";
	type[4]="arrays",type[5]="records";
	object[0]="constant";object[1]="variable";
	object[2]="typel";   object[3]="procedure";
	object[4]="function";

	 m_TabList.SetExtendedStyle( m_TabList.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	 m_TabList.DeleteAllItems();
  	CString name,line,link,obj,typ,ref,normal,lev,adr,no;
	 m_TabList.InsertColumn(0,"No.",LVCFMT_CENTER,50,0);
	 m_TabList.InsertColumn(1,"name",LVCFMT_CENTER,90,0);
	 m_TabList.InsertColumn(2,"obj",LVCFMT_CENTER,90,0);
	 m_TabList.InsertColumn(3,"typ",LVCFMT_CENTER,90,0);
	 m_TabList.InsertColumn(4,"line",LVCFMT_CENTER,50,0);
	 m_TabList.InsertColumn(5,"link",LVCFMT_CENTER,50,0);
	 m_TabList.InsertColumn(6,"ref",LVCFMT_CENTER,50,0);
	 m_TabList.InsertColumn(7,"normal",LVCFMT_CENTER,90,0);
	 m_TabList.InsertColumn(8,"lev",LVCFMT_CENTER,50,0);
	 m_TabList.InsertColumn(9,"adr",LVCFMT_CENTER,50,0);
	for(int i=0;i<=t;i++)
	{
		name.Format("%s",tab[i].name);
	    link.Format("%d",tab[i].link);
		line.Format("%d",tab[i].line);	    
		obj.Format("%s",object[tab[i].obj]);
	    typ.Format("%s",type[tab[i].typ]);
    	ref.Format("%d",tab[i].ref);
		normal.Format("%d",tab[i].normal);
    	lev.Format("%d",tab[i].lev);
        adr.Format("%d",tab[i].adr);
		no.Format("%d",i);
		 m_TabList.InsertItem(i,no);
		 m_TabList.SetItemText(i,1,name);
	     m_TabList.SetItemText(i,2,obj);
		 m_TabList.SetItemText(i,3,typ);
	     m_TabList.SetItemText(i,4,line);
		 m_TabList.SetItemText(i,5,link);
		 m_TabList.SetItemText(i,6,ref);
		 m_TabList.SetItemText(i,7,normal);
		 m_TabList.SetItemText(i,8,lev);
		 m_TabList.SetItemText(i,9,adr);
	}
}
//输出用户程序的p代码
void COutput::outputPcode(int pc){
	CString no,pcode,pcode1,pcode2;
	order o;
	char *mne[64];
	mne[0]="LDA  ";mne[1]="LOD  ";mne[2]="LDI  ";
	mne[3]="DIS  ";mne[8]="FCT  ";mne[9]="INT  ";
	mne[10]="JMP  ";mne[11]="JPC  ";mne[12]="JPG ";
	mne[13]="CAS  ";mne[14]="F1U  ";mne[15]="F2U  ";
	mne[16]="F1D  ";mne[17]="F2D  ";  mne[18]="MKS  ";
	mne[19]="CAL  ";mne[20]="IDX  ";mne[21]="IXX  ";
	mne[22]="LDB  ";mne[23]="CPB  ";mne[24]="LDC  ";
	mne[25]="LDR  ";mne[26]="FLT  ";mne[27]="RED  ";
	mne[28]="WRS ";mne[29]="WRW ";mne[30]="WRU ";
	mne[31]="HLT  ";mne[32]="EXP  ";mne[33]="EXF  ";
	mne[34]="LDT  ";mne[35]="NOT  ";mne[36]="MUS  ";
	mne[37]="WRR ";mne[38]="STO  ";mne[39]="EQR  ";
	mne[40]="NER  ";mne[41]="LSR  ";mne[42]="LRE  ";
	mne[43]="GTR  ";mne[44]="GRE  ";mne[45]="EQL  ";
	mne[46]="NEQ  ";mne[47]="LSS  ";mne[48]="LEQ  ";
	mne[49]="GRT  ";mne[50]="GEQ  ";mne[51]="ORR  ";
	mne[52]="ADD  ";mne[53]="SUB  ";mne[54]="ADR  ";
	mne[55]="SUR  ";mne[56]="AND  ";mne[57]="MUL  ";
	mne[58]="DIV  ";mne[59]="MOD  ";mne[60]="MUR  ";
	mne[61]="DIR  ";mne[62]="RDL  ";mne[63]="WRL ";
	
		no.Format("%2d",pc);
		o=code[pc];
		pcode.Format("%s",mne[o.f]);
		if(o.f<31){
			if(o.f<4){
			pcode1.Format("%1d %5d",o.x,o.y);
			pcode=pcode+pcode1;
			}
			else
			{
			pcode2.Format("%5d",o.y);
			pcode=pcode+pcode2;
			}
		}
		else
		{
			pcode1="          ";
			pcode=pcode+pcode1;
		}
     
	  m_PcodeList.AddString(no+pcode);
}
//输出用户程序的运行栈
void COutput::outputDataStack(int t,int b){
	CString data;
	int i;
//  int i,end,p,inc;
//	p=s[b+4].i;
//	end=btab[tab[p].ref].vsize;
	 m_DataStack.ResetContent();
	for(i=0;i<=t;++i){
		 data.Format("%2d%6d|%14f",i,s[i].i,s[i].r);
	      m_DataStack.AddString(data);
	}
/*	for(i=b+5;i<=end;++i){
		 data.Format("%2d%10s%6d|%f",i,tab[p].name,s[i].i,s[i].r);
	      m_DataStack.AddString(data);
	}
	for(i=end+1;i<=t;++i){
		 data.Format("%2d%6d|%14f",i,s[i].i,s[i].r);
	      m_DataStack.AddString(data);
	}*/
	 m_DataStack.SetCurSel(t);
}
//输出解释执行时的分程序索引表
void COutput::outputDisplay(int *display,int h2,bool flag){
	int h;
	CString temp;
    h=tab[h2].lev;
	 m_DisplayList.ResetContent();
	if(flag){
	temp.Format("call:%s",tab[h2].name);
	 m_DisplayList.AddString(temp);
	temp.Format("level:%d",h);
	 m_DisplayList.AddString(temp);
	}
	else
	{
		 m_DisplayList.AddString("调整后:");
	}
   	 m_DisplayList.AddString("display表:");
	for(int i=1;i<=h;++i){
		temp.Format("层次:%d",i);
		m_DisplayList.AddString(temp);	
		temp.Format("基址:%d",display[i]);
		m_DisplayList.AddString(temp);	
	}	
}
	


	
//初始化解释执行
void COutput::interpretInit(char *file){
   	if(!readbinary(file)){
		printf("加载文件失败!\n");
		canexe=false;
     return;
	}
	else
		canexe=true;
    ShowTables();
	if(!canexe){
		AfxMessageBox("请先编译正确后,再执行!");
       return;
	}
	szout="";
	m_szOutput="";
    m_DisplayList.ResetContent();
	UpdateData(false);
    Invalidate();

	s[1].i=0; s[2].i=0;
	s[3].i=-1;s[4].i=btab[1].last;
	disp[1]=0;
	t1=btab[2].vsize-1;
	b1=0;         pc=tab[s[4].i].adr;
	lncnt=0;ocnt=0;
	ps=run;
	m_PcodeList.SetCurSel(pc);
	outputDataStack(t1,b1);
	Base.Format("(当前基址b=%d)",b1);
	m_baseIndex=Base;
	lineNum.Format("源程序行号:%d",code[pc].l);
	m_lineNum=lineNum;
	ShowLine(code[pc].l);
	UpdateData(false);
	}
//单步解释执行用户的p代码
void COutput::interpretStep(int &t,int &b){
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
	    ir=code[pc];
		pc++;ocnt++; 
		switch(ir.f){
		case 0:
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t].i=disp[ir.x]+ir.y;
			break;
		case 1:
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t]=s[disp[ir.x]+ir.y];
			break;
		case 2:;
			t++;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t]=s[s[disp[ir.x]+ir.y].i];
			break;
		case 3:
			h1=ir.y;h2=ir.x;h3=b;
			do{
				disp[h1]=h3;h1--;h3=s[h3+2].i;
			}while(h1!=h2);
			outputDisplay(disp,h2,false);
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
			disp[h3+1]=h1;
			h4=s[h1+3].i+h1;
			s[h1+1].i=pc;
			s[h1+3].i=b;
			for(h3=t+1;h3<=h4;++h3)
				s[h3].i=0;
			b=h1;t=h4;
			pc=tab[h2].adr;
			outputDisplay(disp,h2,true);
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
				//scanf("%d",&s[s[t].i].i);
				in=inputdata(1);
				s[s[t].i].i=in.i;
				break;
			case 2:
				//scanf("%f",&s[s[t].i].r);
				in=inputdata(3);
                s[s[t].i].r=in.r;
				break;
			case 3:
				//scanf("%c",&temp);
				in=inputdata(2);
                s[s[t].i].i=in.i;
				break;

			}
			t--;
			break;
		case 28:
			h1=s[t].i;
			h2=ir.y;t--;
			/*do{
				outputc((char)stab[h2]);
				h1--;
				h2++;
				
			}while(h1!=0);*/
			if(h1!=0)
			outputs(stab,h2,h1);
			break;
		case 29:
			switch(ir.y){
			case 1:
				outputi(s[t].i);
				break;
			case 2:
				outputf(s[t].r);
				break;
			case 3:
				outputc((char)s[t].i);
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
			outputc('\r');
			outputc('\n');
			break;
		}
		m_PcodeList.SetCurSel(pc);
		outputDataStack(t,b1);
		Base.Format("(当前基址b=%d)",b1);
		m_baseIndex=Base;
		lineNum.Format("源程序行号:%d",code[pc].l);
		m_lineNum=lineNum;
		ShowLine(code[pc].l);
		UpdateData(false);
}


COutput::COutput(CWnd* pParent /*=NULL*/)
	: CDialog(COutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutput)
	m_szOutput = _T("");
	m_baseIndex = _T("");
	m_lineNum = _T("");
	m_breakPoint = 0;
	m_lineContent = _T("");
	//}}AFX_DATA_INIT

}



void COutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutput)
	DDX_Control(pDX, IDC_LIST6, m_DisplayList);
	DDX_Control(pDX, IDC_LIST5, m_DataStack);
	DDX_Control(pDX, IDC_EDIT3, m_stab);
	DDX_Control(pDX, IDC_LIST4, m_Rconst);
	DDX_Control(pDX, IDC_LIST3, m_BtabList);
	DDX_Control(pDX, IDC_LIST2, m_TabList);
	DDX_Control(pDX, IDC_LIST7, m_ArrayList);
	DDX_Control(pDX, IDC_LIST1, m_PcodeList);
	DDX_Text(pDX, IDC_EDIT1, m_szOutput);
	DDX_Text(pDX, IDC_EDIT2, m_baseIndex);
	DDX_Text(pDX, IDC_EDIT4, m_lineNum);
	DDX_Text(pDX, IDC_EDIT5, m_breakPoint);
	DDV_MinMaxInt(pDX, m_breakPoint, 0, 100000);
	DDX_Text(pDX, IDC_EDIT6, m_lineContent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutput, CDialog)
	//{{AFX_MSG_MAP(COutput)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkList3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST7, OnDblclkList7)
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutput message handlers


HBRUSH COutput::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here

	
	if(pWnd->GetDlgCtrlID()==IDC_EDIT1||pWnd->GetDlgCtrlID()==IDC_EDIT3){
			//改变字符串和输出信息的显示颜色
		pDC->SetTextColor(RGB(0,10,200));
		hbr=HBRUSH(GetStockObject(HOLLOW_BRUSH));
			}
          	//static颜色
	if (pWnd->GetDlgCtrlID()==IDC_STATIC) 
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
    }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
//用于显示任务栏图标
BOOL COutput::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)   
      {   
      case   WM_LBUTTONDOWN:   
		  break;
      case   WM_LBUTTONUP:  
		  break;
      case   WM_MOUSEMOVE:   
          	m_ToolTip.RelayEvent(pMsg);;   
		  break;
      }   


	return CDialog::PreTranslateMessage(pMsg);
}

BOOL COutput::OnInitDialog()//添加提示信息
{
    m_ToolTip.Create(this);
	m_ToolTip.SetTipTextColor(RGB(0,106,53));
	m_ToolTip.SetTipBkColor(RGB(213,253,224));
	m_ToolTip.SetMaxTipWidth(200);
	m_ToolTip.AddTool(GetDlgItem(IDC_LIST2),"编译结束后的符号表\n\rP代码将从中获取信息");
	m_ToolTip.AddTool(GetDlgItem(IDC_LIST3),"编译结束后的分程序表\n\rP代码执行时将从中获取信息");
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT3),"程序中所有的字符串常量\n\r首尾相连存入一个字符数组");
	m_ToolTip.AddTool(GetDlgItem(IDC_LIST4),"程序中所有的实数常量,存\n\r入了一个双精度浮点数组\n\r每行显示一个数");
	m_ToolTip.AddTool(GetDlgItem(IDC_LIST5),"P代码解释执行时数据栈的\n\r动态情况,栈顶在最下方,\n\r每个元素是整数或实数");
	m_ToolTip.AddTool(GetDlgItem(IDC_LIST1),"P代码的操作码以\n\r及x,y域,单步执行\n\r时将选中将要执行\n\r的一条指令");
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT1),"程序中所有write函数\n\r的输出窗口");
	m_ToolTip.AddTool(GetDlgItem(IDC_LIST6),"调用函数或过程或mks调整\n\r时打印display表");
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT5),"该行号为源程序中所\n\r对应的行号而不是p代\n\r码,而且该值在生成有p\n\r代码的行上才有效");
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT6),"将显示解释执行时p代码\n\r对应的源程序行");
	m_ToolTip.AddTool(GetDlgItem(IDC_LIST7),"编译结束后的数组信息向量表\n\rP代码将从中获取信息");
	return CDialog::OnInitDialog();
}
//解释执行p代码到结束
void COutput::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if(!canexe){
		AfxMessageBox("编译未成功或未刷新表格！");
		return;
	}
	while(ps==run)
	interpretStep(t1,b1);
	isFinish();
}
//单步解释执行p代码
void COutput::OnButton2() 
{
	// TODO: Add your control notification handler code here
	if(!canexe){
		AfxMessageBox("编译未成功或未刷新表格！");
		return;
	}
	if(ps==run)
	{
		interpretStep(t1,b1);
	}
    else 
	{
		isFinish();
	}
}
void COutput::OnButton3(){
    interpretInit(f);

}

//显示各种在解释执行时已确定的表格
void COutput::ShowTables()
{
   	if(!isShow)
	{
	outputTab(t);
	outputBtab(b);
	outputRconst(c2);
	ouptputStab(sx);
	outputarray(a);
	for(int i=0;i<lc;++i){
		outputPcode(i);
	}
	isShow=true;
	}
}
//判断是否正常运行完毕
bool COutput::isFinish()
{
	if(ps!=fin){
		CString out;
		out.Format("pcode指令停止在：%d 因为",pc-1);
		AfxMessageBox(out);
		switch(ps){
		case divchk:
			AfxMessageBox("\n除零溢出!\n");
			break;
		case inxchk:
			AfxMessageBox("\n无效索引!\n");
			break;
		case stkchk:
			AfxMessageBox("\n存储溢出!\n");
			break;
		case linchk:
			AfxMessageBox("\n输出信息太多!\n");
			break;
		}
		AfxMessageBox("程序由于运行时错误终止!");
		return false;
	}
	else
	{
		AfxMessageBox("程序正常执行完毕!");
		return true;
	}

}

//解释执行到断点指定的行
void COutput::OnButton4() 
{
	// TODO: Add your control notification handler code here
	if(!canexe){
		AfxMessageBox("编译未成功或未刷新表格！");
		return;
	}
	UpdateData(true);
	while(ps==run){
		if(code[pc].l==m_breakPoint)
			return;
     	interpretStep(t1,b1);
	}
	isFinish();
}
void COutput::OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		CString str,temp;
	str="         分程序表项\r\n\r\n";
	int i=m_BtabList.GetNextItem(-1,LVNI_SELECTED);
	if(i!=-1){
		temp=m_BtabList.GetItemText(i,0);
		str=str+"No.       :"+temp+"\r\n";
		temp=m_BtabList.GetItemText(i,1);
		str=str+"last       :"+temp+"\r\n";
		temp=m_BtabList.GetItemText(i,2);
		str=str+"lastpar  :"+temp+"\r\n";
		temp=m_BtabList.GetItemText(i,3);
		str=str+"psize    :"+temp+"\r\n";
		temp=m_BtabList.GetItemText(i,4);
		str=str+"vsize    :"+temp+"\r\n";
		temp=m_BtabList.GetItemText(i,5);
		str=str+"line       :"+temp+"\r\n";
	}
    CInfoDlg dlg;
	dlg.info=str;
	dlg.DoModal();
	*pResult = 0;
}

void COutput::OnDblclkList7(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		CString str,temp;
	str="     数组信息向量表项\r\n\r\n";
	int i=m_ArrayList.GetNextItem(-1,LVNI_SELECTED);
	if(i!=-1){
		temp=m_ArrayList.GetItemText(i,0);
		str=str+"No.        :"+temp+"\r\n";
		temp=m_ArrayList.GetItemText(i,1);
		str=str+"inxtyp    :"+temp+"\r\n";
		temp=m_ArrayList.GetItemText(i,2);
		str=str+"eltyp      :"+temp+"\r\n";
		temp=m_ArrayList.GetItemText(i,3);
		str=str+"elref      :"+temp+"\r\n";
		temp=m_ArrayList.GetItemText(i,4);
		str=str+"low        :"+temp+"\r\n";
		temp=m_ArrayList.GetItemText(i,5);
		str=str+"high       :"+temp+"\r\n";
		temp=m_ArrayList.GetItemText(i,6);
		str=str+"elsize    :"+temp+"\r\n";
		temp=m_ArrayList.GetItemText(i,7);
		str=str+"size       :"+temp+"\r\n";
	}
    CInfoDlg dlg;
	dlg.info=str;
	dlg.DoModal();
	*pResult = 0;
}

void COutput::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString str,temp;
	str="         符号表项\r\n\r\n";
	int i=m_TabList.GetNextItem(-1,LVNI_SELECTED);
	if(i!=-1){
		temp=m_TabList.GetItemText(i,0);
		str=str+"No.       :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,1);
		str=str+"name    :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,2);
		str=str+"obj        :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,3);
		str=str+"typ        :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,4);
		str=str+"line       :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,5);
		str=str+"link       :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,6);
		str=str+"ref        :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,7);
		str=str+"normal :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,8);
		str=str+"level    :"+temp+"\r\n";
		temp=m_TabList.GetItemText(i,9);
		str=str+"adr       :"+temp+"\r\n";
	}
    CInfoDlg dlg;
	dlg.info=str;
	dlg.DoModal();
	*pResult = 0;
}
//显示当前正在解释执行的源代码行
void COutput::ShowLine(int line)
{
	char ch;
	char temp[500];
	int i=line;
	if(i==0)
		return;
	FILE *fp=fopen(::f,"r");
	while(i>1){
		do
		ch=fgetc(fp);
		while(ch!='\n'&&ch!=EOF);
		--i;
	}
	fgets(temp,500,fp);
	m_lineContent=temp;
	m_lineContent.SetAt(m_lineContent.GetLength()-1,'\0');
	UpdateData(false);
	fclose(fp);


}

void COutput::outputarray(int a)
{
   	char *type[6];
 	type[0]="notyp";  type[1]="ints";
   	type[2]="reals";    type[3]="chars";
	type[4]="arrays",type[5]="records";
    m_ArrayList.SetExtendedStyle(m_ArrayList.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ArrayList.DeleteAllItems();
   	CString no,inxtyp,eltyp,elref,low,high,elsize,lev,size;
	m_ArrayList.InsertColumn(0,"No.",LVCFMT_CENTER,50,0);
	m_ArrayList.InsertColumn(1,"inxtyp",LVCFMT_CENTER,90,0);
    m_ArrayList.InsertColumn(2,"eltyp",LVCFMT_CENTER,90,0);
	m_ArrayList.InsertColumn(3,"elref",LVCFMT_CENTER,90,0);
	m_ArrayList.InsertColumn(4,"low",LVCFMT_CENTER,50,0);
	m_ArrayList.InsertColumn(5,"high",LVCFMT_CENTER,50,0);
	m_ArrayList.InsertColumn(6,"elsize",LVCFMT_CENTER,60,0);
	m_ArrayList.InsertColumn(7,"size",LVCFMT_CENTER,50,0);
	for(int i=0;i<=a;i++)
	{
		inxtyp.Format("%s",type[atab[i].inxtyp]);
	    eltyp.Format("%s",type[atab[i].eltyp]);
		elref.Format("%d",atab[i].elref);	    
		low.Format("%d",atab[i].low);
	    high.Format("%d",atab[i].high);
    	elsize.Format("%d",atab[i].elsize);
		size.Format("%d",atab[i].size);
		no.Format("%d",i);
	    
		 m_ArrayList.InsertItem(i,no);
		 m_ArrayList.SetItemText(i,1,inxtyp);
	     m_ArrayList.SetItemText(i,2,eltyp);
		 m_ArrayList.SetItemText(i,3,elref);
	     m_ArrayList.SetItemText(i,4,low);
		 m_ArrayList.SetItemText(i,5,high);
		 m_ArrayList.SetItemText(i,6,elsize);
		 m_ArrayList.SetItemText(i,7,size);
	}
}
//输出字符串
void COutput::outputs(char *s, int start, int len)
{
	   CString temp;
	   temp.Empty();
	   temp.Format("%s",s);
	   temp=temp.Left(start+len);
	   temp=temp.Right(len);
	   UpdateData();
	   szout= m_szOutput;
	   m_szOutput=szout+temp;
       UpdateData(false);

}

//对话框窗口缺省消息处理
LRESULT COutput::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{	
	//return CDialog::DefWindowProc(message, wParam, lParam);  
	LRESULT lrst=CDialog::DefWindowProc(message, wParam, lParam);


	if (!::IsWindow(m_hWnd))
		return lrst;
	
	if (message==WM_MOVE||message==WM_PAINT||message==WM_NCPAINT||message==WM_NCACTIVATE ||message == WM_NOTIFY)
	{
		try
		{
			CDC* pWinDC = GetWindowDC();
			if (pWinDC)
				DrawTitleBar(pWinDC);
			ReleaseDC(pWinDC);
		}
		catch( CException* e )
		{
			e->Delete();
		}
	}
	return lrst;
}


// 绘制标题栏、边框颜色，绘制标题内容、图标和按钮

void COutput::DrawTitleBar(CDC *pDC)
{
	if (m_hWnd)
	{
	//	CBrush Brush(RGB(187,200,143));
		CBrush Brush(RGB(187,0,255));
		CBrush* pOldBrush = pDC->SelectObject(&Brush);

		CRect rtWnd, rtTitle, rtButtons;
		GetWindowRect(&rtWnd);
		
		//取得标题栏的位置
		  //SM_CXFRAME 窗口边框的边缘宽度
		  //SM_CYFRAME 窗口边框的边缘高度
		  //SM_CXSIZE  窗口标题栏宽度
	   	  //SM_CYSIZE  窗口标题栏高度
		rtTitle.left = GetSystemMetrics(SM_CXFRAME); 
		rtTitle.top = GetSystemMetrics(SM_CYFRAME);  
		rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME);
		rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

		CPoint point;
		//填充顶部框架
		point.x = rtWnd.Width();						
		point.y = GetSystemMetrics(SM_CYSIZE) + GetSystemMetrics(SM_CYFRAME) + 0;
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		//填充左侧框架
		point.x = GetSystemMetrics(SM_CXFRAME) -1;
		point.y = rtWnd.Height()- 1;
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		//填充底部框架
		point.x = rtWnd.Width(); 
		point.y = GetSystemMetrics(SM_CYFRAME);
		pDC->PatBlt(0, rtWnd.Height()-point.y, point.x, point.y, PATCOPY);
		//填充右侧框架
		point.x = GetSystemMetrics(SM_CXFRAME);
		point.y = rtWnd.Height();
		pDC->PatBlt(rtWnd.Width()-point.x, 0, point.x, point.y, PATCOPY);
		
		
		//重画标题栏图标
		m_rtIcon.left = rtTitle.left ;
		m_rtIcon.top = rtTitle.top;
		m_rtIcon.right = m_rtIcon.left + 16;
		m_rtIcon.bottom = m_rtIcon.top + 15;
		::DrawIconEx(pDC->m_hDC, m_rtIcon.left, m_rtIcon.top,  AfxGetApp()->LoadIcon(IDI_ICON1), 
			m_rtIcon.Width(), m_rtIcon.Height(), 0, NULL, DI_NORMAL);
		m_rtIcon.OffsetRect(rtWnd.TopLeft());
	
		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC=new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);
		
		//重画关闭button
		rtButtons.left = rtTitle.right - 16;
		rtButtons.top = rtTitle.top - 1;
		rtButtons.right = rtButtons.left + 16;
		rtButtons.bottom = rtButtons.top + 15;
		pBitmap->LoadBitmap(IDB_EXIT_FOCUS);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtExit = rtButtons;
		m_rtButtExit.OffsetRect(rtWnd.TopLeft()); 
		pBitmap->DeleteObject();
		
		//重画最大化/恢复button
		rtButtons.right = rtButtons.left - 3;
		rtButtons.left = rtButtons.right - 16;
		if (IsZoomed())
			pBitmap->LoadBitmap(IDB_RESTORE_NORMAL);
		else
			pBitmap->LoadBitmap(IDB_MAX_NORMAL);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMax = rtButtons;
		m_rtButtMax.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();
		
		//重画最小化button
		rtButtons.right = rtButtons.left - 3;
		rtButtons.left = rtButtons.right - 16;
		pBitmap->LoadBitmap(IDB_MIN_NORMAL);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMin = rtButtons;
		m_rtButtMin.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//重画caption
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		COLORREF clOldText=pDC->SetTextColor(RGB(255, 255, 255));
		
		CFont m_captionFont;
		m_captionFont.CreateFont(
			18,                        // 字体的高度			
			0,                         // 字体的宽度
			0,                         // 字体显示的角度
			0,                         // 字体的角度
			FW_BOLD,                   // 字体的磅数
			FALSE,                     // 斜体字体
			FALSE,                     // 带下划线的字体
			0,                         // 带删除线的字体
			ANSI_CHARSET,              // 所需的字符集
			OUT_DEFAULT_PRECIS,        // 输出的精度
			CLIP_DEFAULT_PRECIS,       // 裁减的精度
			DEFAULT_QUALITY,           // 逻辑字体与输出设备的实际字体之间的精度
			DEFAULT_PITCH | FF_SWISS,  // 字体间距和字体集
			_T("Arial"));              // 字体名称
			
		CFont* pOldFont = NULL;			
		pOldFont = pDC->SelectObject(&m_captionFont);
		
		rtTitle.left += m_rtIcon.Width ()+3;
		rtTitle.top = rtTitle.top;
		rtTitle.bottom = rtTitle.top + 30;
		CString m_strTitle;
		GetWindowText(m_strTitle);
		pDC->DrawText(m_strTitle, &rtTitle, DT_LEFT);
		pDC->SetBkMode(nOldMode);
		pDC->SetTextColor(clOldText);
		
		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}



// 在非客户区单击 绘制消息

void COutput::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	if (m_rtButtExit.PtInRect(point)) //关闭
		SendMessage(WM_CLOSE);
	else if (m_rtButtMin.PtInRect(point)) //最小化
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	else if (m_rtButtMax.PtInRect(point))
	{
		if (IsZoomed()) //最大化
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
			CRect rtWnd;
			GetWindowRect(&rtWnd);
			CRgn rgn;
			rgn.CreateRoundRectRgn(0,0,rtWnd.Width(),rtWnd.Height(),5,5);
			SetWindowRgn((HRGN)rgn,true); 
			Invalidate();
		}
		else
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));
			
			CRect rtWnd;
			GetWindowRect(&rtWnd);
			CRgn rgn;
			rgn.CreateRoundRectRgn(0,0,rtWnd.Width(),rtWnd.Height(),5,5);
			SetWindowRgn((HRGN)rgn,true); 
			Invalidate();
		}
	}
	else if (!IsZoomed())
		Default();
}

// 在非客户区 鼠标移动 绘制消息

void COutput::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	CWindowDC dc(this);
	CWindowDC* pDC = &dc;
	CDC* pDisplayMemDC=new CDC;
	pDisplayMemDC->CreateCompatibleDC(pDC);
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CRect rtWnd, rtButton;
	
	if (pDC)
	{
		GetWindowRect(&rtWnd);
		
		//关闭button
		if (m_rtButtExit.PtInRect(point))
			pBitmap->LoadBitmap(IDB_EXIT_NORMAL);
		else
			pBitmap->LoadBitmap(IDB_EXIT_FOCUS);
		rtButton = m_rtButtExit;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
		
		//最大化/恢复button
		if (m_rtButtMax.PtInRect(point))
		{
			if (IsZoomed())
				pBitmap->LoadBitmap(IDB_RESTORE_FOCUS);
			else
				pBitmap->LoadBitmap(IDB_MAX_FOCUS);
		}
		else
		{
			if (IsZoomed())
				pBitmap->LoadBitmap(IDB_RESTORE_NORMAL);
			else
				pBitmap->LoadBitmap(IDB_MAX_NORMAL);
		}
		rtButton = m_rtButtMax;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
		
		//最小化button
		if (m_rtButtMin.PtInRect(point))
			pBitmap->LoadBitmap(IDB_MIN_FOCUS);
		else
			pBitmap->LoadBitmap(IDB_MIN_NORMAL);
		rtButton = m_rtButtMin;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
		
	}
	
	pDisplayMemDC->DeleteDC();
	
	delete pDisplayMemDC;
	delete pBitmap;

	CDialog::OnNcMouseMove(nHitTest, point);
}

//填充背景
BOOL COutput::OnEraseBkgnd(CDC* pDC) 
{
	BOOL retValue= CDialog::OnEraseBkgnd(pDC);

/*	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc,RGB(236,233,216));*/
	
	return retValue;
}

//改变窗口边框为圆角
int COutput::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rtWnd;
	GetWindowRect(&rtWnd);
	
	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,rtWnd.Width(),rtWnd.Height(),10,10);
	SetWindowRgn((HRGN)rgn,true); 

	return 0;
}



