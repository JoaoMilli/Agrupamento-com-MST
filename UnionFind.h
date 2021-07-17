#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "ponto.h"

//Ponto* UF_union(Ponto** vetor, Ponto* p1, Ponto* p2);

Ponto* UF_find(Ponto** vetor, int ID);
void UF_Union(Ponto** vetor, int size, Ponto* p1, Ponto* p2);


#endif