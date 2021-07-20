#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ponto.h"

struct ponto{
    char* nome;
    long double X;
    long double Y;
    int index; //Posição do ponto no vetor
    int groupID; //Identificador de outro ponto no mesmo grupo, mais próximo do root do grupo (o ponto que tem index = groupID)
};

Ponto* criaPonto (char* nome, long double X, long double Y, int index){
    Ponto* ponto = malloc(sizeof(Ponto));
    ponto->nome = strdup(nome);
    ponto->X = X;
    ponto->Y = Y;
    ponto->index = index; // Número que representa o ponto (como um código)
    ponto->groupID = index;
    return ponto;
}

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

int retornaID(Ponto* ponto){
    return ponto->groupID;
}

void mudaID(Ponto* ponto, int groupID){
    ponto->groupID = groupID;
}

void imprimePonto(Ponto* ponto){
    printf("%s, %Lf, %Lf, %d, %d\n", retornaNome(ponto), retornaX(ponto), retornaY(ponto), retornaIndex(ponto), retornaID(ponto));
}

void destroiPonto (Ponto* ponto){
    if(ponto){
        if(ponto->nome){
            free(ponto -> nome);
        }
        free(ponto);
    }
}
