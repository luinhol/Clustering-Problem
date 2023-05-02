#include "ponto.h"
#include "stdlib.h"
#include "stdio.h"

struct ponto
{
    char* id;
    int number;
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