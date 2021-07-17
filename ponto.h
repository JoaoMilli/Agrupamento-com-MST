#ifndef PONTO_H
#define PONTO_H

/* Tipo opaco; Struct ponto
* Informações do ponto (X, Y) no plano
*/

typedef struct ponto Ponto;

/* Inicializa um ponto (X, Y) no plano
* Entradas: Nome do ponto, coordenadas X e Y e índice 
* Saídas: Ponto 
* Pós-condições: Ponto existe no plano
*/

Ponto* criaPonto (char* nome, long double  X, long double Y, int index);

/* Retorna nome do ponto (X, Y)
* Entradas: Ponto
* Saídas: Nome do ponto
* Pós-condições: -
*/

char* retornaNome (Ponto* ponto);

/* Retorna X do ponto (X, Y)
* Entradas: Ponto
* Saídas: X do ponto
* Pós-condições: -
*/

long double retornaX (Ponto* ponto);

/* Retorna Y do ponto (X, Y)
* Entradas: Ponto
* Saídas: Y do ponto
* Pós-condições: -
*/

long double retornaY (Ponto* ponto);

/* Retorna índice do ponto (X, Y)
* Entradas: Ponto
* Saídas: Índice do ponto   
* Pós-condições: -
*/

int retornaIndex(Ponto* ponto);

/* Calcula a distância entre dois pontos no plano
* Entradas: Dois pontos
* Saídas: Distância euclidiana
* Pós-condições: -
*/

long double distanciaEuclidiana(Ponto* p1, Ponto* p2);

/* Retorna o ID do ponto (X, Y)
* Entradas: Ponto
* Saídas: ID do ponto   
* Pós-condições: -
*/

int retornaID(Ponto* ponto);

/* Muda o ID do ponto (X, Y)
* Entradas: Ponto com o novo ID
* Saídas: -
* Pós-condições: Ponto com ID modificado
*/

void mudaID(Ponto* ponto, int ID);

/* Imprime dados do ponto (X, Y)
* Entradas: Ponto a ser impresso
* Saídas: Dados do ponto impressos
* Pós-condições: -
*/

void imprimePonto(Ponto* ponto);

/* Libera a memória de um ponto 
* Entradas: Ponto a ser liberado
* Saídas: -
* Pós-condições: Ponto não existe mais
*/

void destroiPonto (Ponto* ponto);

#endif /* PONTO_H */