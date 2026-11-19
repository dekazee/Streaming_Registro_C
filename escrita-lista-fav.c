#include <stdio.h>
#include <string.h>

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
void mostrarCatalogo(struct Filmes f[]);
char retornarNomePorId(struct Filmes f[], int id);
void mostrarListaFav(struct Filmes f[], struct Usuario l, int times);

int main() {
    FILE *arq;
    FILE *arqfav;
    struct Filmes filmes[30];
    struct Usuario usuario1, lista;
    int status, decisao = -1, times = 0, statusLista, id;
    arq = fopen("filmes.bin", "r+b");

    if(arq == NULL) {
        printf("Não foi possível abrir o Catálogo");
    }
    status = fread(filmes, sizeof(struct Filmes), 30, arq);
    if(status != 30) {
        printf("Catálogo incompleto\n");
        printf("%d filmes disponíveis\n", status);
    }
    criarUsuario(&usuario1);
    while(decisao != 0) {
        printf("O que deseja fazer?\n");
        printf("\n=========================\n");
        printf("1- Ver catálogo de Filmes\n");
        printf("2- Favoritar um Filme\n");
        printf("3- Mostrar Lista de Favoritos\n");
        printf("4- Remover um Filme dos Favoritos\n");
        printf("5- Fechar Programa\n");
        scanf("%d", &decisao);
        while(decisao < 0 || decisao > 5) {
            printf("Digite apenas os números indicados:\n");
            scanf("%d", &decisao);
        }
        
        if(decisao == 1) {
            printf("Catálogo: \n");
            mostrarCatalogo(filmes);
        }
        else if(decisao == 2) {
            arqfav = fopen("filmesFav.bin", "w+b");
            if(arqfav == NULL && times == 0) {
                printf("Não foi possivel criar a lista\n");
            } else if(arqfav == NULL) {
                printf("Não foi possível adicionar filme na lista\n");
            }
            if( times >= 30 ) {
                printf("todos os filmes foram adicionados a lista de favoritos\n");
            } else{
            printf("Qual filme deseja adicionar a lista?\n");
            printf("Digite o ID do filmes : ");
            scanf("%d", &id);
            lista.filmesFavId[times] = id;

            statusLista = fwrite(&lista, sizeof(struct Usuario), 1, arqfav);
            if(statusLista != 1) {
                printf("Não foi possível adicionar esse filme a lista");
            }
            times += 1;
            statusLista = fread(&lista, sizeof(struct Usuario), 1, arqfav);
            if(statusLista != 1) {
                printf("Não foi possível abrir a Lista");
            }
            fclose(arqfav);


            
            }

        }
        else if(decisao == 3) {
            mostrarListaFav(filmes, lista, times);
        } 
        else if(decisao == 4) {

        }

    }
    

    return 0;

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

void mostrarCatalogo(struct Filmes f[]) {
    for(int i = 0; i < FILMES_FAV; i += 1) {
        printf("FILME %d", i + 1);
        printf("Nome: %s\n", f[i].titulo);
        printf("Descricao: %s\n", f[i].descricao);
        printf("Duracao: %.2lf\n", f[i].duracao);
        printf("ID: %d\n", f[i].id);
    }

}
// Não sei oq fzr com essas funções
/*
char retornarNomePorId(struct Filmes f[], int id) {
    char temp[31] = "Filme Não existe";
    for(int i = 0; i < FILMES_FAV; i += 1) {
        if(f[i].id == id) {
            return f[i].titulo;
        }
    }
    return temp;
}*/

void mostrarListaFav(struct Filmes f[], struct Usuario l, int times) {
    int i, j;
    for (i = 0; i < FILMES_FAV; i += 1) {
        for(j = 0; j < times; j += 1) {
            if(f[i].id == l.filmesFavId[j]) {
                printf("Filme %d", j += 1);
                printf("Nome: %s\n", f[i].titulo);
                printf("Descricao: %s\n", f[i].descricao);
                printf("Duracao: %.2lf\n", f[i].duracao);
                printf("ID: %d\n", f[i].id);
            }
        }
    }
}

