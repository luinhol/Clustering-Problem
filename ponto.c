#include "ponto.h"
#include "stdlib.h"
#include "stdio.h"

struct ponto
{
    char* id;
    int number;
    float x;
    float y;
};

Ponto* inicializaPonto(char* identificador, float x, float y, int num){
    Ponto* p = (Ponto*)malloc(sizeof(Ponto));
    p->id = identificador;
    p->number = num;
    p->x = x;
    p->y = y;
    return p;
}

void liberaPonto(Ponto* p){
    free(p->id);
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

float getX(Ponto* p){
    return p->x;
}

float getY(Ponto* p){
    return p->y;
}

int pontoComp(const void* a, const void* b) {
    Ponto* arg1 = *(Ponto**)a;
    Ponto* arg2 = *(Ponto**)b;

    return strcmp(getId(arg1), getId(arg2));
}