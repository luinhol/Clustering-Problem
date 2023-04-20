#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ponto.h"
#include "aresta.h"

static int getNumLinhas(FILE *entrada);
void getPontos(FILE *entrada, Ponto** vet);

// execucao:
// ./prog entrada.txt

int main(int argc, char* argv[]){
    char nomeArquivo[99] = "./";
    FILE *entrada;
    int numLinhas = 0;

    strcat(nomeArquivo, argv[1]);

    entrada = fopen(nomeArquivo, "r");

    if(entrada == NULL){
        printf("nao foi possivel abrir o arquivo\n");
        return 0;
    }

    // descobre numero de linhas
    numLinhas = getNumLinhas(entrada);
    printf("num linhas: %d\n", numLinhas);

    // aloca vet de pontos
    Ponto* vetPontos[numLinhas];
    // aloca vetor de distancias
    Aresta* vetArestas[numLinhas*numLinhas];

    // salva os pontos no vet de pontos
    getPontos(entrada, vetPontos);

    // preenche vetor de distancias
        // calculando a distancia entre 2 pontos

    // escreve distancias.txt

    // testes
    int i;
    char* id;
    float x, y;
    for(i = 0; i < numLinhas; i++){
        id = getId(vetPontos[i]);
        x = getX(vetPontos[i]);
        y = getY(vetPontos[i]);
        printf("id: %s, x: %0.2f, y: %0.2f\n", id, x, y);
    }
    
    return 0;
}

// funcao que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
static int getNumLinhas(FILE *entrada){
    char *line = NULL;
    size_t len = 0;
    unsigned int lineno = 0;

    while (! feof_unlocked (entrada))
    {
        ssize_t n = getline (&line, &len, entrada);
        if (n <= 0){
            // linha vazia ou final do arquivo
            break;
        }
        if(n > 1){
            ++lineno;
        }
    }
    return lineno;
}

// funcao que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
void getPontos(FILE *entrada, Ponto** vet){
    fseek(entrada, 0, SEEK_SET);
    char *line = NULL;
    size_t len = 0;
    unsigned int lineno = 0;
    char* pt;

    char* id;
    int idSize = 0;
    float x = 0;
    float y = 0;

    while (! feof_unlocked (entrada))
    {
        ssize_t n = getline (&line, &len, entrada);
        if (n <= 0){
            // linha vazia ou final do arquivo
            break;
        }
        if(n > 1){
            // armazena a id do ponto
            pt = strtok(line, ",\n");
            idSize = strlen(pt);
            id = (char*)malloc(sizeof(char)*idSize);
            strcpy(id, pt);

            // armazena o x do ponto
            pt = strtok(NULL, ",\n");
            x = atof(pt);

            // armazena o y do ponto
            pt = strtok(NULL, ",\n");
            y = atof(pt);

            // insere ponto no vet na posicao lineno
            vet[lineno] = inicializaPonto(id, x, y);

            // teste
            // printf("id: %s, x: %0.2f, y: %0.2f\n", id, x, y);

            lineno++;
        }
    }
}