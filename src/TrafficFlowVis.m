clear; clc;

traffic = csvread('TrafficFlowPos.csv');
y = traffic(1,1:end-1)*0;

figure(001);
xlabel('Position');
ylabel('Different Lanes');
title('Animation of the Vehicles');
set(gca, 'XLim', [traffic(1,end-1) traffic(end,1)], 'YLim', [-1 1]);
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);


for i=1:size(traffic,1)
      clearpoints(road);
      addpoints(road,traffic(i,1:end-1), y);
      drawnow;   
end


        