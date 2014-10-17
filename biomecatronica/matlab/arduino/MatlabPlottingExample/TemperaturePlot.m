% Basic Text File Read, Search, and Plot
% Phil R
% 13/5/2012

% When a text file is loaded the spaces are removed. Originally I had temperature and humidity logging
% which was printed to the serial port like this "H: 63 % T: 22 *C". When its loaded in to freemat
% it appears like this "H:63%T:22*C" so we will look for the "%T:" to indicate that the next two digits
% are the logged temperature. These will then be extracted and plotted.

% User Settings
clear all %start with fresh workspace
dataPath = 'C:\Users\Phil\Desktop\';
textFilename = 'arduinolog1.txt';
widthOfTempdata = 2; %eg arduino prints T: 22*C, we are interested in the 22 so that is 2 digits 
temperatureDelimiter = '%T:'; %This appears before each temperature reading

% % Open the file and load it in to
fp = fopen([dataPath textFilename]);
loadedText = fscanf(fp,'%s');

% Find Indicies Where TemperatureDelimiter Exists In Loaded String
matchIndex = strfind(loadedText, temperatureDelimiter);

% Loop Through and Store Found Temperatue Readings
for i = 1:length(matchIndex)
    loggedTemps(i) = str2num(loadedText((matchIndex(i)+length(temperatureDelimiter)):(matchIndex(i)+length(temperatureDelimiter))+widthOfTempdata-1));
end

% Loop Through and Store Found Humidity Readings
humidityDelimiter = 'H:'; %This appears before each temperature reading
matchIndex = strfind(loadedText, humidityDelimiter);
for i = 1:length(matchIndex)
    loggedHumidity(i) = str2num(loadedText((matchIndex(i)+length(humidityDelimiter)):(matchIndex(i)+length(humidityDelimiter))+widthOfTempdata-1));
end

% Plot The Resulting Temperatures
figure(1);clf;
subplot(2,1,1)
plot(loggedTemps)
title('Room Temperature','fontsize',13,'fontweight','bold');
xlabel('Record Number','fontsize',10,'fontweight','bold');
ylabel('Temperature [DegC]','fontsize',10,'fontweight','bold');
axis([0 250 16 24])

% Plot The Resulting Humidity
subplot(2,1,2)
plot(loggedHumidity,'color','r')
title('Room Humidity','fontsize',13,'fontweight','bold');
xlabel('Record Number','fontsize',10,'fontweight','bold');
ylabel('Temperature [DegC]','fontsize',10,'fontweight','bold');
axis([0 250 60 70])
