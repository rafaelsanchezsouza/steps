%**************************************************************************
% Autores:  Alexandre Mitsuru Nishikawa     N∫ USP: 5947440
%           Henrique Yuji Sugimoto                  5945917
%
% DescriÁ„o: 
%  Script para gerar um vÌdeo do movimento de acordo com os dados
%  exportados pelo software Motive:Tracker.
%
%------------ Escola PolitÈcnica da Universidade de S„o Paulo -------------
%
% Vers„o: 1.0
% Data: 21.05.2014
%
% Steps:
%  - Plot motion;
%  - Create video.
%
%**************************************************************************

%% Create Export Video

videoName = inputdlg({'File name:'},'Save Video As',1,{'Untitled.avi'});
videoObject = VideoWriter(videoName{1});
videoObject.FrameRate = 120;
open(videoObject);

%% Set Axis and Figure Properties
figure;
xlim([-1.5, -0.5]);
ylim([-1, 0]);
zlim([0, 1]);
view(40, 20);
axis tight;
grid;

% Compatibility of Motive:Tracker and MatLab axes
xlabel('Axis Z');
ylabel('Axis X');
zlabel('Axis Y');

set(gca,'NextPlot','replaceChildren');
set(gcf,'Renderer','zbuffer');

% Create a set of frames and write each frame to the file
for i = 1:iFrameCount
 %   hold on;    
    h = plot3(frMarkerData(i,1,3),frMarkerData(i,1,1),frMarkerData(i,1,2),...
        's',frMarkerData(i,2,3),frMarkerData(i,2,1),frMarkerData(i,2,2),...
        'o',frMarkerData(i,3,3),frMarkerData(i,3,1),frMarkerData(i,3,2),...
        'o',frMarkerData(i,4,3),frMarkerData(i,4,1),frMarkerData(i,4,2),...
        'o',frMarkerData(i,5,3),frMarkerData(i,5,1),frMarkerData(i,5,2),...
        'o','MarkerSize',12,'MarkerFaceColor','k');

%     line([frMarkerData(i,1,3), frMarkerData(i,2,3)],[frMarkerData(i,1,1),...
%     frMarkerData(i,2,1)],[frMarkerData(i,1,2), frMarkerData(i,2,2)]);
%     line([frMarkerData(i,2,3), frMarkerData(i,3,3)],[frMarkerData(i,2,1),...
%     frMarkerData(i,3,1)],[frMarkerData(i,2,2), frMarkerData(i,3,2)]);
%     line([frMarkerData(i,3,3), frMarkerData(i,4,3)],[frMarkerData(i,3,1),...
%     frMarkerData(i,4,1)],[frMarkerData(i,3,2), frMarkerData(i,4,2)]);
%     line([frMarkerData(i,4,3), frMarkerData(i,5,3)],[frMarkerData(i,4,1),...
%     frMarkerData(i,5,1)],[frMarkerData(i,4,2), frMarkerData(i,5,2)]);
%    hold off;
%    drawnow;
    frame = getframe;
    writeVideo(videoObject,frame);
end

close(videoObject);


