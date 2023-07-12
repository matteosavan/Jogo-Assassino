#include "vencedor.h"

int alguem_ganhou(Lista *lista_vivos) {
  // vai imprimir a mensagem do vencedor e encerrar o jogo. Retorna 1 se o jogo encerrou
  if (lista_vivos->depressivo_foi_o_mais_votado == 1) {
    printf("O depressivo venceu!\n");
    return 1;
  } else if (lista_vivos->quantidade_de_jogadores == 1 && lista_vivos->sentinela->proximo_jogador->papel == 0) {//caso só tem o matador
    printf("O assassino venceu!\n");
    return 1;
  }else if (vazia(lista_vivos)) { // se todos os jogadores morreram então houve empate
    printf("Empate!\n");
    return 1;
  }
  else if (lista_vivos->assassino_morreu == 1) { //caso vila venceu
    printf("A vila venceu!\n");
    return 1;
  }
  return 0;
}