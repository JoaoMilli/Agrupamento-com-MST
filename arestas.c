#include "arestas.h"
#include "ponto.h"
#include <stdlib.h>
#include <stdio.h>

// Uma matriz de doubles alocada dinamicamente com a posição i,j contendo a distância entre o ponto i e o ponto j
// Se uma posição tiver o valor -1.0, significa que essa aresta já foi removida
struct arestas {
    long double **matriz;
    int numPontos;
};

////////// Funções internas /////////////////

/* Preenche uma matriz triangular com as distâncias entre os pontos
* Entradas: arestas - ponteiro para o TAD das arestas // pontos - Vetor com todos os pontos (vértices) do grafo;
* Saídas: void;
* Pós-condições: As posições da matriz em arestas são atualizadas com os valores das distâncias;
*/
void calculaTodasArestas(Arestas* arestas, Ponto** pontos){
    int i, j;
    for(i=0; i<arestas->numPontos; i++){
        for(j=0; j<i; j++){ //Vai até i, que é o número de colunas da linha i
            arestas->matriz[i][j] = distanciaEuclidiana(pontos[i], pontos[j]);
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







///////// Funções Externas ////////////////


/* Inicializa o TAD com informação sobre todas as arestas entre os pontos passados
* Entradas: pontos - Vetor com todos os pontos (vértices) do grafo
* Saídas: Um ponteiro para o TAD criado, com o tamanho de todas as arestas já calculado
* Pós-condições: É alocado na memória o TAD Arestas e todas as informações sobre as arestas
*/
Arestas* criaArestas(Ponto** pontos, int numPontos){
    Arestas* arestas = (Arestas*) malloc(sizeof(Arestas));
    arestas->numPontos = numPontos;
    arestas->matriz = (long double**) malloc(sizeof(long double*)*numPontos);
    int i;
    for(i=0; i<numPontos; i++){
        //Aloca uma "matriz trinagular", sendo que a primeira linha tem zero colunas, a segunda tem uma e assim em diante
        arestas->matriz[i] = (long double*) malloc(sizeof(long double)*(i));
    }
    calculaTodasArestas(arestas, pontos);


    return arestas;
}


/* Remove a menor aresta ainda presente em "arestas"
* Entradas: arestas - Ponteiro para o TAD com as arestas
* Saídas: -;
* Pós-condições: A aresta de menor tamanho é removida de arestas (marcada com -1). 
*               Os conteudos de id_vertice_1 e 2 são alterados para os inteiros que representam os vértices componentes da aresta removida.
*/
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


/* Libera o TAD Arestas da memória
* Entradas: arestras - o ponteiro para o TAD a ser liberado
* Saídas: -;
* Pós-condições: A memória anteriormente alocada para arestas é liberada
*/
Arestas* destroiArestas(Arestas* arestas){
    int i;
    for(i=0; i<arestas->numPontos; i++){
        //Aloca uma "matriz trinagular", sendo que a primeira linha tem uma coluna, a segunda tem duas e assim em diante
        if(arestas->matriz[i]) free(arestas->matriz[i]);
    }
    if(arestas->matriz) free(arestas->matriz);
    free(arestas);
}




