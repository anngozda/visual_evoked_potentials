function przedzialy(sygnal,kanal, rozpraszacz,x, przedzial1,przedzial2)

s1= (sygnal(kanal,rozpraszacz(x)-przedzial1:rozpraszacz(x)+przedzial2));
s2=sygnal(kanal,rozpraszacz(x+1)-przedzial1:rozpraszacz(x+1)+przedzial2);
plot(s1);
hold on
plot(s2);
figure
plot(s1-s2);

end