#include "arquivo.h"
#include <sys/types.h>

int getNumLinhas(FILE *entrada)
{
    fseek(entrada, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    int lineno = 0;

    // enquanto nao chega ao final do arquivo
    while (!feof_unlocked(entrada))
    {
        // le a linha correspondente
        ssize_t n = getline(&line, &len, entrada);
        if (n <= 0)
        {
            // linha vazia ou final do arquivo
            break;
        }
        if (n > 1)
        {
            // se a linha tiver tamanho > 1, incrementa o numero de linhas
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

    // le a primeira linha do arquivo
    ssize_t n = getline(&line, &len, entrada);
    if (n <= 0)
    {
        // linha vazia ou final do arquivo
        return 0;
    }

    // le o id do ponto mas nao utiliza para nada
    pt = strtok(line, ",");

    // loop lendo a quantidade de coordenadas
    while (pt != NULL)
    {
        pt = strtok(NULL, ",");
        // incrementa coordenadas
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

    // enquanto nao chega ao final do arquivo
    while (!feof_unlocked(entrada))
    {
        // faz a leitura da linha
        ssize_t n = getline(&line, &len, entrada);
        if (n <= 0)
        {
            // linha vazia ou final do arquivo
            break;
        }
        // se nao for uma linha nula
        if (n > 1)
        {
            // aloca espaco para as coordenadas do ponto
            coords = (float*)malloc(sizeof(float*)*numCoords);

            // armazena a id do ponto
            pt = strtok(line, ",");
            id = strdup(pt);

            // realiza a leitura das coordenadas, inserindo no vetor
            for(i = 0; i < numCoords; i++){
                pt = strtok(NULL, ",");
                coords[i] = atof(pt);
            }

            // insere ponto no vet na posicao lineno
            vet[lineno] = inicializaPonto(id, coords, lineno);

            // incrementa a linha
            lineno++;
        }
    }
    free(line);
}