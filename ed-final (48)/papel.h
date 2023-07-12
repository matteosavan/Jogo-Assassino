#ifndef PAPEL
#define PAPEL
#include "lista_de_jogadores.h"
#include "votacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void implementacao(Iterador iterador, Lista *lista_vivos, Lista *lista_mortos); // implementação dos papéis: o que cada um faz
int num_aleatorio(int min, int max); // sorteia um papel para cada jogador
void sortear_assassino(int min, int max, Lista *lista_vivos); // sorteia um jogador para ser o assassino
void dar_prioridade(Lista *lista_vivos); // função a mais adicionada para poder testar a prioridade
void mensagem_de_quem_eh_a_vez(Iterador iterador, Lista *lista_vivos); // verifica de qual jogador é a vez

#endif