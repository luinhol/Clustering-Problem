#include "ponto.h"

typedef struct aresta Aresta;

Aresta* inicializaAresta(Ponto* p1, Ponto* p2, float peso);

// todo
void liberaAresta(Aresta* a);

float getPeso(Aresta* a);

Ponto* getp1(Aresta* a);

Ponto* getp2(Aresta* a);

int arestComp(const void* a, const void* b);