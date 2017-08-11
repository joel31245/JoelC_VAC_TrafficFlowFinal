clear; clc;

% File Creates every Individual Graph of Conventional

insFile = 'matlabInstructionsPos.txt';
insFv = 'matlabInstructionsVel.txt';
fileId = fopen(insFile);
fv = fopen(insFv);

amtFiles = fscanf(fileId, "%d ");
amtFv = fscanf(fv, "%d");

fileNames = fscanf(fileId, "%s");
disp(fileNames);

for i=1:amtFiles
    x(i,:,:) = csvread(fileNames(i)) ;
    y(i,:,:) = x(i,1,1:end-1)*0;
end

for i=0:amtFiles-1
    figure(i);
    xlabel('Position (m)');
    yL = sprintf('Conventional Program %d Traffic Flow', i);
    ylabel(yL);
    
    tL = sprintf('Distance: Program %d', i);
    title(tL);
    
    % Distance Video
    set(gca, 'XLim', [x(i,1,end-1)-10 x(i,end,1)+10], 'YLim', [-.1 .1]);   
    road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);
    for j=1:size(x,2)
          clearpoints(road);
          xC(:) = x(i,j,1:end-1);
          addpoints(road, xC, y(i,:));  
          drawnow;   
          M(i) = getframe(gcf);
    end
    videoName = sprintf('Distance Program%d',i);
    video = VideoWriter(videoName, 'MPEG-4');
    open(video);
    writeVideo(video, M);
    close(video);
    
    % Separation Video 
    figure(i+amtFiles);
    xlabel('Position (m)');
    yL = sprintf('Conventional Program %d Traffic Flow', i);
    ylabel(yL);
    
    tL = sprintf('Separation: Program %d', i);
    title(tL);
    
    road = animatedline('LineStyle','none', 'Marker','o', 'LineWidth',5);
    for j=1:size(x,2)
          clearpoints(road);
          xC(:) = x(i,j,1:end-1);
          addpoints(road, xC, y(i,:));  
          drawnow;   
          M(i) = getframe(gcf);
    end
    videoName = sprintf('Separation Program%d',i);
    video = VideoWriter(videoName, 'MPEG-4');
    open(video);
    writeVideo(video, M);
    close(video);
    
    
    
end

fclose('all');