#include "ponto.h"

typedef struct aresta Aresta;

Aresta* inicializaAresta(Ponto* p1, Ponto* p2, float peso);

// todo
void liberaAresta();

float getAresta(Aresta* a);