%**************************************************************************
% Autores:  Alexandre Mitsuru Nishikawa     N??? USP: 5947440
%           Henrique Yuji Sugimoto                  5945917
%
% Descri????o: 
%  Script de processamento dos dados do arquivo '.csv' exportado pelo
%  software Motive:Tracker. A interpreta????o dos dados ?? dependente da ordem
%  das linhas do arquivo.
%
%------------ Escola Polit??cnica da Universidade de S??o Paulo -------------
%
% Version: 1.0
% Date: 05.21.2014 [mm.dd.yyyy]
%
% Steps:
%  - Open CSV file;
%  - Extract information of data;
%  - Close CSV file.
%
%**************************************************************************

%% Open CSV file
%FileName = 'Data.csv';
[fileName, pathName, filterIndex] = uigetfile('*.csv');
fileID = fopen(fileName);
fprintf('FileID= %d\n', fileID);
% lineData = fgetl(fileID);
% Data = strsplit(lineData,',');
% 
% %% Skip Comments
% while (strcmpi(Data(1),'comment'))
%     lineData = fgetl(fileID);
%     Data = strsplit(lineData,',');
% end
% 
% %% Read Coordinate System
% if(strcmpi(Data(1),'righthanded'))
%     coordinateSystem = 1;
%     % disp('Coordinate System: right-handed');
% elseif(strcmpi(Data(1),'lefthanded'))
%     coordinateSystem = -1;
%     % disp('Coordinate System: left-handed');
% else
%     error('Error: Coordinate System');
% end
% 
% lineData = fgetl(fileID);
% Data = strsplit(lineData,',');
% 
% %% Read info
% while (strcmpi(Data(1),'info'))
%     if(strcmpi(Data(2),'version'))
%         iVersion = str2double(Data(3));
%     elseif(strcmpi(Data(2),'framecount'))
%         iFrameCount = str2double(Data(3));
%     elseif(strcmpi(Data(2),'rigidbodycount'))
%         iRigidBodyCount = str2double(Data(3));
%     end
%     lineData = fgetl(fileID);
%     Data = strsplit(lineData,',');
% end
% fprintf('File Version:  %.1f\n', iVersion);
% fprintf('Frame Count:  %d\n', iFrameCount);
% fprintf('Rigid Body Count:  %d\n\n', iRigidBodyCount);
% 
% %% Read Rigid Body Definitions
% 
% % Pre-allocate memory
% rbName = cell(iRigidBodyCount,1);
% rbID = zeros(iRigidBodyCount,1);
% rbMarkerCount = zeros(iRigidBodyCount,1);
% 
% % Read Informations
% i = 1;
% while(strcmpi(Data(1),'rigidbody'))
%     
%     rbName(i) = Data(2);
%     rbID(i) = str2double(Data(3));
%     rbMarkerCount(i) = str2double(Data(4));
%     
%     for j=1:rbMarkerCount(i)
%         rbMarketPosition(i,j,1) = str2double(Data(3*j+2));  % X
%         rbMarketPosition(i,j,2) = str2double(Data(3*j+3));  % Y
%         rbMarketPosition(i,j,3) = str2double(Data(3*j+4));  % Z
%     end
%     
%     i = i + 1;
%     lineData = fgetl(fileID);
%     Data = strsplit(lineData,',');
% end
% 
% %% Read Frame and Extended Rigid Body Information
% 
% % Pre-allocate Memory
% frFrameIndex = zeros(iFrameCount,1);
% frTimeStamp = zeros(iFrameCount,1);
% frRigidBodyCount = zeros(iFrameCount,1);    % utilizar para consist??ncia
% frRigidBodyData = zeros(iFrameCount,iRigidBodyCount,11);
% frMarkerCount = zeros(iFrameCount,1);       % utilizar para consist??ncia
% 
% % Read informations
% i = 1;
% while(ischar(lineData))
%     Data = strsplit(lineData,',');
%     if (strcmpi(Data(1),'frame'))
%         frFrameIndex(i) = str2double(Data(2));
%         frTimeStamp(i) = str2double(Data(3));
%         frRigidBodyCount(i) = str2double(Data(4));
%         
%         for j=1:frRigidBodyCount(i)
%             for k=1:11
%                 frRigidBodyData(i,j,k) = str2double(Data(11*j-7+k));
%             end
%         end
%         
%         frMarkerCount(i) = str2double(Data(11*frRigidBodyCount(i)+5));
%         
%         for l=1:frMarkerCount(i)
%            for m=1:3
%                frMarkerData(i,l,m) = ...
%                    str2double(Data(5*l+11*frRigidBodyCount(i)+m));
%            end
%            frMarkerID(i,l) = str2double(Data(5*l+11*frRigidBodyCount(i)+4));
%            frMarkerName(i,l) = Data(5*l+11*frRigidBodyCount(i)+5);
%         end
%         
%         i = i + 1;
%     elseif (strcmpi(Data(1),'rigidbody'))
%         %************%
%         %   TO DO    %
%         %************%
%         
%         i = i + 1;
%     else
%         error('Error: Frame and Rigid Body Data');
%     end
%     
%     lineData = fgetl(fileID);
% end
% fclose(fileID);
