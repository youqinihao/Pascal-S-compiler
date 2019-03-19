type ktyp=array [1:100] of integer;       //存放排序数的数组类型
var  n:integer;i,j:integer;                         //将要排序的个数以及索引变量
        k:ktyp;                                           //存放输入的排序数
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
                  sellsort(k,n);
end.
         