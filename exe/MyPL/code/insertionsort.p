type ktyp=array [1:100] of integer;       //�������������������
var  n:integer;i,j:integer;                         //��Ҫ����ĸ����Լ���������
        k:ktyp;                                           //�������������� 
procedure insertsort(k:ktyp;n:integer);
var temp,i,j,flag:integer;
begin
      for i:=2 to n do
       begin
             temp:=k[i];
             j:=i-1;
             if j>0 then begin            //�����еȼ���j>0&&temp<k[j]
                       if temp<k[j] then flag:=1 else flag:=0;//
             end else  flag:=0;         //
             while flag=1 do 
                 begin 
                       k[j+1]:=k[j];
                       j:=j-1;
  
                       if j>0 then begin               //�����еȼ���j>0&&temp<k[j]
                       if temp<k[j] then flag:=1 else flag:=0;//
                        end else  flag:=0;          //
                 end;
                k[j+1]:=temp;
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
                   insertsort(k,n); 
end.
