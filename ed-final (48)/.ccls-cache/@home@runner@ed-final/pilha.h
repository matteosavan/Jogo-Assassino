#ifndef PILHA_H
#define PILHA_H
#include "lista_de_jogadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int topo;
  int tamanho;
  int *elementos;
} Pilha;

void inicializar_pilha(Pilha *p, int tamanho_maximo); //inicializa a pilha
int tamanho_pilha(Pilha *p); //verifica o tamanho da pilha
int pilha_vazia(Pilha *p); //verifica se a pilha está vazia
int pilha_cheia(Pilha *p); //verifica se a pilha está cheia
void empilhar(Pilha *p, int elemento); //adiciona um elemento à pilha
int desempilhar(Pilha *p); //remove um elemento da pilha
void destroi_pilha(Pilha *p); //destrói a pilha

#endif
