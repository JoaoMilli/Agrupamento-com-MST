#ifndef GRUPOS_H
#define GRUPOS_H

#include "ponto.h"

typedef struct grupos Grupos;

Grupos* inicializaGrupos(Ponto** vetorPontos, int numeroDePontos);
Ponto* UF_Find(Grupos* grupos, int index);
void UF_Union(Grupos* grupos, Ponto* p1, Ponto* p2);

Ponto* retornaPontoPorIndex(Grupos* grupos, int index);
int retornaNumeroPontos(Grupos* grupos);

int* retornaTamanhoGrupos(Grupos* grupos);

Grupos* destroiGrupos(Grupos *grupos);


#endif