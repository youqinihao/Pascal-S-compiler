   //��������������˵ĳ��� 
type ktyp=array [0..20,0:20] of real;
var a,b,c:ktyp;i,j,n:integer;
procedure multi(a,b:ktyp,n:integer);
var i,j,k:integer;              
begin
                 for i:=0 to n-1 do begin
                           for j:=0 to n-1 do begin
                                       c[i][j]:=0;
                                       for k:=0 to n-1 do begin
                                              c[i][j:=a[i][k]*b[k][j]+c[i][j];
                                        end;
                           end;
                  end;
end;
begin
                writeln("����������ά����");
                read(n);
                writeln("�������һ������");
                for i:=0 to n-1 do begin
                      for j:=0 to n-1 do begin
                               read(a[i][j]);
                       end;
                end;
                writeln("������ڶ�������");
                for i:=0 to n-1 do begin
                      for j:=0 to n-1 do begin
                               read(b[i][j]);
                       end;
                end;
               multi(a,b,n);
               writeln("��˺�Ľ��Ϊ��");
                for i:=0 to n-1 do begin
                      for j:=0 to n-1 do begin
                               write(c[i][j]);write("  ");
                      end;
                      writeln("");
               end;

end.