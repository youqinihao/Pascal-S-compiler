type ktyp=array [1:100] of integer;       //存放排序数的数组类型
var  n:integer;i,j:integer;                         //将要排序的个数以及索引变量
        k:ktyp;                                           //存放输入的排序数 
procedure insertsort(k:ktyp;n:integer);
var temp,i,j,flag:integer;
begin
      for i:=2 to n do
       begin
             temp:=k[i];
             j:=i-1;
             if j>0 then begin            //此三行等价于j>0&&temp<k[j]
                       if temp<k[j] then flag:=1 else flag:=0;//
             end else  flag:=0;         //
             while flag=1 do 
                 begin 
                       k[j+1]:=k[j];
                       j:=j-1;
  
                       if j>0 then begin               //此三行等价于j>0&&temp<k[j]
                       if temp<k[j] then flag:=1 else flag:=0;//
                        end else  flag:=0;          //
                 end;
                k[j+1]:=temp;
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
                   insertsort(k,n); 
end.
