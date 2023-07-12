#include "votacao.h"
#include <locale.h>

void a_historia(){ //contém informações sobre o jogo
  system("clear");
  printf("História do Jogo:\n");
  printf("Uma vila pequena e normalmente tranquila está sofrendo com um terrível ataque de um serial killer. Todos os moradores devem se juntar para descobrir quem é este assassino e não deixar que ele acabe com a vila.\n");
  printf("A cada noite, o assassino tentará matar alguém. Use seu papel para ajudar a vila e descobrir quem ele é, ou mate todos caso você seja o assassino...\n\n\n");
  printf("Os papéis:\n");
  printf("Assassino: a pessoa com este papel deverá escolher alguém para matar todas as noites. Na primeira noite, o assassino não mata.\n\n");
  printf("Dama da Noite: a pessoa com este papel visitará alguém todas as noites. Se o assassino tentar matá-la, ela não morrerá pois não vai estar em casa. Se o assassino tentar matar a pessoa que ela visitou, ela morrerá junto. Se ela visitar o assassino, ela também morrerá.\n\n");
  printf("Opressora: a pessoa com este papel terá o direito de silenciar alguém todas as noites. Quem ela silenciar, perderá o direito de votar pela manhã.\n\n");
  printf("Médico: a pessoa com esse papel poderá proteger alguém todas as noites. Quem ela proteger, não morrerá para o assassino.\n\n");
  printf("Aldeão: a pessoa com este papel é um simples aldeão e não conseguirá fazer nada durante a noite além de dormir.\n\n");
  printf("Necromante: a pessoa com este papel poderá reviver um jogador que já morreu. Porém, ela só pode fazer isso uma vez.\n\n");
  printf("Matador de Aluguel: a pessoa com este papel possui uma arma com duas balas, e poderá usar essas balas para atirar em quem acredita ser o assassino.\n\n");
  printf("Depressivo: a pessoa com esse papel tem um único objetivo de morrer durante o jogo. Porém, ela deverá morrer através da votação, e não pelo assassino ou matador de aluguel.\n\n");
  mensagem_de_apertar_c();
  system("clear");
}


void mensagem_de_anoitecer(Lista *lista_vivos){ // mensagem que será mostrada na tela a cada anoitecer
  lista_vivos->contador_noite++;
  system("clear");
  if(lista_vivos->contador_noite == 1){
    printf("Problemas na vila! Há um assassino à solta perseguindo os aldeões durante a noite, tratem de expulsá-lo!!!\n");
  }
  printf("Noite número %d\nA vila vai dormir e os jogadores ficam em silêncio.\n", lista_vivos->contador_noite);
  mensagem_de_apertar_c();
}

void mensagem_de_apertar_c(){ // um utilitário para solicitarmos que o jogador aperte 'c' para prosseguir
  char descartar = 'a';
  printf("Insira 'c' para continuar.\n");
  do{
    scanf("%c", &descartar);}while(descartar!='c');
  fflush(stdin);
}

void mensagem_de_amanhecer(Lista *lista_vivos){ // mensagem mostrada em todo amanhecer
  char continuar;
  system("clear");
  printf ("Amanheceu e a vila deverá expulsar o assassino. Todos os jogadores acordaram e podem debater entre si, preparem-se para votar em quem vocês desconfiam...\nAgora, o jogadores que restam são:\n");
  printar_todos_os_jogadores_vivos_ou_mortos(lista_vivos);
  printf("pressione ""c"" para continuar.\n");
  scanf(" %c", &continuar);
  system("clear");
}
void a_votacao(Lista *lista_vivos, Lista *lista_mortos){ //codigo de votação
  Iterador iterador;
  int voto;
  
  iterador = iterador_primeiro(lista_vivos);
  
  while(iterador.endereco_jogador!=lista_vivos->sentinela){ //para pedir o voto de cada pessoa
  printf("Quem irá votar agora é %s.\n", iterador.endereco_jogador->nome_do_jogador);

  if (iterador.endereco_jogador->vai_votar_pela_manha==0){
    printf("Você foi silenciado pela opressora e não votará hoje.\n");
    mensagem_de_apertar_c();
    }
  else{
    printf("Selecione alguém:\n");
    printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(lista_vivos, iterador.endereco_jogador->numero_do_jogador); //nao mostrar o jogador em si
    scanf("%d", &voto);
    aumentar_votos_recebidos(lista_vivos, voto);
    }
  iterador = proximo(iterador);
  system("clear");
  } 
  
  iterador = quem_teve_mais_votos(lista_vivos); 

  if (teve_empate(iterador, lista_vivos)){ //caso de empate
    printf("Empate! A vila não decidiu quem condenar.\n");
  }
  else{
  if (iterador.endereco_jogador->papel==7)lista_vivos->depressivo_foi_o_mais_votado=1; //caso depressivo morto
  if (iterador.endereco_jogador->papel==0)lista_vivos->assassino_morreu=1; //caso assassino morto
  printf("%s foi condenado(a) pela vila.\n", iterador.endereco_jogador->nome_do_jogador);

  trocar_jogadores_de_lista(lista_mortos, lista_vivos, iterador.endereco_jogador->numero_do_jogador);
  }
  zerar_votos(lista_vivos);
  resetar(lista_vivos);
  zerar_votos(lista_mortos);
  resetar(lista_mortos);
  mensagem_de_apertar_c();
}

Iterador quem_teve_mais_votos(Lista *lista_vivos){ //retorna um iterador de quem foi o jogador mais votado
  Iterador iterador, iterador_quem_teve_mais_votos;
  iterador = iterador_quem_teve_mais_votos = iterador_primeiro(lista_vivos);
  while (iterador.endereco_jogador != lista_vivos->sentinela){
  if (iterador.endereco_jogador->contador_de_votos > iterador_quem_teve_mais_votos.endereco_jogador->contador_de_votos){
    iterador_quem_teve_mais_votos = iterador;
    }
  iterador = proximo(iterador);
  }

  return iterador_quem_teve_mais_votos;  
}

int teve_empate(Iterador mais_votado, Lista *lista_vivos){ //confere se houve empate na votação
  int houve_empate=0;
  Iterador iterador = proximo(mais_votado); //para decorrer procurando mais alguem que teve a mesma quantidade de votos do mais votado
  while (iterador.endereco_jogador != lista_vivos->sentinela){
  if (mais_votado.endereco_jogador->contador_de_votos == iterador.endereco_jogador->contador_de_votos){
     houve_empate=1;
  }
  iterador = proximo(iterador);
  }

  return houve_empate;
}


void zerar_votos(Lista *lista_vivos){ // importante para os votos não acumularem entre dias seguidos
  Iterador iterador = iterador_primeiro(lista_vivos); 
  while (iterador.endereco_jogador != lista_vivos->sentinela){
    iterador.endereco_jogador->contador_de_votos=0;
    iterador = proximo(iterador);
  }
}

void aumentar_votos_recebidos(Lista *lista_vivos, int numero_do_jogador){ //aumenta a quantidade de votos que um jogador recebeu
  Iterador iterador = buscar_elemento_na_lista(lista_vivos, numero_do_jogador);
  iterador.endereco_jogador->contador_de_votos++;
}