type ktyp=array [1:100] of integer;       //存放排序数的数组类型
var  n:integer;i,j:integer;                         //将要排序的个数以及索引变量
        k:ktyp;                                           //存放输入的排序数
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
         writeln("排序后的结果:");                  //循环输出排序结果
        for j:=1 to  n do
        begin
            write(k[j]);write("  ");
        end;
end;
begin
                 writeln("请输入排序数的个数：");
                 read(n);                                   //输入将要排序的数的个数
                 writeln("请依次输入各数：");
                 for i:=1 to n do
                  begin 
                      read(k[i]);                           //依次读入各将要排序的数 
                  end;   
                  selectsort(k,n);
end.