#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ponto.h"
#include "grupos.h"
#include "arestas.h"

typedef struct aresta{
    int indexPonto1;
    int indexPonto2;
    long double tamanho;
}Aresta;

struct arestas {
    Aresta **vetorArestas;
    int numPontos;
    int indiceMenorAresta; //Número que vai indicar o índice da próxima aresta a ser removida
};

////////////// Funções internas /////////////////

////////////// FUNÇÃO PARA TESTES //////////////
void imprimeArestas(Arestas* arestas){
    int i, j;
    for(i=0; i<(arestas->numPontos)*(arestas->numPontos - 1)/2; i++){ //Passa por todas as arestas
        Aresta* aresta = arestas->vetorArestas[i];
        printf("%d - %d / Tam - %Lf\n", aresta->indexPonto1, aresta->indexPonto2, aresta->tamanho);
    }
}

int comparadorTamanho(const void *a, const void *b) {
    //printf("Nulo\n");
    
    Aresta* a1 = *(Aresta**)a;
    Aresta* b1 = *(Aresta**)b;

    if(a1->tamanho < b1->tamanho){
        return -1;
    } else if(a1->tamanho == b1->tamanho) {
        return 0;
    } else {
        return 1;
    }
}


/* Preenche um vetor de arestas com as distâncias entre os pontos
* Entradas: arestas - ponteiro para o TAD das arestas // grupos - Struct que contém um vetor com todos os pontos (vértices) do grafo;
* Saídas: void;
* Pós-condições: As posições do vetorArestas em arestas são atualizadas com os as arestas;
*/
void calculaTodasArestas(Arestas* arestas, Grupos* grupos){
    
    int i, j, indice = 0;
    for(i=0; i<arestas->numPontos; i++){
        for(j=0; j<i; j++){ //Vai até i, que é o número de colunas da linha i
            //Cria uma aresta entre o ponto i e o ponto j
            Aresta *aresta = (Aresta*) malloc(sizeof(Aresta));
            aresta->indexPonto1 = i;
            aresta->indexPonto2 = j;
            aresta->tamanho = distanciaEuclidiana(retornaPontoPorIndex(grupos, i), retornaPontoPorIndex(grupos, j));
            
            arestas->vetorArestas[indice] = aresta;
            indice++;
        }
    }

    int numArestas = arestas->numPontos*(arestas->numPontos - 1)/2;
    qsort(arestas->vetorArestas, numArestas, sizeof(Aresta*), comparadorTamanho);
}

///////////// Funções Externas ////////////////

Arestas* criaArestas(Grupos* grupos){
    Arestas* arestas = (Arestas*) malloc(sizeof(Arestas));
    arestas->numPontos = retornaNumeroPontos(grupos);
    arestas->indiceMenorAresta = 0;
    arestas->vetorArestas = (Aresta**) malloc(sizeof(Aresta*) * (arestas->numPontos)*(arestas->numPontos - 1)/2);
    
    calculaTodasArestas(arestas, grupos);

    return arestas;
}

void removeMenorAresta(Arestas* arestas, int *id_vertice_1, int *id_vertice_2){
    if(arestas->indiceMenorAresta >= (arestas->numPontos*(arestas->numPontos - 1)/2) - 1) {
        printf("Erro ao tentar remover aresta fora do vetor!\n");
        return;
    }

    //Informa quais os vertices que compõem a menor aresta
    Aresta *menorAresta = arestas->vetorArestas[arestas->indiceMenorAresta];
    *id_vertice_1 = menorAresta->indexPonto1;
    *id_vertice_2 = menorAresta->indexPonto2;

    //Incrementa o contador para a próxima menor aresta
    arestas->indiceMenorAresta = arestas->indiceMenorAresta + 1;
}

Arestas* destroiArestas(Arestas* arestas){
    int i;
    for(i=0; i < (arestas->numPontos)*(arestas->numPontos - 1)/2 ; i++){
        free(arestas->vetorArestas[i]);
    }

    free(arestas->vetorArestas);
    free(arestas);

    return NULL;
}