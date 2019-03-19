
//词法分析时将会用到的数据结构


#include "symset.h"

const int nkw=19,       //保留字个数
          alng=10,      //标识符的字符最大个数
          kmax=9,       //整数的最大数字个数
          tmax=100,     //符号表的最大尺寸
		  amax=30,      //数组信息向量表的的大小
          bmax=20,      //分程序表的最大尺寸
          c2max=20,     //实常量表的尺寸
	      cmax=800,     //代码数组的尺寸
	      lmax=7,       //层次的最大数
	      smax=600,     //字符串常量的尺寸
          ermax=58,     //最大错误数
		  nmax=100000000,      //最大整数
	      stacksize=1450;      //运行栈的最大尺寸

//单词符号的类别
enum symbol {intcon,realcon,charcon,stringcon,
			 plus1,minus1,times,idiv,rdiv,
			 eql,neq,gtr,geq,lss,leq,
			 lparent,rparent,comma,semicolon,period,
			 colon,becomes,constsy,varsy,funcsy,
			 procsy,ident,beginsy,ifsy,whilesy,forsy,endsy,
			 elsesy,dosy,tosy,downtosy,thensy,eof,lbrack,rbrack,
			 typesy,arraysy,recordsy,ofsy
};
//符号对象
enum object {constant,variable,typel,procedure,function};
//符号类型
enum types  {notyp,ints,reals,chars,arrays,records};
//常量，程序块，因子，语句的开始符号集
symset constbegsys,blockbegsys,facbegsys,statbegsys,typebegsys;
//表达式返回类型
struct item{
	types typ;
	int ref;
};
//指令结构
struct order{
	int f;
	int x;
	int y;
	int l;    //生成该指令的源程序的行号
};
//分程序结构
struct btable{
	int last,lastpar,psize,vsize,line;
};
//符号表结构
struct table{
	char name[alng+1];     int link;
	object obj;            types typ;
	int ref;    	       int lev;       
	int adr;               bool normal;
    int line;
};
//数组信息向量表结构
struct atable{
	types inxtyp,eltyp;
	int elref,low,high,elsize,size;
};
//表达式求值返回
struct conrec{
	types tp;
	int i;
	double r;
};
//运行栈的结构
union datastack{
	int i;
	double r;
	};