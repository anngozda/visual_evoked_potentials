function sr = srednia9kw(sygnal,rozpraszacz,przedzial1, przedzial2, liczba_usrednien)

m1=[1:2:49];
m2=[2:2:50];

t=[0:0.000488:0.439];
%L= (length(rozpraszacz))-4;

%rozciecie sygnalu  
for i=1:16
    for m=2:liczba_usrednien
        for j=1:przedzial2      %sygnal(target(1-9),channel,przedzial 1-61761))
            wyciete(i,m,j) = sygnal(:,i,((rozpraszacz(m)-przedzial1)+j));   %wyciete(kanal,rozpraszacz,przedzial)            
        end     
    end
end

for i=1:16  
   for j=1:przedzial2
            sr(i,j) = sum(wyciete(i,:,j))/(liczba_usrednien-1);   
   end          
end




