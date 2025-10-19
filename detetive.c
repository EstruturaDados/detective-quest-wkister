/**
 * @file algoritmos_avancados.c
 * @brief Desafio Detective Quest
 * @note Tema 4 - Árvores e Tabela Hash
 * @author Wellington Kister do Nascimento
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h" // Protótipos das funções e definições gerais
#include "arvore.h" // Protótipos das funções e definições de árvores
#include "bst.h" // Protótipos das funções e definições de árvores binárias de busca

int main() {
    // Definição e inicialização da raiz da árvore de salas
    Sala* raiz = inicializarArvoreSalas();

    // Definição da variável para a árvore de pistas (BST)
    struct No* arvorePistas = NULL;

    // Exploração das salas pelo jogador
    // explorarSala(raiz, arvorePistas);
    explorarSala(raiz);

    // Liberar a memória alocada para a árvore de salas
    liberarMemoria(raiz);

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

