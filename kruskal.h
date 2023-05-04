/** Define um um conjunto de funcoes de manipulacao de pontos, arestas e conjuntos.
 * @file kruskal.h
 * @author Lucas Pereira Taborda e Gabriel de Castro Lima
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aresta.h"
#include "ponto.h"

/**
 * Função que inicia o Weighted Quick-Union
 * @param parent Vetor para armazenar os conjuntos
 * @param rank Vetor para armazenar os pesos para o Weighted Quick-Union
 * @param numPontos Numero de pontos
 */
void init(int parent[], int rank[], int numPontos);

/**
 * Função que retorna o grupo de um elemento
 * @param parent Vetor dos elementos
 * @param num Indice do elemento
 * @return Raiz do elemento
 */
int find(int parent[], int num);

/**
 * Função que retorna se 2 elementos tem a mesma raiz
 * @param parent Vetor dos elementos
 * @param num Indice do elemento
 * @return Raiz do elemento
 */
bool connected(int parent[], int p, int q);

/**
 * Função que faz a uniao de 2 elementos
 * @param p Indice do elemento 1
 * @param q Indice do elemento 2
 * @param parent Vetor dos elementos
 * @param rank Vetor de pesos
 */
void uni(int p, int q, int parent[], int rank[]);

/**
 * Função que constroi a MST e já remove os numConjuntos-1 arestas
 * @param parent Vetor de elementos
 * @param rank Vetor de pesos
 * @param vetArestas Vetor de arestas
 * @param tamanhoVetArestas Tamanho do vetor de arestas
 * @param numPontos Quantidade de pontos
 * @param numConjuntos Quantidade de conjuntos
 */
void kruskalAlgo(int parent[], int rank[], Aresta *vetArestas[], int tamanhoVetArestas, int numPontos, int numConjuntos);

/**
 * Função que imprime os agrupamentos do vetor de conjuntos
 * @param saida Arquivo de saida
 * @param parent Vetor de elementos
 * @param rank Vetor de pesos
 * @param vetPontos Vetor de pontos
 * @param numPontos Quantidade de pontos
 */
void printAgrupamentos(FILE *saida, int parent[], int rank[], Ponto* vetPontos[], int numPontos);