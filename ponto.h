#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto;

Ponto* criaPonto (char* nome, float X, float Y, int index);
char* retornaNome (Ponto* ponto);
double retornaX (Ponto* ponto);
double retornaY (Ponto* ponto);
int retornaIndex(Ponto* ponto);
void destroiPonto (Ponto* ponto);


#endif