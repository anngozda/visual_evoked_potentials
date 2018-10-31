
function [SSVEP,syg_avg,ref,ref_sincos]= fftSSVEP(data,dataRef,fs,freq,samples)

[hdr,rec]=edfread(data);   %wczytanie skryptu czytaj¹cego pliki edf 
[hdr,recRef]=edfread(dataRef);
  for m=1:17
  syg(m,:)=downsample(rec(m,:),4);   % dla b7 - 4
  sygRef(m,:)=downsample(recRef(m,:),4);
  end

A = diff(syg(17,:));   % liczy roznice pomiedzy probkami w kanale z flagami
[pks,x] = findpeaks(A);   % znajduje piki 
rozpr = 0; 
rozpr1=0;
rozpr2=0;
rozpr3=0;

for i=1:length(pks)
   if pks(i) == 256
       rozpr =  [rozpr,x(i)];
   else if pks(i) == 512
       rozpr1 = [rozpr1,x(i)];
  
   else if pks(i) == 1024  
       rozpr2 = [rozpr2,x(i)];
   else if pks(i) == 2048  
       rozpr3 = [rozpr3,x(i)];
      end
      end
      end
   end
end
rozpr = rozpr(2:length(rozpr));  
rozpr1 = rozpr1(2:length(rozpr1)); 
rozpr2 = rozpr2(2:length(rozpr2));
rozpr3 = rozpr3(2:length(rozpr3)); 
%rozciete = rec(:,start:stop);  % wyciecie wszystkich kanalow od star do stop

ref_filtr = butterworth_band_pass(sygRef,fs,6.5,13);
syg_filtr = butterworth_band_pass(syg,fs,6.5,13);  % filtracjabp(syg,bp); 

syg_avg(:,:,1) = srednia_5s(syg_filtr,rozpr,samples,10,218);  %218 opoznienie
syg_avg(:,:,2) = srednia_5s(syg_filtr,rozpr1,samples,10,218);
syg_avg(:,:,3) = srednia_5s(syg_filtr,rozpr2,samples,10,218);
syg_avg(:,:,4) = srednia_5s(syg_filtr,rozpr3,samples,10,218);

SSVEP(:,:,:,1)=rozciete(syg_filtr,samples,rozpr,10,218);  
SSVEP(:,:,:,2)=rozciete(syg_filtr,samples,rozpr1,10,218);
SSVEP(:,:,:,3)=rozciete(syg_filtr,samples,rozpr2,10,218);
SSVEP(:,:,:,4)=rozciete(syg_filtr,samples,rozpr3,10,218);

ref =  srednia_5s(ref_filtr,1000:1024:26624,samples,25,0);

ref_sincos(:,:,:,:) = reference(freq,fs, samples, 2);
