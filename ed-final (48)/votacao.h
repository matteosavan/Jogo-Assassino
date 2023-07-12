#ifndef VOTACAO
#define VOTACAO
#include "lista_de_jogadores.h"
#include <locale.h>

void mensagem_de_amanhecer(Lista *lista_vivos); // mensagem mostrada em todo amanhecer
void a_votacao(Lista *lista_vivos, Lista *lista_mortos); // contém a implementação da votação
Iterador quem_teve_mais_votos(Lista *lista_vivos); // retorna um iterador de quem foi o jogador mais votado
 void zerar_votos(Lista *lista_vivos); // importante para os votos não acumularem entre dias seguidos
void aumentar_votos_recebidos(Lista *lista_vivos,  int numero_do_jogador); // aumenta a quantidade de votos que um jogador recebeu
int teve_empate(Iterador mais_votado, Lista *lista_vivos); // confere se houve empate na votação. Se sim, retorna 1. Caso contrário retorna 0
void mensagem_de_apertar_c(); // um utilitário para solicitarmos que o jogador aperte 'c' para prosseguir
void mensagem_de_anoitecer(Lista *lista_vivos); // mensagem que será mostrada na tela a cada anoitecer
void a_historia(); //contém informações sobre o jogo
#endif
