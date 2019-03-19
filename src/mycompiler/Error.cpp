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
 err[0]="undef id|�ñ�ʶ��δ����";  
 err[1]="multi def|��ʶ���ظ�����";
 err[2]="identifier|Ӧ�Ǳ�ʶ��";
 err[3]="program incomplete|�������ش��󣬳����޷���������";
 err[4]=")Ӧ��'��'";         
 err[5]=":|Ӧ��'��'����˵������ʱ�����д�ð��";
 err[6]="syntax|�Ƿ����ţ�������������÷��źͺ����ĳЩ����";   
 err[7]="ident,var|��ʽ�������У��β�˵��Ӧ�Ա�ʶ����var��ͷ";
 err[8]="of";       
 err[9]="Ӧ��'��'";
 err[10]="id,array|���Ͷ�������Ա�ʶ��,array��record��ͷ"; 
 err[11]="[|Ӧ��[";
 err[12]="]|Ӧ��]";       
 err[13]=":|Ӧ��':'";
 err[14]=";|Ӧ��'��'";     
 err[15]="fun.type|�������������integer��real��char����";
 err[16]="=|Ӧ��'='��'��='��ֻ���ڸ�ֵ�����ʹ�ã���������˵����ʹ��";  
 err[17]="boolean";
 err[18]="convar typ|��for�����ѭ������ֻ����interger��char��";
 err[19]="type|for����г�ֵ����ֵ���ʽ������ѭ������������ͬ";
 err[20]="prog.param";
 err[21]="too big|��̫�����Ϊ8λ���֣������ֵ������10**9";
 err[22]=".|�����β��'��'��������Ӧ��begin��end��";        
 err[23]="type(case)";
 err[24]="character|�Ƿ��ַ�"; 
 err[25]="const id|�ڳ��������У��Ⱥź�������ǳ���������ʶ��";
 err[26]="index type|�±���ʽ����������˵���е��±�������ͬ";
 err[27]="index bound|����˵����,�½粻�ܳ����Ͻ�,ͬʱ���ǵ����ͱ�����ͬ(ͬΪ����,���ַ�),ʵ�����½��ǷǷ���";
 err[28]="no array|û������������";  
 err[29]="type id|Ӧ�����ͱ�ʶ��";
 err[30]="undef type|������û�ж���(������ݹ鶨������";
 err[31]="no record|û�������ļ�¼";
 err[32]="bool type";
 err[33]="arith type|���������ʽ�����Ͳ��Ϸ�";
 err[34]="integer|mod����Ĳ���������������";   
 err[35]="types|��ȽϵĶ�������ͱ�����ͬ����������һ�������ͣ���һ����ʵ��";
 err[36]="param type|ʵ�κͶ�Ӧ���βα�����ͬ������Ҫô�β�Ϊʵ����ֵ��ʵ��Ϊ���ͻ��ַ��ͣ�Ҫô�β�Ϊ���͵�ֵ��ʵ��Ϊ�ַ���";err[37]="variable id|Ӧ�Ǳ���";
 err[38]="string|�ַ���������һ���ַ�";  
 err[39]="no. of pars|ʵ�θ������βθ�������";
 err[40]="real number|С�����û������";
 err[41]="type|read��write�Ĳ������Ͳ���ȷ";
 err[42]="real type|�ñ��ʽӦΪʵ��"; 
 err[43]="integer";
 err[44]="var,const|���ʽ�в��ܳ������ͻ���̱�ʶ��";  
 err[45]="var,proc|Ӧ�Ǳ�������̡�������ʶ��";
 err[46]="types(:=)|�ڸ�ֵ����б�������Ӧ����ʽ������ͬ������ǰ��Ϊʵ�Ͷ�����Ϊ����";  err[47]="typ(case)";
 err[48]="type";      
 err[49]="store ovfl|�ڴ����";
 err[50]="constant|Ӧ�ǳ���";  
 err[51]=":=|Ӧ��'��='"; 
 err[52]="then|Ӧ��then ";    
 err[53]="while|Ӧ��while";
 err[54]="do|Ӧ��do";       
 err[55]="to downto|Ӧ��to��downto";
 err[56]="begin|Ӧ��begin";     
 err[57]="end|Ӧ��end";
 err[58]="factor|���ӱ����Ա�ʶ������������'��'��ʼ";

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
