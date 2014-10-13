%**************************************************************************
% Autores:  Rafael Sanchez Souza e muitos outros
%
% Descrição: 
%  Script para leitura de dados de uma entrada digital e armazenamento da
%  carta de tempos em um vetor.
%
%------------ Escola Politécnica da Universidade de S??o Paulo -------------
%
% Version: 1.0
% Date: 10.12.2014 [mm.dd.yyyy]
%
% Steps:
%  - Serial connection
%  - Read data;
%  - Create timetable
%  - Save CSV file.
%
%**************************************************************************

%% Simulador do MPU6050 versão 4
% Defines.
% +32767;-32768
clear all;
clc;
f_aquisita = 120;
qte_calibra = 50;
offset= 50;


disp('Etapa 1: Valores iniciais definidos. Iniciando conexão serial.');
%% Start

s = serial('COM3');
set(s,'BaudRate',230400);
fopen(s);

disp('Etapa 2: Aquisição de Dados e Criação de Tabela');
%% Dados
    
for i = 1:(qte_calibra + offset);
    tic;    
    leitura_penultimo = fscanf(s, '%s');
    leitura_ultimo = leitura_penultimo;
    while toc < (1/f_aquisita);
        leitura_penultimo = leitura_ultimo;
        leitura_ultimo = fscanf(s,'%s'); 
    end
    leitura_serial{i} = leitura_penultimo;
end

disp('Etapa 3: Exporta dados *.csv');

