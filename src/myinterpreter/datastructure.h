//�ʷ�����ʱ�����õ������ݽṹ

const int nkw=15,       //�����ָ���
          alng=10,      //��ʶ�����ַ�������
          kmax=9,       //������������ָ���
          tmax=100,     //���ű�����ߴ�
          amax=30,      //������Ϣ������ĵĴ�С
          bmax=20,      //�ֳ��������ߴ�
          c2max=20,     //ʵ������ĳߴ�
	      cmax=800,     //��������ĳߴ�
	      lmax=7,       //��ε������
	      smax=600,     //�ַ��������ĳߴ�
          ermax=58,     //��������
		  nmax=100000000,      //�������
	      stacksize=3000;      //����ջ�����ߴ�

//���ʷ��ŵ����
enum symbol {intcon,realcon,charcon,stringcon,
			 plus1,minus1,times,idiv,rdiv,
			 eql,neq,gtr,geq,lss,leq,
			 lparent,rparent,comma,semicolon,period,
			 colon,becomes,constsy,varsy,funcsy,
			 procsy,ident,beginsy,ifsy,whilesy,forsy,endsy,
			 elsesy,dosy,tosy,downtosy,thensy,eof};
//���Ŷ���
enum object {constant,variable,typel,procedure,function};
//��������
enum types  {notyp,ints,reals,chars};

//���ʽ��������
struct item{
	types typ;
	int ref;
};
//ָ��ṹ
struct order{
	int f;
	int x;
	int y;
	int l;    //���ɸ�ָ���Դ������к�
};
//�ֳ���ṹ
struct btable{
	int last,lastpar,psize,vsize,line;
};
//���ű�ṹ
struct table{
	char name[alng+1];     int link;
	object obj;            types typ;
	int ref;    	       int lev;       
	int adr;               bool normal;
	int line;
};
//������Ϣ������ṹ
struct atable{
	types inxtyp,eltyp;
	int elref,low,high,elsize,size;
};
//���ʽ��ֵ����
struct conrec{
	types tp;
	int i;
	double r;
};
//����ջ�Ľṹ
union datastack{
	int i;
	double r;
	};