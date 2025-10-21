#include <stdio.h>
#include "geral.h"

/**
 * @brief Função para limpar o buffer de entrada
 */
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
