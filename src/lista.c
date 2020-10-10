#include <stdlib.h>
#include <lista.h>


struct no{
    SITE *site;
    struct no* proximo;
};

struct lista{ 
    NO* inicio;
};


LISTA *lista_criar(){
  LISTA* lista = (LISTA*) calloc(1, sizeof(LISTA));
  lista->inicio = NULL;
  return lista;
}



boolean lista_inserir(LISTA *lista, SITE* s){
  NO* n = (NO*) malloc(sizeof(NO));

  n->site = s;
  n->proximo = NULL;

  if(lista->inicio == NULL){
    lista->inicio = n;
    return TRUE;
  }

  NO* no_atual = lista->inicio;
  NO* no_anterior = NULL;
  
  while(no_atual != NULL && getSiteId(n->site) > getSiteId(no_atual->site)){
    no_anterior = no_atual;
    no_atual = no_atual->proximo;
  } 

  if(no_anterior == NULL){
    lista->inicio = n;
  }else{
    no_anterior->proximo = n;
  }
  
  n->proximo = no_atual;

  return TRUE;
}


boolean lista_remover(LISTA *lista, int id){
  if( lista->inicio == NULL){
    return FALSE;
  }

  NO* no_atual = lista->inicio;
  NO* no_anterior = NULL;

  while(no_atual != NULL && id > getSiteId(no_atual->site)){
    no_anterior = no_atual;
    no_atual = no_atual->proximo;
  } 

  if(no_atual != NULL && getSiteId(no_atual->site) != id){
    return FALSE;
  }

  if(no_anterior == NULL){
    lista->inicio = no_atual->proximo;
  }else{
    no_anterior->proximo = no_atual->proximo;
  }

  remover_site(&(no_atual->site));
  free(no_atual);

  return TRUE;
}

SITE *lista_busca(LISTA *lista, int id){
  NO* no_atual = lista->inicio;

  while(no_atual != NULL && id > getSiteId(no_atual->site)){
    no_atual = no_atual->proximo;
  } 

  if(no_atual != NULL && getSiteId(no_atual->site) == id){
    return no_atual->site;
  }

  return NULL;
}

void lista_imprimir(LISTA* lista){
  NO* n = lista->inicio;
  while(n != NULL){
    imprimir_site(n->site);
    n = n->proximo;
  }
  return;
}
