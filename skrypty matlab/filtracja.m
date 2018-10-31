function [Lp,lp,del] = filtracja (sygnal, dolno, gorno)

l_kanalow = 16;
%  for m=1:l_kanalow
%  syg(m,:)=downsample(sygnal(m,:),2);
%  end


for i=1:l_kanalow
   Lp(i,:) = filter(dolno,sygnal(i,:));
   l=length(Lp(i,:));
   del = mean(grpdelay(dolno));
   lp(i,:) = Lp(i,del:l);
   Hp(i,:) = filter(gorno, lp(i,:));
   l1=length(Hp(i,:));
   del2 = mean(grpdelay(gorno));
   hp(i,:) = Hp(i,del2:l1);
end