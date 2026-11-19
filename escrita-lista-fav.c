#include <stdio.h>

// ver como fazer a criação desse arquivo

#define TAM 255
#define FILMES_FAV 30
struct Usuario {
    char nome[TAM];
    int filmesFavId[FILMES_FAV];
};

struct Filmes {
    char titulo[TAM];
    char descricao[TAM];
    double duracao;
    int id;
};

void criarUsuario(struct Usuario *u);
void lerStr(char str[], int tamMax);

int main() {
    FILE *arq;
    arq = fopen("filmes.bin", "r+b");
    if(arq == NULL) {
        printf("Não foi possível abrir o Catálogo");
    }
    struct Filmes filmes;
    struct Usuario usuario1;
    int decisao;
    criarUsuario(&usuario1);
    while(decisao != 0) {
    printf("O que deseja fazer?\n");
    printf("\n=========================\n");
    printf("1- Ver catálogo de Filmes\n");
    printf("2- Favoritar um Filme\n");
    printf("3- Remover um Filme dos Favoritos\n");
    printf("4- Fechar Programa\n");
    scanf("%d", &decisao);
    while(decisao < 0 || decisao > 4) {
        printf("Digite apenas os números indicados:\n");
        scanf("%d", &decisao);
    }

    if(decisao == 1) {

    }
    


}

void criarUsuario(struct Usuario *u) {
    printf("Digite o nome do Usuário: ");
    lerStr(u->nome, TAM);
}


void lerStr(char str[], int tamMax) {
    fgets(str, tamMax, stdin);
    int tam = strlen(str);
    if(tam > 0 && str[tam -  1] == '\n') {
        str[tam - 1] = '\0';
    }
}

void mostrarCatalogo(FILE arq) {


}

