#include <stdio.h>
#include <string.h>

#define TAM 255
#define QTD_FILMES 30


// uma struct de Filmes
struct Filmes {
    char titulo[TAM];
    char descricao[TAM];
    double duracao;
    int id;
};

void preencherFilme(struct Filmes *f, int i);
void lerStr(char str[], int tamMax);

int main() {
    FILE *arq;
    struct Filmes filmes[QTD_FILMES];
    int status;
    // preenchimento de todo vetor
    for(int i = 0; i < QTD_FILMES; i += 1) {
        filmes[i].titulo[0] = '\0';
        filmes[i].descricao[0] = '\0';
        filmes[i].duracao = 0;
        filmes[i].id = 99;
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

