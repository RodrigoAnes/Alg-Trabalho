#ifndef LISTA_H
#define LISTA_H

#include <site.h>

typedef struct lista LISTA;

#define TRUE 1;
#define FALSE 0;
            
typedef int boolean;
typedef struct no NO;
typedef struct lista LISTA;

LISTA *lista_criar();

boolean lista_inserir(LISTA *lista, SITE *s);
boolean lista_remover(LISTA *lista, int id);
SITE* lista_busca(LISTA *lista, int id);

void lista_imprimir(LISTA* lista);

#endif