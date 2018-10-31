function sr = srednia(sygnal,rozpraszacz,przedzial1, przedzial2, liczba_usrednien)

L=liczba_usrednien;
%rozciecie sygnalu
for i=1:16
    for m=1:1:L  % rozpraszacze
        for j=1:przedzial2  % sygnal(kanaly,:)
            wyciete(i,m,j) = sygnal(i,((rozpraszacz(m)-przedzial1)+j));   %wyciete(kanal,rozpraszacz,przedzial)          
        end     
    end
end

for i=1:16  
        for j=1:przedzial2    
            sr(i,j) = sum(wyciete(i,:,j))/L;   % sprawdz, sr(i,j) = sum(i,:,:)
        end          
end




