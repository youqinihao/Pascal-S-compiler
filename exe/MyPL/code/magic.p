const   MaxN = 20;
type ktyp=array[ 0: MaxN ,0: MaxN ] of integer;
var    k:ktyp;n,i,j:integer;
procedure magic(var k:ktyp;n:integer);
var i,j,num,flag:integer;
begin
        for i:=0 to n-1 do begin
           for j:=0 to n-1 do
                    k[i][j]:=0;                   //���������Ԫ������
           end;
        i:=0; j:=n div 2;                     //ȷ��i,j�ĳ�ʼλ��
        for num:=1 to n*n do
          begin 
                       flag:=0;
                    if i<0 then
                    begin 
                         if j<0 then flag:=1
                    end;
                    if i>=0 then begin if j>=0 then begin
                    if k[i][j]<>0 then flag:=1;end;end;
                    if flag=1 then 
                    begin 
                    i:=i+2;
                    j:=j+1;
                    end;
                    k[i][j]:=num;  //����һ����num �����޸�λ�ã�i,j��
                     i:=i-1;  j:=j-1;
                     flag:=0;
                     if i<0 then begin if j>=0 then flag:=1 end;
                     if flag=1 then i:=n-1;         //����i��λ��
                     flag:=0;
                     if j<0 then begin if i>=0 then flag:=1 end;
                     if flag=1
                     then j:=n-1;                              //����j��λ��
                    
                     end;
end;
begin
              n:=13;
               magic(k,n);
               for i:=0 to n-1 do begin
                  for j:=0 to n-1 do begin
                  write( k[i][j]);write("   ");                   //���������Ԫ������
                    end;
                    writeln("");
               end;


end.
    
           
