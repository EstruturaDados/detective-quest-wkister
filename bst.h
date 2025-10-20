/**
 * @file bst.h
 * @brief Protótipos das funções para manipulação de árvores binárias de busca
 * @author Wellington Kister do Nascimento
 */

#ifndef BST_H
#define BST_H

// Definição da estrutura de um nó na árvore binária
typedef struct No {
  char valor[50];
  struct No *esquerda;
  struct No *direita;
} No;

No* criarNo(const char* valor); // Cria um novo nó na árvore
void inserirBST(No** raiz, const char* valor); // Insere um novo valor na árvore binária de busca
int buscarBST(No* raiz, const char* chave); // Busca um valor na árvore binária de busca
No* removerBST(No* raiz, const char* valor); // Remove um valor da árvore binária de busca
No* encontrarMinimoBST(No* raiz); // Encontra o nó com o valor mínimo na árvore
void exibirPistas(No* arvorePistas); // Exibe as pistas em ordem alfabética
void exibirEmOrdem(No* raiz); // Exibe os valores da árvore em ordem (emOrdem)

#endif