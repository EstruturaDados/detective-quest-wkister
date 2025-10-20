/**
 * @file tabela_hash.c
 * @brief Implementação da tabela hash para mapeamento de pistas a suspeitos
 * @author Wellington Kister do Nascimento
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

/**
 * @brief Calcula o índice hash para uma chave de string.
 * @param chave String utilizada como chave de hash.
 * @return Índice calculado na faixa [0, TAMANHO_TABELA-1].
 */
int funcao_hash(const char* chave) {
  int soma = 0;
  for (int i = 0; chave[i] != '\0'; i++) {
    soma += chave[i];
  }
  return soma % TAMANHO_TABELA;
}

/**
 * @brief Insere uma pista na tabela hash usando sondagem linear para colisões.
 * @param chave String com a chave a ser inserida.
 * @param valor String com o nome do valor associado.
 * @param tabela_hash Ponteiro para a tabela hash.
 */
void inserirTabelaHash(const char* chave, const char* valor, EntradaTabelaHash* tabela_hash) {
  int indice = funcao_hash(chave);
  printf("-------------------------------------------\n");
  printf("Índice hash inicial para '%s': %d\n", chave, indice);

  for (int i = 0; i < TAMANHO_TABELA; i++) {
    int pos = (indice + i) % TAMANHO_TABELA;

    if (tabela_hash[pos].ocupado == 0 || tabela_hash[pos].ocupado == -1) {
      strcpy(tabela_hash[pos].valor, valor);
      strcpy(tabela_hash[pos].chave, chave);
      tabela_hash[pos].ocupado = 1;
      printf("'%s' -> '%s' inserido na posição %d. Status: %d\n", chave, tabela_hash[pos].valor, pos, tabela_hash[pos].ocupado);
      // printf("-------------------------------------------\n");
      return;
    }
  }

  printf("Tabela cheia. Não foi possível inserir '%s'.\n", chave);
  printf("-------------------------------------------\n");
}

/**
 * @brief Obtém todos os valores associados a uma chave na tabela hash.
 * @param chave String com a chave a ser buscada.
 * @param tabela_hash Ponteiro para a tabela hash.
 * @return Valores associados à chave ou NULL se não encontrado.
 */
struct valor* pegarValoresTabelaHash(const char* chave, const EntradaTabelaHash* tabela_hash) {
  int indice = funcao_hash(chave);

  // Define o ponteiro que guardar os valores encontrados
  struct valor* valores = NULL;

  // Varre TODA a tabela para encontrar todas as entradas com a chave
  for (int i = 0; i < TAMANHO_TABELA; i++) {
    int pos = (indice + i) % TAMANHO_TABELA;

    struct EntradaTabelaHash entradaAtual = tabela_hash[pos];

    // Debug: mostra o que está sendo verificado
    // printf("Verificando posição %d: chave='%s', valor='%s', ocupado=%d\n",
    //        pos, entradaAtual.chave, entradaAtual.valor, entradaAtual.ocupado);

    // Coleta TODAS as entradas ocupadas que têm a chave procurada
    if (entradaAtual.ocupado == 1 && strcmp(entradaAtual.chave, chave) == 0) {
      // printf("  -> MATCH! Adicionando valor '%s' à lista\n", entradaAtual.valor);
      struct valor* novoValor = (struct valor*) malloc(sizeof(struct valor));
      strcpy(novoValor->valor, tabela_hash[pos].valor);
      novoValor->proximo = valores;
      valores = novoValor;
    }
  }

  return valores;
}

/**
 * @brief Busca um valor na tabela hash
 * @param valor String com a pista a ser buscada.
 * @param tabela_hash Ponteiro para a tabela hash.
 * @return Índice da pista na tabela, ou -1 se não encontrado.
 */
int buscarValorTabelaHash(const char* valor, const EntradaTabelaHash* tabela_hash) {
  int indice = funcao_hash(valor);

  for (int i = 0; i < TAMANHO_TABELA; i++) {
    int pos = (indice + i) % TAMANHO_TABELA;

    if (tabela_hash[pos].ocupado == 0) {
      return -1; // Paramos: posição nunca foi usada
    }

    // if (tabela_hash[pos].ocupado == 1 && strcmp(tabela_hash[pos].pista, pista) == 0) {
    //   return pos;
    // }
  }

  return -1; // Não encontrou
}

/**
 * @brief Obtém o suspeito associado a uma pista.
 * @param pista String com a pista a ser buscada.
 * @param tabela_hash Ponteiro para a tabela hash.
 * @return Nome do suspeito ou NULL se não encontrado.
 */
// char* obterSuspeito(const char* pista, const EntradaTabelaHash* tabela_hash) {
  // int pos = buscarPistaTabelaHash(pista, tabela_hash);
  // if (pos != -1) {
  //   return (char*)tabela_hash[pos].suspeito;
  // }
//   return NULL;
// }

/**
 * @brief Inicializa a tabela hash com todas as pistas mapeadas para suspeitos.
 * @return Ponteiro para a tabela hash inicializada.
 * @param tabela_hash Ponteiro para a tabela hash a ser inicializada.
 */
void inicializarTabelaPistasSuspeitos(EntradaTabelaHash* tabela_hash) {
  // Inicializa a tabela como vazia
  for (int i = 0; i < TAMANHO_TABELA; i++) {
    tabela_hash[i].ocupado = 0;
  }

  // Insere todas as pistas na tabela
  // --- Lógica das Associações ---
  // 🕵️ Ana
  // Pistas: "Chave antiga", "Mochila rosa", "Agenda cheia"
  // Lógica: Ana é a governanta da casa
  // "Chave antiga" → Tem as chaves de todos os cômodos
  // "Mochila rosa" → Pertence a Ana (item pessoal)
  // "Agenda cheia" → Controla a agenda da família
  // 📚 Bruno
  // Pistas: "Livro grande", "Tinta preta", "Caneta azul"
  // Lógica: Bruno é o estudante/escritor
  // "Livro grande" → Livros de estudo/trabalho
  // "Tinta preta" → Materiais de escrita
  // "Caneta azul" → Ferramentas de trabalho
  // 🌿 Carlos
  // Pistas: "Terra molhada", "Folhas verdes"
  // Lógica: Carlos é o jardineiro
  // "Terra molhada" → Trabalha com plantas/jardinagem
  // "Folhas verdes" → Evidências do jardim
  // 💊 Amanda
  // Pistas: "Remedio forte", "Lenço limpo"
  // Lógica: Amanda é a enfermeira
  // "Remedio forte" → Conhecimento médico
  // "Lenço limpo" → Hábitos de higiene profissional
  printf("\n=== Inicializando Tabela Hash de Pistas ===\n");
  inserirTabelaHash("Chave antiga", "Ana", tabela_hash);
  inserirTabelaHash("Mochila rosa", "Ana", tabela_hash);
  inserirTabelaHash("Agenda cheia", "Ana", tabela_hash);
  inserirTabelaHash("Livro grande", "Bruno", tabela_hash);
  inserirTabelaHash("Tinta preta", "Bruno", tabela_hash);
  inserirTabelaHash("Caneta azul", "Bruno", tabela_hash);
  inserirTabelaHash("Terra molhada", "Carlos", tabela_hash);
  inserirTabelaHash("Folhas verdes", "Carlos", tabela_hash);
  inserirTabelaHash("Remedio forte", "Amanda", tabela_hash);
  inserirTabelaHash("Lenço limpo", "Amanda", tabela_hash);
  printf("=== Finalizado Tabela Hash de Pistas -> Suspeitos ===\n");

  // return *tabela_hash;
}

/**
 * @brief Inicializa a tabela hash com todas as salas mapeadas para pistas.
 * @return Ponteiro para a tabela hash inicializada.
 * @param tabela_hash Ponteiro para a tabela hash a ser inicializada.
 */
void inicializarTabelaSalasPistas(EntradaTabelaHash* tabela_hash){
  /**
   * @note Esta função inicializa a tabela hash com as salas para armazenar, de forma aleatória, as pistas associadas a cada sala.
   */
  // Inicializa a tabela como vazia
  for (int i = 0; i < TAMANHO_TABELA; i++) {
    tabela_hash[i].ocupado = 0;
  }

  printf("\n=== Inicializando Tabela Hash de Pistas ===\n");
  // Vetor de índices para embaralhar as pistas
  int* indicesPistasEmbaralhadas = fisherYatesIndices(MAX_PISTAS);

  // Varrendo o vetor de pistas embaralhadas e inserindo na tabela hash
  for (int i = 0; i < MAX_PISTAS; i++) {
    inserirTabelaHash(nomesSalas[i % MAX_SALAS], tipoPistas[indicesPistasEmbaralhadas[i]], tabela_hash);
  }

  free(indicesPistasEmbaralhadas); // Libera memória alocada
  printf("=== Finalizado Tabela Hash de Pistas -> Suspeitos ===\n");
}

/**
 * @brief Exibe estatísticas sobre as pistas por suspeito.
 * @param tabela_hash Ponteiro para a tabela hash.
 */
void exibirEstatisticas(const EntradaTabelaHash* tabela_hash) {
  int contagem[MAX_SUSPEITOS] = {0};

  printf("\n=== Estatísticas: Pistas por Suspeito ===\n");

  // Conta quantas pistas apontam para cada suspeito
  for (int i = 0; i < TAMANHO_TABELA; i++) {
    if (tabela_hash[i].ocupado == 1) {
      for (int j = 0; j < MAX_SUSPEITOS; j++) {
        // if (strcmp(tabela_hash[i].valor, suspeitos[j].nome) == 0) {
        //   contagem[j]++;
        //   break;
        // }
      }
    }
  }

  // Exibe as estatísticas
  for (int i = 0; i < MAX_SUSPEITOS; i++) {
    printf("%s: %d pista(s)\n", suspeitos[i].nome, contagem[i]);
  }
  printf("\n");
}
