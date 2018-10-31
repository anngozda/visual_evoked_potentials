
function [SSVEP,syg_avg,ref,ref_sincos]= skryptSSVEP_12kwa(data,dataRef,fs,freq,samples)

[hdr,rec]=edfread(data);   
[hdr,recRef]=edfread(dataRef);

  for m=1:17
  syg(m,:)=downsample(rec(m,:),8);   
  sygRef(m,:)=downsample(recRef(m,:),8);
  end
  
 A = diff(syg(17,:));   % liczy roznice pomiedzy probkami w kanale z flagami
[pks,x] = findpeaks(A,'MinPeakDistance',40);    

pks1(1)=0;
x1(1)=0;
for i=1:length(pks)
   pks1(i+1)=pks(i);
   x1(i+1)=x(i);
end

rozpr1 = 0;
rozpr2 = 0;
rozpr3 = 0;
rozpr4 = 0;  
rozpr5 = 0; 
rozpr6 = 0;
rozpr7 = 0;  
rozpr8 = 0; 
rozpr9 = 0;
rozpr10 = 0;  
rozpr11 = 0; 
rozpr12 = 0;

for i=2:length(pks1)-1
   
   if (pks1(i-1) == 16384) && (pks1(i) == 32768) && (x1(i)-x1(i-1)< 650)    
      rozpr12 = [rozpr12,x1(i-1)];
   else if (pks1(i-1) == 4096) && (pks1(i) == 8192) && (x1(i)-x1(i-1)<650)
      rozpr11 = [rozpr11,x1(i-1)];
   else if (pks1(i-1) == 1024) && (pks1(i) == 2048) && (x1(i)-x1(i-1)<650)
      rozpr10 = [rozpr10,x1(i-1)];
   else if (pks1(i-1) == 256) && (pks1(i) == 512) && (x1(i)-x1(i-1)<650)
      rozpr9 = [rozpr9,x1(i-1)];
   else if (pks1(i) == 256) && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr1 = [rozpr1,x1(i)];
   else if (pks1(i) == 512) && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr2 = [rozpr2,x1(i)];
   else if pks1(i) == 1024 && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr3 = [rozpr3,x1(i)];
   else if pks1(i) == 2048 && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr4 = [rozpr4,x1(i)];
   else if pks1(i) == 4096 && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr5 = [rozpr5,x1(i)];
   else if pks1(i) == 8192 && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr6 = [rozpr6,x1(i)];
   else if pks1(i) == 16384 && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr7 = [rozpr7,x1(i)];
   else if pks1(i) == 32768 && (x1(i+1)-x1(i)>650) && (x1(i)-x1(i-1)>650)
      rozpr8 = [rozpr8,x1(i)];

   end
   end
   end
   end
   end
   end
   end
   end
   end
   end
   end
   end 
end

  %wycinam zero ktore daje na starcie
rozpr1 = rozpr1(2:length(rozpr1)); 
rozpr2 = rozpr2(2:length(rozpr2));
rozpr3 = rozpr3(2:length(rozpr3)); 
rozpr4 = rozpr4(2:length(rozpr4)); 
rozpr5 = rozpr5(2:length(rozpr5));
rozpr6 = rozpr6(2:length(rozpr6)); 
rozpr7 = rozpr7(2:length(rozpr7)); 
rozpr8 = rozpr8(2:length(rozpr8));
rozpr9 = rozpr9(2:length(rozpr9)); 
rozpr10 = rozpr10(2:length(rozpr10)); 
rozpr11 = rozpr11(2:length(rozpr11));
rozpr12 = rozpr12(2:length(rozpr12)); 
%rozciete = rec(:,start:stop);  % wyciecie wszystkich kanalow od star do stop

ref_filtr = butterworth_band_pass(sygRef,fs,6.5,13);
syg_filtr = butterworth_band_pass(syg,fs,6.5,13);  % filtracjabp(syg,bp); 

%syg_avg(channel, samples,frequency)
syg_avg(:,:,1) = srednia_5s(syg_filtr,rozpr1,samples,10,35);     %218);
syg_avg(:,:,2) = srednia_5s(syg_filtr,rozpr2,samples,10,35);
syg_avg(:,:,3) = srednia_5s(syg_filtr,rozpr3,samples,10,35);
syg_avg(:,:,4) = srednia_5s(syg_filtr,rozpr4,samples,10,35);
syg_avg(:,:,5) = srednia_5s(syg_filtr,rozpr5,samples,10,35);
syg_avg(:,:,6) = srednia_5s(syg_filtr,rozpr6,samples,10,35);
syg_avg(:,:,7) = srednia_5s(syg_filtr,rozpr7,samples,10,35);
syg_avg(:,:,8) = srednia_5s(syg_filtr,rozpr8,samples,10,35);
syg_avg(:,:,9) = srednia_5s(syg_filtr,rozpr9,samples,10,35);
syg_avg(:,:,10) = srednia_5s(syg_filtr,rozpr10,samples,10,35);
syg_avg(:,:,11) = srednia_5s(syg_filtr,rozpr11,samples,10,35);
syg_avg(:,:,12) = srednia_5s(syg_filtr,rozpr12,samples,10,35);

SSVEP(:,:,:,1)=rozciete(syg_filtr,samples,rozpr1,10,35);  
SSVEP(:,:,:,2)=rozciete(syg_filtr,samples,rozpr2,10,35);
SSVEP(:,:,:,3)=rozciete(syg_filtr,samples,rozpr3,10,35);
SSVEP(:,:,:,4)=rozciete(syg_filtr,samples,rozpr4,10,35);
SSVEP(:,:,:,5)=rozciete(syg_filtr,samples,rozpr5,10,35);
SSVEP(:,:,:,6)=rozciete(syg_filtr,samples,rozpr6,10,35);
SSVEP(:,:,:,7)=rozciete(syg_filtr,samples,rozpr7,10,35);
SSVEP(:,:,:,8)=rozciete(syg_filtr,samples,rozpr8,10,35);
SSVEP(:,:,:,9)=rozciete(syg_filtr,samples,rozpr9,10,35);
SSVEP(:,:,:,10)=rozciete(syg_filtr,samples,rozpr10,10,35);
SSVEP(:,:,:,11)=rozciete(syg_filtr,samples,rozpr11,10,35);
SSVEP(:,:,:,12)=rozciete(syg_filtr,samples,rozpr12,10,35);

ref =  srednia_5s(ref_filtr,1000:1024:26624,samples,25,218);

ref_sincos(:,:,:,:) = reference(freq,fs, samples, 2);
