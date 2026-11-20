#include <stdio.h>

#define TAM 255
#define QTD 30

// Criei os structs que serão utilizados



struct Usuario {
    char nome[TAM];
    int filmesFavId[QTD];
    int times;
};


int main() {
    FILE *arq;
    arq = fopen("filmesFav.bin", "w+b");
    int status;
    struct Usuario listaReset;
    if(arq == NULL) {
        printf("Não foi possível abrir o arquivo\n");
    } else {
        printf("Foi possível abrir o arquivo\n");
    }
    for(int i = 0; i < QTD; i += 1) {
        listaReset.filmesFavId[i] = 99;
    }
    listaReset.times = 0;
    status = fwrite(&listaReset, sizeof(struct Usuario), 1, arq);
    if(status == 1) {
        printf("Arquivo bin resetado\n");
    } else {
        printf("Não foi possível resetar o arquivo");
    }

}