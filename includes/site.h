#ifndef SITE_H
#define SITE_H

#include <stdio.h>

typedef struct site SITE;

SITE *ler_site_arquivo(FILE *fp);

SITE* criar_site(int siteId, char* nome, int relevancia, char* link, char** palavras_chave, int numero_palavras_chave);
void remover_site(SITE **site);
void imprimir_site(SITE *site);
int inserir_nova_palavra_chave(SITE *site, char *novaPalavraChave);
int mudar_relevancia(SITE *site, int novaRelevancia);

int getSiteId(SITE *site);
char *getNome(SITE *site);
int getRelevancia(SITE *site);
char *getLink(SITE *site);
char **getPalavrasChave(SITE *site);

#endif
