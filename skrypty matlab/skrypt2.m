
function [target,nontarget,distractor,ref]=  skrypt2(data,dataRef,fs, f1,f2)

[hdr,rec]=edfread(data);   %wczytanie skryptu czytaj¹cego pliki edf 
[hdr,recRef]=edfread(dataRef);
%  for m=1:17
%  syg(m,:)=downsample(rec(m,:),2);
%  sygRef(m,:)=downsample(recRef(m,:),2);
%  end

A = diff(rec(17,:));   % liczy roznice pomiedzy probkami w kanale z flagami
[pks,x] = findpeaks(A,'MinPeakDistance',700);   % znajduje piki 
rozpr = 0; 
rozpr1=0;
rozpr2=0;% zeby nie napdpisywac daje 0 , start i stop ma zawsze t¹ sam¹ wartoœc pierwsza i osattnia wiec nie musze zerowac 
%p1=0;
for i=1:length(pks)
   if pks(i) == 256
       rozpr =  [rozpr,x(i)];
   else if pks(i) == 512
       rozpr1 = [rozpr1,x(i)];
  
   else if pks(i) == 1024  
       rozpr2 = [rozpr2,x(i)];
      end
      end
   end
end
rozpr = rozpr(2:length(rozpr));   %wycinam zero ktore daje na starcie
rozpr1 = rozpr1(2:length(rozpr1)); 
rozpr2 = rozpr2(2:length(rozpr2)); 
%rozciete = rec(:,start:stop);  % wyciecie wszystkich kanalow od star do stop

ref_filtr = butterworth_band_pass(recRef,fs,f1,f2);
syg_filtr = butterworth_band_pass(rec,fs,f1,f2);  % filtracjabp(syg,bp); rec(kanaly,:)

target = srednia(syg_filtr,rozpr,100,1600,10);  % 1600
nontarget = srednia(syg_filtr,rozpr1,100,1600,125);
distractor = srednia(syg_filtr,rozpr2,100,1600,20);

ref =  srednia(ref_filtr,12000:2000:72000,100,1600,30);     %1600:96400,100,1600,30); 

