%**************************************************************************
% Autores:  Alexandre Mitsuru Nishikawa     N∫ USP: 5947440
%           Henrique Yuji Sugimoto                  5945917
%
% DescriÁ„o: 
%  Script de processamento dos dados do arquivo '.csv' exportado pelo
%  software Motive:Tracker e geraÁ„o de um vÌdeo do movimento realizado.
%
%------------ Escola PolitÈcnica da Universidade de S„o Paulo -------------
%
% Version: 1.0
% Date: 05.21.2014 [mm.dd.yyyy]
%
% Steps:
%  - Open CSV file;
%  - Extract information of data;
%  - Close CSV file;
%  - Plot motion;
%  - Create a video file.
%
%**************************************************************************

%% Clear Workspace and Command Window and Close Figures
clear;
close all;
clc;

fprintf('*****   Welcome to Motion Visualizer Software!   *****\n\n');
run('script_csv.m');
run('script_video.m');
