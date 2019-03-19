
//利用记录类型将N个数由大到小排序，输出排序结果并显示每个数原来的位置序号。 

type     dd=record                        //{定义DD记录类型} 
            ii:integer;                        //{域名ii表示数} 
            id:integer                         //{域名id表示数ii的位置序号} 
            end; 
var a:array[1:100]of dd; 
       i,j,k,n:integer; 
       t:dd; 
begin 
      writeln("请输入数的个数:"); 
       read(n); 
      writeln("请依次输入各数:"); 
      i:=1; 
     for i:=1 to n do 
       begin 
          read(a[i].ii); 
         a[i].id:=i;       
          for j:=1 to i-1 do          //插入排序 
           if a[j].ii<a[i].ii then 
              begin 
                t:=a[i]; 
                for k:=i-1 downto j do 
                  a[k+1]:=a[k]; 
                a[j]:=t; 
              end; 
        end; 
     writeln("结果为：");
      for i:=1 to n do 
        begin 
          write(a[i].ii);write("  ");write(a[i].id);writeln("");
        end; 
end.