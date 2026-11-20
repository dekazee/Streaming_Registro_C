#include <stdio.h>
#include <string.h>

// ver como fazer a criação desse arquivo

#define TAM 255
#define FILMES_FAV 30
struct Usuario {
    char nome[TAM];
    int filmesFavId[FILMES_FAV];
    int times;
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
//char retornarNomePorId(struct Filmes f[], int id);
void mostrarListaFav(struct Filmes f[], struct Usuario l, int times);

int main() {
    FILE *arq;
    FILE *arqfav;
    struct Filmes filmes[30]; // é onde o filmes.bin vai ir
    struct Usuario usuario1, lista;
    int status, decisao = -1, times, statusLista, id;
    arq = fopen("filmes.bin", "r+b");
    arqfav = fopen("filmesFav.bin", "r+b"); // ele abre o filmesFav.bin
    statusLista = fread(&lista, sizeof(struct Usuario), 1, arqfav); // aqui ele ja joga na variavel lista oq ta no filmesFav
    if(statusLista != 1) {
        printf("Não foi possível abrir a Lista\n");
        printf("status = %d\n", statusLista);
    }
    // confiro se consigo abrir
    times = lista.times; // a posição onde a lista termina. Sempre quando escrita-lista.c é executado isso vira 0
    if(arq == NULL) {
        printf("Não foi possível abrir o Catálogo");
    }
    status = fread(filmes, sizeof(struct Filmes), 30, arq); // aqui eu coloco tudo do filmes.bin para a variavel filmes
    if(status != 30) { // se caso der algum erro na copia
        printf("Catálogo incompleto\n"); 
        printf("%d filmes disponíveis\n", status);
    }
    criarUsuario(&usuario1); // aqui so serve pra colocar um nome do usuario
    //provavelmente a gente vai apagar essa variável, mas não agr
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
            if( times >= 30 ) { // times serve pra impedir de adicionar filmes além da quantidade de filmes
                printf("todos os filmes foram adicionados a lista de favoritos\n");
            } else{
                printf("Qual filme deseja adicionar a lista?\n");
                printf("Digite o ID do filmes : ");
                scanf("%d", &id);
                while(id < 1 || id > 30) {
                    printf("Digite entre 1 e 30: \n");
                    scanf("%d", &id);
                }
                usuario1.filmesFavId[times] = id; // aqui eu coloco o id dentro dessa lista
                times += 1; // aqui eu adiciono mais 1, pq na proxima vez de adicionar ele vai para a posição da frente
                usuario1.times = times;
                rewind(arqfav); // reseta o ponteiro do arquivo 
                statusLista = fwrite(&usuario1, sizeof(struct Usuario), 1, arqfav);
                fclose(arqfav); // fecha o arquivo(nao sei se precisa, mas funcionou assim ent deixa ai)
                if(statusLista != 1) {
                    printf("Não foi possível adicionar esse filme a lista\n"); // se der diferente de um, significa que o ponteiro nao foi pra posicao 1 do arquivo
                } else {
                    arqfav = fopen("filmesFav.bin", "r+b"); // abro o arquivo dnv
                    printf("status = %d\n", statusLista); // ele mostra 1 se deu tudo certo
                    printf("Filme adicionado na lista\n");
                    rewind(arqfav); // reseta o ponteiro para dnv
                    statusLista = fread(&lista, sizeof(struct Usuario), 1, arqfav); // aqui a gente joga os arquivos dnv na lista
                    if(statusLista != 1) {
                        printf("Não foi possível abrir a Lista\n"); // aqui é se o ponteiro nao chegar la dnv
                        printf("status = %d\n", statusLista);
                    } else {
                        printf("%s adicionado\n", filmes[lista.filmesFavId[times-1] - 1].titulo); // aqui mostra exatamente o filme que foi adicionado(ja que os ids começam do 1 e vai ate o 30)
                    }
                }
            }

        }
        else if(decisao == 3) {
            mostrarListaFav(filmes, lista, times); // mostra tudo que ta na lista fav
        } 
        else if(decisao == 4) {
            // aqui é onde estará a remoção
        } else {
            printf("\nFim do programa\n");
            fclose(arq);
            fclose(arqfav);
            decisao = 0;
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
        printf("FILME %d\n", i + 1);
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
    if(times == 0) {
        printf("Não a filmes na lista de favoritos\n"); // caso o arquivo foi resetado recentemente e o usuario apertar no 3, vai aparecer isso
    } else {
        for (i = 0; i < FILMES_FAV; i += 1) {
            for(j = 0; j < times; j += 1) {
                if(f[i].id == l.filmesFavId[j]) {
                    printf("Filme %d\n", j + 1);
                    printf("Nome: %s\n", f[i].titulo);
                    printf("Descricao: %s\n", f[i].descricao);
                    printf("Duracao: %.2lf\n", f[i].duracao);
                    printf("ID: %d\n", f[i].id);
                }
            }
        }
    }
}

