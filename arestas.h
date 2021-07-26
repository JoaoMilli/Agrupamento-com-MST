#ifndef ARESTAS_H
#define ARESTAS_H
#include "grupos.h"
#include "ponto.h"

/* Tipo opaco; Struct arestas
* Uma matriz de doubles alocada dinamicamente com a posição i,j contendo a distância entre o ponto i e o ponto j
* Se uma posição tiver o valor -1.0, significa que essa aresta já foi removida
*/
typedef struct arestas Arestas;

/* Inicializa o TAD com informação sobre todas as arestas entre os pontos passados
* Entradas: grupos - Struct que contém um vetor com todos os pontos (vértices) do grafo;
* Saídas: Um ponteiro para o TAD criado, com o tamanho de todas as arestas já calculado
* Pós-condições: É alocado na memória o TAD Arestas e todas as informações sobre as arestas
*/
Arestas* criaArestas(Grupos* grupos);

/* Remove a menor aresta ainda presente em "arestas"
* Entradas: arestas - Ponteiro para o TAD com as arestas
* Saídas: -;
* Pós-condições: A aresta de menor tamanho é removida de arestas. Os conteudos de id_vertice_1 e 2 são alterados para os inteiros que representam os vértices componentes da aresta removida.
*/
void removeMenorAresta(Arestas* arestas, int *id_vertice_1, int *id_vertice_2);

/* Libera o TAD Arestas da memória
* Entradas: arestras - o ponteiro para o TAD a ser liberado
* Saídas: -;
* Pós-condições: A memória anteriormente alocada para arestas é liberada
*/
Arestas* destroiArestas(Arestas* arestas);

#endif /* ARESTAS_H */