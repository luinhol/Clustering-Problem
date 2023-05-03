#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"

int getNumLinhas(FILE *entrada);

/**
 * Função que realiza a leitura do arquivo de entrada, inicializa os pontos e insere no vetor de pontos
 * @param entrada Arquivo de entrada
 * @param vet Vetor de pontos
 * @param numCoords Numero de coordenadas de cada ponto
 */
void getPontos(FILE *entrada, Ponto **vet, int numCoords);

/**
 * Função que realiza a leitura do arquivo de entrada, inicializa as arestas, inserindo os pontos
 * @param vetPontos Vetor de pontos
 * @param numPontos Quantidade de pontos
 * @param numCoords Numero de coordenadas de cada ponto
 * @param vetArestas Vetor de arestas
 */
void getArestas(Ponto **vetPontos, int numPontos,int numCoords, Aresta **vetArestas);

/**
 * Função que retorna o numero de coordanadas de cada ponto
 * @param entrada Arquivo de entrada
 * @return Numero de coordenadas de cada ponto
 */
int getNumCoordenadas(FILE *entrada);