#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct ponto Ponto;

Ponto* inicializaPonto(char* identificador, float x, float y, int num);

void liberaPonto(Ponto* p);

char* getId(Ponto* p);

int getNum(Ponto* p);

float getX(Ponto* p);

float getY(Ponto* p);