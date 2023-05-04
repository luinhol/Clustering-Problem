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
    char nomeArquivoEntrada[99] = "";
    FILE *entrada;

    char nomeArquivoSaida[99] = "";
    FILE *saida;

    int numLinhas = 0, numCoords = 0, i, num, j;

    // copia o nome dos arquivos fornecidos como parametros
    strcat(nomeArquivoEntrada, argv[1]);
    strcat(nomeArquivoSaida, argv[3]);

    // adquire o numero de conjuntos fornecido como parametro
    int numConjuntos = atoi(argv[2]);

    // realiza abertura dos arquivos para manipulacao
    entrada = fopen(nomeArquivoEntrada, "r");
    saida = fopen(nomeArquivoSaida, "w");

    // verifica se o arquivo de entrada é válido
    if (entrada == NULL)
    {
        printf("nao foi possivel abrir o arquivo de entrada\n");
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

    // aloca dinamicamente vetores para armazenar os conjuntos
    int* parent;
    parent = (int*)malloc(sizeof(int)*numLinhas);
    int* rank;
    rank = (int*)malloc(sizeof(int)*numLinhas);

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
    setArestas(vetPontos, numLinhas, numCoords, vetArestas);

    // realiza o algoritmo kruskal
    kruskalAlgo(parent, rank, vetArestas, tamanhoVetArestas, numLinhas, numConjuntos);

    // printa os agrupamentos
    printAgrupamentos(saida, parent, rank, vetPontos, numLinhas);

    // libera as variaveis alocadas dinamicamente e fechando o arquivo aberto   
    liberaPontos(vetPontos, numLinhas);
    liberaArestas(vetArestas, tamanhoVetArestas);
    fclose(entrada);
    fclose(saida);
    free(vetArestas);
    free(vetPontos);
    free(parent);
    free(rank);
    return 0;
}