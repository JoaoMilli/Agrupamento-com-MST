#include <stdlib.h>
#include <stdio.h>
#include "ponto.h"
#include "grupos.h"
#include "arestas.h"


struct arestas {
    long double **matriz;
    int numPontos;
};

////////////// Funções internas /////////////////

/* Preenche uma matriz triangular com as distâncias entre os pontos
* Entradas: arestas - ponteiro para o TAD das arestas // pontos - Vetor com todos os pontos (vértices) do grafo;
* Saídas: void;
* Pós-condições: As posições da matriz em arestas são atualizadas com os valores das distâncias;
*/
void calculaTodasArestas(Arestas* arestas, Grupos* grupos){
    int i, j;
    for(i=0; i<arestas->numPontos; i++){
        for(j=0; j<i; j++){ //Vai até i, que é o número de colunas da linha i
            arestas->matriz[i][j] = distanciaEuclidiana(retornaPontoPorIndex(grupos, i), retornaPontoPorIndex(grupos, j));
        }
    }
}

////////////// FUNÇÃO PARA TESTES //////////////
void imprimeArestas(Arestas* arestas){
    int i, j;
    for(i=0; i<arestas->numPontos; i++){
        for(j=0; j<i; j++){ //Vai até i, que é o número de colunas da linha i
            printf("%Lf ", arestas->matriz[i][j]);
        }
        printf("\n");
    }
}

///////////// Funções Externas ////////////////

Arestas* criaArestas(Grupos* grupos){
    Arestas* arestas = (Arestas*) malloc(sizeof(Arestas));
    arestas->numPontos = retornaNumeroPontos(grupos);
    arestas->matriz = (long double**) malloc(sizeof(long double*)*arestas->numPontos);
    int i;
    for(i=0; i<arestas->numPontos; i++){
        //Aloca uma "matriz trinagular", sendo que a primeira linha tem zero colunas, a segunda tem uma e assim em diante
        arestas->matriz[i] = (long double*) malloc(sizeof(long double)*(i));
    }
    calculaTodasArestas(arestas, grupos);

    return arestas;
}

void removeMenorAresta(Arestas* arestas, int *id_vertice_1, int *id_vertice_2){
    //Busca a menor aresta
    int i, j;
    long double aresta, menorAresta=-1.0;
    for(i=0; i<arestas->numPontos; i++){
        for(j=0; j<i; j++){ //Vai até i, que é o número de colunas da linha i
            aresta = arestas->matriz[i][j];
            if(aresta != -1.0){
                if(menorAresta == -1.0){
                    menorAresta = aresta;
                    *id_vertice_1 = i;
                    *id_vertice_2 = j;
                } else if(aresta < menorAresta){
                    menorAresta = aresta;
                    *id_vertice_1 = i;
                    *id_vertice_2 = j;
                }
            }
        }
    }
    //Marca a menor aresta como removida
    arestas->matriz[*id_vertice_1][*id_vertice_2] = -1.0;
}

Arestas* destroiArestas(Arestas* arestas){
    int i;
    for(i=0; i<arestas->numPontos; i++){
        //Aloca uma "matriz trinagular", sendo que a primeira linha tem uma coluna, a segunda tem duas e assim em diante
        if(arestas->matriz[i]) free(arestas->matriz[i]);
    }
    if(arestas->matriz) free(arestas->matriz);
    free(arestas);

    return NULL;
}