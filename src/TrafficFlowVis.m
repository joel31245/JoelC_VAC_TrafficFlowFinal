clear; clc;

traffic = csvread('PosProg4.csv');
y = traffic(1,1:end-1)*0;

figure(001);
xlabel('Position (m) ');
ylabel('Program');
title('Distance Animation: Program 4 Full Stop');
set(gca, 'XLim', [traffic(1,end-1)-10 traffic(end,1)+10], 'YLim', [-1 1]);
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);


for i=1:size(traffic,1)
      clearpoints(road);
%       set(gca, 'XLim', [traffic(i,end-1)-10 traffic(i,1)+10], 'YLim', [-1 1]);
      addpoints(road,traffic(i,1:end-1), y);
      drawnow;   
      M(i) = getframe(gcf);
end

video = VideoWriter('Distance Animation. Program 4', 'MPEG-4');
open(video);
writeVideo(video, M);
close(video);


        