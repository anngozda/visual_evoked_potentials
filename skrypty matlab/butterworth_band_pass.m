function y = butterworth_band_pass(data,Fsp,Fl,Fh)

 nchannel = 16;
%  for m=1:l_kanalow+1
%  sygnal(m,:)=downsample(syg(m,:),8);
%  end


bpFilt = designfilt('bandpassiir','FilterOrder',6, ...
         'HalfPowerFrequency1',Fl,'HalfPowerFrequency2',Fh, ...
         'SampleRate',Fsp); %, 'DesignMethod', 'butter');
      
for i=1:nchannel      
    y(i,:)= filtfilt(bpFilt,data(i,:));    
end    

subplot(2,2,1)
plot(y(1,:))
subplot(2,2,2)
plot (data(1,:), 'r')
title('Filtered Waveforms')
legend('Zero-phase Filtering','Original data')


