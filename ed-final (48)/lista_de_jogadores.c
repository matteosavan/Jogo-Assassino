#include "lista_de_jogadores.h"
#include <locale.h>

void inicializar_lista_jogadores(Lista *lista) { // essa função vai inicializar a lista de jogadores, inclusive cria um sentinela

  lista->quantidade_de_jogadores = 0; // definindo a quantidade inicial de jogadores (no caso, 0)
  lista->sentinela = (struct Jogador *)malloc(sizeof(struct Jogador)); // aloca um sentinela
  lista->sentinela->proximo_jogador = lista->sentinela;
  lista->sentinela->jogador_anterior = lista->sentinela;
  lista->depressivo_foi_o_mais_votado = 0;
  lista->assassino_morreu = 0;
  lista->contador_noite = 0;
}

void inicializar_jogador(
    struct Jogador *jogador) { // inicializa os campos do jogador
  jogador->esta_protegido = 0;
  jogador->numero_do_jogador = 50;
  jogador->quantidade_necromante = 0;
  jogador->necromante_vai_reviver = 0;
  jogador->tiros_matador = 2;
  jogador->vai_votar_pela_manha = 1;
  jogador->contador_de_votos = 0;
  jogador->tem_visita = 0;
  jogador->morreu_de_noite = 0;
  jogador->atirador_vai_atirar = 0;
  jogador->acabou_de_reviver = 0;
}

void adicionar_jogador(Lista *lista) { // adicionar um jogador a lista de jogadores
  struct Jogador *novo = (struct Jogador *)malloc(sizeof(struct Jogador));
  inicializar_jogador(novo);
  printf("insira o nome do jogador: ");
  scanf(" %[^\n]s", novo->nome_do_jogador);

  novo->jogador_anterior = lista->sentinela->jogador_anterior; 
  novo->proximo_jogador = lista->sentinela;                    

  lista->sentinela->jogador_anterior->proximo_jogador = novo; 
  lista->sentinela->jogador_anterior = novo;

  lista->quantidade_de_jogadores++;
}

Iterador buscar_elemento_na_lista(Lista *lista, int dado) { // dado o numero do jogador, retorna o iterador "mirando" no jogador solicitado. Retorna o sentinela da lista caso não encontre o jogador
  Iterador iterador_aux;
  iterador_aux = iterador_primeiro(lista);
  while (iterador_aux.endereco_jogador != lista->sentinela) {
    if (iterador_aux.endereco_jogador->numero_do_jogador == dado)
      break;
    iterador_aux = proximo(iterador_aux);
  }
  return iterador_aux;
}

void limpar_lista_jogadores(Lista *lista){ //elimina todos os elementos da lista
  Iterador iterador, iterador_aux;
  
  iterador = iterador_primeiro(lista);

    while (iterador.endereco_jogador!=lista->sentinela) {
      iterador_aux = iterador;
      free(iterador_aux.endereco_jogador); //desaloca o elemento
      iterador = proximo(iterador); 
      lista->quantidade_de_jogadores--;
  }
  free(lista->sentinela);
  
  
}

void excluir_jogador(Lista *lista_vivos, int numero_do_jogador) { //exclui jogador da lista de jogadores
  Iterador iterador_aux;
  iterador_aux = buscar_elemento_na_lista(lista_vivos, numero_do_jogador); 
  iterador_aux.endereco_jogador->jogador_anterior->proximo_jogador =
      iterador_aux.endereco_jogador->proximo_jogador;
  iterador_aux.endereco_jogador->proximo_jogador->jogador_anterior =
      iterador_aux.endereco_jogador->jogador_anterior;
  free(iterador_aux.endereco_jogador);
  lista_vivos->quantidade_de_jogadores--;
}

int vazia(Lista *lista) { // retorna 1 se a lista esta vazia. Se não, retorna 0
  return (lista->quantidade_de_jogadores == 0);
}

void trocar_jogadores_de_lista(Lista *destino, Lista *origem,int numero_do_jogador) { // tiramos um jogador de uma lista (origem) e o inserimos em uma outra lista (destino) de forma ordenada quanto ao numero do jogador
  Iterador iterador_origem, iterador_destino_menor,
      iterador_destino_maior; // elemento de numero maior e numero menor que o numero do jogador que queremos inserir para conseguirmos manter a ordenação

  iterador_origem = buscar_elemento_na_lista(origem, numero_do_jogador);
  // tenho que realizar um codigo que me ordene a lista de jogadores... mas acho que por ser lista encadeada, o mais coerente é encontrar dois elementos, um que seja maior e outro que seja menor que o numero do jogador que sera trocado de lista e inserir o elemento no meio deles

  iterador_destino_maior =
      elemento_proximo_ao_numero(destino, numero_do_jogador);
  iterador_destino_menor = elemento_anterior_ao_numero(iterador_destino_maior);

  iterador_origem.endereco_jogador->jogador_anterior->proximo_jogador =
      iterador_origem.endereco_jogador->proximo_jogador;
  iterador_origem.endereco_jogador->proximo_jogador->jogador_anterior =
      iterador_origem.endereco_jogador->jogador_anterior;

  iterador_destino_menor.endereco_jogador->proximo_jogador =
      iterador_origem.endereco_jogador;
  iterador_destino_maior.endereco_jogador->jogador_anterior =
      iterador_origem.endereco_jogador;

  iterador_origem.endereco_jogador->proximo_jogador =
      iterador_destino_maior.endereco_jogador;
  iterador_origem.endereco_jogador->jogador_anterior =
      iterador_destino_menor.endereco_jogador;

  origem->quantidade_de_jogadores--;
  destino->quantidade_de_jogadores++;
}

Iterador elemento_anterior_ao_numero(Iterador iterador) {
  Iterador iterador_aux;
  iterador_aux = anterior(iterador);
  return iterador_aux;
}

Iterador elemento_proximo_ao_numero(
    Lista *lista,
    int numero_do_jogador) { // da o iterador mirado no jogador que tem numero maior que o jogador de numero numero_do_jogador da lista lista.
  Iterador iterador;

  iterador = iterador_primeiro(lista);

  while (iterador.endereco_jogador != lista->sentinela) {
    if (iterador.endereco_jogador->numero_do_jogador > numero_do_jogador) {
      break;
    }
    iterador = proximo(iterador);
  }

  return iterador;
}

Iterador iterador_primeiro(Lista *lista) { // devolve um iterador com o primeiro elemento da lista
  Iterador iterador;
  iterador.endereco_jogador = lista->sentinela->proximo_jogador;
  iterador.lista = lista;
  return iterador;
}

Iterador proximo(Iterador iterador) { // passamos um interador e ele nos devolve um iterador com o proximo elemento

  Iterador iterador_aux;
  iterador_aux.endereco_jogador = iterador.endereco_jogador->proximo_jogador;
  iterador_aux.lista = iterador.lista;
  return iterador_aux; 
}

Iterador anterior(Iterador iterador) { // nos da um iterador com o elemento anterior ao iterador
  Iterador iterador_aux;
  iterador_aux.endereco_jogador = iterador.endereco_jogador->jogador_anterior;
  iterador_aux.lista = iterador.lista;
  return iterador_aux; 
}

void resetar(Lista *lista_vivos_ou_mortos) { // ela vai voltar alguns campos específicos de flags para um valor que não interfira em proximas rodadas
  Iterador iterador;

  iterador = iterador_primeiro(lista_vivos_ou_mortos);

  while (iterador.endereco_jogador != lista_vivos_ou_mortos->sentinela) {
    iterador.endereco_jogador->contador_de_votos = 0;
    iterador.endereco_jogador->esta_protegido = 0;
    iterador.endereco_jogador->vai_votar_pela_manha = 1;
    iterador.endereco_jogador->tem_visita = 0;
    iterador.endereco_jogador->morreu_de_noite = 0;
    iterador.endereco_jogador->atirador_vai_atirar = 0;
    iterador.endereco_jogador->acabou_de_reviver=0;

    iterador = proximo(iterador);
  }
}

void dar_numeros_jogadores(Lista *vivos) { // enumera os jogadores
  Iterador iterador = iterador_primeiro(vivos);
  for (int i = 0; vivos->sentinela != iterador.endereco_jogador; i++) {
    iterador.endereco_jogador->numero_do_jogador = i;
    iterador = proximo(iterador);
  }
}
void printar_todos_os_jogadores_vivos_ou_mortos(Lista *vivos_ou_mortos) { // imprime todos os jogadores presentes em uma determinada lista
  Iterador iterador_aux;
  iterador_aux = iterador_primeiro(vivos_ou_mortos);

  if (vazia(vivos_ou_mortos)) {
    printf("a lista está vazia!\n");
  }

  while (iterador_aux.endereco_jogador != vivos_ou_mortos->sentinela) {
    printf("[%d] %s\n", iterador_aux.endereco_jogador->numero_do_jogador,
           iterador_aux.endereco_jogador->nome_do_jogador);
    iterador_aux = proximo(iterador_aux);
  }
}

void printar_todos_os_jogadores_vivos_ou_mortos_com_excessao(    Lista *vivos_ou_mortos,int excessao) { // vai imprimir na tela todas as pessoas possiveis de selecionar exceto a pessoa em si
  Iterador iterador_aux;
  iterador_aux = iterador_primeiro(vivos_ou_mortos);

  if (vazia(vivos_ou_mortos)) {
    printf("a lista está vazia!\n");
  }

  while (iterador_aux.endereco_jogador != vivos_ou_mortos->sentinela) {
    if (iterador_aux.endereco_jogador->numero_do_jogador != excessao)
      printf("[%d] %s\n", iterador_aux.endereco_jogador->numero_do_jogador,
             iterador_aux.endereco_jogador->nome_do_jogador);
    iterador_aux = proximo(iterador_aux);
  }
}
