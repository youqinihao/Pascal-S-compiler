         //����һ���ַ��������㷨����  
type ktyp=array [1:100] of char;       //��������ַ�����������
var  n:integer;i,j:integer;                         //��Ҫ����ĸ����Լ���������
        k:ktyp;                                           //��������������
procedure bubblesort(k:ktyp;n:integer);        //��������
    var i,j:integer;t:char;
begin
        
        for  j:=n-1 downto 1 do                  //��һ��ѭ��
       begin
        for i:=1 to j do                                //�ڶ���ѭ�� 
        begin
              if k[i]>k[i+1]
              then
                        begin
                               t:=k[i] ;               //���ǰ�ߴ�ͽ���
                               k[i]:=k[i+1];
                               k[i+1]:=t;
                        end;
        end;      
      end;
       writeln("�����Ľ��:");                  //ѭ�����������
       for j:=1 to  n do
       begin
        write(k[j]);
        end;
end;
begin
                 writeln("�����������ַ����ĸ�����");
                 read(n);                                   //���뽫Ҫ������ַ��ĸ���
                 writeln("�����β����������ַ���");
                 for i:=1 to n do
                  begin 
                      read(k[i]);                           //���ζ������Ҫ��������ַ�
                   end;     
 
                 bubblesort(k,n);                     //������������   
end.

