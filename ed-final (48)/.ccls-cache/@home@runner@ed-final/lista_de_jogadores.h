#ifndef LISTA_DE_JOGADORES
#define LISTA_DE_JOGADORES
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Jogador {
  char nome_do_jogador[40]; //nome do jogador
  int papel; //papel do jogador
  int numero_do_jogador; //numero do jogador na partida
  int esta_protegido; //flag para saber se o jogador está protegido ou não. Manipulação exclusiva da medica
  int quem_visitou_dama; //uso exclusivo da Dama da noite. Contem o numero do jogador que ela visitou à noite
  int vai_votar_pela_manha; //fla de referência para a votação. Somente a Opressora pode manipular ele
  int quem_vai_reviver_necromante; //uso exclusivo do necromante
  int prioridade; //referencia para sabermos a ordem em que os papeis serão executados (alguns papeis precisam ter suas ações executadas antes de outras. Por exemplo, proteger alguém antes de ele ser atacado e morto)
  struct Jogador *proximo_jogador, *jogador_anterior; //contém o endereço do proximo jogador e do jogador anterior
  int tiros_matador;     //contador de acesso exclusivo pela Matador de Aluguel. O matador tem apenas duas balas
  int quem_vai_atacar;   //campo exclusivo para quem é o Assassino ou o Matador de Aluguel. Guarda quem ele vai atacar
  int quantidade_necromante; //uso exclusivo do necromante. Como o necromante só pode reviver uma vez, é um contador fundamental
  int contador_de_votos; //contador de votos recebidos
  int quem_vai_proteger; //para uso exclusivo do médico. Guarda a informação de quem ele protegeu
  int quem_opressora_vai_silenciar; //para uso exclusivo da opressora; informa quem ela silenciou durante a noite
  int tem_visita; //flag para conferir se o jogador tem visita de alguma Dama da Noite
  int atirador_vai_atirar; //flag individual do atirador. Controla se ele irá atirar em alguém ou não
  int morreu_de_noite; //para a gente controlar os casos especificos de papeis que conseguem matar tentarem matar um ao outro 
  int necromante_vai_reviver; //uso exclusivo do necromante. Contém a informação de quem ele vai reviver
  int acabou_de_reviver;
};

typedef struct { //contém informações da lista e do jogo
  struct Jogador *sentinela;
  int quantidade_de_jogadores;
  int contador_noite;
  int depressivo_foi_o_mais_votado;
  int assassino_morreu;
} Lista;

typedef struct {
  struct Jogador *endereco_jogador; // para guardar o endereço do jogador
  Lista *lista; // para acessar a lista e os elementos da lista, junto com seus campos individuais
} Iterador;

void inicializar_lista_jogadores(Lista *lista);
void inicializar_jogador(struct Jogador *jogador);
void adicionar_jogador(Lista *lista);

void resetar(Lista *lista_vivos_ou_mortos);

void trocar_jogadores_de_lista(Lista *destino, Lista *origem,
                               int numero_do_jogador);

Iterador iterador_primeiro(Lista *lista); // retorna uma variavel do tipo Iterador com o endereço do primeiro elemento da lista. Necessaria para começarmos com um iterador no começo da lista e não acabar pegando, por exemplo, um jogador do fim

Iterador buscar_elemento_na_lista(Lista *lista, int dado); // nos devolve uma instancia de Iterador que tem um dado especifico (no caso o numero do jogador) 

Iterador proximo(Iterador iterador); // passamos uma instância de Iterador e ele nos devolve uma instância Iterador com o proximo elemento ao Iterador

int vazia(Lista *lista); //retorna 1 se a lista estiver vazia e 0 caso contrário

void dar_numeros_jogadores(Lista *vivos); // antes do jogo começar, da os numeros a cada jogador

void printar_todos_os_jogadores_vivos_ou_mortos(Lista *vivos_ou_mortos); // imprime todos os jogadores presentes em uma determinada lista

void printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(Lista *vivos_ou_mortos, int excessao); // vai imprimir na tela todas as pessoas possiveis de selecionar exceto a pessoa em si

void excluir_jogador(Lista *lista_vivos, int numero_do_jogador); //exclui o jogador da lista de jogadores

void limpar_lista_jogadores(Lista *lista); //elimina todos os elementos da lista

Iterador elemento_anterior_ao_numero(Iterador iterador); // usada para o caso de trocar de lista de forma ordenada. Nos devolve o iterador focado no jogador anterior ao passado

Iterador elemento_proximo_ao_numero(Lista *lista, int numero_do_jogador); // dado um numero de jogador, retorna o jogador que está na lista mas tem numero superior ao passado como argumento da função. Usado na ordenação da função de trocar elementos de listas 

Iterador anterior(Iterador iterador); // nos da um iterador com o elemento anterior ao iterador

#endif