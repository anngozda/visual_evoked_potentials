function [t,ref]=  skrypt9kwa(data,dataRef,fs,przedzial1,przedzial2,repeat) %repeat = 7 dla b5 i b6 yellow
%function [t1,t2,t3,t4,t5,t6,t7,t8,t9,ref]=  skrypt9kwa(data,dataRef,fs)


[hdr,rec]=edfread(data);   %wczytanie skryptu czytaj¹cego pliki edf   
[hdr,recRef]=edfread(dataRef);
A = diff(rec(17,:));   % liczy roznice pomiedzy probkami w kanale z flagami
[pks,x] = findpeaks(A,'MinPeakDistance',200);   % znajduje piki 

pks1(1)=0;
x1(1)=0;
for i=1:length(pks)
   pks1(i+1)=pks(i);
   x1(i+1)=x(i);
end

pause=0;

%rozcinanie sygnalu w miejscu flagi F3F4
for i=2:length(pks1)
    if (pks1(i-1) == 1024) && (pks1(i) == 2048) && (x1(i)-x1(i-1)<720)    %<720 dla b5)     %<650 b6)
         pause = [pause,x1(i-1)];
    end
end
pause(1) = x1(2)-2240;

   for channel=1:17
    signal(1,channel,:)=rec(channel,pause(1):pause(1)+ 101000);     %100000 dla b6 yellow);    %64000 dla b5);   %61760);    %pause(2));
    signal(2,channel,:)=rec(channel,pause(2):pause(2)+ 101000);
    signal(3,channel,:)=rec(channel,pause(3):pause(3)+ 101000);
    signal(4,channel,:)=rec(channel,pause(4):pause(4)+ 101000);
    signal(5,channel,:)=rec(channel,pause(5):pause(5)+ 101000);
    signal(6,channel,:)=rec(channel,pause(6):pause(6)+ 101000);
    signal(7,channel,:)=rec(channel,pause(7):pause(7)+ 101000);
    signal(8,channel,:)=rec(channel,pause(8):pause(8)+ 101000);
    signal(9,channel,:)=rec(channel,pause(9):pause(9)+ 101000); 
   end

    m=0;
    pks2=0;
    x2=0;
    A2=0;
    

for target = 1:size(signal,1)  %analizujemy ka¿dy po kolei przedzia³ 
  sig(1:size(signal,3)) = signal(target,17,:);
  A2 = diff(sig);   % liczy roznice pomiedzy probkami w kanale z flagami
  [pks2,x2] = findpeaks(A2, 'MinPeakDistance',200);   % znajduje piki    

  pks3(1)=0;
  x3(1)=0;
for i=1:length(pks2)
   pks3(i+1)=pks2(i);
   x3(i+1)=x2(i);
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

for i=2:length(pks3)-1
   if (pks3(i-1) == 256) && (pks3(i) == 512) && (x3(i)-x3(i-1)<650)
       rozpr9 = [rozpr9,x3(i-1)];
   else if (pks3(i) ==   256) && (x3(i+1)-x3(i)>650)
       rozpr1 = [rozpr1,x3(i)];
   else if pks3(i) == 512
      rozpr2 = [rozpr2,x3(i)];
 
   else if pks3(i) == 1024
      rozpr3 = [rozpr3,x3(i)];
   else if pks3(i) == 2048
      rozpr4 = [rozpr4,x3(i)];
   else if pks3(i) == 4096
      rozpr5 = [rozpr5,x3(i)];
   else if pks3(i) == 8192
      rozpr6 = [rozpr6,x3(i)];
   else if pks3(i) == 16384
      rozpr7 = [rozpr7,x3(i)];
   else if pks3(i) == 32768
      rozpr8 = [rozpr8,x3(i)];

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
rozpr3 = rozpr3(2:length(rozpr3));   %wycinam zero ktore daje na starcie
rozpr4 = rozpr4(2:length(rozpr4));
rozpr5 = rozpr5(2:length(rozpr5));
rozpr6 = rozpr6(2:length(rozpr6));
rozpr7 = rozpr7(2:length(rozpr7));   %wycinam zero ktore daje na starcie
rozpr8 = rozpr8(2:length(rozpr8));
rozpr9 = rozpr9(2:length(rozpr9));

pks1=0;
x1=0;
ref_filtr = butterworth_band_pass(recRef,fs,1,20);
syg_filtr = butterworth_band_pass2(signal(target,:,:),fs,1,20);  % filtracjabp(syg,bp); 

%t(target(1-9),channel,przedzial 1-1200,triale 7)
    t(target,:,:,1) = srednia9kw(syg_filtr,rozpr1,przedzial1,przedzial2,repeat); %syg_filtr(target(1-9),channel,przedzial 1-61761))
    t(target,:,:,2) = srednia9kw(syg_filtr,rozpr2,przedzial1,przedzial2,repeat);
    t(target,:,:,3)= srednia9kw(syg_filtr,rozpr3,przedzial1,przedzial2,repeat);
    t(target,:,:,4) = srednia9kw(syg_filtr,rozpr4,przedzial1,przedzial2,repeat);
    t(target,:,:,5) = srednia9kw(syg_filtr,rozpr5,przedzial1,przedzial2,repeat);
    t(target,:,:,6)= srednia9kw(syg_filtr,rozpr6,przedzial1,przedzial2,repeat);
    t(target,:,:,7) = srednia9kw(syg_filtr,rozpr7,przedzial1,przedzial2,repeat);
    t(target,:,:,8) = srednia9kw(syg_filtr,rozpr8,przedzial1,przedzial2,repeat);
    t(target,:,:,9)= srednia9kw(syg_filtr,rozpr9,przedzial1,przedzial2,repeat);

    rozpr1 = 0;  
    rozpr2 = 0; 
    rozpr3 = 0;
    rozpr4 = 0;  
    rozpr5 = 0; 
    rozpr6 = 0;
    rozpr7 = 0;  
    rozpr8 = 0; 
    rozpr9 = 0;
 end

ref = srednia(ref_filtr,1000:1600:49600,przedzial1,przedzial2,30);




