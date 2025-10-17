#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"
#include "arvore.h"
#include "bst.h"

char tipoPistas[TAM_PISTAS][TAM_STRING] = {
    "Pegadas de Lama",
    "Chave perdida",
    "Livro com pagina faltando",
    "Lencol manchado",
    "Gaveta perdida"
};

/**
 * @brief Função para criar uma nova sala na árvore do tabuleiro
 * @param nome Nome da sala a ser armazenado
 * @return Ponteiro para a nova sala criado
 */
Sala* criarSala(char* nome, char* pista) {
  // Criação da nova sala
  Sala* novo = (Sala*) malloc(sizeof(Sala));
  strcpy(novo->nome, nome);
  strcpy(novo->pista, pista);
  novo->esquerda = NULL;
  novo->direita = NULL;
  return novo;
}

/**
 * @brief Função para inicializar a árvore de salas do tabuleiro
 * @return Ponteiro para a raiz da árvore de salas
 */
Sala* inicializarArvoreSalas() {
  // Vetor de índices para embaralhar as pistas
  int* indicesEmbaralhados = fisherYatesIndices(TAM_PISTAS);

  // Raiz da árvore
  Sala* raiz = criarSala("Hall de Entrada", tipoPistas[indicesEmbaralhados[0]]);

  // Inserção das salas
  raiz->esquerda = criarSala("Sala de Estar", tipoPistas[indicesEmbaralhados[1]]);
  raiz->direita = criarSala("Biblioteca", tipoPistas[indicesEmbaralhados[2]]);
  raiz->esquerda->esquerda = criarSala("Quarto", tipoPistas[indicesEmbaralhados[3]]);
  raiz->esquerda->direita = criarSala("Cozinha", tipoPistas[indicesEmbaralhados[4]]);

  return raiz;
}

/**
 * @brief Função para liberar a memória alocada para a árvore de salas
 * @param raiz Ponteiro para a raiz da árvore de salas
 */
void explorarSala(struct Sala* raiz, struct No* arvorePistas) {
  // Navegação pela árvore de salas
  char opcao;
  do{
    // Adicionar a pista da sala atual na árvore de pistas
    inserir(arvorePistas, raiz->pista);

    printf("\n---------------------------\n");
    printf("Você está na sala: %s. Pista: %s\n", raiz->nome, raiz->pista);
    printf("---------------------------\n");
    // Perguntar para onde deseja ir
    printf("Para onde deseja ir? (e: esquerda, d: direita, s: sair): ");
    scanf(" %c", &opcao);
    limparBufferEntrada();
    switch(opcao){
      case 'e': // Escolha para o lado esquerdo
        if (raiz->esquerda != NULL){
          raiz = raiz->esquerda;
        } else {
          printf("Não há sala à esquerda. Saindo.\n");
          return;
        }
        break;
      case 'd': // Escolha para o lado direito
        if (raiz->direita != NULL){
          raiz = raiz->direita;
        } else {
          printf("Não há sala à direita. Saind.\n");
          return;
        }
        break;
      case 's': // Sair
        printf("Saindo da exploração das salas.\n");
        break;
      default:
        printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
    }
  } while (opcao != 's');
}

/**
 * @brief Função para liberar a memória alocada para a árvore de salas
 * @param raiz Ponteiro para a raiz da árvore de salas
 */
void liberarMemoria(struct Sala* raiz) {
  if (raiz == NULL) return;
  liberarMemoria(raiz->esquerda);
  liberarMemoria(raiz->direita);
  free(raiz);
}

/**
 * @brief Função para trocar dois elementos
 * @param a Ponteiro para o primeiro elemento
 * @param b Ponteiro para o segundo elemento
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Função para embaralhar um array usando o algoritmo Fisher-Yates
 * @param arr Array a ser embaralhado
 * @param size Tamanho do array
 */
int* fisherYatesShuffle(const int original[], int size) {
  // Aloca memória para a cópia
  int *shuffled = (int*)malloc(size * sizeof(int));
  if (shuffled == NULL) {
    return NULL;
  }

  // Copia o array original
  for (int i = 0; i < size; i++) {
    shuffled[i] = original[i];
  }

  // Inicializa o gerador de números aleatórios
  srand(time(NULL));

  // Algoritmo Fisher-Yates
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(&shuffled[i], &shuffled[j]);
  }

  return shuffled;
}

/**
 * @brief Função para gerar uma sequência de índices embaralhados usando Fisher-Yates
 * @param size Tamanho da sequência
 * @return Ponteiro para o array de índices embaralhados
 */
int* fisherYatesIndices(int size) {
  int *indices = (int*)malloc(size * sizeof(int));
  if (indices == NULL) {
    return NULL;
  }

  // Inicializa índices sequenciais [0, 1, 2, ..., size-1]
  for (int i = 0; i < size; i++) {
    indices[i] = i;
  }

  srand(time(NULL));

  // Embaralha os índices
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(&indices[i], &indices[j]);
  }

  return indices;
}
