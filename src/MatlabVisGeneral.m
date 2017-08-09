%%
clear; clc;

figure(2);
hold on;
z = 0:.01:10;
x = cos(2*z);
y = sin(2*z);
a = cos(2*z)+.5;
b = cos(2*z)+.5;

curve = animatedline('LineWidth', 1);

view(45,45);
set(gca, 'XLim',[-10 10], 'YLim', [-10 10], 'ZLim', [0 15]);

for i=1:length(z)
    % addpoints adds the line
    % addpoints(curve, x(i), y(i), z(i) );
    % addpoints(curve, a(i), b(i), z(i) );
    % head is the front end marker of the line
    head = scatter3(x(i), y(i), z(i), 'filled', 'MarkerFaceColor','b', 'MarkerEdgeColor', 'b');
    head1 = scatter3(a(i), b(i), z(i), 'filled', 'MarkerFaceColor','r', 'MarkerEdgeColor', 'r');
    %drawnow
    pause(0.01);
    delete(head);
    delete(head1);
end

clear; clc;
%%