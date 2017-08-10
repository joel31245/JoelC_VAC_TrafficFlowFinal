clear; clc;

%% PROGRAM RUNS Side By Side Comparison with Results of Diff Init Set Dist
x1 = csvread('PosLambda50.csv');               
y1 = x1(1,1:end-1)*0 + .50;         
x2 = csvread('PosLambda75.csv');               
y2 = x2(1,1:end-1)*0 + .75;
x3 = csvread('PosLambda100.csv');               
y3 = x3(1,1:end-1)*0 + 1.00;         
x4 = csvread('PosLambda125.csv');               
y4 = x4(1,1:end-1)*0 + 1.25;
x5 = csvread('PosLambda150.csv');               
y5 = x5(1,1:end-1)*0 + 1.50;         
x6 = csvread('PosLambda175.csv');               
y6 = x6(1,1:end-1)*0 + 1.75;
x7 = csvread('PosLambda200.csv');               
y7 = x7(1,1:end-1)*0 + 2.00;         
x8 = csvread('PosLambda225.csv');               
y8 = x8(1,1:end-1)*0 + 2.25;

figure(001);
xlabel('Position');
ylabel('Lambda');
title('Distance: Deceleration (30-0 m/s). Variable Lambda. (InitialSep 35m)');
set(gca, 'XLim', [x8(1,end-1)-10 x8(end,1)+10], 'YLim', [.25 2.50]);   
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);
hold on;

for i=1:size(x1,1)
      clearpoints(road);
%       set(gca, 'XLim', [x8(i,end-1)-10 x8(i,1)+10], 'YLim', [.25 2.50]); 
      addpoints(road,x1(i,1:end-1), y1);                            
      addpoints(road,x2(i,1:end-1), y2);
      addpoints(road,x3(i,1:end-1), y3);                            
      addpoints(road,x4(i,1:end-1), y4);
      addpoints(road,x5(i,1:end-1), y5);                            
      addpoints(road,x6(i,1:end-1), y6);
      addpoints(road,x7(i,1:end-1), y7);                            
      addpoints(road,x8(i,1:end-1), y8);
      drawnow;   
      M(i) = getframe(gcf);
end

video = VideoWriter('Distance Decel LambdaAll35', 'MPEG-4');
open(video);
writeVideo(video, M);
close(video);


       