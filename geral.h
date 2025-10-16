#ifndef GERAL_H
#define GERAL_H

#include <time.h>

// --- Constantes ---
#define TAM_STRING 50 // Tamanho máximo para strings
#define MAX_PECAS 5 // Tamanho máximo de peças no jogo

// --- Protótipos das funções gerais ---
// Função para limpar o buffer de entrada
void limparBufferEntrada();

// Função para imprimir o tempo gasto em operações
void tempoGasto(clock_t inicio, clock_t fim);

// Função para pausar a execução até o usuário pressionar Enter
void pausa();

#endif