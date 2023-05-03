#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ponto.h"
#include "aresta.h"
#include "kruskal.h"
#include "arquivo.h"

int main(int argc, char *argv[])
{
    // declaracao de variaveis
    char nomeArquivo[99] = "";
    FILE *entrada;
    int numLinhas = 0, numCoords = 0, i, num, j;

    // copia o nome do arquivo fornecido como parametro
    strcat(nomeArquivo, argv[1]);

    // adquire o numero de conjuntos fornecido como parametro
    int numConjuntos = atoi(argv[2]);

    // realiza abertura do arquivo para manipulacao
    entrada = fopen(nomeArquivo, "r");

    // verifica se o arquivo é válido
    if (entrada == NULL)
    {
        printf("nao foi possivel abrir o arquivo\n");
        return 0;
    }

    // descobre o numero de coordanadas que cada ponto tem
    numCoords = getNumCoordenadas(entrada);
    // descobre numero de linhas
    numLinhas = getNumLinhas(entrada);

    // aloca dinamicamente um vetor para armazenar os pontos
    Ponto** vetPontos;
    vetPontos = (Ponto**)malloc(sizeof(Ponto*)*numLinhas);

    // calcula o tamanho do vetor de distancias
    int tamanhoVetArestas = ((numLinhas-1) * numLinhas) / 2;

    // aloca dinamicamente um vetor para armazenar as distancias
    Aresta** vetArestas;
    vetArestas = (Aresta**)malloc(sizeof(Aresta*)*tamanhoVetArestas);

    // aloca vetores para armazenar os conjuntos
    int parent[numLinhas];
    int rank[numLinhas];

    // salva os pontos no vet de pontos
    getPontos(entrada, vetPontos, numCoords);

    // ordena vet de pontos
    qsort(vetPontos, numLinhas, sizeof(Ponto*), pontoComp);
    for(i = 0; i < numLinhas; i++){
        // reorganiza os indices do pontos do vetPontos
        setNum(vetPontos[i], i);
    }

    // preenche vetor de distancias
    // calculando a distancia entre 2 pontos
    getArestas(vetPontos, numLinhas, numCoords, vetArestas);

    // realiza o algoritmo kruskal
    kruskalAlgo(parent, rank, vetArestas, tamanhoVetArestas, numLinhas, numConjuntos);

    // printa os agrupamentos
    printAgrupamentos(parent, rank, vetPontos, numLinhas);

    // libera as variaveis alocadas dinamicamente e fechando o arquivo aberto   
    liberaPontos(vetPontos, numLinhas);
    liberaArestas(vetArestas, tamanhoVetArestas);
    fclose(entrada);
    free(vetArestas);
    free(vetPontos);
    return 0;
}