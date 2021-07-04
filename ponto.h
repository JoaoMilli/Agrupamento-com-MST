#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto;

Ponto* criaPonto (char* nome, float X, float Y);
char* retornaNome (Ponto* ponto);
double retornaX (Ponto* ponto);
double retornaY (Ponto* ponto);
void destroiPonto (Ponto* ponto);


#endif