// mycompiler.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "mycompiler.h"

#include<string>
#include<map>
#include<iostream>
#include "symset.h"
#include "Error.h"
using namespace std ;


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
// CMycompilerApp

BEGIN_MESSAGE_MAP(CMycompilerApp, CWinApp)
	//{{AFX_MSG_MAP(CMycompilerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMycompilerApp construction

CMycompilerApp::CMycompilerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMycompilerApp object

CMycompilerApp theApp;


//错误处理类
CError err;

int linenum=1;       //词法，语法的当前行
char ch;             //当前读取的字符
double rnum;         //词法分析时存放实常数

int inum;              //词法分析时存放整数常数
int sleng;             //字符串长度
             
int lc;                //指令数组的当前索引
int t,a,b,sx,c1,c2;    //各种表格的索引
MyExport bool canexe;           //是否可以解释执行p代码
int display[lmax];     //分程序索引表
table tab[tmax+1];     //符号表   
btable btab[bmax+1];   //分程序表
char stab[smax+1];     //字符串常量数组
double rconst[c2max];  //实常量数组
order code[cmax+1];    //p代码数组
atable atab[amax+1];   //数组信息向量表

symbol sy;             //当前读入符号的类型
char id[alng+1];       //存放单词值

char *key[nkw+1];      //保留字数组
symbol ksy[nkw+1];     //保留字类别数组
FILE * psin;           //源程序输入文件

char inf[200],outf[200];//输入，输出文件名
map<char,symbol> sps;   //特殊符号类别 

/////////////////////////////////////////////////////////////////////////////

//读入一个字符
void nextch(){
	ch=fgetc(psin);
	putchar(ch);
}
//打印致命错误
void fatal(int n){
	char* msg[8];
	msg[1]="identfier";msg[2]="prcedures";
	msg[3]="reals";    msg[4]="arrays";
	msg[5]="levels";   msg[6]="code";
	msg[7]="strings";
	CString temp;
	temp.Format("ERROR:compiler table for %s is too small!",msg[n]);
	AfxMessageBox(temp);
	exit(0);
}
//初步判别字符的类别
char kind(char ch){
	if(isalpha(ch)) 
		return '1';
	else if(isdigit(ch))
		return '2';
	else if(ch=='+'||ch=='-'||ch=='*'||ch=='('||ch==')'||ch=='='
		||ch==','||ch==';'||ch=='['||ch==']')
		return '3';
	else 
		return ch;

}
//词法分析
void insymbol(){
int i,j,k,l;
one: while(ch==' '||ch=='	'||ch=='\n'){
		 if(ch=='\n'){
			 linenum++;
		 }
		 nextch();
	 }
	switch(kind(ch)){
	case '1':
		k=0;
		for(l=0;l<alng+1;++l)
			id[l]=' ';
		do
		{
			if(k<alng){
				id[k]=ch;k++;
			}
			nextch();
		}while((ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'||ch>='0'&&ch<='9'));
		i=1;j=nkw;
	/*	do
		{
			k=(i+j)/2;
			if(strcmp(id,key[k])<=0) j=k-1;
			if(strcmp(id,key[k])>=0) i=k+1;
		}while(i<j);
		if(i-1>j)
			sy=ksy[k];
		else
			sy=ident;*///二分法搜索关键字数组
		sy=ident;
		for(i=1;i<=nkw;++i)
			if(strcmp(id,key[i])==0)
			{
				sy=ksy[i];        //顺序法搜索
				break;
			}
		break;
	case '2':
		k=0;inum=0;sy=intcon;
		do
		{
			inum=inum*10+(ch-'0');
			k++;
			nextch();
		}while((ch>='0'&&ch<='9'));
	
		if(k>kmax||inum>nmax)
		{
			err.error(linenum,21);inum=0;k=0;
		}
		if(ch=='.'){
			nextch();
			sy=realcon;rnum=inum;
			double t=0,s=1.0;
			if(!isdigit(ch))
                 err.error(linenum,40);
			while(ch>='0'&&ch<='9'){
				s=s*10.0;
				t=t+(ch-'0')/s;
				nextch();
			}
			rnum=rnum+t;
		}
		break;
	case ':':
		nextch();
		if(ch=='=')
		{
			sy=becomes;nextch();
		}
		else
			sy=colon;
	    break;
	case '<':
		nextch();
		if(ch=='=')
		{
			sy=leq;nextch();
		}
		else if(ch=='>')
		{
			sy=neq;nextch();
		}
		else
			sy=lss;
		break;
	case '>':
		nextch();
		if(ch=='=')
		{
			sy=geq;nextch();
		}
		else 
			sy=gtr;
		break;
	case '.':
		nextch();
		if(ch=='.'){
			sy=colon;nextch();
		}
		else
			sy=period;
		break;
	case '\'':
		nextch();
		if(isalnum(ch))
		{   
			inum=ch;
			nextch();
			if(ch=='\'')
			{
			sy=charcon;nextch();
			}
			else
			{
				err.error(linenum,38);sy=charcon;inum=0;
			}
		}	
		else
		{
				err.error(linenum,38);sy=charcon;inum=0;
		}
		break;
	case '"':
		k=0;
		do{
        nextch();
		if(sx+k==smax)
			fatal(7);
		stab[sx+k]=ch;k++;
        }while(ch!='"'&&k<600);
		nextch();
        if(k>=600)
		   err.error(linenum,38);//the string too long or the symbol " lost!
	    sy=stringcon;inum=sx;
  	    sleng=k-1;sx+=k-1;
		break;
	case '3':
		sy=sps[ch];nextch();
		break;
	case EOF:
		sy=eof;
		break;
	case '/':
			nextch();
		    if(ch=='/'){
			do{
				nextch();
			}while(ch!='\n'&&ch!=EOF);
			goto one;
			}               //处理注释行
			else
			{
				sy=sps['/']; //rdiv 				
			}
			break;
   	default:
		err.error(linenum,24);nextch();goto one;
		break;
	}
}
//登陆符号表
void enter(char *x0,object x1,types x2,int x3){
t++;
strcpy(tab[t].name,x0);   tab[t].link=t-1;  
tab[t].obj=x1;            tab[t].normal=true;
tab[t].typ=x2;            tab[t].ref=0;     
tab[t].lev=0;             tab[t].adr=x3;
tab[t].line=linenum;
}
//登陆数组信息
void enterarray(types tp,int l,int h){
	if(l>h)
		err.error(linenum,27);
	if(abs(l)>nmax||abs(h)>nmax)
	{
		err.error(linenum,27);
		l=0;h=0;
	}
	if(a==amax)
		fatal(4);
	else
	{
		++a;
		atab[a].inxtyp=tp;atab[a].low=l;atab[a].high=h;
	}
}
//登陆分程序块
void enterblock(){
	if(b==bmax)
		fatal(2);
	else
	{
		++b;btab[b].last=0;btab[b].lastpar=0;btab[b].line=linenum;;
	}
}
//登陆实数
void enterreal(double x){
	if(c2==c2max)
		fatal(3);
	else
	{
		rconst[c2+1]=x;c1=1;
		while(abs(rconst[c1]-x)>0.0000001)
			c1++;
		if(c1>c2)
			c2=c1;
	}
}
//p代码输出到p代码数组
void emit(int fct){
	if(lc==cmax)fatal(6);
	code[lc].f=fct;code[lc].l=linenum;lc++;
}
//p代码输出到p代码数组
void emit1(int fct,int b){
	if(lc==cmax)fatal(6);
	code[lc].f=fct;code[lc].y=b;code[lc].l=linenum;
	lc++;
}
//p代码输出到p代码数组
void emit2(int fct,int a,int b){
	if(lc==cmax) fatal(6);
	code[lc].f=fct;code[lc].x=a;code[lc].y=b;code[lc].l=linenum;
	lc++;
}
//初始化关键字类别和值
void setup(){

	key[1]="begin      "; 
	key[2]="const      "; key[3]="div        ";
	key[4]="do         "; key[5]="downto     ";
	key[6]="else       "; key[7]="end        ";
	key[8]="for        "; key[9]="function   ";
	key[10]="if         ";key[11]="procedure  ";
	key[12]="then       ";key[13]="to         ";
    key[14]="var        ";key[15]="while      ";
	key[16]="array      ";key[17]="record     ";
	key[18]="type       ";key[19]="of         ";
    
	ksy[1]=beginsy;      
	ksy[2]=constsy;      ksy[3]=idiv;
	ksy[4]=dosy;         ksy[5]=downtosy;
	ksy[6]=elsesy;       ksy[7]=endsy;
	ksy[8]=forsy;        ksy[9]=funcsy;
	ksy[10]=ifsy;        ksy[11]=procsy;
	ksy[12]=thensy;	     ksy[13]=tosy;    
	ksy[14]=varsy;       ksy[15]=whilesy; 
	ksy[16]=arraysy;     ksy[17]=recordsy;
	ksy[18]=typesy;      ksy[19]=ofsy;
	sps['+']=plus1;      sps['-']=minus1;
	sps['*']=times;      sps['/']=rdiv;
	sps['(']=lparent;    sps[')']=rparent;
	sps['[']=lbrack;     sps[']']=rbrack;
	sps['=']=eql;        sps[',']=comma;
	sps[';']=semicolon;
}
//跳读直到合法符号出现
void skip(symset fsys,int n){
	err.error(linenum,n);
    while(!fsys.InSet(sy)) {
		insymbol();
		if(sy==eof)
			return;
	}
}
//测试后继符号的合法性
void test(symset s1,symset s2,int n){
    if(!s1.InSet(sy))
	{
		s1+=s2;
		skip(s1,n);
	}
}
//测试后继符号是否是分号
void testsemicolon(symset fsys){
	symset s1;
	s1+=blockbegsys;
	s1+=ident;
    if(sy==semicolon)
		insymbol();
	else
	{
		err.error(linenum,14);
		if(sy==comma||sy==colon)
			insymbol();
	}
	test(s1,fsys,6);
}
//登陆标识符的值
void enter(char *id,object k,int level){
	int j,l;
	if(t==tmax)
		fatal(1);
	else
	{
		strcpy(tab[0].name,id);
		j=btab[display[level]].last;l=j;
		while(strcmp(tab[j].name,id)!=0)
			j=tab[j].link;
		if(j!=0)
			err.error(linenum,1);
		else
		{
			t++;
			strcpy(tab[t].name,id);         tab[t].link=l;
			tab[t].obj=k;                   tab[t].typ=notyp;   
			tab[t].ref=0;                   tab[t].normal=false;
			tab[t].lev=level;               tab[t].adr=0; 
			tab[t].line=linenum;
		}
		btab[display[level]].last=t;
	}
}
//用给定的值查找符号表
int loc(char * id,int level){
	int i,j;
	i=level;
	strcpy(tab[0].name,id);
	do
	{
		j=btab[display[i]].last;
		while(strcmp(tab[j].name,id)!=0)
			j=tab[j].link;
		i--;
	}while(i>=0&&j==0);
	if(j==0)err.error(linenum,0);
	return j;

}
//将变量的层次登陆符号表
void entervariable(int level){
	if(sy==ident)
	{
		enter(id,variable,level);insymbol();
	}
	else
		err.error(linenum,2);
}
//常量分析
void constant1(symset fsys,conrec &c,int level){
	int x,sign;
	c.tp=notyp;c.i=0;
	test(constbegsys,fsys,50);
	if(constbegsys.InSet(sy))
	{
		if(sy==charcon)
		{
			c.tp=chars;c.i=inum;
			insymbol();
		}
		else
		{
			sign=1;
			if(sy==plus1||sy==minus1)
			{
				if(sy==minus1)sign=-1;
				insymbol();
			}
			if(sy==ident)
			{
				x=loc(id,level);
				if(x!=0)
				{
					if(tab[x].obj!=constant)
						err.error(linenum,25);
					else
					{
						c.tp=tab[x].typ;
						if(c.tp==reals)
						{
							c.r=sign*rconst[tab[x].adr];
						}
						else
							c.i=sign*tab[x].adr;
					}
						insymbol();
				}
			}
			else if(sy==intcon)
			{
				c.tp=ints;c.i=sign*inum;
				insymbol();
			}
			else if(sy==realcon)
			{
				c.tp=reals;c.r=sign*rnum;
				insymbol();
			}
			else
				skip(fsys,50);
		}
		test(fsys,fsys,6);
	}

}
//函数或过程的参数分析
void parameterlist(symset fsys,int &dx,int level){
	types tp;
	bool valpar;
	int rf,sz,x,t0;
	insymbol();
	tp=notyp;rf=0;sz=0;
	symset s1,s2;
    s1+=ident;s1+=varsy;
	s2=fsys;s2+=rparent;
	symset s3,s4;
    s3+=semicolon;s3+=rparent;
    s4=fsys;s4+=comma;s4+=ident;
	symset s5,s6;
	s5+=ident;s5+=varsy;
	s6=fsys;s6+=rparent;
	test(s1,s2,7);
	while(s1.InSet(sy)){
		if(sy!=varsy)
			valpar=true;
		else
		{
			insymbol();
			valpar=false;
		}
		t0=t;entervariable(level);
		while(sy==comma){
			insymbol();
			entervariable(level);
		}
		if(sy==colon)
		{
			insymbol();
			if(sy!=ident)
				err.error(linenum,2);
			else
			{
				x=loc(id,level);insymbol();
				if(x!=0){
					if(tab[x].obj!=typel)err.error(linenum,29);
					else
						tp=tab[x].typ;rf=tab[x].ref;
					if(valpar)
						sz=tab[x].adr;
					else
						sz=1;
				}
			}
        	test(s3,s4,14);
		}
		else
		err.error(linenum,5);
		while(t0<t)
		{
			t0++;
			tab[t0].typ=tp;tab[t0].ref=rf;
			tab[t0].adr=dx;tab[t0].lev=level;
			tab[t0].normal=valpar;
			dx+=sz;
		}
		if(sy!=rparent)
		{
			if(sy==semicolon)
				insymbol();
			else
			{
				err.error(linenum,14);
				if(sy==comma)
        			insymbol();		
			}
            	test(s5,s6,6);
		}
	}
	if(sy==rparent)
	{
		insymbol();
	    symset s7;
		s7+=semicolon;s7+=colon;
		test(s7,fsys,6);
	}
	else
		err.error(linenum,4);
}
void typ(symset fsys,types &tp,int &rf,int &sz,int level);
//数组分析
void arraytyp(symset fsys,int&aref,int &arsz,int level){
   types eltp;
   conrec low,high;
   int elrf,elsz;
   symset s1;
   s1+=fsys;
   s1+=colon;s1+=rbrack;s1+=rparent;s1+=ofsy;
   constant1(s1,low,level);
   if(low.tp==reals)
   {
	   err.error(linenum,27);
	   low.tp=ints;low.i=0;
   }
   if(sy==colon)
	   insymbol();
   else
	   err.error(linenum,13);
   constant1(s1,high,level);
   if(high.tp!=low.tp){
	   err.error(linenum,27);
	   high.i=low.i;
   }
   enterarray(low.tp,low.i,high.i);
   aref=a;
   if(sy==comma){
    insymbol();
	eltp=arrays;
	arraytyp(fsys,elrf,elsz,level);
   }
   else
   {
	   if(sy==rbrack)
		   insymbol();
	   else
	   {
		   err.error(linenum,12);
		   if(sy==rparent)
			   insymbol();
	   }
	   if(sy==ofsy){
		   insymbol();
	   }
	   else
		   err.error(linenum,8);
	  typ(fsys,eltp,elrf,elsz,level);
   }
   arsz=(atab[aref].high-atab[aref].low+1)*elsz;atab[aref].size=arsz;
   atab[aref].eltyp=eltp;atab[aref].elref=elrf;atab[aref].elsize=elsz;
}
void selector(symset fsys,item &v,int level);
//类型分析
void typ(symset fsys,types &tp,int &rf,int &sz,int level){
	int x;
	types eltp;
	int elrf;
	int elsz,offset,t0,t1;
	symset s1,s2,s3;
	s1+=fsys;
	s1-=semicolon;	s1-=comma;s1-=ident;
	s1+=endsy;
	s2+=fsys;
	s2+=semicolon;s2+=endsy;s2+=comma;s2+=ident;
	s3+=ident;s3+=endsy;s3+=semicolon;
	tp=notyp;rf=0;sz=0;
	test(typebegsys,fsys,10);
    if(typebegsys.InSet(sy)){
	if(sy==ident)
	{
		x=loc(id,level);
		if(x!=0)
		{
			if(tab[x].obj!=typel)
				err.error(linenum,29);
			else
			{
				tp=tab[x].typ; rf=tab[x].ref;
				sz=tab[x].adr;
			    if(tp==notyp)err.error(linenum,30);
			}
			insymbol();
		}
	}
	else if(sy==arraysy){
		insymbol();
		if(sy==lbrack)
			insymbol();
		else
		{
			err.error(linenum,11);
			if(sy==lparent)
				insymbol();
		}
	    tp=arrays;arraytyp(fsys,rf,sz,level);
	}
	else
	{
		insymbol();
		enterblock();
		tp=records;rf=b;
		if(level==lmax)
			fatal(5);
		++level;display[level]=b;offset=0;
		while(!s1.InSet(sy)){
		if(sy==ident){
		    t0=t;entervariable(level);
			while(sy==comma){
			insymbol();entervariable(level);
			}
			if(sy==colon)
				insymbol();
			else
				err.error(linenum,5);

			t1=t;
			typ(s2,eltp,elrf,elsz,level);
			while(t0<t1){
				t0++;
				tab[t0].typ=eltp;
				tab[t0].ref=elrf;
				tab[t0].normal=true;
				tab[t0].adr=offset;
				offset+=elsz;
			}
			if(sy!=semicolon)
				break;
			else
				insymbol();
		}
		}
	if(sy!=endsy){
		if(sy==semicolon){
			insymbol();
		}
		else
		{
			err.error(linenum,14);
			if(sy==comma)
				insymbol();
		}
		test(s3,fsys,6);
	}
	btab[rf].vsize=offset;sz=offset;
	btab[rf].psize=0;
	insymbol();--level;
	}
	}
	test(fsys,fsys,6);
}
//常量声明
void constdec(symset fsys,int level){
    conrec c;
	insymbol();
	symset s1;
	s1+=ident;
	test(s1,blockbegsys,2);
	while(sy==ident)
	{
		enter(id,constant,level);insymbol();
		if(sy==eql)
			insymbol();
		else
		{
			err.error(linenum,16);
			if(sy==becomes)
				insymbol();
		}
		symset s2;
		s2=fsys;
		s2+=semicolon;s2+=comma;s2+=ident;
		constant1(s2,c,level);
		tab[t].typ=c.tp;tab[t].ref=0;
		if(c.tp==reals)
		{
			enterreal(c.r);tab[t].adr=c1;
		}
		else
			tab[t].adr=c.i;
		if(sy==comma){
			insymbol();
			continue;
		}
		else if(sy==semicolon){
			insymbol();
			break;
		}
	}

}
//类型声明
void typedec(symset fsys,int level){
	types tp;
	int rf,sz,t1;
	symset s1,s2;
	s1+=ident;
	s2+=fsys;
	s2+=semicolon;
	s2+=comma;
	s2+=ident;
	insymbol();
	test(s1,blockbegsys,2);
	while(sy==ident){
		enter(id,typel,level);
		t1=t;insymbol();
		if(sy==eql)
			insymbol();
		else
		{
			err.error(linenum,16);
			if(sy==becomes)
				insymbol();
		}
		typ(s2,tp,rf,sz,level);
		tab[t1].typ=tp;tab[t1].ref=rf;
		tab[t1].adr=sz;	
	testsemicolon(fsys);
	}
}
//变量声明
void variabledec(symset fsys,int &dx,int level){
     types tp;
	 int t0,t1,rf,sz;
	 insymbol();
	 while(sy==ident){
		 t0=t;entervariable(level);
		 while(sy==comma){
			 insymbol();entervariable(level);
		 }
		 if(sy==colon)
			 insymbol();
		 else
			 err.error(linenum,5);
		 t1=t;
		 symset s1;
		 s1+=semicolon;s1+=comma;s1+=ident;
		 s1+=fsys;
		 typ(s1,tp,rf,sz,level);
		 while(t0<t1){
			 t0++;
			 tab[t0].typ=tp;   tab[t0].ref=rf;
			 tab[t0].lev=level;tab[t0].adr=dx;
			 tab[t0].normal=true;
			 dx+=sz;
		 }
		 testsemicolon(fsys);
	 }
   
}
void block(symset fsys,bool isfun,int level);
//过程或函数声明
void procdec(symset fsys,int level){
   symset s1;
   s1+=semicolon;
   s1+=fsys;
   bool isfun=false;
   if(sy==funcsy)
	   isfun=true;
   insymbol();
   if(sy!=ident){
	   err.error(linenum,2);strcpy(id,"          ");
   }
   if(isfun)
	   enter(id,function,level);
   else
	   enter(id,procedure,level);
   tab[t].normal=true;
   insymbol();
   block(s1,isfun,level+1);
   if(sy==semicolon)
	   insymbol();
   else
	   err.error(linenum,14);
   emit(32+isfun);//
}
//类型转换
types resulttype(types a,types b){
	if(a==chars)
		a=ints;
	if(b==chars)
		b=ints;
	if(a>reals||b>reals)
	{
		err.error(linenum,33);
		return notyp;
	}
	else if(a==notyp||b==notyp)
	    return notyp;
	else if(a==ints){
		if(b==ints)
			return ints;
		else
		{
			emit1(26,1);
			return reals;
		}
	}
	else
	{
		if(b==ints) emit1(26,0);
		return reals;
	}

}
//测试是否是标准数据类型
bool instantyps(types tp){
	if(tp<=chars&&tp>=notyp)
		return true;
	return false;
}
void expression(symset fsys,item &x,int level);
//函数或过程调用语句分析
void call(symset fsys,int i,int level){
	item x;
	int lastp,cp,k;
	symset s1,s2,s3,s4;
	s1+=comma;s1+=colon;s1+=rparent;
	s1+=fsys;
	s2+=comma;s2+=rparent;
	s2+=fsys;
	s3+=lbrack;s3+=lparent;s3+=period;
	s4+=fsys;
	s4+=comma;s4+=colon; s4+=rparent;
	emit1(18,i);
	lastp=btab[tab[i].ref].lastpar;
	cp=i;
	if(sy==lparent){
		do{
			insymbol();
			if(cp>=lastp)err.error(linenum,39);
			else
			{
				cp++;
				if(tab[cp].normal)
				{
					expression(s1,x,level);
					if(x.typ==tab[cp].typ)
					{
					    if(x.ref!=tab[cp].ref)
						    err.error(linenum,36);
				    	else if(x.typ==arrays){
					    	emit1(22,atab[x.ref].size);
						}
					    else if(x.typ==records){
						    emit1(22,btab[x.ref].vsize);
						}
					}
				    else if(x.typ==ints&&tab[cp].typ==reals)
						 emit1(26,0);
					else if(x.typ==chars&&tab[cp].typ==reals)
						 emit1(26,0);
					else if(x.typ==chars&&tab[cp].typ==ints)
						 ;
				   	else if(x.typ!=notyp)
						err.error(linenum,36);
				}
				else
				{
					if(sy!=ident)
						err.error(linenum,2);
					else
					{
						k=loc(id,level);
						insymbol();
				    	if(k!=0){
					     	if(tab[k].obj!=variable)
						    	err.error(linenum,37);
					        x.typ=tab[k].typ;
						    x.ref=tab[k].ref;
					    	if(tab[k].normal)
						    	emit2(0,tab[k].lev,tab[k].adr);
						    else
						    	emit2(1,tab[k].lev,tab[k].adr);
							if(s3.InSet(sy))
								selector(s4,x,level);
					     	if(x.typ!=tab[cp].typ||x.ref!=tab[cp].ref)
						    	err.error(linenum,36);
						}
					}

				}
			}
		   test(s2,fsys,6);
		}while(sy==comma);
		if(sy==rparent)
			insymbol();
		else
			err.error(linenum,4);
	}
	if(cp<lastp)
		err.error(linenum,39);
	emit1(19,btab[tab[i].ref].psize-1);
	if(tab[i].lev<level)
		emit2(3,tab[i].lev,level);
}
//因子分析
void factor(symset fsys,item &x,int level){
     int i,f;
	 x.typ=notyp;
	 x.ref=0;
	 symset s1;
	 s1+=lbrack;s1+=lparent;s1+=period;
	 test(facbegsys,fsys,58);
	 while(facbegsys.InSet(sy))
	 {
		 if(sy==ident){
			 i=loc(id,level);
			 insymbol();
			 switch(tab[i].obj){
			 case constant:
				 x.typ=tab[i].typ;
				 x.ref=0;
				 if(x.typ==reals)
					 emit1(25,tab[i].adr);
				 else
					 emit1(24,tab[i].adr);
				 break;
			 case variable:
				 x.typ=tab[i].typ;
				 x.ref=tab[i].ref;
				 if(s1.InSet(sy)){
					 if(tab[i].normal)
						 f=0;
					 else
						 f=1;
					 emit2(f,tab[i].lev,tab[i].adr);
					 selector(fsys,x,level);
					 if(instantyps(x.typ))
						 emit(34);
				 }
				 else
				 {
				 if(instantyps(x.typ)){
					 if(tab[i].normal)
						 f=1;
					 else
						 f=2;
				 }
				 else
				 {
					 if(tab[i].normal) 
						 f=0;
					 else
						 f=1;
				 }
				 emit2(f,tab[i].lev,tab[i].adr);
				
				 }
			 
				 break;
			 case procedure:
				 err.error(linenum,44);
				 break;
			 case function:
				 x.typ=tab[i].typ;
				 if(tab[i].lev!=0)
					 call(fsys,i,level);
				 break;
			 }
		 }
		 else if(sy==charcon||sy==intcon||sy==realcon)
		 {
			 if(sy==realcon)
			 {
				 x.typ=reals;
				 enterreal(rnum);
				 emit1(25,c1);
			 }
			 else
			 {
				 if(sy==charcon)
					 x.typ=chars;
				 else
					 x.typ=ints;
				 emit1(24,inum);
			 }
			 x.ref=0;
			 insymbol();
		 }
		 else if(sy==lparent)
		 {
			 insymbol();
			 symset s1;
			 s1=fsys;s1+=rparent;
			 expression(s1,x,level);
			 if(sy==rparent)
				 insymbol();
			 else
				 err.error(linenum,4);
		 }
		 test(fsys,facbegsys,6);
		
	 }
}
//项的分析
void term(symset fsys,item &x,int level){
	item y;
	symbol op;
	symset s1;
	s1+=times;s1+=rdiv;s1+=idiv;
	s1+=fsys;
	factor(s1,x,level);
	while(sy==times||sy==rdiv||sy==idiv){
		op=sy;
		insymbol();
		factor(s1,y,level);
		if(op==times){
			x.typ=resulttype(x.typ,y.typ);
			switch(x.typ){
			case notyp: 
				break;
			case ints:
				emit(57);
				break;
			case reals:
				emit(60);
				break;
			}
		}
		else if(op==rdiv){
			if(x.typ==ints||x.typ==chars){
				emit1(26,1);
				x.typ=reals;
			}
			if(y.typ==ints||y.typ==chars){
				emit1(26,0);
				y.typ=reals;
			}
			if(x.typ==reals&&y.typ==reals){
				emit(61);
			}
			else
			{
				if(x.typ!=notyp&&y.typ!=notyp)
					err.error(linenum,33);
				x.typ=notyp;
			}
		}
		else 
		{
			if(x.typ==chars)
				x.typ=ints;
			if(y.typ==chars)
				y.typ=ints;
			if(x.typ==ints&&y.typ==ints)
			{
				if(op==idiv)
					emit(58);
			//	else
			//		emit(59);
			}
			else
			{
				if(x.typ!=notyp&&y.typ!=notyp)
					err.error(linenum,34);
				x.typ=notyp;
			}
		}
	}


}
void selector(symset fsys,item &v,int level){
	 item x;
	 int a,j;
	 symset s1,s2;
	 s1+=fsys;
	 s1+=comma;s1+=rbrack;
	 s2+=lbrack;s2+=lparent;s2+=period;
	 do
	 {
		 if(sy==period){
			 insymbol();
			 if(sy!=ident){
				err.error(linenum,2);
			 }
			 else
			 {
				 if(v.typ!=records)
					 err.error(linenum,31);
				 else
				 {
				 j=btab[v.ref].last;
				 strcpy(tab[0].name,id);
				 while(strcmp(tab[j].name,id)!=0)
					 j=tab[j].link;
				 if(j==0)
					 err.error(linenum,0);
				 v.typ=tab[j].typ;
				 v.ref=tab[j].ref;
				 a=tab[j].adr;
				 if(a!=0)
					 emit1(9,a);
				 }
			 }
			 insymbol();
		 }
		 else
		 {
		 if(sy!=lbrack)
			 err.error(linenum,11);
		 do{
			 insymbol();
			 expression(s1,x,level);
			 if(v.typ!=arrays)
				 err.error(linenum,28);
			 else
			 {
				 a=v.ref;
				 if(atab[a].inxtyp!=x.typ)
					 err.error(linenum,26);
				 else if(atab[a].elsize==1)
					 emit1(20,a);
				 else
					 emit1(21,a);
				 v.typ=atab[a].eltyp;
				 v.ref=atab[a].elref;
			 }
		 }while(sy==comma);
		 if(sy==rbrack)
			 insymbol();
		 else
		 {
			 err.error(linenum,12);
			 if(sy==rparent)
				 insymbol();
		 }
		 }
	 }while(s2.InSet(sy));
	 test(fsys,fsys,6);
}
//表达式的分析
void expression(symset fsys,item &x,int level){
    item y;
	symbol op;
	symset s1;
	s1+=plus1;s1+=minus1;s1+=fsys;
	if(sy==plus1||sy==minus1){
		op=sy;
		insymbol();
		term(s1,x,level);
		if(x.typ>reals)
			err.error(linenum,33);
		else if(op==minus1)
			emit(36);
	}
	else
		term(s1,x,level);
	while(sy==plus1||sy==minus1){
		op=sy;
		insymbol();
		term(s1,y,level);
		x.typ=resulttype(x.typ,y.typ);
		switch(x.typ){
		case ints:
			if(op==plus1)
				emit(52);
			else
				emit(53);
			break;
		case reals:
			if(op==plus1)
				emit(54);
			else
				emit(55);
			break;
		}
	}

}
//条件的分析
void condition(symset fsys,item &x,int level){
	item y;
	symbol op;
	symset s1,s2;
	s1+=eql;s1+=neq;s1+=lss;s1+=leq;s1+=gtr;s1+=geq;
	s2=s1;s2+=fsys;
	expression(s1,x,level);
	if(s1.InSet(sy)){
		op=sy;
		insymbol();
		expression(fsys,y,level);
		if((x.typ==notyp||x.typ==ints||x.typ==chars)&&x.typ==y.typ){
			switch(op){
			case eql:
				emit(45);break;
			case neq:
				emit(46);break;
			case lss:
				emit(47);break;
			case leq:
				emit(48);break;
			case gtr:
				emit(49);break;
			case geq:
				emit(50);break;
			}
		}
		else if(y.typ==ints){
			y.typ=reals;emit1(26,0);
		}
		else if(x.typ==reals&&y.typ==reals)
			switch(op){
			case eql:
				emit(39);break;
			case neq:
				emit(40);break;
			case lss:
				emit(41);break;
			case leq:
				emit(42);break;
			case gtr:
				emit(43);break;
			case geq:
				emit(44);break;
		}
		else
			err.error(linenum,35);
	}
      x.typ=ints;
}
//赋值语句的分析
void assignment(symset fsys, int lv,int ad,int level,int i){
	item x,y;
	int f;
	symset s1,s2;
	s1+=lbrack;s1+=lparent;s1+=period;
	s2+=fsys;s2+=becomes;s2+=eql;
	x.typ=tab[i].typ;
	x.ref=tab[i].ref;
	if(tab[i].normal)
		f=0;
	else
		f=1;
	emit2(f,lv,ad);
	if(s1.InSet(sy))
		selector(s2,x,level);
	
	if(sy==becomes)
		insymbol();
	else
		err.error(linenum,51);
	if(sy==eql)
		insymbol();
	expression(fsys,y,level);
	if(x.typ==y.typ)
	{
		if(x.typ>=notyp&&x.typ<=chars)
			emit(38);
		else if(x.ref!=y.ref)
			err.error(linenum,46);
	    else if(x.typ==arrays)
			emit1(23,atab[x.ref].size);
		else 
			emit1(23,btab[x.ref].vsize);
	}
	else if(x.typ==reals&&y.typ==ints){
		emit1(26,0);
		emit(38);
	}
	else if(x.typ==reals&&y.typ==chars){
		emit1(26,0);
		emit(38);
	}
	else if(x.typ==ints&&y.typ==chars)
		emit(38);
	else if(x.typ!=notyp&&y.typ!=notyp)
		err.error(linenum,46);
	else if(x.typ==notyp&&y.typ!=notyp)
		err.error(linenum,46);


}
void statement(symset fsys,int level);
//复合语句的分析
void compoundstatement(symset fsys,int level){
	symset s1,s2;
	s1+=semicolon;s1+=endsy;
	s1+=fsys;
	s2+=semicolon;
	s2+=statbegsys;
	insymbol();
	statement(s1,level);
	while(s2.InSet(sy)){
		if(sy==semicolon){
			insymbol();
		}
		else 
			err.error(linenum,14);
		statement(s1,level);
	}
	if(sy==endsy)
		insymbol();
	else
		err.error(linenum,57);
}
//if语句的分析
void ifstatement(symset fsys,int level){
	item x;
	int lc1,lc2;
	symset s1,s2;
	s1+=thensy;s1+=dosy;
	s1+=fsys;
	insymbol();
	condition(s1,x,level);
	if(x.typ!=ints)
		err.error(linenum,17);
	lc1=lc;
	emit(11);
	if(sy==thensy)
		insymbol();
	else
	{
		err.error(linenum,52);
		if(sy==dosy)
			insymbol();
	}
	s2+=elsesy;s2+=fsys;
	statement(s2,level);
	if(sy==elsesy){
		insymbol();lc2=lc;
		emit(10);code[lc1].y=lc;
		statement(fsys,level);code[lc2].y=lc;
	}
	else
		code[lc1].y=lc;

}
//先do后while循环的分析
void whilestatement(symset fsys,int level){
	item x;
	int lc1;
	symset s1,s2;
	s1+=whilesy;
	s1+=semicolon;
	lc1=lc;
	insymbol();
	statement(s1,level);
	if(sy==whilesy){
		insymbol();
		condition(fsys,x,level);
		if(x.typ!=ints)err.error(linenum,17);
		emit1(12,lc1);
	}
	else
		err.error(linenum,53);

}
//先while后do循环的分析
void while2statement(symset fsys,int level){
	item x;
	int lc1,lc2;
	symset s1;
	insymbol();
	lc1=lc;
	s1+=dosy;
	s1+=fsys;
	condition(s1,x,level);
	if(x.typ==notyp)
		err.error(linenum,17);
	lc2=lc;emit(11);
	if(sy==dosy)
		insymbol();
	else
		err.error(linenum,54);
	statement(fsys,level);
	emit1(10,lc1);
	code[lc2].y=lc;
	
}
//for循环的分析
void forstatement(symset fsys,int level){
	types cvt;
	item x;
	int i,f,lc1,lc2;
	symset s1,s2,s3;
	s1+=tosy;s1+=downtosy;s1+=dosy;
	s1+=fsys;s2=s1;
	s1+=becomes;
	s3+=dosy;
	s3+=fsys;
	insymbol();
	if(sy==ident){
		i=loc(id,level);
		insymbol();
		if(i==0)cvt=ints;
		else if(tab[i].obj==variable){
			cvt=tab[i].typ;
			if(!tab[i].normal)err.error(linenum,37);
			else
				emit2(0,tab[i].lev,tab[i].adr);
			if(cvt<notyp||cvt>chars)
				err.error(linenum,18);
		}
		else
		{
			err.error(linenum,37);cvt=ints;
		}
	}
	else
		skip(s1,2);
	if(sy==becomes)
	{
		insymbol();
		expression(s2,x,level);
		if(x.typ!=cvt)
			err.error(linenum,19);
	}
	else
		skip(s2,51);
	f=14;
	if(sy==tosy||sy==downtosy)
	{
		if(sy==downtosy)
			f=16;
		insymbol();
		expression(s3,x,level);
		if(x.typ!=cvt)err.error(linenum,19);
	}
	else
		skip(s3,55);
    lc1=lc;emit(f);
	if(sy==dosy)
		insymbol();
	else
		err.error(linenum,54);
	lc2=lc;
	statement(fsys,level);
	emit1(f+1,lc2);
	code[lc1].y=lc;
}
//write和read过程的处理
void standproc(symset fsys,int n,int level){
	item x;
	int i,f;
	symset s1,s2,s3,s4;
	s1+=comma;s1+=rparent;
	s2+=comma;s2+=colon;s2+=rparent;s2+=fsys;
	s3+=lbrack;s3+=lparent;s3+=period;
	s4+=fsys;s4+=comma;s4+=rparent;
	if(n==1||n==2){
		if(sy==lparent){
			do{
			insymbol();
			if(sy!=ident)
				err.error(linenum,2);
			else
			{
				i=loc(id,level);
				insymbol();
				if(i!=0){
					if(tab[i].obj!=variable)
						err.error(linenum,37);
					else
					{
						x.typ=tab[i].typ;
						x.ref=tab[i].ref;
					    if(tab[i].normal)
							f=0;
						else 
							f=1;
						emit2(f,tab[i].lev,tab[i].adr);
						if(s3.InSet(sy)){
							selector(s4,x,level);
						}
						if(x.typ>=notyp&&x.typ<=chars)
							emit1(27,x.typ);
					}
				}
			}
				test(s1,fsys,6);
			}while(sy==comma);
			if(sy==rparent)
				insymbol();
			else
				err.error(linenum,4);
		}
		}
	if(n==3||n==4){
		if(sy==lparent){
			insymbol();
			if(sy==stringcon){
				emit1(24,sleng);
				emit1(28,inum);
				insymbol();
				if(sy==comma)
				{
					insymbol();
					expression(s2,x,level);
			    	if(!instantyps(x.typ))
				    	err.error(linenum,41);
				    else
					    emit1(29,x.typ);
				}
			}
			else
			{
				expression(s2,x,level);
				if(!instantyps(x.typ))
					err.error(linenum,41);
				else
					emit1(29,x.typ);
			}
			if(sy==rparent)
				insymbol();
			else 
				err.error(linenum,4);
			if(n==4)
				emit(63);

		}

	}
			
}
//语句的分析
void statement(symset fsys,int level){
	int i;
	symset s1;
	s1=statbegsys;s1+=ident;
	switch(sy){
	case ident:
		i=loc(id,level);
		insymbol();
		if(i!=0)
		{
			switch(tab[i].obj){
			case constant:
				err.error(linenum,45);
				break;
			case typel:
				err.error(linenum,45);
				break;
			case variable:
				assignment(fsys,tab[i].lev,tab[i].adr,level,i);
				break;
			case function:
				if(tab[i].ref==display[level])
					assignment(fsys,tab[i].lev+1,0,level,i);
				else
					err.error(linenum,45);
				break;
			case procedure:
				if(tab[i].lev!=0)
					call(fsys,i,level);
				else
					standproc(fsys,tab[i].adr,level);
				break;
			}
		}
		break;
	case beginsy:
		compoundstatement(fsys,level);
		break;
	case ifsy:
		ifstatement(fsys,level);
		break;
	case dosy:
		whilestatement(fsys,level);
		break;
	case forsy:
		forstatement(fsys,level);
		break;
	case whilesy:
		while2statement(fsys,level);
		break;
	}
	test(fsys,fsys,14);
}
//程序块的分析
void block(symset fsys,bool isfun,int level){
	int dx;
	int prt;
	int prb;
	int x;
	symset s1,s2,s3,s4,s5,s6,s7;
	s1+=lparent;s1+=colon;s1+=semicolon;
	s2+=semicolon;
	s2+=fsys;
	s3+=beginsy;
	s4=blockbegsys;s4+=statbegsys;
	s5+=semicolon;s5+=endsy;s5+=fsys;
	s6+=semicolon;s6+=statbegsys;
	s7+=period;s7+=fsys;
	dx=5;prt=t;
	if(level>lmax)
		fatal(5);
	if(level!=1){
	test(s1,fsys,14);
	}
	enterblock();
	prb=b;display[level]=b;
	tab[prt].typ=notyp;tab[prt].ref=prb;
	if(sy==lparent&&level>1)
		parameterlist(fsys,dx,level);
	btab[prb].lastpar=t;btab[prb].psize=dx;
	if(isfun){
		if(sy==colon){
			insymbol();
			if(sy==ident){
				x=loc(id,level);
				insymbol();
				if(x!=0){
					if(tab[x].typ>=notyp&&tab[x].typ<=chars)
						tab[prt].typ=tab[x].typ;
					else
						err.error(linenum,15);
				}
				else
					skip(s2,2);
			}
			else
				err.error(linenum,10);
		}
		else
			err.error(linenum,5);
	}
			if(sy==semicolon)
				insymbol();
			else if(level!=1)
				err.error(linenum,14);
			do{
				if(sy==constsy)
					constdec(fsys,level);
				if(sy==typesy)
					typedec(fsys,level);
				if(sy==varsy)
					variabledec(fsys,dx,level);
				btab[prb].vsize=dx;
				while(sy==procsy||sy==funcsy)
					procdec(fsys,level);
				test(s3,s4,56);
				if(sy==eof)
					break;
			}while(!statbegsys.InSet(sy));	
			tab[prt].adr=lc;
			if(sy==beginsy){
			insymbol();
			statement(s5,level);
			while(sy==semicolon){
					insymbol();
				    statement(s5,level);
				}
			if(sy==endsy)
				insymbol();
			else
				err.error(linenum,57);
			}
		test(s7,s7,6);
}
//打印p代码到一个文件
void printpcode(FILE *fp){
	int i;
	order o;
	char *mne[64];
	mne[0]="LDA  ";mne[1]="LOD  ";mne[2]="LDI  ";
	mne[3]="DIS  ";mne[8]="FCT  ";mne[9]="INT  ";
	mne[10]="JMP  ";mne[11]="JPC  ";mne[12]="JPG  ";
	mne[13]="CAS  ";mne[14]="F1U  ";mne[15]="F2U  ";
	mne[16]="F1D  ";mne[17]="F2D  ";  mne[18]="MKS  ";
	mne[19]="CAL  ";mne[20]="IDX  ";mne[21]="IXX  ";
	mne[22]="LDB  ";mne[23]="CPB  ";mne[24]="LDC  ";
	mne[25]="LDR  ";mne[26]="FLT  ";mne[27]="RED  ";
	mne[28]="WRS  ";mne[29]="WRW  ";mne[30]="WRU  ";
	mne[31]="HLT  ";mne[32]="EXP  ";mne[33]="EXF  ";
	mne[34]="LDT  ";mne[35]="NOT  ";mne[36]="MUS  ";
	mne[37]="WRR  ";mne[38]="STO  ";mne[39]="EQR  ";
	mne[40]="NER  ";mne[41]="LSR  ";mne[42]="LRE  ";
	mne[43]="GTR  ";mne[44]="GRE  ";mne[45]="EQL  ";
	mne[46]="NEQ  ";mne[47]="LSS  ";mne[48]="LEQ  ";
	mne[49]="GRT  ";mne[50]="GEQ  ";mne[51]="ORR  ";
	mne[52]="ADD  ";mne[53]="SUB  ";mne[54]="ADR  ";
	mne[55]="SUR  ";mne[56]="AND  ";mne[57]="MUL  ";
	mne[58]="DIV  ";mne[59]="MOD  ";mne[60]="MUR  ";
	mne[61]="DIR  ";mne[62]="RDL  ";mne[63]="WRL  ";

	fprintf(fp,"   ******The List Of Pcode******\n");
	for(i=0;i<lc;++i){
		fprintf(fp,"%5d ",i);
		o=code[i];
		fprintf(fp,"%s%5d  ",mne[o.f],o.f);
		if(o.f<31){
			if(o.f<4){
			fprintf(fp,"%5d    %5d",o.x,o.y);
			}
			else
			{
			fprintf(fp,"%5d",o.y);
			}
		}
		else
		{
			fprintf(fp,"          ");
		}
		fprintf(fp,"\n");
	}

}
//登陆基本数据类型和标准输入输出函数的标识符号
void enterids(){
	enter("           ",variable,notyp,0);
	enter("real       ",typel,reals,1);
	enter("char       ",typel,chars,1);
	enter("integer    ",typel,ints,1);
	enter("read       ",procedure,notyp,1);
	enter("write      ",procedure,notyp,3);
	enter("writeln    ",procedure,notyp,4);
	enter("           ",procedure,notyp,0);
}
//输出二进制p代码文件
void printbinary(char *file){
	char bfile[300];
	strcpy(bfile,file);
	strcat(bfile,".bpl");
	FILE *fp=fopen(bfile,"wb");
	fwrite(&t,sizeof(int),1,fp);
//	fprintf(fp,"%d",t);
	fwrite(tab,sizeof(table),t+1,fp);
	fwrite(&b,sizeof(int),1,fp);
//	fprintf(fp,"%d",b);
	fwrite(btab,sizeof(btable),b+1,fp);
	fwrite(&sx,sizeof(int),1,fp);
//	fprintf(fp,"%d",sx);
	fwrite(stab,sizeof(char),sx+1,fp);
	fwrite(&c2,sizeof(int),1,fp);
//	fprintf(fp,"%d",c2);
	fwrite(rconst,sizeof(double),c2+1,fp);
	fwrite(&lc,sizeof(int),1,fp);
//	fprintf(fp,"%d",lc);
	fwrite(code,sizeof(order),lc+1,fp);
	fwrite(&a,sizeof(int),1,fp);
	fwrite(atab,sizeof(atable),a+1,fp);
	fclose(fp);

}
//对用户的pl源程序进行编译
extern "C" _declspec(dllexport) int compiler(char *file){
   	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	FILE *out;
	char filein[200];
	setup();
	constbegsys+=plus1;    constbegsys+=minus1;
    constbegsys+=intcon;   constbegsys+=realcon;
	constbegsys+=charcon;  constbegsys+=ident;

	blockbegsys+=constsy;  blockbegsys+=varsy;
	blockbegsys+=procsy;   blockbegsys+=funcsy;
	blockbegsys+=beginsy;  blockbegsys+=typesy;

	facbegsys+=intcon;     facbegsys+=realcon;
	facbegsys+=charcon;    facbegsys+=ident;
	facbegsys+=lparent;

	statbegsys+=beginsy;   statbegsys+=ifsy;
	statbegsys+=whilesy;   statbegsys+=forsy;

	typebegsys+=ident;     typebegsys+=arraysy;
	typebegsys+=recordsy;

	lc=0;        
	ch=' ';
	err.num=0;
	canexe=false;

	if(strcmp(file,"")==0)
	{
		AfxMessageBox("文件为空!");
		return 1;
	}
	psin=fopen(file,"r");
	if(!psin)
	{
	    AfxMessageBox("错误的输入文件名!");
		return 1;
	}
	strcpy(filein,file);
	strcat(filein,".pl");
	strcpy(outf,filein);
	out=fopen(outf,"w");
	if(!out)
		AfxMessageBox("错误的输入文件名!");
	t=-1;          a=0;
	b=1;           sx=0;
	c2=0;          display[0]=1;
	linenum=0;
    enterids();
	linenum=1;
	btab[1].last=t;btab[1].lastpar=1;btab[1].psize=0;btab[1].vsize=0;
	symset s1;
	s1+=blockbegsys;
	s1+=statbegsys;
		

    insymbol();
	block(s1,false,1);
	if(sy!=period)
	   err.error(linenum,2);
	emit(31);
    insymbol();
    if(sy!=eof)
			err.error(linenum,3);

	err.Disp();
	if(err.Number()==0){
		canexe=true;
		printpcode(out);
		printbinary(file);
		if(out)
			fclose(out);
	}
	if(psin)
	    fclose(psin);
	if(out)
		fclose(out);
	//cout <<"\nThe compiler finished!";
	if(err.Number()==0)
		return 0;
	else 
	return 1;
} 