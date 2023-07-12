#ifndef JOGADA
#define JOGADA
#include "lista_de_jogadores.h"
#include "papel.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

void analise_da_noite(Lista *lista_vivos, Lista *lista_mortos); //analisa tudo o que aconteceu na rodada, quem morreu e quem sobreviveu
void procurar_dama_e_matar(Lista *lista_vivos, Lista *lista_mortos,int numero_de_quem_foi_atacado); //se o jogador que o lobisomem matou foi visitado por uma dama da noite, ela morre também
void procurar_assassinos(Lista *lista_vivos,Lista *lista_mortos); //verifica se o assassino matou o matador ou vice-versa, para que nenhum dos dois seja adicionado à lista dos mortos antes da rodada acabar, pois possuem a mesma prioridade

#endif