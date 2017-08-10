clear; clc;

%% PROGRAM RUNS Side By Side Comparison with Results of Diff Init Set Dist
x1 = csvread('PosProg0.csv');               
y1 = x1(1,1:end-1)*0 + 0;         
x2 = csvread('PosProg1.csv');               
y2 = x2(1,1:end-1)*0 + 1;
x3 = csvread('PosProg2.csv');               
y3 = x3(1,1:end-1)*0 + 2;         
x4 = csvread('PosProg3.csv');               
y4 = x4(1,1:end-1)*0 + 3;         
x5 = csvread('PosProg4.csv');               
y5 = x5(1,1:end-1)*0 + 4;

figure(001);
xlabel('Position');
ylabel('Runtime Program Protocol');
title('Distance: Different Programs: Automated');
set(gca, 'XLim', [x1(1,end-1)-10 x4(end,1)+10], 'YLim', [-.5 4.5]);   
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);
hold on;

for i=1:size(x1,1)
      clearpoints(road);
%       set(gca, 'XLim', [x1(i,end-1)-10 x4(i,1)+10], 'YLim', [-.5 4.5]); 
      addpoints(road,x1(i,1:end-1), y1);                            
      addpoints(road,x2(i,1:end-1), y2);
      addpoints(road,x3(i,1:end-1), y3);                            
      addpoints(road,x4(i,1:end-1), y4);
      addpoints(road,x5(i,1:end-1), y5);
      drawnow;   
      M(i) = getframe(gcf);
end

video = VideoWriter('Distance AllPrograms Auto', 'MPEG-4');
open(video);
writeVideo(video, M);
close(video);


       