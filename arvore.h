/**
 * @file arvore.h
 * @brief Definições e protótipos para manipulação de árvores binárias
 * @author Wellington Kister do Nascimento
 *
 * Este arquivo contém as definições das estruturas de dados e os protótipos
 * das funções para criar, manipular e liberar árvores binárias.
 */

#ifndef ARVORE_H
#define ARVORE_H

#include "bst.h" // Inclusão do arquivo de árvore binária de busca

// --- Constantes ---
#define MAX_PISTAS 10 // Número de tipos de pistas disponíveis (atualizado para tabela hash)
#define MAX_SALAS 5  // Número máximo de salas na árvore

// Vetor de pistas
extern char tipoPistas[MAX_PISTAS][TAM_STRING];

// Vetor de salas
extern char nomesSalas[MAX_SALAS][TAM_STRING];

// Definição da estrutura de um nó na árvore binária
typedef struct Sala {
  char nome[TAM_STRING];
  struct Sala *esquerda;
  struct Sala *direita;
  int visitado; // Flag para controle de liberação de memória em grafos com ciclos
} Sala;

// Protóripos das funções
Sala* criarSala(char* nome); // Cria uma nova sala na árvore
Sala* inicializarArvoreSalas(); // Inicializa a árvore de salas do tabuleiro
void explorarSala(struct Sala* raiz, struct No* arvorePistas); // Permite a navegação do jogador pela árvore
// void explorarSala(struct Sala* raiz); // Permite a navegação do jogador pela árvore
void liberarMemoria(struct Sala* raiz); // Libera a memória alocada para a árvore
int* fisherYatesIndices(int size); // Gera uma permutação aleatória de índices
int* fisherYatesShuffle(const int original[], int size); // Embaralha um array usando o algoritmo Fisher-Yates
void swap(int *a, int *b); // Troca dois elementos

#endif