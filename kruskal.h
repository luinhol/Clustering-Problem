#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aresta.h"
#include "ponto.h"

void init(int parent[], int rank[], int numPontos);

int find(int parent[], int num);

bool connected(int parent[], int p, int q);

void uni(int p, int q, int parent[], int rank[]);

int conteudo(int parent[], int p);

void kruskalAlgo(int parent[], int rank[], Aresta *vetArestas[], int tamanhoVetArestas, int numPontos, int numConjuntos);

void printAgrupamentos(int parent[], int rank[], Ponto* vetPontos[], int numPontos);