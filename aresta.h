/** Define um tad Aresta.
 * @file aresta.h
 * @author Lucas Pereira Taborda e Gabriel de Castro Lima
 */

#include "ponto.h"

/**
 * Tad aresta
 */
typedef struct aresta Aresta;

/**
 * Função que inicializa um ponto
 * @param p1 Ponto1
 * @param p2 Ponto2
 * @param peso Peso
 * @return Aresta
 */
Aresta* inicializaAresta(Ponto* p1, Ponto* p2, float peso);

/**
 * Função que realiza a leitura do arquivo de entrada, inicializa as arestas, inserindo os pontos
 * @param vetPontos Vetor de pontos
 * @param numPontos Quantidade de pontos
 * @param numCoords Numero de coordenadas de cada ponto
 * @param vetArestas Vetor de arestas
 */
void setArestas(Ponto **vetPontos, int numPontos,int numCoords, Aresta **vetArestas);

/**
 * Destrutor de aresta
 * @param a Aresta
 */
void liberaAresta(Aresta* a);

/**
 * Função que retorna o peso de uma aresta
 * @param a Aresta
 * @return Peso da aresta
 */
float getPeso(Aresta* a);

/**
 * Função que retorna o ponto1 da aresta
 * @param a Aresta
 * @return p1 da Aresta
 */
Ponto* getp1(Aresta* a);

/**
 * Função que retorna o ponto2 da aresta
 * @param a Aresta
 * @return p2 da aresta
 */
Ponto* getp2(Aresta* a);

/**
 * Função de comparacao de arestas
 * @param a Aresta
 * @param b Aresta
 * @return value = -1 if peso(a) is less than peso(b).
 * @return value = 1 if peso(b) is less than peso(a).
 * @return value = 0 if peso(a) is equal to peso(b).
 */
int arestComp(const void* a, const void* b);

/**
 * Destrutor do vetor de arestas
 * @param vetArestas Vetor de arestas
 * @param tamVetArestas Tamanho do vetor de arestas
 */
void liberaArestas(Aresta **vetArestas, int tamVetArestas);