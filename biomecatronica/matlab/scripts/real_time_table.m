%########################### Real-time table ##############################
%#real_time_table()                                                       #
%#File name  : real_time_table.m                                          #
%#Created on : 17-08-2013                                                 #
%#Description: Real time uitable                                          #
%#Copyright 2013 Vando Salgueiro                                          #
%##########################################################################
function [U] = real_time_table()
values = cell(6,1);                                 %Create cell array, used to preallocate.
data = cell2mat(values);                            %Convert cell array to numeric array.
value = cell2mat(values);                           %Convert cell array to numeric array.
t = uitable('Parent', ...                           %Create 2-D graphic table GUI component.
    figure('Position',[300 300 400 350]), ...       %The handle of the uitable's parent object.
    'ColumnEditable', false, ...                    %Determines if column is user-editable.
    'RowName', [], ...                              %Row heading names.
    'ColumnName', {'Time', 'Data'}, ...             %Column heading names.
    'Position',[124.25 75 151.5 250]);              %Size and location of uitable, [left bottom width height].
set(t, 'BackgroundColor', [1 1 1]);                 %Cell background color, white in this case.
set(gcf, 'color', 'white');                         %GUI background color.
i = 0;                                              %Variable used to increase the cycle.
x = 1;                                              %Variable used to increase the vector.
close_btn = uicontrol('Style', 'pushbutton', ...    %Create user interface control object.
    'String', 'close',...                           %Its a push button type with the string 'close'.
    'Position', [340 320 50 20],...                 %Size and location of the button.
    'Callback', 'close');                           %Name of the .m file with the function.
set(close_btn, 'BackgroundColor', 'black');         %Cell background color.
set(close_btn, 'ForegroundColor', 'white');         %Font color.
stop_btn = uicontrol('Style', 'pushbutton', ...     %Create user interface control object.
    'String', 'stop',...                            %Its a push button type with the string 'stop'.
    'Position', [230 20 50 20],...                  %Size and location of the button.
    'Callback', 'stop');                            %Name of the .m file with the function.
set(stop_btn, 'BackgroundColor', 'white');          %Cell background color, white in this case.
return_btn = uicontrol('Style', 'pushbutton', ...   %Create user interface control object.
    'String', 'return',...                          %Its a push button type with the string 'return'.
    'Position', [290 20 50 20],...                  %Size and location of the button.
    'Callback', 'return');                          %Name of the .m file with the function.
set(return_btn, 'BackgroundColor', 'white');        %Cell background color.
while(i < 6)                                        %Six values.
    pause(2);                                       %Halt execution temporarily.
    i = i + 1;                                      %Increment the cycle.
    value(x) = x;                                   %Stores the value of the x variable.
    data(x) = rand(1);                              %Stores a random value.
    if(x == 2)                                      %If x is equal to two.
        value = value';                             %Transpose.
        data = data';                               %Transpose.
    end
    mydata = [value data];                          %Create a new vector.
    set(t, 'Data', mydata);                         %Set the data to display in the table.
    if(data(x) > 0.5)                               %String condition.
        d = uicontrol('Style','text',...            %Create user interface control object.
        'Position',[125 50 150 20],...              %Size and location of the text.
        'String','The value is above the normal.'); %Text to display.
        set(d, 'BackgroundColor', 'white');         %Cell background color.
        set(d, 'ForegroundColor', 'red');           %Font color.
    elseif(data(x) < 0.5)                           %String condition.
        d = uicontrol('Style','text',...            %Create user interface control object.
        'Position',[125 50 150 20],...              %Size and location of the text.
        'String','The value is okay.');             %Text to display.
        set(d, 'BackgroundColor', 'white');         %Cell background color.
    end
    x = x + 1;                                      %Increment the vector.
end
end