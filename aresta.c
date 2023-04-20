#include "aresta.h"

struct aresta
{
    Ponto* p1;
    Ponto* p2;
    float peso;
};

Aresta* inicializaAresta(Ponto* p1, Ponto* p2, float peso){
    
}

// todo
void liberaAresta(){

}

float getAresta(Aresta* a){
    return a->peso;
}