// Error.cpp : implementation file
//

#include "stdafx.h"
#include "Error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CError

IMPLEMENT_DYNCREATE(CError, CCmdTarget)

CError::CError()
{
 num=0;
 err[0]="undef id|该标识符未定义";  
 err[1]="multi def|标识符重复定义";
 err[2]="identifier|应是标识符";
 err[3]="program incomplete|出现严重错误，程序无法继续编译";
 err[4]=")应是'）'";         
 err[5]=":|应是'：'，在说明类型时必须有此冒号";
 err[6]="syntax|非法符号，编译程序将跳读该符号和后面的某些符号";   
 err[7]="ident,var|形式参数表中，形参说明应以标识符或var开头";
 err[8]="of";       
 err[9]="应是'（'";
 err[10]="id,array|类型定义必须以标识符,array或record开头"; 
 err[11]="[|应是[";
 err[12]="]|应是]";       
 err[13]=":|应是':'";
 err[14]=";|应是'；'";     
 err[15]="fun.type|函数结果必须是integer，real，char类型";
 err[16]="=|应是'='，'：='，只能在赋值语句里使用，而不能在说明中使用";  
 err[17]="boolean";
 err[18]="convar typ|在for后面的循环变量只能是interger，char型";
 err[19]="type|for语句中初值或终值表达式必须与循环变量类型相同";
 err[20]="prog.param";
 err[21]="too big|数太大，最多为8位数字，其绝对值不超过10**9";
 err[22]=".|程序结尾是'。'，请检查相应的begin和end。";        
 err[23]="type(case)";
 err[24]="character|非法字符"; 
 err[25]="const id|在常量定义中，等号后面必须是常数或常量标识符";
 err[26]="index type|下标表达式必须与数组说明中的下标类型相同";
 err[27]="index bound|数组说明中,下界不能超过上界,同时它们的类型必须相同(同为整数,或字符),实数上下界是非法的";
 err[28]="no array|没有这样的数组";  
 err[29]="type id|应是类型标识符";
 err[30]="undef type|该类型没有定义(不允许递归定义类型";
 err[31]="no record|没有这样的记录";
 err[32]="bool type";
 err[33]="arith type|该算术表达式的类型不合法";
 err[34]="integer|mod运算的操作符必须是整数";   
 err[35]="types|相比较的对象的类型必须相同，除非它们一个是整型，另一个是实型";
 err[36]="param type|实参和对应的形参必须相同，除非要么形参为实数的值而实参为整型或字符型，要么形参为整型的值而实参为字符型";err[37]="variable id|应是变量";
 err[38]="string|字符串至少有一个字符";  
 err[39]="no. of pars|实参个数与形参个数不等";
 err[40]="real number|小数点后没有数字";
 err[41]="type|read或write的参数类型不正确";
 err[42]="real type|该表达式应为实型"; 
 err[43]="integer";
 err[44]="var,const|表达式中不能出现类型或过程标识符";  
 err[45]="var,proc|应是变量或过程、函数标识符";
 err[46]="types(:=)|在赋值语句中被赋变量应与表达式类型相同，除非前者为实型而后者为整型";  err[47]="typ(case)";
 err[48]="type";      
 err[49]="store ovfl|内存溢出";
 err[50]="constant|应是常量";  
 err[51]=":=|应是'：='"; 
 err[52]="then|应是then ";    
 err[53]="while|应是while";
 err[54]="do|应是do";       
 err[55]="to downto|应是to或downto";
 err[56]="begin|应是begin";     
 err[57]="end|应是end";
 err[58]="factor|因子必须以标识符，常量，或'（'开始";

}

CError::~CError()
{

}
void CError::error(int line,int err){
	
	if(num<errmax){
		errors[num]=err;
		lines[num++]=line;
	}
	
}


BEGIN_MESSAGE_MAP(CError, CCmdTarget)
	//{{AFX_MSG_MAP(CError)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CError message handlers
