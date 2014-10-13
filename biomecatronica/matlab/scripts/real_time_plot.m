%######### Real-time chart ###########
%#Plot_Example(cycles)               #
%#cycles - Number of points to draw  #
%#File name  : Plot_Example.m        #
%#Created on : 11-07-2013            #
%#Description: Real time plot        #
%#Copyright 2013 Vando Salgueiro     #
%#####################################
function Plot_Example(cycles)
global t                                %Can be used in several functions.
n = 0;
i = 1;
    while(n < cycles)
        t(i) = rand(1);                 %Creates a matrix with the random values.
        i = i + 1;                      %Increase the position in the matrix.
        set(gcf, 'color', 'white');     %Change background color.
        drawnow;                        %Flush event queue and update figure window.
        plot(t,'-.dk','linewidth',1.8), axis([1 cycles 0 1])
        grid on;                        %Grid lines for 2-D and 3-D plots.
        title('Example');               %Add title to current axes.
        xlabel('Time');                 %Label x-axis.
        ylabel('Random value');         %Label y-axis.
        n = n + 1;
    end
    fprintf('The global variable in function %s is %s\n', ...
        mfilename, t(cycles));          %Just kidding around with the global.
    clear all                           %Remove items from MATLAB workspace.
end