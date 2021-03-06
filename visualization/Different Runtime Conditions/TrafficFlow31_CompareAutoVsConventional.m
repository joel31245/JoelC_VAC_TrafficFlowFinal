clear; clc;

%% PROGRAM RUNS Side By Side Comparison with Results of Diff Init Set Dist
x(1,:,:) = csvread('PosProg0.csv');               
y(1,:,:) = x(1,1,1:end-1)*0 + 1;         
x(2,:,:) = csvread('PosProg1.csv');               
y(2,:,:) = x(2,1,1:end-1)*0 + 1;
x(3,:,:) = csvread('PosProg2.csv');               
y(3,:,:) = x(3,1,1:end-1)*0 + 1;         
x(4,:,:) = csvread('PosProg3.csv');               
y(4,:,:) = x(4,1,1:end-1)*0 + 1;         
x(5,:,:) = csvread('PosProg4.csv');               
y(5,:,:) = x(5,1,1:end-1)*0 + 1;

x(6,:,:) = csvread('PosProg0A.csv');               
y(6,:,:) = x(6,1,1:end-1)*0 + 0;         
x(7,:,:) = csvread('PosProg1A.csv');               
y(7,:,:) = x(7,1,1:end-1)*0 + 0;
x(8,:,:) = csvread('PosProg2A.csv');               
y(8,:,:) = x(8,1,1:end-1)*0 + 0;         
x(9,:,:) = csvread('PosProg3A.csv');               
y(9,:,:) = x(9,1,1:end-1)*0 + 0;         
x(10,:,:) = csvread('PosProg4A.csv');               
y(10,:,:) = x(10,1,1:end-1)*0 + 0;

for j=1:5
    figure(j);
    xlabel('Position (m)');
    ylabel('0-Automated   1-Conventional');
    
    if ( j==1 ) titleName = sprintf('Distance: Program %d - Steady State',j-1); end
    if ( j==2 ) titleName = sprintf('Distance: Program %d - Accelerate 30P',j-1); end
    if ( j==3 ) titleName = sprintf('Distance: Program %d - Decelerate 30P',j-1); end
    if ( j==4 ) titleName = sprintf('Distance: Program %d - Accelerate 0-42m/s',j-1); end
    if ( j==5 ) titleName = sprintf('Distance: Program %d - Decelerate 30-0m/s',j-1); end  
        
    title(titleName);
    set(gca, 'XLim', [x(j,1,end-1)-10 x(j,end,1)+10], 'YLim', [-.25 1.25]);   
    road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);

    for i=1:size(x,2)
          clearpoints(road);
%           set(gca, 'XLim', [x(j,i,end-1)-10 x(j,i,1)+10], 'YLim', [-.25 1.25]); 
          xC(:) = x(j,i,1:end-1);
          addpoints(road, xC, y(j,:));  
          xC1(:) = x(j+5,i,1:end-1);
          addpoints(road, xC1, y(j+5,:));
          drawnow;   
          M(i) = getframe(gcf);
    end
    videoName = sprintf('Distance Comparison Program%d',j);
    video = VideoWriter(videoName, 'MPEG-4');
    open(video);
    writeVideo(video, M);
    close(video);
end