/**
 * @file bst.c
 * @brief Implementação de uma árvore binária de busca (BST)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"
#include "bst.h"

/**
 * @brief Função para criar um novo nó na árvore
 * @param valor Valor a ser armazenado no nó
 * @return Ponteiro para o novo nó criado
 */
No* criarNo(const char* valor) {
  No* novo = (No*) malloc(sizeof(No));
  strcpy(novo->valor, valor);
  novo->esquerda = NULL;
  novo->direita = NULL;
  return novo;
}

/**
 * @brief Função para inserir um novo valor na árvore binária de busca
 * @note Os menores valores vão para a esquerda e os maiores para a direita
 * @param raiz Ponteiro para a raiz da árvore
 * @param valor Valor a ser inserido
 * @return Ponteiro para a raiz atualizada da árvore
 */
void inserirBST(No** raiz, const char* valor) {
  if (*raiz == NULL){
    *raiz = criarNo(valor);
  } else if (strcmp(valor, (*raiz)->valor) < 0){
      inserirBST(&(*raiz)->esquerda, valor);
  } else if (strcmp(valor, (*raiz)->valor) > 0){
      inserirBST(&(*raiz)->direita, valor);
  }
}

/**
 * @brief Função para buscar um valor na árvore binária de busca
 * @param raiz Ponteiro para a raiz da árvore
 * @param chave Valor a ser buscado
 * @return 1 se encontrado, 0 caso contrário
 */
int buscarBST(No* raiz, const char* chave) {
  if (raiz == NULL){
    return 0;
  }

  if (strcmp(chave, raiz->valor) == 0){
    return 1;
  } else if (strcmp(chave, raiz->valor) < 0){
    return buscarBST(raiz->esquerda, chave);
  } else {
    return buscarBST(raiz->direita, chave);
  }
}

/**
 * @brief Função para remover um valor da árvore binária de busca
 * @param raiz Ponteiro para a raiz da árvore
 * @param valor Valor a ser removido
 * @return Ponteiro para a raiz atualizada da árvore
 */
No* removerBST(No* raiz, const char* valor) {
  if (raiz == NULL){
    return NULL;
  }

  if (strcmp(valor, raiz->valor) < 0) {
    raiz->esquerda = removerBST(raiz->esquerda, valor);
  } else if (strcmp(valor, raiz->valor) > 0) {
    raiz->direita = removerBST(raiz->direita, valor);
  } else {
    if (raiz->esquerda == NULL && raiz->direita == NULL) {
      // Caso 1: sem filhos
      // free(raiz->valor);
      free(raiz);
      return NULL;

      // Caso 2: um único filho
    } else if (raiz->esquerda == NULL) {
      No* temp = raiz->direita;
      // free(raiz->valor);
      free(raiz);
      return temp;
    } else if (raiz->direita == NULL) {
      No* temp = raiz->esquerda;
      // free(raiz->valor);
      free(raiz);
      return temp;

      // Caso 3: dois filhos
    } else {
      No* sucessor = encontrarMinimoBST(raiz->direita);
      free(raiz->valor);
      // raiz->valor = strdup(sucessor->valor);
      strcpy(raiz->valor, sucessor->valor);
      raiz->direita = removerBST(raiz->direita, sucessor->valor);
    }
  }

  return raiz;
}

/**
 * @brief Função auxiliar para encontrar o nó mínimo em uma subárvore
 * @param raiz Ponteiro para a raiz da subárvore
 * @return Ponteiro para o nó com o valor mínimo
 */
No* encontrarMinimoBST(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

/**
 * @brief Função para exibir os valores da árvore em ordem (emOrdem)
 * @param arvorePistas Ponteiro para a raiz da árvore
 */
void exibirPistas(No* arvorePistas) {
  if (arvorePistas != NULL) {
    exibirPistas(arvorePistas->esquerda);
    printf("'%s' ", arvorePistas->valor);
    exibirPistas(arvorePistas->direita);
  }
}

/**
 * @brief Funções para percorrer a árvore em ordem
 * @note Na seguinte ordem: esquerda, raiz, direita
 * @param raiz Ponteiro para a raiz da árvore
 */
void exibirEmOrdem(No* raiz) {
  if (raiz != NULL) {
    exibirEmOrdem(raiz->esquerda);
    printf("'%s' ", raiz->valor);
    exibirEmOrdem(raiz->direita);
  }
}