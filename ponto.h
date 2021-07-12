#ifndef PONTO_H
#define PONTO_H

/* Tipo opaco; Struct ponto
* Informações do ponto (X, Y) no plano
*/
typedef struct ponto Ponto;

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

/* Inicializa um ponto (X, Y) no plano
* Entradas: Nome do ponto, coordenadas X e Y e índice 
* Saídas: Ponto 
* Pós-condições: Ponto existe no plano
*/
Ponto* criaPonto (char* nome, long double  X, long double Y, int index);

/* Calcula a distância entre dois pontos no plano
* Entradas: Dois pontos
* Saídas: Distância euclidiana
* Pós-condições: -
*/
long double distanciaEuclidiana(Ponto* p1, Ponto* p2);

/* Libera a memória de um ponto 
* Entradas: Ponto a ser liberado
* Saídas: -
* Pós-condições: Ponto não existe mais
*/
void destroiPonto (Ponto* ponto);

#endif /* PONTO_H */