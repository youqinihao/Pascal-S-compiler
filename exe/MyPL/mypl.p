type ktyp=array [1:100] of integer;         //存放排序数的数组类型
var  n:integer;i,j:integer;                         //将要排序的个数以及索引变量
        k:ktyp;                                             //存放输入的排序数
procedure swap(var a,b:integer);
var temp:integer;
begin
     temp:=a; a:=b; b:=temp;
end;
procedure quick(var k:ktyp;s,t:integer);
var i,j,flag,flag1:integer;
begin
       flag:=1;
       if s<t 
       then
        begin 
                    i:=s; j:=t+1;
            while flag=1 do
            begin 
                do
                begin
                      i:=i+1;
                      if k[s]>k[i]
                      then 
                        begin
                         if i<>t  then flag1:=1 //  
                         else flag1:=0            //
                        end                            //
                      else flag1:=0;               //等价于!(k[s]<=k[i] || i==t))
                end while flag1=1;
               do
               begin
                      j:=j-1;
                      if k[s]<k[j]
                      then 
                        begin
                         if j<>s  then flag1:=1 //  
                         else flag1:=0            //
                        end                            //
                      else flag1:=0;               //等价于!(k[s]<=k[t] || j==s))
               end while flag1=1;
                if i<j  then    swap(k[i],k[j])
                else  flag:=0 ;                    //跳出最外层循环 
            end;
               swap(k[s],k[j]); 
               quick(k,s,j-1);      //递归调用 
               quick(k,j+1,t);      //递归调用 
         end;
end;        
procedure quicksort(var k:ktyp;n:integer);
begin
           quick(k,1,n);
end;
begin
          
                 writeln("请输入排序数的个数：");
                 read(n);                                   //输入将要排序的数的个数
                 writeln("请依次输入各数：");
                 for i:=1 to n do
                  begin 
                       read(k[i]);                           //依次读入各将要排序的数 
                   end;     
                  quicksort(k,n);                     //调用快速排序函数    
                  writeln("排序后的结果:");                  //循环输出排序结果
                  for j:=1 to  n do
                  begin
                    write(k[j]);write("  ");
                 end;
end.  

