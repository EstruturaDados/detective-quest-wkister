#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "geral.h"
#include "arvore.h"
#include "bst.h"
#include "tabela_hash.h"

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

// Lista de suspeitos
struct Suspeito suspeitos[MAX_SUSPEITOS] = {
  {"Ana", "Governanta"},
  {"Bruno", "Escritor"},
  {"Carlos", "Jardineiro"},
  {"Amanda", "Enfermeira"}
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
   *      /      \
   *    Quarto  Jardim
   *     /
   *  Cozinha
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
  Sala* jardim = criarSala("Jardim");
  salaEstar->esquerda = quarto; // Link da sala de estar para o quarto pela esquerda
  salaEstar->direita = jardim; // Link da sala de estar para o jardim pela direita
  jardim->esquerda = salaEstar; // Link de volta para a sala de estar
  quarto->direita = salaEstar; // Link de volta para a sala de estar

  // Cozinha <-> Quarto <-> Sala de estar <-> Hall <-> Biblioteca
  Sala* cozinha = criarSala("Cozinha");
  quarto->esquerda = cozinha; // Link da sala de estar para a cozinha pela direita
  cozinha->direita = quarto; // Link de volta para a sala de estar

  return hall;
}

/**
 * @brief Função para exibir a lista de suspeitos com suas profissões
 */
void exibirSuspeitos() {
  /**
   * @note Esta função exibe a lista de suspeitos disponíveis no jogo com suas respectivas profissões.
   */
  printf("\n=== Lista de Suspeitos ===\n");
  for (int i = 0; i < MAX_SUSPEITOS; i++) {
    printf("%d. %s - %s\n", i + 1, suspeitos[i].nome, suspeitos[i].profissao);
  }
  printf("=========================\n");
}

/**
 * @brief Função para liberar a memória alocada para a árvore de salas
 * @param raiz Ponteiro para a raiz da árvore de salas
 */
void explorarSala(struct Sala* raiz, struct No* arvorePistas, const EntradaTabelaHash* tabelaSalasPistas, const EntradaTabelaHash* tabelaPistasSuspeiros) {
  // Variável para detectar movimento (0 = sem movimento, 1 = houve movimento)
  int movimento = 1;

  // Navegação pela árvore de salas
  char opcao;
  do{
    // Exibe a lista de suspeitos com suas profissões
    exibirSuspeitos();

    // Se houve movimento, significa que o jogador foi para uma sala diferente e coleta a pista da sala
    if (movimento) {
      // Procurar pelas pistas da sala atual na tabela hash
      struct valor* pistas = pegarValoresTabelaHash(raiz->nome, tabelaSalasPistas);

      while (pistas != NULL) {
        // Verifica se a pista já foi coletada
        if (!buscarBST(arvorePistas, pistas->valor)) {
          // Adicionar a pista da sala atual na árvore de pistas
          inserirBST(&arvorePistas, pistas->valor);
          break;
        }
        pistas = pistas->proximo;
      }
    }

    // Exibir as pistas em ordem alfabética
    printf("Pistas(s) coletada(s): ");
    exibirEmOrdem(arvorePistas);

    printf("\n---------------------------\n");
    // printf("Você está na sala: %s. Pista: %s\n", raiz->nome, raiz->pista);
    printf("Você está na sala: %s.\n", raiz->nome);
    printf("---------------------------\n");
    // Perguntar para onde deseja ir
    printf("Para onde deseja ir? (t: suspeito, e: esquerda, d: direita, s: sair): ");
    scanf(" %c", &opcao);
    limparBufferEntrada();
    switch(opcao){
      case 'e': // Escolha para o lado esquerdo
        if (raiz->esquerda != NULL){
          raiz = raiz->esquerda;

          movimento = 1; // Houve movimento
        } else {
          printf("\n=============================\n");
          printf("= Não há nenhuma sala à esquerda. =\n");
          printf("=============================\n");

          movimento = 0;
        }
        break;
      case 'd': // Escolha para o lado direito
      if (raiz->direita != NULL){
          raiz = raiz->direita;

          movimento = 1; // Houve movimento
        } else {
          printf("\n=============================\n");
          printf("=   Não há sala à direita. =\n");
          printf("=============================\n");

          movimento = 0;
        }
        break;
      case 't':
        escolherSuspeito(arvorePistas, tabelaPistasSuspeiros);
        return; // Sai da função após escolher o suspeito
        break;
      case 's': // Sair
        printf("Saindo da exploração das salas.\n");
        break;
      default:
        printf("Opção inválida. Use 'suspei(t)o, (e)squerda', '(d)ireita' ou '(s)air'.\n");
    }
  } while (opcao != 's');

  // Mostra as pistas coletadas em ordem alfabética
  printf("\n=====================================\n");
  printf("Pistas coletadas em ordem alfabética:\n");
  exibirEmOrdem(arvorePistas);
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
 * @brief Função auxiliar para trocar dois elementos (uso interno)
 * @param a Ponteiro para o primeiro elemento
 * @param b Ponteiro para o segundo elemento
 */
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

void escolherSuspeito(const struct No* arvorePistas, const EntradaTabelaHash* tabelaPistasSuspeiros) {
  int escolha;
  exibirSuspeitos();
  printf("Escolha o número do suspeito que deseja acusar: ");
  scanf("%d", &escolha);
  limparBufferEntrada();

  while(escolha < 1 || escolha > MAX_SUSPEITOS) {
    printf("Escolha inválida. Tente novamente: ");
    scanf("%d", &escolha);
    limparBufferEntrada();
  }

  printf("Você acusou %s, o(a) %s.\n", suspeitos[escolha - 1].nome, suspeitos[escolha - 1].profissao);

  // Estrutura para armazenar os suspeitos e quantas e quais pistas foram associadas a cada um
  struct {
    char nome[TAM_STRING];
    int contagem;
    char pistas[MAX_PISTAS][TAM_STRING];
  } suspeitosContagem[MAX_SUSPEITOS];

  // Inicializa as contagens
  for (int i = 0; i < MAX_SUSPEITOS; i++) {
    strcpy(suspeitosContagem[i].nome, suspeitos[i].nome);
    suspeitosContagem[i].contagem = 0;
  }

  // Transformando a árvore binária em lista encadeada para facilitar a iteração
  struct listaNo* listaEncadeada = arvoreParaListaEncadeada(arvorePistas);
  struct listaNo* atual = listaEncadeada;

  // Varrendo a lista de pistas para contar as pistas por suspeito
  while (atual != NULL){
    // Pega os suspeitos associados à pista atual
    struct valor* suspeitosAssociados = pegarValoresTabelaHash(atual->valor, tabelaPistasSuspeiros);
    while (suspeitosAssociados != NULL) {
      // Incrementa a contagem para o suspeito correspondente
      for (int i = 0; i < MAX_SUSPEITOS; i++) {
        if (strcmp(suspeitosAssociados->valor, suspeitosContagem[i].nome) == 0) {
          suspeitosContagem[i].contagem++;
          strcpy(suspeitosContagem[i].pistas[suspeitosContagem[i].contagem - 1], atual->valor);
          break;
        }
      }
      suspeitosAssociados = suspeitosAssociados->proximo;
    }
    atual = atual->proximo;
  }

  // Verificando se a acusação está correta
  if (suspeitosContagem[escolha - 1].contagem > 1) {
    printf("\nParabéns! Sua acusação está correta. %s tem as seguintes pistas contra ele(a):", suspeitos[escolha - 1].nome);
    for (int i = 0; i < suspeitosContagem[escolha - 1].contagem; i++) {
      printf("\n- %s", suspeitosContagem[escolha - 1].pistas[i]);
    }
    printf("\n");
  } else {
    printf("\nSua acusação está incorreta. %s não tem pistas suficientes contra ele(a).\n", suspeitos[escolha - 1].nome);
  }

  // Liberando a memória da lista encadeada
  while (listaEncadeada != NULL) {
    struct listaNo* temp = listaEncadeada;
    listaEncadeada = listaEncadeada->proximo;
    free(temp);
  }
}

/**
 * @brief Função auxiliar recursiva para converter árvore em lista encadeada em ordem
 * @param raiz Ponteiro para a raiz da árvore binária
 * @param lista Ponteiro para ponteiro da cabeça da lista (passado por referência)
 * @param cauda Ponteiro para ponteiro da cauda da lista (para inserção eficiente no final)
 */
static void arvoreParaListaEncadeadaAux(const struct No* raiz, struct listaNo** lista, struct listaNo** cauda) {
  if (raiz == NULL) return;

  // Percorre a subárvore esquerda primeiro (ordem crescente em BST)
  arvoreParaListaEncadeadaAux(raiz->esquerda, lista, cauda);

  // Processa o nó atual
  struct listaNo* novoNo = (struct listaNo*) malloc(sizeof(struct listaNo));
  strcpy(novoNo->valor, raiz->valor);
  novoNo->proximo = NULL;

  // Se a lista está vazia, este é o primeiro nó
  if (*lista == NULL) {
    *lista = novoNo;
    *cauda = novoNo;
  } else {
    // Adiciona no final da lista para manter a ordem
    (*cauda)->proximo = novoNo;
    *cauda = novoNo;
  }

  // Percorre a subárvore direita
  arvoreParaListaEncadeadaAux(raiz->direita, lista, cauda);
}

/**
 * @brief Função para converter uma árvore binária em uma lista encadeada em ordem
 * @param raiz Ponteiro para a raiz da árvore binária
 * @return Ponteiro para a cabeça da lista encadeada (em ordem crescente para BST)
 */
struct listaNo* arvoreParaListaEncadeada(const struct No* raiz) {
  struct listaNo* lista = NULL;
  struct listaNo* cauda = NULL;
  arvoreParaListaEncadeadaAux(raiz, &lista, &cauda);
  return lista;
}