type ktyp=array [1:100] of integer;       //�������������������
var  n:integer;i,j:integer;                         //��Ҫ����ĸ����Լ���������
        k:ktyp;                                           //��������������
procedure selectsort(k:ktyp;n:integer);
var i,j,d,temp:integer;
begin
    for i:=1 to n-1 do begin
         d:=i;
          for j:=i+1 to n do begin
                 if k[j]<k[d] then
                    d:=j;
              end;
                if d<>i then begin
                 temp:=k[d];
                 k[d]:=k[i];
                 k[i]:=temp;
                end;
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
                  selectsort(k,n);
end.