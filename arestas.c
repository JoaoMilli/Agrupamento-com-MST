#include "arestas.h"
#include "ponto.h"
#include <stdlib.h>

// Uma matriz de doubles alocada dinamicamente com a posição i,j contendo a distância entre o ponto i e o ponto j
struct arestas {
    double **matriz;
    int numPontos;
};

////////// Funções internas /////////////////

void calculaTodasArestas(Arestas* arestas, Ponto** pontos){
    
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
    arestas->matriz = (double**) malloc(sizeof(double*)*numPontos);
    int i;
    for(i=0; i<numPontos; i++){
        //Aloca uma "matriz trinagular", sendo que a primeira linha tem uma coluna, a segunda tem duas e assim em diante
        arestas->matriz[i] = (double*) malloc(sizeof(double)*(i+1));
    }
    calculaTodasArestas(arestas, pontos);

    return arestas;
}


/* Remove a menor aresta ainda presente em "arestas"
* Entradas: arestas - Ponteiro para o TAD com as arestas
* Saídas: -;
* Pós-condições: A aresta de menor tamanho é removida de arestas. 
*               Os conteudos de id_vertice_1 e 2 são alterados para os inteiros que representam os vértices componentes da aresta removida.
*/
void removeMenorAresta(Arestas* arestas, int *id_vertice_1, int *id_vertice_2);


/* Libera o TAD Arestas da memória
* Entradas: arestras - o ponteiro para o TAD a ser liberado
* Saídas: -;
* Pós-condições: A memória anteriormente alocada para arestas é liberada
*/
Arestas* destroiArestas(Arestas* arestas);




