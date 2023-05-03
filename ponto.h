/** Define um tad Ponto.
 * @file ponto.h
 * @author Lucas Pereira Taborda e Gabriel de Castro Lima
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 * Tad ponto
 */
typedef struct ponto Ponto;

/**
 * Função que inicializa o ponto
 * @param identificador Id do ponto
 * @param coords Vetor com as coordenadas do ponto
 * @param num Indice do ponto no vetPontos
 * @return Ponto
 */
Ponto* inicializaPonto(char* identificador, float* coords, int num);

/**
 * Destrutor de ponto
 * @param p Id do ponto
 */
void liberaPonto(Ponto* p);

/**
 * Função que retorna o id do ponto
 * @param p Ponto
 * @return Id do ponto
 */
char* getId(Ponto* p);

/**
 * Função que retorna o numero do ponto
 * @param p Ponto
 * @return Indice do ponto no vetPontos
 */
int getNum(Ponto* p);

/**
 * Função que atribui o indice do ponto no vetPontos
 * @param p Ponto
 * @param num Indice do ponto no vetPontos
 */
void setNum(Ponto* p, int num);

/**
 * Função que retorna a coordanada da posicao k do vetor de coordenadas
 * @param p Ponto
 * @param k Posicao da coordenada no vetor de coordenadas
 * @return Coordenada
 */
float getCoord(Ponto* p, int k);

/**
 * Função de comparacao de pontos
 * @param a Ponto1
 * @param b Ponto2
 * @return value < 0 if id(a) is less than id(b).
 * @return value > 0 if id(b) is less than id(a).
 * @return value = 0 if id(a) is equal to id(b).
 */
int pontoComp(const void* a, const void* b);

/**
 * Função que retorna a distancia entre 2 pontos
 * @param p1 Ponto1
 * @param p2 Ponto2
 * @param numCoords Numero de coordenadas de cada ponto
 * @return Distancia entre os 2 pontos
 */
float dist(Ponto *p1, Ponto *p2, int numCoords);

/**
 * Destrutor de um vetor de pontos
 * @param vetPontos Vetor de pontos
 * @param numPontos Numero de pontos do vetor
 */
void liberaPontos(Ponto **vetPontos, int numPontos);