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

struct Admin {
    char nome[TAM];
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
int atribuiVarCopiaArq(struct Usuario *l, FILE **afav, int id, int *qtd);
int filmeFavExiste(int id, struct Usuario u, int times);
void adminOuUsuario(int *d);
void criarAdmin(struct Admin *a);
void preencherFilme(struct Filmes *f);
int removerFilmePorId(FILE *arq,struct Filmes f[], int id);
void ordenarCatalogo(struct Filmes f[]);
int main() {
    FILE *arq;
    FILE *arqfav;
    struct Filmes filmes[30], filmeAdd; // é onde o filmes.bin vai ir
    struct Usuario usuario1, lista;
    struct Admin adm;
    int status, decisao = -1, times, statusLista, id, removed = 0, admUsuario, posFilme;
    char temp[10], filme[TAM];
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
    adminOuUsuario(&admUsuario);
    if(admUsuario == 1) {
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
                    posFilme = -1;
                    for (int i = 0; i < FILMES_FAV; i++) {
                        if (filmes[i].id == id && id != 99) {
                            posFilme = i;
                            break;
                        }
                    }
                    while (posFilme == -1) {
                        printf("ID nao encontrado. Digite um ID existente no catalogo: \n");
                        scanf("%d", &id);
                        for (int i = 0; i < FILMES_FAV; i++) {
                            if (filmes[i].id == id && id != 99) {
                                posFilme = i;
                                break;
                            }
                        }
                    }
                    if(filmeFavExiste(id, lista, times) != -1) {
                        printf("Esse filme já está na lista\n");
                        statusLista = -1;
                    } else {
                        lista.filmesFavId[times] = id; // aqui eu coloco o id dentro dessa lista
                        times += 1; // aqui eu adiciono mais 1, pq na proxima vez de adicionar ele vai para a posição da frente
                        lista.times = times;
                        rewind(arqfav); // reseta o ponteiro do arquivo 
                        statusLista = fwrite(&lista, sizeof(struct Usuario), 1, arqfav);
                        fclose(arqfav);
                    } // fecha o arquivo(nao sei se precisa, mas funcionou assim ent deixa ai)
                    if(statusLista != 1) {
                        printf("Não foi possível adicionar esse filme a lista\n");
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
                            printf("%s adicionado\n", filmes[posFilme].titulo);
                        }
                    }
                }

            }
            else if(decisao == 3) {
                mostrarListaFav(filmes, lista, times); // mostra tudo que ta na lista fav
            }  
            else if (decisao == 4) {
                printf("Qual filme remover da lista?\n");
                printf("Digite o ID do filme:\n");
                scanf("%d", &id);

                if (atribuiVarCopiaArq(&lista, &arqfav, id, &times)) {
                    printf("Filme removido dos favoritos!\n");
                } else {
                    printf("Esse filme não estava na lista de favoritos.\n");
                }
            }
            else {
                printf("\nFim do programa\n");
                fclose(arq);
                fclose(arqfav);
                decisao = 0;
            }

        } 
    } else {
        lerStr(temp, 10);
        criarAdmin(&adm);
        while(decisao != 0) {
            printf("O que deseja fazer?\n");
            printf("\n=========================\n");
            printf("1- Ver catálogo de Filmes\n");
            printf("2- Adicionar filme ao catálogo\n");
            printf("3- Remover um Filme do Catálogo\n");
            printf("4- Fechar Programa\n");
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
                int posLivre = -1;
                int maiorId = 0;

                // Procurar a primeira posicao vazia e o maior ID cadastrado
                for (int i = 0; i < FILMES_FAV; i++) {
                    if (filmes[i].id == 99) {
                        if (posLivre == -1) posLivre = i;
                    } else if (filmes[i].id > maiorId) {
                        maiorId = filmes[i].id;
                    }
                }

                if (posLivre == -1) {
                    printf("Catalogo cheio!\n");
                } else {
                    lerStr(temp, 10);
                    printf("Preencha as informacoes do filme: \n");
                    preencherFilme(&filmeAdd);

                    // O novo ID e o maior ID existente + 1
                    filmeAdd.id = maiorId + 1;
                    if (filmeAdd.id == 99) filmeAdd.id = 100; // 99 fica reservado para posicoes vazias

                    filmes[posLivre] = filmeAdd;
                    ordenarCatalogo(filmes);

                    // Gravar o vetor inteiro, sem repetir o mesmo registro
                    rewind(arq);
                    status = fwrite(filmes, sizeof(struct Filmes), FILMES_FAV, arq);
                    fflush(arq);

                    if (status != FILMES_FAV) {
                        printf("Erro ao gravar o catalogo.\n");
                    } else {
                        printf("Filme adicionado ao catalogo! ID: %d\n", filmeAdd.id);
                    }
                }
            } else if(decisao == 3) {
                printf("Digite o id do filme que deseja remover:\n");
                scanf("%d", &id);
                status = removerFilmePorId(arq, filmes, id);
                if(status == 0) {
                    printf("Filme não foi removido\n");
                    printf("Erro\n");
                } else {
                    printf("Filme removido com sucesso!\n");
                }
            } else {
                printf("\nFim do programa\n");
                fclose(arq);
                fclose(arqfav);
                decisao = 0;
            }
            
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
    int i;
    int j = 0;
    for(i = 0; i < FILMES_FAV; i += 1) {
        if(f[i].id != 99) {
        printf("FILME %d\n", i + 1);
        printf("Nome: %s\n", f[i].titulo);
        printf("Descricao: %s\n", f[i].descricao);
        printf("Duracao: %.2lf\n", f[i].duracao);
        printf("ID: %d\n", f[i].id);
        j += 1;
        }
    }
    if(j == 0) {
        printf("Nenhum Filme no Catálogo\n");
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

int atribuiVarCopiaArq(struct Usuario *l, FILE **afav, int id, int *qtd) {
    struct Usuario lido;
    FILE *afavcpy = fopen("temp.bin", "wb");
    int status1, status2, removeu = 0;

    *afav = fopen("filmesFav.bin", "rb");

    if (*afav == NULL || afavcpy == NULL) {
        printf("Um dos arquivos não conseguiu ser acessado! Na função atribuiVarCopiaArq!\n");
        if (*afav != NULL) fclose(*afav);
        if (afavcpy != NULL) fclose(afavcpy);
        *afav = NULL;
        return 0;
    }

    while ((status1 = fread(&lido, sizeof(struct Usuario), 1, *afav)) == 1) {
        struct Usuario copia = lido;
        int novaQtd = 0;

        for (int i = 0; i < lido.times && i < FILMES_FAV; i++) {
            if (lido.filmesFavId[i] != id) {
                copia.filmesFavId[novaQtd] = lido.filmesFavId[i];
                novaQtd++;
            } else {
                removeu = 1;
            }
        }

        for (int i = novaQtd; i < FILMES_FAV; i++) {
            copia.filmesFavId[i] = 99;
        }

        copia.times = novaQtd;

        status2 = fwrite(&copia, sizeof(struct Usuario), 1, afavcpy);
        if (status2 != 1) {
            printf("Não foi possível escrever no arquivo cópia! Na função atribuiVarCopiaArq!\n");
            fclose(*afav);
            fclose(afavcpy);
            remove("temp.bin");
            *afav = NULL;
            return 0;
        }

        if (l != NULL) *l = copia;
        if (qtd != NULL) *qtd = novaQtd;
    }

    fclose(*afav);
    fclose(afavcpy);

    remove("filmesFav.bin");
    rename("temp.bin", "filmesFav.bin");

    *afav = fopen("filmesFav.bin", "r+b");
    return removeu;
}

int filmeFavExiste(int id, struct Usuario u, int times) {
    for (int i = 0; i < times && i < FILMES_FAV; i++) {
        if (u.filmesFavId[i] == id) {
            return i;
        }
    }
    return -1;
}

void adminOuUsuario(int *d) {
    printf("Como deseja entrar?\n");
    printf("1-Usuário\n");
    printf("2-Admin\n");
    scanf("%d", &(*d));
    while(*d < 1 || *d > 2) {
        printf("Digite apenas 1 ou 2");
        scanf("%d", &(*d));
    }
}

void criarAdmin(struct Admin *a) {
    printf("Digite o nome do Admin: ");
    lerStr(a->nome, TAM);
}

void preencherFilme(struct Filmes *f) {
    char temp[10];
    printf("Digite o nome do filme: ");
    lerStr(f->titulo, TAM);
    printf("Digite a descricao do filme: ");
    lerStr(f->descricao, TAM);
    printf("Qual a duração: ");
    scanf("%lf", &f->duracao);
    lerStr(temp, 10);
}

void ordenarCatalogo(struct Filmes f[]) {
    struct Filmes temp;

    // Mantem os filmes em ordem crescente de ID e os vazios no final
    for (int i = 0; i < FILMES_FAV - 1; i++) {
        for (int j = i + 1; j < FILMES_FAV; j++) {
            if (f[j].id != 99 && (f[i].id == 99 || f[j].id < f[i].id)) {
                temp = f[i];
                f[i] = f[j];
                f[j] = temp;
            }
        }
    }
}

int removerFilmePorId(FILE *arq, struct Filmes f[], int id) {

    int pos = -1;

    // 1. Procurar o filme pelo ID
    for (int i = 0; i < FILMES_FAV; i++) {
        if (f[i].id == id) {
            pos = i;
            break;
        }
    }

    // 2. Verificar se encontrou (99 representa uma posicao vazia)
    if (pos == -1 || id == 99) {
        printf("Filme nao encontrado!\n");
        return 0;
    }

    // 3. Deslocar os filmes para a esquerda
    for (int i = pos; i < FILMES_FAV - 1; i++) {
        f[i] = f[i + 1];
    }

    // 4. Limpar a última posição
    memset(&f[FILMES_FAV - 1], 0, sizeof(struct Filmes));
    f[FILMES_FAV - 1].id = 99;

    // Deixar os filmes em ordem crescente de ID
    ordenarCatalogo(f);

    // 5. Atualizar o arquivo binário
    rewind(arq);

    size_t status = fwrite(f, sizeof(struct Filmes), FILMES_FAV, arq);

    if (status != FILMES_FAV) {
        printf("Erro ao atualizar arquivo!\n");
        return 0;
    }

    // 6. Garantir que os dados sejam gravados
    fflush(arq);

    // 7. Mostrar o vetor atualizado
    printf("\nFilmes apos remocao:\n");

    for (int i = 0; i < FILMES_FAV; i++) {
        printf("Posicao %d: ID %d\n", i, f[i].id);
    }

    return 1;
}
