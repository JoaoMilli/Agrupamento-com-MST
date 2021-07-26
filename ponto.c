#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ponto.h"

struct ponto{
    char* nome;
    long double* coordenadas;
    int nCoord;
    int index; //Posição do ponto no vetor
    int groupID; //Identificador de outro ponto no mesmo grupo, mais próximo do root do grupo (o ponto que tem index = groupID)
};

Ponto* criaPonto (char* nome, long double* coordenadas, int index, int nCoord){
    Ponto* ponto = malloc(sizeof(Ponto));
    ponto->nCoord = nCoord;
    ponto->coordenadas = malloc(sizeof(long double) * nCoord);
    for(int i = 0; i<nCoord; i++){
        ponto->coordenadas[i] = coordenadas[i];
    }
    ponto->nome = strdup(nome);
    ponto->index = index; // Número que representa o ponto (como um código)
    ponto->groupID = index;
    return ponto;
}

char* retornaNome (Ponto* ponto){
    return ponto->nome;
}

int retornaIndex(Ponto* ponto){
    return ponto->index;
}

int retornaNCoord(Ponto* ponto){
    return ponto->nCoord;
}

long double distanciaEuclidiana(Ponto* p1, Ponto* p2){

    Ponto* menornCoord, *maiornCoord;
    int i;
    long double distQuadradas = 0;

    if (retornaNCoord(p1) > retornaNCoord(p2)){
        menornCoord = p2;
        maiornCoord = p1;
    }
    else {
        menornCoord = p1;
        maiornCoord = p2;
    }

    for (i=0; i<retornaNCoord(menornCoord); i++){
        distQuadradas += pow(p1->coordenadas[i] - p2->coordenadas[i],2);
    }
    while(i < retornaNCoord(maiornCoord)){
        distQuadradas += pow(maiornCoord->coordenadas[i],2);
    }

    return sqrt(distQuadradas);
}

int retornaID(Ponto* ponto){
    return ponto->groupID;
}

void mudaID(Ponto* ponto, int groupID){
    ponto->groupID = groupID;
}

void destroiPonto (Ponto* ponto){
    if(ponto){
        if(ponto->nome){
            free(ponto -> nome);
        }
        if(ponto->coordenadas){
            free(ponto->coordenadas);
        }
        free(ponto);
    }
}
