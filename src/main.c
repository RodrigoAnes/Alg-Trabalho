#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lista.h>

char *readLine(FILE *stream) {
    char *str = calloc(1, sizeof(char)), c;

    c = getc(stream);

    while(c != '\n' && c != EOF) {
        if(c != '\r') {
            str = realloc(str, sizeof(char) * (strlen(str) + 1) + sizeof(char));
            strncat(str, &c, 1);
        }
        c = getc(stream);
    }
    strncat(str, "\0", 1);
    return str;
}

void carregar_dados(LISTA* lista){
    SITE *site = NULL;
    FILE *fp = fopen("res/googlebot.txt", "r");

    while(!feof(fp)){
        site = ler_site_arquivo(fp);
        lista_inserir(lista, site);
    }
    fclose(fp);

    lista_imprimir(lista);
}

void interface_inserir_site(LISTA* lista){
    int siteId, relevancia, numeroPalavrasChave;
    char *nome, *link, **palavrasChave;
    
    printf("Insira um novo site\n");
    printf("Codigo (ex. 0002): ");
    scanf("%d%*c", &siteId);
    printf("\nNome do site: ");
    nome = readLine(stdin);
    printf("\nRelevancia (0 - 1000): ");
    scanf("%d%*c", &relevancia);
    printf("\nLink: ");
    link = readLine(stdin);
    printf("\nNumero de palavras chave: ");
    scanf("%d%*c", &numeroPalavrasChave);

    if (numeroPalavrasChave > 0) {
        palavrasChave = calloc(1, sizeof(char *));
        for (int i = 0; i < numeroPalavrasChave; i++) {
            if (i != 0) palavrasChave = realloc(palavrasChave, sizeof(char *) * (i + 1));
            palavrasChave[i] = readLine(stdin);
        }
    }
    
    SITE *novoSite = criar_site(siteId, nome, relevancia, link, palavrasChave, numeroPalavrasChave);
    boolean confirmacaoSite = lista_inserir(lista, novoSite);
    
    if (confirmacaoSite) {
        printf("Site inserido com sucesso.\n");
    } else {
        printf("ERRO: site nao pode ser inserido.\n");
    }
}


void interface_remover_site(LISTA* lista){
    int codigo;
    
    printf("Insira o codigo do site que deseja remover:\n");
    scanf("%d", &codigo);
    
    if(lista_remover(lista, codigo))
        printf("Site removido com sucesso");
    else
        printf("Falha de remoção");
}

void interface_inserir_palavra_chave(LISTA* lista){
    int codigo;
    char* palavra = NULL;
    SITE* site = NULL;
    
    printf("Insira o codigo do site que deseja editar:\n");
    scanf("%d%*c", &codigo);
    site = lista_busca(lista, codigo);
    if(site == NULL){
        printf("O site nao foi encontrado");
        return;
    }

    printf("Insira a nova palavra chave:\n");
    palavra = readLine(stdin);
    inserir_nova_palavra_chave(site, palavra);
    return;
}

void interface_atualizar_relevancia(LISTA* lista){
    int codigo;
    int relevancia;
    SITE* site = NULL;
    
    printf("Insira o codigo do site que deseja editar:\n");
    scanf("%d", &codigo);
    site = lista_busca(lista, codigo);
    if(site == NULL){
        printf("O site nao foi encontrado");
        return;
    }

    printf("Insira a nova relevancia:\n");
    scanf("%d", &relevancia);
    mudar_relevancia(site, relevancia);
    return;
}


int interface_opcoes_usuario() {
    int escolha;

    printf("Mini Googlebot\n");
    printf("1. Inserir um site\n");
    printf("2. Remover um site\n");
    printf("3. Inserir nova palavra-chave\n");
    printf("4. Atualizar relevancia\n");
    printf("5. Imprimir lista de sites\n");
    printf("6. Sair\n\n");
    printf("Escolha uma acao(1 a 6): ");

    scanf("%d", &escolha);
    while (escolha > 6 || escolha < 1) {
        printf("ERRO: opcao inexistente, escolha um valor entre 1 a 5.\n");
        scanf("%d", &escolha);
    }

    return escolha;
}

int main(){
    LISTA* lista = lista_criar();

    carregar_dados(lista);

    int acaoUsuario;
    do {
        acaoUsuario = interface_opcoes_usuario();

        switch (acaoUsuario) {
            case 1:
                interface_inserir_site(lista);
                break;
            case 2:
                interface_remover_site(lista);
                break;
            case 3:
                interface_inserir_palavra_chave(lista);
                break;
            case 4:
                interface_atualizar_relevancia(lista);
                break;
            case 5:
                lista_imprimir(lista);
                break;
            case 6:
                printf("Programa finalizado\n");
                break; 
            default:
                break;                
        }
    } while (acaoUsuario != 6); 

    return(0);
}