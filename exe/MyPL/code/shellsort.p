type ktyp=array [1:100] of integer;       //�������������������
var  n:integer;i,j:integer;                         //��Ҫ����ĸ����Լ���������
        k:ktyp;                                           //��������������
procedure sellsort(k:ktyp;n:integer);
var i,j,flag,gap,temp:integer;
begin 
      gap:=n;
       while gap>1  do
       begin
         gap:=gap div 2;
         do begin
                    flag:=0;
                    for i:=1 to n-gap-1 do 
                      begin  j:=i+gap;
                          if k[i]>k[j] then 
                         begin
                                  temp:=k[j];    k[j]:=k[i];    k[i]:=temp;
                                  flag:=1;                            
                         end;
                      end;
                 end while flag<>0;
          end;
             writeln("�����Ľ��:");                  //ѭ�����������
             for j:=1 to  n do
             begin
             write(k[j]);write("  ");
             end;
end;
begin
                writeln("�������������ĸ�����");
                 read(n);                                   //���뽫Ҫ��������ĸ���
                 writeln("���������������");
                 for i:=1 to n do
                  begin 
                      read(k[i]);                           //���ζ������Ҫ������� 
                  end; 
                  sellsort(k,n);
end.
         