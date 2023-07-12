#include "jogada.h"
#include "lista_de_jogadores.h"
#include "papel.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

/* 
Função para descobrir a dama que visitou o jogador e matá-la também:
Caso o jogador que o assassino irá matar tenha sido visitado por uma dama da noite,
a dama deverá morrer também
Implementação:
*/
void achar_visita_e_matar(int n, Lista *lista_vivos, Lista *lista_mortos) {
  Iterador buscar;
  Iterador auxiliar;
  buscar = iterador_primeiro(lista_vivos);
  while (buscar.endereco_jogador != lista_vivos->sentinela) {
    if (buscar.endereco_jogador->papel == 1) {
      if (buscar.endereco_jogador->quem_visitou_dama == n) {
        auxiliar = buscar;
        buscar = proximo(buscar);
        trocar_jogadores_de_lista(lista_mortos, lista_vivos,auxiliar.endereco_jogador->numero_do_jogador);
        
        
      } else {
        buscar = proximo(buscar);
      }
    } else {
      buscar = proximo(buscar);
    }
  }
}

/*
Função procurar_assassinos:
O assassino e o matador possuem a mesma prioridade.
Portanto, se um acabar matando o outro, teremos um problema na execução de seu papel,
pois este terá ido para a lista dos mortos antes da rodada acabar.
Sendo assim, foi necessário criar uma função para veificar se isso aconteceu,
mas é um caso especial.
*/

void procurar_assassinos(Lista *lista_vivos,Lista *lista_mortos) {
  Iterador iterador;
  Iterador iterador_aux;
  iterador = iterador_primeiro(lista_vivos);

  while (iterador.endereco_jogador != lista_vivos->sentinela) {
    if (iterador.endereco_jogador->morreu_de_noite == 1) {
      iterador_aux = iterador;
      iterador = proximo(iterador);
      trocar_jogadores_de_lista(lista_mortos, lista_vivos,iterador_aux.endereco_jogador->numero_do_jogador);
      
      
    } 
    else {
      iterador = proximo(iterador);
    }
  }
}

//Análise da noite: analisamos os papéis dos jogadores por sua prioridade para que sejam executados na ordem certa

void analise_da_noite(Lista *lista_vivos, Lista *lista_mortos) {

  Iterador iterador, buscar, aux;
  int quem_foi_protegido;

    iterador = iterador_primeiro(lista_vivos);

  for (int i = 0; iterador.lista->sentinela != iterador.endereco_jogador && !vazia(lista_vivos);i++) {
    if (iterador.endereco_jogador->prioridade == 4) { //o único papel de prioridade 4 é o médico
      //busca o endereço do jogador que foi protegido pelo médico:
      quem_foi_protegido = iterador.endereco_jogador->quem_vai_proteger;
      buscar = buscar_elemento_na_lista(lista_vivos, quem_foi_protegido);
      buscar.endereco_jogador->esta_protegido = 1;
    }
    iterador = proximo(iterador);
  }
  
    iterador = iterador_primeiro(lista_vivos);

  for (int i = 0; (lista_vivos->sentinela != iterador.endereco_jogador) && (!vazia(lista_vivos));
       i++) {
    if (iterador.endereco_jogador->prioridade == 3) { //os papéis de prioridade 3 são a dama e a necromante
      switch (iterador.endereco_jogador->papel) {
      case 1: // dama

        buscar = buscar_elemento_na_lista(
            lista_vivos, iterador.endereco_jogador->quem_visitou_dama); // buscar agora mira em quem a dama visitou
                 if (buscar.endereco_jogador->papel == 0 && iterador.endereco_jogador->acabou_de_reviver!=1) { // se visitou lobo, morre

          aux = iterador;
          iterador = proximo(iterador);
          trocar_jogadores_de_lista(lista_mortos, lista_vivos, aux.endereco_jogador->numero_do_jogador);
                   
                   
        } else {
          iterador = proximo(iterador); 
        }
        break;

      case 5: // necromante
        if (iterador.endereco_jogador->necromante_vai_reviver == 1 && iterador.endereco_jogador->quantidade_necromante==1) {
          buscar = buscar_elemento_na_lista(          lista_mortos, iterador.endereco_jogador->quem_vai_reviver_necromante);
          if (buscar.endereco_jogador != lista_mortos->sentinela) { // se o jogador ja nao foi revivido
            buscar.endereco_jogador->acabou_de_reviver=1; //para que seu papel nao seja executado com as informações dos campos de antes de morrer (pois agora o jogador revivido será tratado como vivo)
            trocar_jogadores_de_lista(lista_vivos, lista_mortos,buscar.endereco_jogador->numero_do_jogador);
          }

        }
        iterador = proximo(iterador);
        break;
      }
    } 
    else {
      iterador = proximo(iterador);
    }
  }

  //entendi.. aparentemente, ela está sendo revivida e morrendo logo em seguida pois como agora ela está na lista dos vivos ela tbm tem seu papel executado

  iterador = iterador_primeiro(lista_vivos);

  for (int i = 0; (lista_vivos->sentinela != iterador.endereco_jogador) && (!vazia(lista_vivos));
       i++) {

    if (iterador.endereco_jogador->prioridade == 2) { //os papéis de prioridade 2 são o assassino e o matador

      switch (iterador.endereco_jogador->papel) {

      case 0: // assassino
        if (lista_vivos->contador_noite != 1) { // nao é a primeira noite
          buscar = buscar_elemento_na_lista(
              lista_vivos, iterador.endereco_jogador->quem_vai_atacar);
          if (buscar.endereco_jogador == lista_vivos->sentinela)
            break; // caso o jogador ja tenha morrido

          if (buscar.endereco_jogador->tem_visita == 1) { // mata a visita do jogador
            achar_visita_e_matar(buscar.endereco_jogador->numero_do_jogador,lista_vivos, lista_mortos); //aqui tem que conferir tbm
          }
          if ((buscar.endereco_jogador->esta_protegido == 0) && (buscar.endereco_jogador->papel != 1) &&(buscar.endereco_jogador->papel != 6)) {
            trocar_jogadores_de_lista(lista_mortos, lista_vivos,buscar.endereco_jogador->numero_do_jogador); // matar o jogador em si
            
            
          }
          if (buscar.endereco_jogador->papel == 6 && buscar.endereco_jogador->esta_protegido == 0) {
            buscar.endereco_jogador->morreu_de_noite = 1;
          }
        }
        break;

      case 6: // matador
          if (iterador.endereco_jogador->atirador_vai_atirar && iterador.endereco_jogador->acabou_de_reviver!=1) {
          buscar = buscar_elemento_na_lista(
              lista_vivos, iterador.endereco_jogador->quem_vai_atacar);
          if (buscar.endereco_jogador == lista_vivos->sentinela)
            break; // caso o jogador ja tenha morrido
          if (buscar.endereco_jogador->papel == 0) { // se for o lobo
            buscar.endereco_jogador->morreu_de_noite = 1;
            lista_vivos->assassino_morreu = 1;
          } else {
            trocar_jogadores_de_lista(lista_mortos, lista_vivos,buscar.endereco_jogador->numero_do_jogador);
            
            
          }
        }
        break;
      }
    }
    iterador = proximo(iterador);
  }

  //Não houve necessidade de analisar as outras prioridades aqui.
  procurar_assassinos(lista_vivos, lista_mortos);
}
