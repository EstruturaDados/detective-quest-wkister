#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"
#include "arvore.h"

/**
 * @brief Função para criar uma nova sala na árvore do tabuleiro
 * @param nome Nome da sala a ser armazenado
 * @return Ponteiro para a nova sala criado
 */
Sala* criarSala(char* nome) {
  Sala* novo = (Sala*) malloc(sizeof(Sala));
  strcpy(novo->nome, nome);
  novo->esquerda = NULL;
  novo->direita = NULL;
  return novo;
}

/**
 * @brief Função para inicializar a árvore de salas do tabuleiro
 * @return Ponteiro para a raiz da árvore de salas
 */
Sala* inicializarArvoreSalas() {
  // Raiz da árvore
  Sala* corredor = criarSala("Corredor Principal");

  // Nível 1
  Sala* lado_esquerdo = criarSala("Lado Esquerdo");
  Sala* lado_direito = criarSala("Lado Direito");
  corredor->esquerda = lado_esquerdo; // Lado esquerdo do tabuleiro
  corredor->direita = lado_direito;   // Lado direito do tabuleiro

  // Nível 2 - Lado esquerdo do tabuleiro
  Sala* cozinha = criarSala("Cozinha");
  Sala* salao_de_festas = criarSala("Salao de Festas");
  lado_esquerdo->esquerda = cozinha;          // Esquerda do lado esquerdo
  lado_esquerdo->direita = salao_de_festas;   // Direita do lado esquerdo

  // Nível 2 - Lado direito do tabuleiro
  Sala* salao_de_musica = criarSala("Salao de Musica");
  Sala* escritorio = criarSala("Escritorio");
  lado_direito->esquerda = salao_de_musica; // Esquerda do lado direito
  lado_direito->direita = escritorio;       // Direita do lado direito

  // Nível 3 - Lado esquerdo do tabuleiro
  Sala* sala_de_estar = criarSala("Sala de Estar");
  Sala* jardim = criarSala("Jardim");
  salao_de_festas->esquerda = sala_de_estar; // Esquerda do salão de festas
  salao_de_festas->direita = jardim;         // Direita do salão de festas

  // Nível 3 - Lado direito do tabuleiro
  Sala* salao_de_jogos = criarSala("Salão de Jogos");
  Sala* biblioteca = criarSala("Biblioteca");
  salao_de_musica->esquerda = salao_de_jogos; // Esquerda do escritório
  escritorio->direita = biblioteca;         // Direita do escritório

  // Nível 4 - Lado direito do tabuleiro
  Sala* sala_de_jantar = criarSala("Sala de Jantar");
  biblioteca->esquerda = sala_de_jantar; // Esquerda da biblioteca

  return corredor;
}

/**
 * @brief Função para liberar a memória alocada para a árvore de salas
 * @param raiz Ponteiro para a raiz da árvore de salas
 */
void explorarSala(struct Sala* raiz) {
  // Navegação pela árvore de salas
  char opcao;
  do{
    printf("\n---------------------------\n");
    printf("Você está na sala: %s\n", raiz->nome);
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

void liberarMemoria(struct Sala* raiz) {
  if (raiz == NULL) return;
  liberarMemoria(raiz->esquerda);
  liberarMemoria(raiz->direita);
  free(raiz);
}

