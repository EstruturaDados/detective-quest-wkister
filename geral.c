#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "geral.h"

// Funções gerais
/**
 * @brief Função para limpar o buffer de entrada
 */
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Função para imprimir o tempo gasto em operações
 * @param inicio Tempo de início
 * @param fim Tempo de fim
 */
void tempoGasto(clock_t inicio, clock_t fim){
    double tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %.6f segundos\n", tempoGasto);
}

/**
 * @brief Função para pausar a execução até o usuário pressionar Enter
 */
void pausa(){
    printf("Pressione Enter para continuar...");
    getchar();
}
