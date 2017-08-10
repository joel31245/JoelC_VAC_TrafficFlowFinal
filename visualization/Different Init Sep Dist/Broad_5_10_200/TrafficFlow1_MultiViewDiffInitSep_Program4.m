clear; clc;

% %% SECTION SETS UP BROAD SPECTRUM
% x1 = csvread('PosInitSep5.csv');
% y1 = x1(1,1:end-1)*0 + 5;
% x2 = csvread('PosInitSep15.csv');
% y2 = x2(1,1:end-1)*0 + 15;
% x3 = csvread('PosInitSep25.csv');
% y3 = x3(1,1:end-1)*0 + 25;
% x4 = csvread('PosInitSep35.csv');
% y4 = x4(1,1:end-1)*0 + 35;
% x5 = csvread('PosInitSep45.csv');
% y5 = x5(1,1:end-1)*0 + 45;
% x6 = csvread('PosInitSep55.csv');
% y6 = x6(1,1:end-1)*0 + 55;
% x7 = csvread('PosInitSep65.csv');
% y7 = x7(1,1:end-1)*0 + 65;
% x8 = csvread('PosInitSep75.csv');
% y8 = x8(1,1:end-1)*0 + 75;
% x9 = csvread('PosInitSep85.csv');
% y9 = x9(1,1:end-1)*0 + 85;
% x10 = csvread('PosInitSep95.csv');
% y10 = x10(1,1:end-1)*0 + 95;
% x11 = csvread('PosInitSep105.csv');
% y11 = x11(1,1:end-1)*0 + 105;
% x12 = csvread('PosInitSep115.csv');
% y12 = x12(1,1:end-1)*0 + 115;
% x13 = csvread('PosInitSep125.csv');
% y13 = x13(1,1:end-1)*0 + 125;
% x14 = csvread('PosInitSep135.csv');
% y14 = x14(1,1:end-1)*0 + 135;
% x15 = csvread('PosInitSep145.csv');
% y15 = x15(1,1:end-1)*0 + 145;
% x16 = csvread('PosInitSep155.csv');
% y16 = x16(1,1:end-1)*0 + 155;
% x17 = csvread('PosInitSep165.csv');
% y17 = x17(1,1:end-1)*0 + 165;
% x18 = csvread('PosInitSep175.csv');
% y18 = x18(1,1:end-1)*0 + 175;
% x19 = csvread('PosInitSep185.csv');
% y19 = x19(1,1:end-1)*0 + 185;
% x20 = csvread('PosInitSep195.csv');
% y20 = x20(1,1:end-1)*0 + 195;

%% SECTION SETS UP SMALL SECTION
x1 = csvread('PosInitSep36.csv');
y1 = x1(1,1:end-1)*0 + 36;
x2 = csvread('PosInitSep37.csv');
y2 = x2(1,1:end-1)*0 + 37;
x3 = csvread('PosInitSep38.csv');
y3 = x3(1,1:end-1)*0 + 38;
x4 = csvread('PosInitSep39.csv');
y4 = x4(1,1:end-1)*0 + 39;

figure(001);
xlabel('Position');
ylabel('Initial Seperation Distances');
title('Distance Animation (Fine): Deceleration From 30 To 0 m/s. Initial Headway: Variable');
set(gca, 'XLim', [x4(1,end-1)-10 x4(end,1)+10], 'YLim', [35 40]);
road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);
hold on;

for i=1:size(x1,1)
      clearpoints(road);
%       set(gca, 'XLim', [x4(i,end-1)-10 x4(i,1)+10], 'YLim', [35 40]);
      addpoints(road,x1(i,1:end-1), y1);
      addpoints(road,x2(i,1:end-1), y2);
      addpoints(road,x3(i,1:end-1), y3);
      addpoints(road,x4(i,1:end-1), y4);
%       addpoints(road,x5(i,1:end-1), y5);
%       addpoints(road,x6(i,1:end-1), y6);
%       addpoints(road,x7(i,1:end-1), y7);
%       addpoints(road,x8(i,1:end-1), y8);
%       addpoints(road,x9(i,1:end-1), y9);
%       addpoints(road,x10(i,1:end-1), y10);
%       addpoints(road,x11(i,1:end-1), y11);
%       addpoints(road,x12(i,1:end-1), y12);
%       addpoints(road,x13(i,1:end-1), y13);
%       addpoints(road,x14(i,1:end-1), y14);
%       addpoints(road,x15(i,1:end-1), y15);
%       addpoints(road,x16(i,1:end-1), y16);
%       addpoints(road,x17(i,1:end-1), y17);
%       addpoints(road,x18(i,1:end-1), y18);
%       addpoints(road,x19(i,1:end-1), y19);
%       addpoints(road,x20(i,1:end-1), y20);
      drawnow;   
      M(i) = getframe(gcf);
end

video = VideoWriter('Distance Animation 2 Deceleration from 30 to 0 m/s Variable Headway', 'MPEG-4');
open(video);
writeVideo(video, M);
close(video);


        