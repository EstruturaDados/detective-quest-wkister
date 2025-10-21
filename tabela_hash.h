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

// Forward declarations (definições completas em arvore.h)
struct valor;
struct listaNo;

// Estrutura para uma entrada na tabela hash (pista -> suspeito)
typedef struct EntradaTabelaHash {
  char chave[TAM_STRING]; // Chave: descrição da pista
  char valor[TAM_STRING]; // Valor: nome do suspeito
  int ocupado;            // 0 = vazio, 1 = ocupado, -1 = removido
} EntradaTabelaHash;

int funcao_hash(const char* chave);                                    // Função hash
void inserirTabelaHash(const char* chave, const char* valor, EntradaTabelaHash* tabela_hash); // Insere pista -> suspeito
struct valor* pegarValoresTabelaHash(const char* chave, const EntradaTabelaHash* tabela_hash); // Obtém valores associados a uma chave
void inicializarTabelaPistasSuspeitos(EntradaTabelaHash* tabela_hash);                 // Inicializa tabela com pistas
void inicializarTabelaSalasPistas(EntradaTabelaHash* tabela_hash);            // Inicializa tabela com salas e pistas


#endif