#include "aresta.h"

struct aresta
{
    Ponto* p1;
    Ponto* p2;
    float peso;
};

Aresta* inicializaAresta(Ponto* p1, Ponto* p2, float peso){
    Aresta* a = (Aresta*)malloc(sizeof(Aresta));
    a->p1 = p1;
    a->p2 = p2;
    a->peso = peso;
    return a;
}

// todo
void liberaAresta(Aresta* a){
    free(a);
}

float getPeso(Aresta* a){
    return a->peso;
}

Ponto* getp1(Aresta* a){
    return a->p1;
}

Ponto* getp2(Aresta* a){
    return a->p2;
}

int arestComp(const void* a, const void* b) {
    Aresta* arg1 = *(Aresta**)a;
    Aresta* arg2 = *(Aresta**)b;

    if(getPeso(arg1) < getPeso(arg2)){
        return -1;
    }
    else if(getPeso(arg1) > getPeso(arg2)){
        return 1;
    }
    else{
        return 0;
    }
}