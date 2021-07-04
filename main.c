#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ponto** leEntrada(){
    FILE* file = fopen("entrada.txt", "r");
    if (file == NULL) return NULL;

    int count = 0;
    size_t buffer = 100;
    char* linha = malloc(sizeof(char)*buffer);
    char* token;
    char* nome;
    double X, Y;


    while (getline (&linha, &buffer, file) != -1) count++; 

    Ponto** ponto = malloc(sizeof(Ponto*)*(count+1));

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < count; i++){

        getline (&linha, &buffer, file);
        token = strtok(linha, ",");

        nome = strdup(token);

        token = strtok(NULL, ",");
        X = atof(token);

        token = strtok(NULL, ",\n");
        Y = atof(token);

        ponto[i] = criaPonto(nome, X, Y);
    }

    ponto[count] == NULL;

    free(linha);
    
    return ponto;
}


int main(){

    Ponto** vetorPonto = leEntrada();
    int i = 0;
    while (vetorPonto[i] != NULL){
        i++;
    }
    return 0;
}