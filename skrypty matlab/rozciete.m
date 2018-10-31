function wyciete = rozciete(sygnal, przedzial,rozpraszacz,l_triali,delay)

for i=1:16
    for m=1:1:l_triali
        for j=1:przedzial   
            wyciete(i,j,m,1) = sygnal(i,((rozpraszacz(m)-delay)+(j-delay)));   
            
        end     
    end
end

end