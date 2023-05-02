#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ponto.h"
#include "aresta.h"
#include "kruskal.h"

static int getNumLinhas(FILE *entrada);
static void getPontos(FILE *entrada, Ponto **vet, int numCoords);
static void getArestas(Ponto **vetPontos, int numPontos,int numCoords, Aresta **vetArestas);
static float dist(Ponto *p1, Ponto *p2, int numCoords);
static void liberaPontos(Ponto **vetPontos, int numPontos);
static void liberaArestas(Aresta **vetArestas, int tamVetArestas);
static int getNumCoordenadas(FILE *entrada);

int main(int argc, char *argv[])
{
    char nomeArquivo[99] = "";
    FILE *entrada;
    int numLinhas = 0, numCoords = 0, i, num, j;

    strcat(nomeArquivo, argv[1]);

    int numConjuntos = atoi(argv[2]);

    entrada = fopen(nomeArquivo, "r");

    if (entrada == NULL)
    {
        printf("nao foi possivel abrir o arquivo\n");
        return 0;
    }


    numCoords = getNumCoordenadas(entrada);
    // descobre numero de linhas
    numLinhas = getNumLinhas(entrada);
    // printf("num linhas: %d\n", numLinhas);

    // aloca vet de pontos
    Ponto** vetPontos;
    vetPontos = (Ponto**)malloc(sizeof(Ponto*)*numLinhas);

    
    // aloca vetor de distancias
    int tamanhoVetArestas = ((numLinhas-1) * numLinhas) / 2;


    Aresta** vetArestas;
    vetArestas = (Aresta**)malloc(sizeof(Aresta*)*tamanhoVetArestas);
    // aloca vetor para armazenar os conjuntos
    int parent[numLinhas];
    int rank[numLinhas];

    // salva os pontos no vet de pontos
    getPontos(entrada, vetPontos, numCoords);
    // ordena vet de pontos
    qsort(vetPontos, numLinhas, sizeof(Ponto*), pontoComp);
    for(i = 0; i < numLinhas; i++){
        setNum(vetPontos[i], i);
    }


    // preenche vetor de distancias
    // calculando a distancia entre 2 pontos
    getArestas(vetPontos, numLinhas, numCoords, vetArestas);

    // teste
    char *id;
    float x, y;

    // teste
    char* idP1;
    char* idP2;
    float dist;

    kruskalAlgo(parent, rank, vetArestas, tamanhoVetArestas, numLinhas, numConjuntos);

    printAgrupamentos(parent, rank, vetPontos, numLinhas);


    liberaPontos(vetPontos, numLinhas);
    liberaArestas(vetArestas, tamanhoVetArestas);
    fclose(entrada);
    free(vetArestas);
    free(vetPontos);
    return 0;
}

// funcao que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
static int getNumLinhas(FILE *entrada)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    int lineno = 0;

    while (!feof_unlocked(entrada))
    {
        ssize_t n = getline(&line, &len, entrada);
        if (n <= 0)
        {
            // linha vazia ou final do arquivo
            break;
        }
        if (n > 1)
        {
            ++lineno;
        }
    }
    free(line);
    return lineno;
}

// funcao que retorna o numero de coordanadas de cada ponto
static int getNumCoordenadas(FILE *entrada)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int numCoords = 0;

    ssize_t n = getline(&line, &len, entrada);
    if (n <= 0)
    {
        // linha vazia ou final do arquivo
        return 0;
    }

    pt = strtok(line, ",");

    while (pt != NULL)
    {
        pt = strtok(NULL, ",");
        numCoords++;
    }
    free(line);
    return numCoords-1;
}

// funcao que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
static void getPontos(FILE *entrada, Ponto **vet, int numCoords)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    int lineno = 0;
    char *pt;
    float* coords;

    char *id;
    int idSize = 0;
    int i;

    while (!feof_unlocked(entrada))
    {
        ssize_t n = getline(&line, &len, entrada);
        if (n <= 0)
        {
            // linha vazia ou final do arquivo
            break;
        }
        if (n > 1)
        {
            coords = (float*)malloc(sizeof(float*)*numCoords);

            // armazena a id do ponto
            pt = strtok(line, ",");
            id = strdup(pt);

            for(i = 0; i < numCoords; i++){
                pt = strtok(NULL, ",");
                coords[i] = atof(pt);
            }

            // insere ponto no vet na posicao lineno
            vet[lineno] = inicializaPonto(id, coords, lineno);

            lineno++;
        }
    }
    free(line);
}

static void getArestas(Ponto **vetPontos, int numPontos, int numCoords, Aresta **vetArestas)
{
    int i, j, posicao = 0;
    float d = 0;

    for (i = 0; i < numPontos; i++)
    {
        for (j = i + 1; j < numPontos; j++)
        {
            d = dist(vetPontos[i], vetPontos[j], numCoords);
            vetArestas[posicao] = inicializaAresta(vetPontos[i], vetPontos[j], d);
            posicao++;
        }
    }
}

static float dist(Ponto *p1, Ponto *p2, int numCoords)
{
    int i;
    float dist = 0.0;
    for (i = 0; i < numCoords; i++)
    {
        dist += pow(getCoord(p1, i) - getCoord(p2, i), 2);
    }
    dist = sqrt(dist);
    return dist;
}

static void liberaPontos(Ponto **vetPontos, int numPontos){
    int i;
    for(i = 0; i < numPontos; i++){
        liberaPonto(vetPontos[i]);
    }
}

static void liberaArestas(Aresta **vetArestas, int tamVetArestas){
    int i;
    for(i = 0; i < tamVetArestas; i++){
        liberaAresta(vetArestas[i]);
    }
}

