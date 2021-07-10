#include "ponto.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct ponto{
    char* nome;
    long double X;
    long double Y;
    int index;
};

Ponto* criaPonto (char* nome, long double X, long double Y, int index){
    Ponto* ponto = malloc(sizeof(Ponto));
    ponto -> nome = strdup(nome);
    ponto -> X = X;
    ponto -> Y = Y;
    ponto -> index = index;
    return ponto;
}

char* retornaNome (Ponto* ponto){
    return ponto -> nome;
}

long double retornaX (Ponto* ponto){
    return ponto -> X;
}

long double retornaY (Ponto* ponto){
    return ponto -> Y;
}

int retornaIndex(Ponto* ponto){
    return ponto -> index;
}

long double distanciaEuclidiana(Ponto* p1, Ponto* p2){
    return sqrt(pow(retornaX(p2) - retornaX(p1),2) + pow(retornaY(p2) - retornaY(p1),2));
}

void destroiPonto (Ponto* ponto){
    free(ponto -> nome);
    free(ponto);
}
