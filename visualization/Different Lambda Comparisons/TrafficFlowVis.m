clear; clc;

traffic = csvread('TrafficFlowPos.csv');
y = traffic(1,1:end-1)*0;

figure(001);
xlabel('Position');
ylabel('Different Lanes');
title('Animation of the Vehicles');
set(gca, 'XLim', [traffic(1,end-1)-10 traffic(end,1)+100], 'YLim', [-1 1]);
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);


for i=1:size(traffic,1)
      clearpoints(road);
      addpoints(road,traffic(i,1:end-1), y);
      drawnow;   
      M(i) = getframe(gcf);
end

video = VideoWriter('TrafficFlowPositions.avi', 'MPEG-4');
open(video);
writeVideo(video, M);
close(video);


        