type ktyp=array [1:100] of integer;         //�������������������
var  n:integer;i,j:integer;                         //��Ҫ����ĸ����Լ���������
        k:ktyp;                                             //��������������
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
                      else flag1:=0;               //�ȼ���!(k[s]<=k[i] || i==t))
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
                      else flag1:=0;               //�ȼ���!(k[s]<=k[t] || j==s))
               end while flag1=1;
                if i<j  then    swap(k[i],k[j])
                else  flag:=0 ;                    //���������ѭ�� 
            end;
               swap(k[s],k[j]); 
               quick(k,s,j-1);      //�ݹ���� 
               quick(k,j+1,t);      //�ݹ���� 
         end;
end;        
procedure quicksort(var k:ktyp;n:integer);
begin
           quick(k,1,n);
end;
begin
          
                 writeln("�������������ĸ�����");
                 read(n);                                   //���뽫Ҫ��������ĸ���
                 writeln("���������������");
                 for i:=1 to n do
                  begin 
                       read(k[i]);                           //���ζ������Ҫ������� 
                   end;     
                  quicksort(k,n);                     //���ÿ���������    
                  writeln("�����Ľ��:");                  //ѭ�����������
                  for j:=1 to  n do
                  begin
                    write(k[j]);write("  ");
                 end;
end.  

