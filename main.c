#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ponto.h"
#include "aresta.h"
#include "kruskal.h"

static int getNumLinhas(FILE *entrada);
static void getPontos(FILE *entrada, Ponto **vet);
static void getArestas(Ponto **vetPontos, int numPontos, Aresta **vetArestas);
static float dist(Ponto *p1, Ponto *p2);
static void liberaPontos(Ponto **vetPontos, int numPontos);
static void liberaArestas(Aresta **vetArestas, int tamVetArestas);

// execucao:
// ./prog entrada.txt

int main(int argc, char *argv[])
{
    char nomeArquivo[99] = "./entrada.txt";
    FILE *entrada;
    int numLinhas = 0;

    int numConjuntos = 3;

    // strcat(nomeArquivo, argv[1]);

    entrada = fopen(nomeArquivo, "r");

    if (entrada == NULL)
    {
        printf("nao foi possivel abrir o arquivo\n");
        return 0;
    }

    // descobre numero de linhas
    numLinhas = getNumLinhas(entrada);
    printf("num linhas: %d\n", numLinhas);

    // aloca vet de pontos
    Ponto *vetPontos[numLinhas];
    // aloca vetor de distancias
    int tamanhoVetArestas = ((numLinhas-1) * numLinhas) / 2;
    Aresta *vetArestas[tamanhoVetArestas];

    // salva os pontos no vet de pontos
    getPontos(entrada, vetPontos);

    // preenche vetor de distancias
    // calculando a distancia entre 2 pontos
    getArestas(vetPontos, numLinhas, vetArestas);

    // escreve distancias.txt

    // testes
    int i, num;
    char *id;
    float x, y;
    for (i = 0; i < numLinhas; i++)
    {
        id = getId(vetPontos[i]);
        x = getX(vetPontos[i]);
        y = getY(vetPontos[i]);
        num = getNum(vetPontos[i]);
        printf("id: %s, num: %d, x: %0.2f, y: %0.2f\n", id, num, x, y);
    }

    printf("\n\n");

    char* idP1;
    char* idP2;
    float dist;
    // printf("tamanho vet arestas: %d\n", tamanhoVetArestas);
    // for(i = 0; i < tamanhoVetArestas; i++){
    //     idP1 = getId(getp1(vetArestas[i]));
    //     idP2 = getId(getp2(vetArestas[i]));
    //     dist = getPeso(vetArestas[i]);
    //     printf("aresta %d: p1- %s, p2- %s, dist- %0.2f\n", i, idP1, idP2, dist);
    // }

    kruskalAlgo(vetArestas, tamanhoVetArestas, numLinhas, numConjuntos);
    // qsort(vetArestas, tamanhoVetArestas, sizeof(Aresta*), arestComp);

    // printf("vet ordenado:\n");
    // for(i = 0; i < tamanhoVetArestas; i++){
    //     idP1 = getId(getp1(vetArestas[i]));
    //     idP2 = getId(getp2(vetArestas[i]));
    //     dist = getPeso(vetArestas[i]);
    //     printf("aresta %d: p1- %s, p2- %s, dist- %0.2f\n", i, idP1, idP2, dist);
    // }


    liberaPontos(vetPontos, numLinhas);
    liberaArestas(vetArestas, tamanhoVetArestas);
    fclose(entrada);
    return 0;
}

// funcao que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
static int getNumLinhas(FILE *entrada)
{
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

// funcao que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
static void getPontos(FILE *entrada, Ponto **vet)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    int lineno = 0;
    char *pt;

    char *id;
    int idSize = 0;
    float x = 0;
    float y = 0;

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
            // armazena a id do ponto
            pt = strtok(line, ",");
            id = strdup(pt);

            // armazena o x do ponto
            pt = strtok(NULL, ",");
            x = atof(pt);

            // armazena o y do ponto
            pt = strtok(NULL, "\n");
            y = atof(pt);

            // insere ponto no vet na posicao lineno
            vet[lineno] = inicializaPonto(id, x, y, lineno);

            // teste
            // printf("id: %s, x: %0.2f, y: %0.2f\n", id, x, y);

            lineno++;
        }
    }
    free(line);
}

static void getArestas(Ponto **vetPontos, int numPontos, Aresta **vetArestas)
{
    int i, j, posicao = 0;
    float d = 0;

    for (i = 0; i < numPontos; i++)
    {
        for (j = i + 1; j < numPontos; j++)
        {
            d = dist(vetPontos[i], vetPontos[j]);
            // printf("inserindo aresta, p1= %s, p2= %s, dist= %0.2f na posicao: %d\n", getId(vetPontos[i]), getId(vetPontos[j]), d, posicao);
            vetArestas[posicao] = inicializaAresta(vetPontos[i], vetPontos[j], d);
            posicao++;
        }
    }
}

static float dist(Ponto *p1, Ponto *p2)
{
    float x1 = getX(p1);
    float y1 = getY(p1);
    float x2 = getX(p2);
    float y2 = getY(p2);

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
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