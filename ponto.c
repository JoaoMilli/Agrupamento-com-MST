#include "ponto.h"
#include <stdlib.h>
#include <string.h>

struct ponto{
    char* nome;
    double X;
    double Y;
};

Ponto* criaPonto (char* nome, float X, float Y){
    Ponto* ponto = malloc(sizeof(Ponto));
    ponto -> nome = strdup(nome);
    ponto -> X = X;
    ponto -> Y = Y;
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

void destroiPonto (Ponto* ponto){
    free(ponto -> nome);
    free(ponto);
}
