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

// --- Constantes ---
#define TAM_PISTAS 5 // Número de tipos de pistas disponíveis

// Vetor de pistas
extern char tipoPistas[TAM_PISTAS][TAM_STRING];

// Definição da estrutura de um nó na árvore binária
typedef struct Sala {
  char nome[TAM_STRING];
  char pista[TAM_STRING];
  struct Sala *esquerda;
  struct Sala *direita;
} Sala;

// Protóripos das funções
Sala* criarSala(char* nome, char* pista); // Cria uma nova sala na árvore
Sala* inicializarArvoreSalas(); // Inicializa a árvore de salas do tabuleiro
void explorarSala(); // Permite a navegação do jogador pela árvore
void liberarMemoria(struct Sala* raiz); // Libera a memória alocada para a árvore
int* fisherYatesIndices(int size); // Gera uma permutação aleatória de índices
int* fisherYatesShuffle(const int original[], int size); // Embaralha um array usando o algoritmo Fisher-Yates
void swap(int *a, int *b); // Troca dois elementos

#endif