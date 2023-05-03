/** Define um tad Ponto.
 * @file ponto.c
 * @author Lucas Pereira Taborda e Gabriel de Castro Lima
 */

#include "ponto.h"
#include "stdlib.h"
#include "stdio.h"

struct ponto
{
    // Nome do ponto
    char* id;
    // Indice do ponto no vet pontos
    int number;
    // Vetor com as coordenadas do ponto
    float* coords;
};

Ponto* inicializaPonto(char* identificador, float* coords, int num){
    Ponto* p = (Ponto*)malloc(sizeof(Ponto));
    p->id = identificador;
    p->number = num;
    p->coords = coords;
    return p;
}

void liberaPonto(Ponto* p){
    free(p->id);
    free(p->coords);
    free(p);
}

char* getId(Ponto* p){
    return p->id;
}

int getNum(Ponto* p){
    return p->number;
}

void setNum(Ponto* p, int num){
    p->number = num;
}

float getCoord(Ponto* p, int k){
    return p->coords[k];
}

int pontoComp(const void* a, const void* b) {
    Ponto* arg1 = *(Ponto**)a;
    Ponto* arg2 = *(Ponto**)b;

    return strcmp(getId(arg1), getId(arg2));
}

float dist(Ponto *p1, Ponto *p2, int numCoords)
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

void liberaPontos(Ponto **vetPontos, int numPontos){
    int i;
    for(i = 0; i < numPontos; i++){
        liberaPonto(vetPontos[i]);
    }
}