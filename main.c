#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ponto.h"

static int getNumLinhas(FILE *entrada);

int main(int argc, char* argv[]){
    FILE *entrada;
    int numPontos = 0;

    entrada = fopen(argv[1], "r");

    if(entrada == NULL){
        printf("nao foi possivel abrir o arquivo\n");
        return 0;
    }

    // descobre numero de linhas
    numPontos = getNumLinhas(entrada);

    // aloca vet de pontos
    Ponto* vetPontos[numPontos];
    // aloca matriz de distancias
    int matDistancias[numPontos][numPontos];

    // salva os pontos no vet de pontos
    

    // preenche matriz
        // calculando a distancia entre 2 pontos

    // escreve distancias.txt
    
    return 0;
}

static int getNumLinhas(FILE *entrada){
    char c;
    int count;
    for (c = getc(entrada); c != EOF; c = getc(entrada)){
        if (c == '\n') {
            count = count + 1;     
        }
    }
    return count;
}