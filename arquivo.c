#include "arquivo.h"
#include <sys/types.h>

/**
 * Função que retorna o numero de linhas validas do documento de entrada (numero de linhas que contem pontos)
 * @param entrada Arquivo de entrada
 * @return Numero de linhas com pontos
 */
int getNumLinhas(FILE *entrada)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    int lineno = 0;

    while (!feof_unlocked(entrada))
    {
        ssize_t n = getline(&line, &len, entrada);
        if (n <= 0)
        {
            // linha vazia ou final do arquivo
            break;
        }
        if (n > 1)
        {
            ++lineno;
        }
    }
    free(line);
    return lineno;
}


int getNumCoordenadas(FILE *entrada)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int numCoords = 0;

    ssize_t n = getline(&line, &len, entrada);
    if (n <= 0)
    {
        // linha vazia ou final do arquivo
        return 0;
    }

    pt = strtok(line, ",");

    while (pt != NULL)
    {
        pt = strtok(NULL, ",");
        numCoords++;
    }
    free(line);
    return numCoords-1;
}

void getPontos(FILE *entrada, Ponto **vet, int numCoords)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    int lineno = 0;
    char *pt;
    float* coords;

    char *id;
    int idSize = 0;
    int i;

    while (!feof_unlocked(entrada))
    {
        ssize_t n = getline(&line, &len, entrada);
        if (n <= 0)
        {
            // linha vazia ou final do arquivo
            break;
        }
        if (n > 1)
        {
            coords = (float*)malloc(sizeof(float*)*numCoords);

            // armazena a id do ponto
            pt = strtok(line, ",");
            id = strdup(pt);

            for(i = 0; i < numCoords; i++){
                pt = strtok(NULL, ",");
                coords[i] = atof(pt);
            }

            // insere ponto no vet na posicao lineno
            vet[lineno] = inicializaPonto(id, coords, lineno);

            lineno++;
        }
    }
    free(line);
}

void getArestas(Ponto **vetPontos, int numPontos, int numCoords, Aresta **vetArestas)
{
    int i, j, posicao = 0;
    float d = 0;

    for (i = 0; i < numPontos; i++)
    {
        for (j = i + 1; j < numPontos; j++)
        {
            d = dist(vetPontos[i], vetPontos[j], numCoords);
            vetArestas[posicao] = inicializaAresta(vetPontos[i], vetPontos[j], d);
            posicao++;
        }
    }
}