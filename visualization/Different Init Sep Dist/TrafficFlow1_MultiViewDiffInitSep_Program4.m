clear; clc;

%% PROGRAM RUNS Side By Side Comparison with Results of Diff Init Set Dist
x1 = csvread('PosDecel200.csv');
y1 = x1(1,1:end-1)*0 + 200;
x2 = csvread('PosDecel50.csv');
y2 = x2(1,1:end-1)*0 + 50;

figure(001);
xlabel('Position');
ylabel('Initial Seperation Distances (Auto) (Conventional)');
title('Seperation (50m Zoom): Deceleration (30-0 m/s). Conventional vs Automated');
% set(gca, 'XLim', [x1(1,end-1)-10 x1(end,1)+10], 'YLim', [40 210]);
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);
hold on;

for i=1:size(x1,1)
      clearpoints(road);
      set(gca, 'XLim', [x2(i,end-1)-10 x2(i,1)+10], 'YLim', [40 210]);
      addpoints(road,x1(i,1:end-1), y1);
      addpoints(road,x2(i,1:end-1), y2);
      drawnow;   
      M(i) = getframe(gcf);
end

video = VideoWriter('Seperation 2 Decel Default Conventional vs Automated', 'MPEG-4');
open(video);
writeVideo(video, M);
close(video);


        