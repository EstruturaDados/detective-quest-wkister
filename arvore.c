#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"
#include "arvore.h"
#include "bst.h"

// Vetor de pistas
char tipoPistas[MAX_PISTAS][TAM_STRING] = {
    "Chave antiga",
    "Mochila rosa",
    "Agenda cheia",
    "Livro grande",
    "Tinta preta",
    "Caneta azul",
    "Terra molhada",
    "Folhas verdes",
    "Remedio forte",
    "Lenço limpo"
};

// Vetor de salas
char nomesSalas[MAX_SALAS][TAM_STRING] = {
  "Hall de Entrada",
  "Sala de Estar",
  "Biblioteca",
  "Quarto",
  "Cozinha"
};

/**
 * @brief Função para criar uma nova sala na árvore do tabuleiro
 * @param nome Nome da sala a ser armazenado
 * @param pista Pista associada à sala
 * @return Ponteiro para a nova sala criado
 */
Sala* criarSala(char* nome) {
  /**
   * @note Esta função aloca memória para uma nova sala, inicializa seus campos
   *       e retorna um ponteiro para essa sala.
   * Foi criada a tag 'visitado' para controle de liberação de memória em grafos com ciclos. O grafo
   * permite que o jogador retorne a salas já visitadas.
   */
  // Criação da nova sala
  Sala* novo = (Sala*) malloc(sizeof(Sala));
  strcpy(novo->nome, nome);
  novo->esquerda = NULL;
  novo->direita = NULL;
  novo->visitado = 0; // Inicializa como não visitado. Tag criada para liberação de memória em grafos com ciclos
  return novo;
}

/**
 * @brief Função para inicializar a árvore de salas do tabuleiro
 * @note  A quantidade de salas não pode ultrapasar o número de pistas disponíveis (MAX_PISTAS), pois não existem
 *        salas sem pistas.
 * @return Ponteiro para a raiz da árvore de salas
 */
Sala* inicializarArvoreSalas() {
  /**
   * Estrutura da Árvore de Salas:
   * A estrutura da árvore é a seguinte:
   *          Hall de Entrada
   *          /             \
   *   Sala de Estar     Biblioteca
   *      /                   \
   *    Quarto               Cozinha
   *
   * A árvore foi modificada para um 'grafo', onde cada sala pode voltar para a sala anterior, para atender às
   * necessidades da programação de que 'o jogo encerra quando quando o jogador decide sair'.
   */



  // Raiz da árvore
  Sala* hall = criarSala("Hall de Entrada");

  // Sala de estar <-> Hall
  Sala* salaEstar = criarSala("Sala de Estar");
  hall->esquerda = salaEstar; // Link do hall para a sala de estar pela esquerda
  salaEstar->direita = hall; // Link de volta para o hall

  // Sala de estar <-> Hall <-> Biblioteca
  Sala* biblioteca = criarSala("Biblioteca");
  hall->direita = biblioteca; // Link do hall para a biblioteca pela direita
  biblioteca->esquerda = hall; // Link de volta para o hall

  // Quarto <-> Sala de estar <-> Hall <-> Biblioteca
  Sala* quarto = criarSala("Quarto");
  salaEstar->esquerda = quarto; // Link da sala de estar para o quarto pela esquerda
  quarto->direita = salaEstar; // Link de volta para a sala de estar

  // Cozinha <-> Quarto <-> Sala de estar <-> Hall <-> Biblioteca
  Sala* cozinha = criarSala("Cozinha");
  quarto->esquerda = cozinha; // Link da sala de estar para a cozinha pela direita
  cozinha->direita = quarto; // Link de volta para a sala de estar

  return hall;
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
    // inserirBST(&arvorePistas, raiz->pista);

    printf("\n---------------------------\n");
    // printf("Você está na sala: %s. Pista: %s\n", raiz->nome, raiz->pista);
    printf("Você está na sala: %s.\n", raiz->nome);
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
          printf("Não há nenhuma sala à esquerda.\n");
          // opcao = 's'; // Força a saída do loop
        }
        break;
      case 'd': // Escolha para o lado direito
        if (raiz->direita != NULL){
          raiz = raiz->direita;
        } else {
          printf("Não há sala à direita.\n");
          // opcao = 's'; // Força a saída do loop
        }
        break;
      case 's': // Sair
        printf("Saindo da exploração das salas.\n");
        break;
      default:
        printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
    }
  } while (opcao != 's');

  // Mostra as pistas coletadas em ordem alfabética
  printf("\n=====================================\n");
  printf("Pistas coletadas em ordem alfabética:\n");
  exibirPistas(arvorePistas);
  printf("\n=====================================\n");
}

/**
 * @brief Função para liberar a memória alocada para a árvore de salas
 * @param raiz Ponteiro para a raiz da árvore de salas
 * @note Esta função usa BFS (Breadth-First Search) para lidar com grafos com ciclos
 */
void liberarMemoria(struct Sala* raiz) {
    if (raiz == NULL) return;

    // Fila para BFS - tamanho suficiente para o grafo pequeno
    Sala* fila[100];
    int inicio = 0, fim = 0;

    // Lista para armazenar nós a serem liberados
    Sala* aLiberar[100];
    int numNos = 0;

    // Adiciona a raiz na fila e marca como visitada
    fila[fim++] = raiz;
    raiz->visitado = 1;

    // BFS para coletar todos os nós únicos
    while (inicio < fim) {
        Sala* atual = fila[inicio++];
        aLiberar[numNos++] = atual;

        // Adiciona o filho esquerdo se existir e não foi visitado
        if (atual->esquerda != NULL && !atual->esquerda->visitado) {
            fila[fim++] = atual->esquerda;
            atual->esquerda->visitado = 1;
        }

        // Adiciona o filho direito se existir e não foi visitado
        if (atual->direita != NULL && !atual->direita->visitado) {
            fila[fim++] = atual->direita;
            atual->direita->visitado = 1;
        }
    }

    // Agora libera todos os nós coletados
    for (int i = 0; i < numNos; i++) {
        free(aLiberar[i]);
    }
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
