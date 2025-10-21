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
#define TAM_STRING 50 // Tamanho máximo para strings

#include "bst.h" // Inclusão do arquivo de árvore binária de busca

// Forward declarations para evitar dependência circular
struct EntradaTabelaHash;

// Estrutura para valores em lista encadeada (usado para múltiplos valores por chave)
struct valor {
  char valor[TAM_STRING];
  struct valor* proximo;
};

// --- Constantes ---
#define MAX_PISTAS 10 // Número de tipos de pistas disponíveis (atualizado para tabela hash)
#define MAX_SALAS 5  // Número máximo de salas na árvore
#define MAX_SUSPEITOS 4 // Número máximo de suspeitos

// Vetor de pistas
extern char tipoPistas[MAX_PISTAS][TAM_STRING];

// Vetor de salas
extern char nomesSalas[MAX_SALAS][TAM_STRING];

// Estrutura de suspeitos
typedef struct Suspeito {
  char nome[TAM_STRING];
  char profissao[TAM_STRING];
} Suspeito;

// Lista de suspeitos
extern struct Suspeito suspeitos[MAX_SUSPEITOS];

// Definição da estrutura de um nó na árvore binária
typedef struct Sala {
  char nome[TAM_STRING];
  struct Sala *esquerda;
  struct Sala *direita;
  int visitado; // Flag para controle de liberação de memória em grafos com ciclos
} Sala;

// Estrutura para lista encadeada de strings
struct listaNo {
  char valor[TAM_STRING];
  struct listaNo* proximo;
};

// Protóripos das funções
Sala* criarSala(char* nome); // Cria uma nova sala na árvore
Sala* inicializarArvoreSalas(); // Inicializa a árvore de salas do tabuleiro
void explorarSala(struct Sala* raiz, struct No* arvorePistas, const struct EntradaTabelaHash* tabelaSalasPistas, const struct EntradaTabelaHash* tabelaPistasSuspeiros); // Permite a navegação do jogador pela árvore
void liberarMemoria(struct Sala* raiz); // Libera a memória alocada para a árvore
int* fisherYatesIndices(int size); // Gera uma permutação aleatória de índices
void exibirSuspeitos(); // Exibe a lista de suspeitos com suas profissões
void escolherSuspeito(const struct No* arvorePistas, const struct EntradaTabelaHash* tabelaPistasSuspeiros); // Permite ao jogador escolher um suspeito
struct listaNo* arvoreParaListaEncadeada(const struct No* raiz); // Converte uma árvore binária em uma lista encadeada

#endif