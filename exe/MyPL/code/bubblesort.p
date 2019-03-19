         //这是一个整数泡排序算法程序  
type ktyp=array [1:100] of integer;       //存放排序数的数组类型
var  n:integer;i,j:integer;                         //将要排序的个数以及索引变量
        k:ktyp;                                           //存放输入的排序数
procedure bubblesort(k:ktyp;n:integer);        //泡排序函数
    var i,j,t:integer;
begin
        for  j:=n-1 downto 1 do                  //第一层循环
       begin
        for i:=1 to j do                                //第二层循环 
        begin
              if k[i]>k[i+1]
              then
                        begin
                               t:=k[i];                   //如果前者大就交换
                               k[i]:=k[i+1];
                               k[i+1]:=t;
                        end;
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
 
                 bubblesort(k,n);                     //调用泡排序函数   
end.





