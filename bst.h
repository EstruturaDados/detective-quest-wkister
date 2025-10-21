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
void exibirEmOrdem(No* raiz); // Exibe os valores da árvore em ordem (in-order)

#endif