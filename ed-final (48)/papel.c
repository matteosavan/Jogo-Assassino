#include "lista_de_jogadores.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "votacao.h"


int num_aleatorio(int min, int max) { //gera numero aleatório entre min e max
  static int init = 1;
  static int adicional = 1; // contador estático usado para deixar a semente do rand() ainda mais aleatoria
  srand(time(NULL) + adicional);
  adicional++;
  return (rand() % (max - min + 1)) + min;
}

void sortear_assassino(int min, int max, Lista *lista_vivos) { // sorteia um jogador para receber o papel do assassino
  int jogador_assassino;
  Iterador iterador;

  static int init = 0;
  if (!init) {
    srand(time(NULL));
    init = 0;
  }
  jogador_assassino = (rand() % (max - min + 1)) + min; // sorteia um jogador para receber o papel do assassino

  iterador = buscar_elemento_na_lista(lista_vivos, jogador_assassino);

  iterador.endereco_jogador->papel = 0;
}

void implementacao(Iterador iterador, Lista *lista_vivos, Lista *lista_mortos) {
  int resp;

  char resposta;
  Iterador buscar;
  fflush(stdin);
  switch (iterador.endereco_jogador->papel) {

  case 0: // caso assassino
    if (iterador.lista->contador_noite == 1) {
      printf("Serial Killer\n");
      printf("Seu objetivo é matar todos da vila, não seja descoberto.\n");
      printf("Nada para fazer na primeira noite, volte a dormir\n");
      mensagem_de_apertar_c();
    } else {

      printf("Selecione um jogador para matar essa noite:\n");
      printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(
          lista_vivos, iterador.endereco_jogador->numero_do_jogador);

      scanf("%d",&iterador.endereco_jogador ->quem_vai_atacar); //verificando quem o assassino quer matar e colocando o endereço do jogador no campo quem_vai_atacar
    }
    break;

  case 1: // dama da noite
    if (iterador.lista->contador_noite == 1) {
      printf("Dama da noite\n");
      printf("Toda noite você visitará alguém, cuidado para não visitar o "
             "assassino.\n");
    }
    printf("Escolha uma casa para visitar essa noite\n");
    printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(
        lista_vivos, iterador.endereco_jogador->numero_do_jogador);
    scanf("%d", &iterador.endereco_jogador->quem_visitou_dama);
    buscar = buscar_elemento_na_lista(
        lista_vivos, iterador.endereco_jogador->quem_visitou_dama);
    buscar.endereco_jogador->tem_visita = 1; //o jogador visitado recebe "1" no campo tem_visita
    
    break;

  case 2: // opressora
    if (iterador.lista->contador_noite == 1) {
      printf("Opressora\n");
      printf("Você tem o direito de silenciar alguém toda noite, essa pessoa "
             "não poderá votar.\n");
    }
    printf("Escolha um jogador para oprimir essa noite\n");
    printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(
        lista_vivos, iterador.endereco_jogador->numero_do_jogador);
    scanf("%d", &iterador.endereco_jogador->quem_opressora_vai_silenciar);
    buscar = buscar_elemento_na_lista(lista_vivos, iterador.endereco_jogador->quem_opressora_vai_silenciar);
    buscar.endereco_jogador->vai_votar_pela_manha = 0; //achar o jogador silenciado e adicionar "0" no campo vai_votar_pela_manha
    break;

  case 3: // medico
    if (iterador.lista->contador_noite == 1) {
      printf("Médico\n");
      printf("Você consegue salvar uma pessoa por noite, escolha "
             "cautelosamente quem proteger.\n");
    }
    printf("Escolha um jogador para proteger essa noite\n");
    printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(lista_vivos, iterador.endereco_jogador->numero_do_jogador);
    scanf("%d", &iterador.endereco_jogador->quem_vai_proteger); //colocar o endereço do jogador protegido no campo quem_vai_proteger
    break;

  case 4: // aldeao
    if (iterador.lista->contador_noite == 1) {
      printf("Aldeão\n");
      printf("Você não pode fazer nada além de dormir durante a noite. Boa "
             "sorte para não ser morto em seus sonhos.\n");
    }
    printf("Nada para fazer!\nPara sua segurança fique em casa e durma zzz!\n");
    mensagem_de_apertar_c();
    break;

  case 5: // necromante
    if (iterador.lista->contador_noite == 1) {
      printf("Necromante\n");
      printf("Você pode reviver uma pessoa morta, mas pense bem! Só poderá "
             "fazer isso uma vez.\n");
    }

    if (iterador.endereco_jogador->quantidade_necromante == 0) { // se a necromante ainda não reviveu ninguém nenhuma vez

      if (vazia(lista_mortos)) { //se a lista de mortos estiver vazia
        printf("Felizmente ninguem foi assassinado, volte a dormir.\n");
        mensagem_de_apertar_c();
      } 
      else { //se a lista de mortos não estiver vazia
        printf("Escolha um jogador morto para reviver ou pule.\n");
        printar_todos_os_jogadores_vivos_ou_mortos(lista_mortos);
        printf("Deseja reviver um jogador essa noite? Insira 1 se gostaria de "
               "reviver e 0 caso contrario.\n");
        scanf("%d", &resp);

        if (resp == 1) {
          iterador.endereco_jogador->necromante_vai_reviver = 1;
          iterador.endereco_jogador->quantidade_necromante++;
          printf("Escolha um jogador para reviver:\n");
          scanf("%d", &iterador.endereco_jogador->quem_vai_reviver_necromante);
        } else {
          iterador.endereco_jogador->necromante_vai_reviver = 0;
          printf("Até a proxima noite...ou nao.\n");
          mensagem_de_apertar_c();
        }
      }
    } else { //se a necromante já reviveu alguém alguma vez
      printf("Nada para fazer por agora. Até a proxima noite...ou nao.\n");
      mensagem_de_apertar_c();
    }
    break;

  case 6: // matador
    if (iterador.lista->contador_noite == 1) {
      printf("Matador de Aluguel\n");
      printf("Você terá duas chances de atirar em alguém que acredita ser o assassino, mas cuidado! Você não quer matar um inocente, quer?\n");
    }
    if (iterador.endereco_jogador->tiros_matador > 0) {
      printf("Você tem %d bala(s) restantes, escolha um jogador para matar ou "
             "pule. Temos:\n",
             iterador.endereco_jogador->tiros_matador);
      printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(lista_vivos, iterador.endereco_jogador->numero_do_jogador);

      printf(
          "Deseja matar um jogador essa noite? (1 para sim ou 0 para não.)\n");
      scanf("%d", &resp); 

      iterador.endereco_jogador->atirador_vai_atirar = resp;
      
      if (resp == 1) {  //se o matador optar por matar alguém
        printf("Escolha um jogador para assassinar: ");
        scanf("%d", &iterador.endereco_jogador->quem_vai_atacar);
        iterador.endereco_jogador->tiros_matador--;
      } else if (resp == 0) { //se o matador pular a vez:
        printf("Até a proxima noite...ou nao.\n");
        mensagem_de_apertar_c();
      } else {
        printf("Opção inválida.\n");
      }
    } else { //quando as balas do matador acabam e ele não pode mais atirar
      printf("Voce não tem mais balas. ");
      printf("Nada para fazer, volte a dormir.\n");
      mensagem_de_apertar_c();
        }
    break;

  case 7: // depressivo
    if (iterador.lista->contador_noite == 1) {
      printf("Depressivo\n");
      printf("Você não está do lado do lobo mas também não está do lado da "
             "vila. Seu objetivo é ser morto pela votação.\n");
    }
    printf("Nada para fazer, volte a dormir ou ligue para um psicólogo.\n");
    mensagem_de_apertar_c();
    break;
  }
}

void dar_prioridade(Lista *lista) {
  Iterador iterador;

  iterador = iterador_primeiro(lista);

  while (iterador.endereco_jogador != lista->sentinela) {

    if (iterador.endereco_jogador->papel == 3) { // medico
      iterador.endereco_jogador->prioridade = 4;
    } else if ((iterador.endereco_jogador->papel == 1) || (iterador.endereco_jogador->papel == 5)) { // dama ou necromante
       iterador.endereco_jogador->prioridade = 3;
    } else if ((iterador.endereco_jogador->papel == 6) ||
               (iterador.endereco_jogador->papel ==
                0)) { // matador ou assassino
      iterador.endereco_jogador->prioridade = 2;
    }

    else { // depressivo, aldeao e opressora
      iterador.endereco_jogador->prioridade = 0;
    }
    iterador = proximo(iterador);
  }
}

//verificar de qual jogador é a vez:

void mensagem_de_quem_eh_a_vez(Iterador iterador, Lista *lista_vivos) {
  system("clear");
  char descartar = 'a';
  printf("Agora é a vez de %s, passe o computador para ele(a).\nInsira 'c' para "
         "continuar\n",
         iterador.endereco_jogador->nome_do_jogador);
  do {
    scanf("%c", &descartar);
  } while (descartar != 'c');
  fflush(stdin);
}