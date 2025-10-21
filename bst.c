/**
 * @file bst.c
 * @brief Implementação de uma árvore binária de busca (BST)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * @brief Função para exibir os valores da árvore em ordem (in-order traversal)
 * @note Percorre na seguinte ordem: esquerda, raiz, direita
 * @param raiz Ponteiro para a raiz da árvore
 */
void exibirEmOrdem(No* raiz) {
  if (raiz != NULL) {
    exibirEmOrdem(raiz->esquerda);
    printf("'%s' ", raiz->valor);
    exibirEmOrdem(raiz->direita);
  }
}