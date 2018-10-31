function srednia = srednia_5s(sygnal,rozpraszacz, przedzial2, liczba_usrednien,delay)


L=liczba_usrednien;
%rozciecie sygnalu
for i=1:16
    for m=1:1:L 
        for j=1:przedzial2   
            wyciete(i,m,j) = sygnal(i,((rozpraszacz(m)+delay )+j));   %-delay)+(j-delay))));   
            
        end     
    end
end

for i=1:16  
        for j=1:przedzial2    
            srednia(i,j) = sum(wyciete(i,:,j))/L;   
        end          
end




