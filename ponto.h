#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto;

Ponto* criaPonto (char* nome, long double  X, long double Y, int index);
char* retornaNome (Ponto* ponto);
long double retornaX (Ponto* ponto);
long double retornaY (Ponto* ponto);
int retornaIndex(Ponto* ponto);
long double distanciaEuclidiana(Ponto* p1, Ponto* p2);
int retornaID(Ponto* ponto);
void mudaID(Ponto* ponto, int ID);
void imprimePonto(Ponto* ponto);
void destroiPonto (Ponto* ponto);

#endif