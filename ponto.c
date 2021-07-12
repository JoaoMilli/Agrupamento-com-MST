#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ponto.h"

struct ponto{
    char* nome;
    long double X;
    long double Y;
    int index; // Número que representa o ponto (como um código)
};

char* retornaNome (Ponto* ponto){
    return ponto->nome;
}

long double retornaX (Ponto* ponto){
    return ponto->X;
}

long double retornaY (Ponto* ponto){
    return ponto->Y;
}

int retornaIndex(Ponto* ponto){
    return ponto->index;
}

long double distanciaEuclidiana(Ponto* p1, Ponto* p2){
    return sqrt(pow(retornaX(p2) - retornaX(p1),2) + pow(retornaY(p2) - retornaY(p1),2));
}

Ponto* criaPonto (char* nome, long double X, long double Y, int index){
    Ponto* ponto = malloc(sizeof(Ponto));
    ponto -> nome = strdup(nome);
    ponto -> X = X;
    ponto -> Y = Y;
    ponto -> index = index;
    return ponto;
}

void destroiPonto (Ponto* ponto){
    if(ponto){
        if(ponto->nome){
            free(ponto -> nome);
        }
        free(ponto);
    }
}
