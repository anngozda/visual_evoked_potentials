% wyswietlenie wszytskich wykresow
function wykresy(dane,dane2,dane3,dane4,dane5,dane6,dane7,dane8,dane9,przedzial1,przedzial2,sampling)      %(dane,dane2,dane3,ref,przedzial1,przedzial2,sampling)
p= przedzial1:1:przedzial2-1;
t=(przedzial1)*(1000/sampling):(1000/sampling):(przedzial2*(1000/sampling)-(1000/sampling));

for i=1:16
     figure
     plot(t,dane(i, :))
     
     hold on
     plot(t,dane2(i,:))
     
     hold on
     plot(t,dane3(i,:))
     
     hold on
     plot(t,dane4(i,:))
     
     hold on
     plot(t,dane5(i,:),'.')
     
     hold on
     plot(t,dane6(i,:),'.')
     
     hold on
     plot(t,dane7(i,:),'.')
     hold on
     plot(t,dane8(i,:),'.')
     hold on
     plot(t,dane9(i,:),'.')
     
     title(['s2: channel ' , num2str(i)]);
     legend('t1','t2', 't3','t4','t5', 't6','t7','t8', 't9');
     %legend('Target','Non-target', 'Distractor','Reference')     %, 'Reference')
     xlabel('time [ms]');    %opisanie osi
     ylabel('Amplitude [uV]|');
     xlim([-50 750]);
     
end

     title(['s4: channel ' , num2str(i)]);
     legend('t1','t2', 't3','t4','t5', 't6','t7','t8', 't9')     %, 'Reference')
     xlabel('time [ms]');    %opisanie osi
     ylabel('Amplitude [uV]');
     xlim([-100 750]);