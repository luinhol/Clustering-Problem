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

int conteudo(int parent[], int p){
    return parent[p];
}

// constroi a mst e já remove os numConjuntos-1 vértices
void kruskalAlgo(int parent[], int rank[], Aresta *vetArestas[], int tamanhoVetArestas, int numPontos, int numConjuntos)
{
    int i, j, v1, v2, wt, conjunto, numArestasRem = numConjuntos-1, numArestasConectadas = 0;

	qsort(vetArestas, tamanhoVetArestas, sizeof(Aresta*), arestComp);

	init(parent, rank, numPontos);

	for (i = 0; i < tamanhoVetArestas; i++) {
		v1 = find(parent, getNum(getp1(vetArestas[i])));
		v2 = find(parent, getNum(getp2(vetArestas[i])));
		wt = getPeso(vetArestas[i]);

		if (v1 != v2) {
			uni(v1, v2, parent, rank);
            numArestasConectadas++;
		}

        if(numArestasConectadas == ((numPontos - 1) - numArestasRem)){
            break;
        }
	}

    // printf("\nvertices:  ");
    // for (i = 'A'; i <= 'J'; i++)
    // {
    //     printf("%c ", i);
    // }
    // printf("\nparent:    ");
    // for (i = 0; i < numPontos; i++)
    // {
    //     printf("%d ", parent[i]);
    // }
    // printf("\nraizes:    ");
    // for (i = 0; i < numPontos; i++)
    // {
    //     printf("%d ", find(parent, i));
    // }
    // printf("\nranks:     ");
    // for (i = 0; i < numPontos; i++)
    // {
    //     printf("%d ", rank[i]);
    // }
}

void printAgrupamentos(int parent[], int rank[], Ponto* vetPontos[], int numPontos){
    int i, j;

    for (j = 0; j < numPontos; j++)
    {
        if(rank[j] != 0){
            printf("%s", getId(vetPontos[j]));
            for(i = j+1; i < numPontos; i++){
                if(connected(parent, j, i)){
                    rank[i] = 0;
                    printf(",%s", getId(vetPontos[i]));
                }
            }
            printf("\n");
        }
    }
}