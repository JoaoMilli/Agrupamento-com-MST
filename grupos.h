#ifndef GRUPOS_H
#define GRUPOS_H

#include "ponto.h"

typedef struct grupos Grupos;

///////////////////////////
// Getters ////////////////
///////////////////////////

/* Retorna um ponteiro para o ponto de index (posiçao no vetor) igual a index
* Entradas: grupos - TAD que contém todos os pontos // index - inteiro que representa a posição do ponto no vetor (sua posição no arquivo de entrada)
* Saídas: Um ponteiro para o Ponto desejado
* Pós-condições: -;
*/
Ponto* retornaPontoPorIndex(Grupos* grupos, int index);

/* Retorna um inteiro que representa o número total de pontos lidos no arquivo de entrada
* Entradas: grupos - TAD que contém todos os pontos;
* Saídas: Um inteiro que representa o número total de pontos lidos no arquivo de entrada
* Pós-condições: -;
*/
int retornaNumeroPontos(Grupos* grupos);

/* Retorna um vetor de inteiros que representa o tamanho dos grupos. Sendo o tamanho do grupo de ID n, o vetor retornado na posição n
* Entradas: grupos - TAD que contém todos os pontos;
* Saídas: O vetor que representa os tamanhos dos grupos
* Pós-condições: -;
*/
int* retornaTamanhoGrupos(Grupos* grupos);



///////////////////////////
// Controle do TAD grupos /
///////////////////////////

/* Cria uma instância do TAD grupos. Alocando memória para o TAD e para o vetor de tamanhos. 
*  O vetor de pontos passado tem apenas seu ponteiro copiado, portanto não aloca memória nova e depende que esse vetor não seja liberada por fora do TAD
* Entradas: vetorPontos - vetor de pontos já alocado e preenchido com os pontos lidos // numeroDePontos - inteiro que informa o número de pontos lidos;
* Saídas: Um ponteiro para o struct Grupos criado
* Pós-condições: Memória para o struct e para o vetor de tamanhos é alocada. Vetor de tamanhos inicializado com 1 em todas as posições;
*/
Grupos* inicializaGrupos(Ponto** vetorPontos, int numeroDePontos);

/* Libera toda a memória utilizada pelo struct grupos passado, inclusive o vetor para os pontos que é parâmetro durante a criação da struct.
* Entradas: grupos - TAD que contém todos os pontos;
* Saídas: Um ponteiro NULL
* Pós-condições: Memória para o struct, para o vetor de tamanhos e para o vetor de pontos é liberada.
*/
Grupos* destroiGrupos(Grupos *grupos);



///////////////////////////
// Union-Find /////////////
///////////////////////////

/* Retorna o ponto root (raiz) do grupo do ponto representado por index
* Entradas: grupos - TAD que contém todos os pontos // 
*           index - inteiro que representa a posição do ponto - que se quer descobrir o grupo - no vetor (sua posição no arquivo de entrada)
* Saídas: Um ponteiro para o Ponto root do grupo. O ID deste ponto retornado é o ID do grupo do ponto informado por index
* Pós-condições: A árvore de grupos é levemente otimizada, diminuindo a sua altura por onde o algoritmo passa, se possível;
*/
Ponto* UF_Find(Grupos* grupos, int index);

/* Une os grupos dos dois pontos passados
* Entradas: grupos - TAD que contém todos os pontos // 
*           p1 e p2 - Ponteiros para os dois pontos que terão seus grupos unidos;
* Saídas: -;
* Pós-condições: As informações sobre os grupos são atualizadas em "grupos", associando o menor grupo sob o maior grupo dentre o de p1 e p2;
*/
void UF_Union(Grupos* grupos, Ponto* p1, Ponto* p2);


#endif