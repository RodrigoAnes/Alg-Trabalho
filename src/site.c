#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <site.h>

struct site {
    int siteId;
    char *nome;
    int relevancia;
    char *link;
    char **palavrasChave;
    int numeroPalavrasChave;
};
/* 
    Aloca um espaco na heap para um novo site, por enquanto sem informacoes
 */
SITE *criar_novo_site() {
    SITE *novoSite = malloc(sizeof(SITE));

    if (novoSite != NULL) {
        novoSite->siteId = 0;
        novoSite->relevancia = 0;
        novoSite->nome = NULL;
        novoSite->link = NULL;
        novoSite->numeroPalavrasChave = 0;
    }

    return novoSite;
}

SITE* criar_site(int siteId, char* nome, int relevancia, char* link, char** palavrasChave, int numeroPalavrasChave){
    SITE *novoSite = malloc(sizeof(SITE));

    if (novoSite != NULL) {
        novoSite->siteId = siteId;
        novoSite->relevancia = relevancia;
        novoSite->nome = nome;
        novoSite->link = link;
        novoSite->palavrasChave = palavrasChave;
        novoSite->numeroPalavrasChave = numeroPalavrasChave;
    }

    return novoSite;
}

/* 
    Le no arquivo .txt um site, insere suas informacoes em um SITE * e retorna o ponteiro
    0001,YouTube,900,https://www.youtube.com/,youtube,videos,online
    debugar e ver se esta fazendo o scanf certo
 */
SITE *ler_site_arquivo(FILE *fp) {
    SITE *site = criar_novo_site();
    char nomeTemp[50];
    char linkTemp[100];
    char auxiliar;

    fscanf(fp,"%d%c%[^,]%c%d%c%[^,\n]", &site->siteId, &auxiliar, nomeTemp, &auxiliar, &site->relevancia, &auxiliar,  linkTemp);

    site->nome = calloc(strlen(nomeTemp) + 1, sizeof(char));
    site->link = calloc(strlen(linkTemp) + 1, sizeof(char));

    strcpy(site->nome, nomeTemp);
    strcpy(site->link, linkTemp);

    int i = 0;
    site->palavrasChave = malloc(sizeof(char *));
    auxiliar = fgetc(fp); //le a ultima virgula antes das palavras chave
    
    while (auxiliar != '\n' && auxiliar != EOF) {
        char palavraTemp[50];
        fscanf(fp,"%[a-zA-Z]", palavraTemp);
        site->palavrasChave[i] = calloc((strlen(palavraTemp) + 1), sizeof(char));
        strcpy(site->palavrasChave[i], palavraTemp);
        strncat(site->palavrasChave[i], "\0", 1);
        auxiliar = fgetc(fp);
        i++;
        site->palavrasChave = realloc(site->palavrasChave, sizeof(char *) * (i + 1));
    }
    
    site->numeroPalavrasChave = i;

    return site;
}

void remover_site(SITE** site) {
    if (site != NULL && (*site) != NULL) {
        for (int i = 0; i < (*site)->numeroPalavrasChave; i++) {
            free((*site)->palavrasChave[i]);
        }
        free((*site)->palavrasChave);
        free((*site)->nome);
        free((*site)->link);
        free((*site));
        (*site) = NULL;
    } else {
        printf("ERRO: codigo informado inexistente no banco de dados.\n");
    }
}

//chamar uma busca aqui mesmo?
int inserir_nova_palavra_chave(SITE *site, char *novaPalavraChave) {
    if (site == NULL) {
        printf("ERRO: site nao encontrado.\n");
        return EXIT_FAILURE;
    }

    if (site->numeroPalavrasChave >= 10) {
        printf("ERRO: numero de palavras chave lotado.\n");
        return EXIT_FAILURE;
    }

    site->numeroPalavrasChave++;
    site->palavrasChave = realloc(site->palavrasChave, sizeof(char *) * site->numeroPalavrasChave);
    site->palavrasChave[site->numeroPalavrasChave - 1] = calloc(strlen(novaPalavraChave) + sizeof(char), sizeof(char));

    strcpy(site->palavrasChave[site->numeroPalavrasChave - 1], novaPalavraChave);

    return EXIT_SUCCESS;
}

int mudar_relevancia(SITE *site, int novaRelevancia) {
    if (site == NULL) {
        printf("ERRO: site nao encontrado.\n");
        return EXIT_FAILURE;
    }

    if (novaRelevancia < 0 || novaRelevancia > 1000) {
        printf("ERRO: nova relevancia deve ser um valor entre 0 e 1000.\n");
        return EXIT_FAILURE;
    }

    site->relevancia = novaRelevancia;
    return EXIT_SUCCESS;
}

void imprimir_site(SITE *site) {
    printf("============================\n");
    printf(">> Site: %s\n", site->nome);
    printf(">> Codigo: %d\n", site->siteId);
    printf(">> Link: %s\n", site->link);
    printf(">> Relevancia: %d\n", site->relevancia);
    printf(">> Palavras chave: ");
    for (int i = 0; i < site->numeroPalavrasChave; i++) {
        printf("%s | ", site->palavrasChave[i]);
    }
    printf("\n");
    printf("============================\n");
}

int getSiteId(SITE *site) {
    if (site != NULL) {
        return site->siteId;
    }

    printf("ERRO: site nao encontrado.\n");
    return 0;
}

char *getNome(SITE *site) {
    if (site != NULL) {
        return site->nome;
    }

    printf("ERRO: site nao encontrado.\n");
    return NULL;
}

int getRelevancia(SITE *site) {
    if (site != NULL) {
        return site->relevancia;
    }

    printf("ERRO: site nao encontrado.\n");
    return 0;
}

char *getLink(SITE *site) {
    if (site != NULL) {
        return site->link;
    }

    printf("ERRO: site nao encontrado.\n");
    return NULL;
}

char **getPalavrasChave(SITE *site) {
    if (site != NULL) {
        return site->palavrasChave;
    }

    printf("ERRO: site nao encontrado.\n");
    return NULL;
}