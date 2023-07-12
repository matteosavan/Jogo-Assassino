#include "jogada.h"
#include "lista_de_jogadores.h"
#include "papel.h"
#include "pilha.h"
#include "vencedor.h"
#include "votacao.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  FEITO POR:
  MARIA FERNANDA, RA: 813371
  MATTEO SAVAN, RA: 793248
  RAYANA, RA: 814029
*/

int main(void) {
  Lista lista_vivos, lista_mortos;
  int opcao;
  Iterador iterador;
  int iniciar_jogo = 0, jogador_excluido;
  char aux_string[20];

  inicializar_lista_jogadores(&lista_vivos);
  inicializar_lista_jogadores(&lista_mortos);

  Pilha *pilha;
  pilha = (Pilha *)malloc(sizeof(Pilha));


  while (!iniciar_jogo) { // quando iniciar_jogo == 1, iniciamos o jogo
    // menu do jogo:
    system("clear");
    printf("escolha uma opção:\n[1] iniciar jogo\n[2] lista de jogadores "
           "registrados\n[3] como jogar\n");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1: // iniciar jogo
      if (vazia(&lista_vivos)){
        system("clear");
        printf("voce precisa adicionar jogadores antes de iniciar um novo jogo!\n");
        break;
      }
      iniciar_jogo = 1;
      break;

    case 2: // mostrar jogadores
      system("clear");

      if (vazia(&lista_vivos))
        printf("a lista de jogadores está vazia\n");
      else {
        printf("temos os seguintes jogadores registrados:\n");
        iterador = iterador_primeiro(&lista_vivos);
        printar_todos_os_jogadores_vivos_ou_mortos(&lista_vivos);
      }
      break;
    case 3: //apresenta ao jogador as regras
      a_historia();
    }
    if (!iniciar_jogo && opcao != 3) { // se não foi escolhido para iniciar jogo e sim para analisar os jogadores
      printf("escolha uma opção:\n[1] remover jogador\n[2] adicionar "
             "jogador\n[3] voltar ao menu inicial\n");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1: // remover jogador
        if (vazia(&lista_vivos)) {
          printf("a lista está vazia! Escolha uma opção:\n[3] voltar ao menu "
                 "inicial\n");
          scanf("%d", &jogador_excluido);
          break;
        }
        printf("qual jogador deseja remover?\n");
        printar_todos_os_jogadores_vivos_ou_mortos(&lista_vivos);
        scanf("%d", &jogador_excluido);
        excluir_jogador(&lista_vivos, jogador_excluido);
        dar_numeros_jogadores(&lista_vivos);
        break;
      case 2:
        adicionar_jogador(&lista_vivos);
        iterador = iterador_primeiro(&lista_vivos);
        dar_numeros_jogadores(&lista_vivos);
        break;
      case 3:
        break;
      }
    }
  }

  // distribuição dos papeis:
  inicializar_pilha(pilha, lista_vivos.quantidade_de_jogadores);
  while (!pilha_cheia(pilha)) { // para empilhar os papeis
    empilhar(pilha, num_aleatorio(1, 6));
  }
  iterador = iterador_primeiro(&lista_vivos);
  while (!pilha_vazia(pilha)) { // para desempilhar e distribuir os papeis
    iterador.endereco_jogador->papel = desempilhar(pilha);
    iterador = proximo(iterador);
  }
  
  sortear_assassino(0, lista_vivos.quantidade_de_jogadores - 1, &lista_vivos);


  iterador = iterador_primeiro(&lista_vivos);
  while (iterador.endereco_jogador !=
         lista_vivos.sentinela) { // para printar as funções
    printf("o jogador %s recebeu o papel %d\n",
           iterador.endereco_jogador->nome_do_jogador,
           iterador.endereco_jogador->papel);
    iterador = proximo(iterador);
  }


  destroi_pilha(pilha);

  dar_prioridade(&lista_vivos);

  iterador = iterador_primeiro(&lista_vivos);

  system("clear");

  // acaba aqui a parte do menu. Abaixo temos o jogo em si

  // código do que ocorre durante a noite e durante a votação:
  
  while (1) {
    iterador = iterador_primeiro(&lista_vivos);
    mensagem_de_anoitecer(&lista_vivos);
    while (iterador.endereco_jogador != lista_vivos.sentinela) {
      mensagem_de_quem_eh_a_vez(iterador, &lista_vivos);
      fflush(stdin);
      implementacao(iterador, &lista_vivos, &lista_mortos);
      iterador = proximo(iterador);
    }
    system("clear");
    iterador = iterador_primeiro(&lista_vivos);
    analise_da_noite(&lista_vivos, &lista_mortos); 
    if (alguem_ganhou(&lista_vivos)) {
      break;
    }
    mensagem_de_amanhecer(&lista_vivos);
    a_votacao(&lista_vivos, &lista_mortos);
    if (alguem_ganhou(&lista_vivos)) {
      break;
    }
    fflush(stdin);
  }

  limpar_lista_jogadores(&lista_vivos);
  limpar_lista_jogadores(&lista_mortos);

  return 0;
}