function test(dane,dane2,Fs1)
 for i=1:16
 sygnal=fft(dane(i,:,:));   %obliczenie transformaty fouriera
 T1=1/Fs1;           %okres
 L1=length(dane(i,:,:));             % dlugosc sygna³u
    %redukcja przedzia³u próbkowania do Fs1/2
 P2=abs(sygnal/L1);   
 P1=P2(1:L1/2+1);
 P1(2:end-1)=2*P1(2:end-1);
 f1=Fs1*(0:(L1/2))/L1;   %wyznaczenie osi czêstotliwoœci
 
 sygnal2=fft(dane2(i,:,:));   %obliczenie transformaty fouriera
 L2=length(dane2(i,:,:));             % dlugosc sygna³u
    %redukcja przedzia³u próbkowania do Fs1/2
 P3=abs(sygnal2/L2);   
 P4=P3(1:L2/2+1);
 P4(2:end-1)=2*P4(2:end-1);
 f2=Fs1*(0:(L2/2))/L2;

 figure
 bar(f1,P1,'r')  % tworzenie wykresu
 hold on
 bar(f2,P4)    
 title(['Widmo kana³u: ' , num2str(i)]);
 legend('square','sin')
 xlabel('f[Hz]');    %opisanie osi
 ylabel('|P1(f)|');
 xlim([5 15]);
 end