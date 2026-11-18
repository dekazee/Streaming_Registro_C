#include <stdio.h>
#include <string.h>

#define TAM 255;
#define QTD_FILMES 30;


// uma struct de Filmes
struct Filmes {
    char titulo[TAM];
    char descricao[TAM];
    double duracao;
    int id;
}

void preencherFilme(struct Filmes *f, int i);
void lerStr(char str[], int tamMax);

int main() {
    FILE *arq;
    struct Filmes filmes[QTD_FILMES];
    int status;
    // preenchimento de todo vetor
    for(int i = 0; i < QTD_FILMES; i += 1) {
        preencherFilme(filmes[i], i + 1);
    }

    arq = fopen("filmes.bin", "wb"); // criacao do arquivo

    if (arq == NULL) {
        printf("Não foi possível criar o arquivo.\n");
    } else {
        printf("Criação concluída.\n");
    }

    status = fwrite(filmes, sizeof(struct Filmes), QTD_FILMES, arq); // colocando todos os elementos do vetor no arquivo

    if(status == QTD_FILMES) {
        printf("Gravação concluída!\n");
    } else {
        printf("Erro na gravação.\n");
        printf("Somente %d gravados", status);
    }

    status = fclose(arq);

    if(status != 0) {
        printf("Erro ao fechar o arquivo!\n");
        return status;

    }
        printf("arquivo fechado com sucesso!\n");

    return 0;

    
}


void preencherFilme(struct Filmes *f, int i) {
    char temp[10];
    printf("Digite o nome do filme: ");
    lerStr(f->titulo, TAM);
    printf("Digite a descricao do filme: ");
    lerStr(f->descricao, TAM);
    printf("Qual a duração: ");
    scanf("%lf", &f->duracao);
    lerStr(temp, 10);
    f->id = i;
}

void lerStr(char str[], int tamMax) {
    fgets(str, tamMax, stdin);
    int tam = strlen(str);
    if(tam > 0 && str[tam -  1] == '\n') {
        str[tam - 1] = '\0';
    }
}
