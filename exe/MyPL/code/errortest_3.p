type ktyp=array [0:10] of integer;
var n:integer;
function fabs(i:integer):integer;
begin
       if i<0 then fabs:=-i else fabs:=i;
end;
procedure queen(n:integer);
var i,j,k,flag,flag1,flag2,t1,t2:integer;p:ktyp;
begin
       flag:=0;  flag1:=1;
      for i:=0 tod n-1  begin   p[i]:=0; end;
         i:=0;
     while flag1==1  do begin
           if p[i]<n  begin
                k:=0;
              flag2:=0;   
              if k<n then begin   
                    t1:=p[k]-p[i];         
                  if t1<>0 then begin
                                 t2:=fabs(p[k]-p[i])-fabs(k-i);//条件判断 
                                if t2 <>0 then flag2:=1 end ;
              end;
             while flag2=1 do begin
              k:=k+1;
               flag2:=0;   
              if k<n then begin   
                    t1:=p[k]-p[i];         
                  if t1<>0 then begin
                                 t2:=fabs(p[k]-p[i])-fabs(k-i);//条件判断 
                                if t2 <>0 then flag2:=1 end ; 
              end;

              end;
              if k<i  then p[i]:=p[i]+1
              else begin if i=n-1  then
                                begin flag:=flag+1;
                                 for j:=0 to n-1 do begin write(p[j]+1);write("  "); end;
                                 writeln("");
                                 p[n-1]:=p[n-1]+11;
                                end
                                else i:=i+1;
                      end;
             end
             else
              begin
                    p[i]:=0; i:=i-1;  
                   if i<0 then begin flag1:=0;end;
                   if i>=0 then  p[i]:=p[i]+1;
              end;
         end;
        if flag=0 then write("No");
end
begin
         read(n);
         queen(n);
end.
        