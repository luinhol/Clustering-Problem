/** Define um um conjunto de funcoes de manipulacao de pontos, arestas e conjuntos.
 * @file kruskal.c
 * @author Lucas Pereira Taborda e Gabriel de Castro Lima
 */

#include "kruskal.h"

void init(int parent[], int rank[], int numPontos){
    int i;
    for (i = 0; i < numPontos; i++)
    {
        parent[i] = i;
        rank[i] = 1;
    }
}

int find(int parent[], int num){
    int i = num;
    while(parent[i] != i){
        i = parent[i];
    }
    return i;
}

bool connected(int parent[], int p, int q){
    return(find(parent, p) == find(parent, q));
}

void uni(int p, int q, int parent[], int rank[]){
    int idp = find(parent, p);
    int idq = find(parent, q);

    if(idp == idq){
        return;
    }

    if(rank[idp] < rank[idq]){
        parent[idp] = idq;
        rank[idq] += rank[idp];
    }
    else{
        parent[idq] = idp;
        rank[idp] += rank[idq];
    }
}

void kruskalAlgo(int parent[], int rank[], Aresta *vetArestas[], int tamanhoVetArestas, int numPontos, int numConjuntos)
{
    // declaracao de variaveis
    int i, j, v1, v2, wt, conjunto, numArestasRem = numConjuntos-1, numArestasConectadas = 0;

    // ordena o vetor de arestas
	qsort(vetArestas, tamanhoVetArestas, sizeof(Aresta*), arestComp);

    // inicia o Weighted Quick-Union
	init(parent, rank, numPontos);

    // percorre o vetor de arestas
	for (i = 0; i < tamanhoVetArestas; i++) {
        // encontra a raiz de p1 da aresta i
		v1 = find(parent, getNum(getp1(vetArestas[i])));
        // encontra a raiz de p2 da aresta i
		v2 = find(parent, getNum(getp2(vetArestas[i])));

        // verifica se as raizes de p1 e p2 sao diferentes
		if (v1 != v2) {
            // se sao de raizes(conjuntos) diferentes, realiza a uniao
			uni(v1, v2, parent, rank);
            // incrementa o numero de arestas conectadas
            numArestasConectadas++;
		}

        // verifica se o numero de arestas conectadas é exatamente o numero de arestas da MST - numArestasRemovidas
        if(numArestasConectadas == ((numPontos - 1) - numArestasRem)){
            break;
        }
	}
}

void printAgrupamentos(FILE *saida, int parent[], int rank[], Ponto* vetPontos[], int numPontos){
    int i, j;

    // percorre o vetor de elementos
    for (j = 0; j < numPontos; j++)
    {
        // verifica se o rank do elemento é 0 (caso ja tenha sido imprimido)
        if(rank[j] != 0){
            // imprime o primeiro elemento do conjunto
            fprintf(saida, "%s", getId(vetPontos[j]));

            // percorre o vetor de elementos verificando se o elemento i e j tem a mesma raiz
            for(i = j+1; i < numPontos; i++){
                // verifica se os elementos estao conectados
                if(connected(parent, j, i)){
                    // zera o rank do elemento
                    rank[i] = 0;
                    // imprime os elementos seguintes
                    fprintf(saida, ",%s", getId(vetPontos[i]));
                }
            }
            // imprime quebra de linha
            fprintf(saida, "\n");
        }
    }
}