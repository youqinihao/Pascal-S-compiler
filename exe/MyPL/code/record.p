
//���ü�¼���ͽ�N�����ɴ�С�����������������ʾÿ����ԭ����λ����š� 

type     dd=record                        //{����DD��¼����} 
            ii:integer;                        //{����ii��ʾ��} 
            id:integer                         //{����id��ʾ��ii��λ�����} 
            end; 
var a:array[1:100]of dd; 
       i,j,k,n:integer; 
       t:dd; 
begin 
      writeln("���������ĸ���:"); 
       read(n); 
      writeln("�������������:"); 
      i:=1; 
     for i:=1 to n do 
       begin 
          read(a[i].ii); 
         a[i].id:=i;       
          for j:=1 to i-1 do          //�������� 
           if a[j].ii<a[i].ii then 
              begin 
                t:=a[i]; 
                for k:=i-1 downto j do 
                  a[k+1]:=a[k]; 
                a[j]:=t; 
              end; 
        end; 
     writeln("���Ϊ��");
      for i:=1 to n do 
        begin 
          write(a[i].ii);write("  ");write(a[i].id);writeln("");
        end; 
end.