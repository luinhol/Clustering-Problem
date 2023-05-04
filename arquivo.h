#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"

/**
 * Função que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
 * @param entrada Arquivo de entrada
 * @return Numero de linhas com pontos
 */
int getNumLinhas(FILE *entrada);

/**
 * Função que realiza a leitura do arquivo de entrada, inicializa os pontos e insere no vetor de pontos
 * @param entrada Arquivo de entrada
 * @param vet Vetor de pontos
 * @param numCoords Numero de coordenadas de cada ponto
 */
void getPontos(FILE *entrada, Ponto **vet, int numCoords);

/**
 * Função que retorna o numero de coordanadas de cada ponto
 * @param entrada Arquivo de entrada
 * @return Numero de coordenadas de cada ponto
 */
int getNumCoordenadas(FILE *entrada);