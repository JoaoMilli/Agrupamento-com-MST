#include "ponto.h"
#include <stdlib.h>
#include <string.h>

struct ponto{
    char* nome;
    double X;
    double Y;
    int index;
};

Ponto* criaPonto (char* nome, float X, float Y, int index){
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

double retornaX (Ponto* ponto){
    return ponto -> X;
}

double retornaY (Ponto* ponto){
    return ponto -> Y;
}

int retornaIndex(Ponto* ponto){
    return ponto -> index;
}

void destroiPonto (Ponto* ponto){
    free(ponto -> nome);
    free(ponto);
}
