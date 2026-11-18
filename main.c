#include <stdio.h>
#include <string.h>

#define TAM 255;

// Criei os structs que serão utilizados

struct Filmes {
    char titulo[TAM];
    char descricao[TAM];
    double duracao;
    int id;
}

struct Usuario {
    char nome[TAM];
    char senha[TAM];
    int filmesFavId[];
}


int main() {
    
}