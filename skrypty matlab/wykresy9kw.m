% wyswietlenie wszytskich wykresow  dla 9 danych
function wykresy9kw(dane1,dane2, dane3,dane4,dane5, dane6,dane7,dane8,dane9,przedzial1,przedzial2,sampling)
p= przedzial1:1:przedzial2-1;
t=(przedzial1)*(1000/sampling):(1000/sampling):(przedzial2*(1000/sampling)-(1000/sampling));

for i=1:16
     figure
     a1(:,1)=dane1(1,i,:);
     a2(:,1)=dane2(1,i,:);
     a3(:,1)=dane3(1,i,:);
     a4(:,1)=dane4(1,i,:);
     a5(:,1)=dane5(1,i,:);
     a6(:,1)=dane6(1,i,:);
     a7(:,1)=dane7(1,i,:);
     a8(:,1)=dane8(1,i,:);
     a9(:,1)=dane9(1,i,:);
     plot(t,a1(:,1))   
     hold on
     plot(t,a2(:,1))   
     hold on
     plot(t,a3(:,1))
     hold on
     plot(t,a4(:,1))     
     hold on
     plot(t,a5(:,1))
     hold on
     plot(t,a6(:,1),'--')  
     hold on
     plot(t,a7(:,1),'.')
     hold on
     plot(t,a8(:,1),'.')   
     hold on
     plot(t,a9(:,1),'.')     

     title(['s11: channel ' , num2str(i)]);
     legend('t1','t2', 't3','t4','t5', 't6','t7','t8', 't9')     %, 'Reference')
     xlabel('time [ms]');    %opisanie osi
     ylabel('Amplitude [uV]');
     xlim([-100 750]);
     
end


