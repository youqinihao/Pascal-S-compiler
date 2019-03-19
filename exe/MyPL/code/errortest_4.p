const M=200;
type ktyp=array [0:M]  integer;
var m,n,i:integer;
function reccurresive(m,n:integer):integer;
var top,flag  integer;stack:ktyp;
begin
            top:=-1;
           do begin
                    flag:=m*n;
                    if flag <> 0 then begin
                       top:=top+1;
                       stack[top]:=m-1;
                         n:=n-1;
                      end else begin
                     n:=m+n+1;
                   if top>=0
                    then  m:=stack[top];
                  top:=top-1;
                   end;
           end while top>=-1;
         reccurresive:=n;
end;
function F(m,n:integer):integer;
var flag:integer;
begin 
        flag:=m*n;
         if flag=0
         then F:=m+n+1
         else F:=F(m-1,F(m,n-1),1);
          write(i);i:=i+1; write("  ");//¸ú×ÙµÝ¹é´ÎÊý 
end;
begin
           m:=3;n:=4;i:=0;
     //    writeln(reccurresive(m,n)); 
            writeln(F(m,n));
end.