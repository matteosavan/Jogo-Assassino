#include "pilha.h"
#include "lista_de_jogadores.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializar_pilha(Pilha *p, int tamanho_maximo) {
  p->topo = -1;
  p->tamanho = tamanho_maximo;
  p->elementos = (int *)malloc(tamanho_maximo * sizeof(int));
}

int tamanho_pilha(Pilha *p) { return p->topo + 1; }

int pilha_vazia(Pilha *p) { return p->topo == -1; }

int pilha_cheia(Pilha *p) { return p->topo == p->tamanho - 1; }

void empilhar(Pilha *p, int elemento) {
  if (pilha_cheia(p)) {
    exit(1); // Pilha cheia
  }
  p->topo++;
  p->elementos[p->topo] = elemento;
}

int desempilhar(Pilha *p) {
  if (pilha_vazia(p)) {
    exit(1); // Pilha vazia
  }
  int elemento = p->elementos[p->topo];
  p->topo--;
  return elemento;
}
void destroi_pilha(Pilha *p) {
  if (p == NULL)
    return;

  // Libera a memória alocada pela pilha
  free(p);
}
