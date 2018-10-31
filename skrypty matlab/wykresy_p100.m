% wyswietlenie wszytskich wykresow
function wykresy_p100(dane,dane2,dane3,przedzial1,przedzial2,sampling)
p= przedzial1:1:przedzial2-1;
t=(przedzial1)*(1000/sampling):(1000/sampling):(przedzial2*(1000/sampling)-(1000/sampling));

for i=1:16
     figure
     plot(t,dane(i, :))
     
     hold on
     plot(t,dane2(i,:))
     
     hold on
     plot(t,dane3(i,:))
     
     
     title(['s11: channel ' , num2str(i)]);
     legend('Series 1','Series 2','Reference')     %, 'Reference')
     xlabel('time [ms]');    %opisanie osi
     ylabel('Amplitude [uV]|');
     xlim([-100 400]);
     
end
