/**
 * @file tabela_hash.h
 * @brief Definições e protótipos para manipulação de tabela hash de pistas
 * @author Wellington Kister do Nascimento
 */

#ifndef  TABELA_HASH_H
#define  TABELA_HASH_H

#include "geral.h"   // Para usar TAM_STRING
#include "arvore.h"  // Para usar MAX_PISTAS

// --- Constantes ---
#define TAMANHO_TABELA 20  // Aumentado para acomodar mais pistas
#define MAX_SUSPEITOS 4
// MAX_PISTAS agora vem de arvore.h (valor: 10)

// Declaração da lista de suspeitos
extern char suspeitos[MAX_SUSPEITOS][50];

// Estrutura para uma entrada na tabela hash (pista -> suspeito)
typedef struct EntradaTabelaHash {
  char chave[MAX_PISTAS];      // Chave: descrição da pista
  char valor[50];    // Valor: nome do suspeito
  int ocupado;          // 0 = vazio, 1 = ocupado, -1 = removido
} EntradaTabelaHash;

// Declaração da tabela hash
extern EntradaTabelaHash tabelaSuspeitos[TAMANHO_TABELA];

int funcao_hash(const char* chave);                                    // Função hash
void inserirTabelaHash(const char* chave, const char* valor, EntradaTabelaHash* tabela_hash); // Insere pista -> suspeito
int buscarPista(const char* pista, const EntradaTabelaHash* tabela_hash);     // Busca pista e retorna posição
char* obterSuspeito(const char* pista, const EntradaTabelaHash* tabela_hash); // Obtém suspeito pela pista
void inicializarTabelaPistasSuspeitos(EntradaTabelaHash* tabela_hash);                 // Inicializa tabela com pistas
void inicializarTabelaSalasPistas(EntradaTabelaHash* tabela_hash);            // Inicializa tabela com salas e pistas
void exibirEstatisticas(const EntradaTabelaHash* tabela_hash);                // Exibe estatísticas de pistas


#endif