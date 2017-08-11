clear; clc;

%% PROGRAM RUNS Side By Side Comparison with Results of Diff Init Set Dist
x1 = csvread('L1.csv');               
y1 = x1(1,1:end-1)*0 + .50;         
x2 = csvread('L2.csv');               
y2 = x2(1,1:end-1)*0 + .7;
x3 = csvread('L3.csv');               
y3 = x3(1,1:end-1)*0 + 0.90;         
x4 = csvread('L4.csv');               
y4 = x4(1,1:end-1)*0 + 1.1;
x5 = csvread('L5.csv');               
y5 = x5(1,1:end-1)*0 + 1.3;         
x6 = csvread('L6.csv');               
y6 = x6(1,1:end-1)*0 + 1.5;
x7 = csvread('L7.csv');               
y7 = x7(1,1:end-1)*0 + 1.70;         
x8 = csvread('L8.csv');               
y8 = x8(1,1:end-1)*0 + 1.9;

figure(001);
xlabel('Position (m)');
ylabel('Lambda');
title('Variable Lambda Separation Distances');
% set(gca, 'XLim', [x8(1,end-1)-10 x8(end,1)+10], 'YLim', [.25 2.15]);   
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);
hold on;

for i=1:size(x1,1)
      clearpoints(road);
      set(gca, 'XLim', [x8(i,end-1)-10 x8(i,1)+10], 'YLim', [.25 2.15]); 
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

video = VideoWriter('VarLambda80Sep', 'MPEG-4');
open(video);
writeVideo(video, M);
close(video);


       