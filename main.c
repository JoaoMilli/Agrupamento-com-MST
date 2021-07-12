#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "arestas.h"

Ponto** leEntrada(int* count){

    FILE* file = fopen("entrada.txt", "r");
    if (file == NULL){
        printf("Arquivo de entrada não encontrado\n");
        return NULL;
    }

    size_t buffer = 100; //unsigned int contendo o tamanho da string que recebera as linhas da entrada (tipo padrao do getiline)
    char* linha = malloc(sizeof(char)*buffer);
    char* token = NULL;
    char* nome = NULL;
    long double X, Y;

    /*Conta o numero de linhas contidas no arquivo de entrada, necessario para alocacao de espaco para o vetor contendo os ponteiros do tipo ponto*/
    while (getline (&linha, &buffer, file) != -1) (*count)++; 

    Ponto** ponto = malloc(sizeof(Ponto*) * (*count));

    /*Reseta o ponteiro de leitura para o incio do arquivo de entrada, para agora obter os dados*/
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < *count; i++){

        getline (&linha, &buffer, file);

        /*Obtem-se cada elemento que eh separado por virgula*/
        token = strtok(linha, ",");       

        nome = strdup(token);

        token = strtok(NULL, ",");
        X = atof(token);

        token = strtok(NULL, ",\n");
        Y = atof(token);

        ponto[i] = criaPonto(nome, X, Y, i);
        if(nome) free(nome);
    }

    if(linha) free(linha);
    fclose(file);
    
    return ponto;
}

int main(){

    int i, count = 0;
    Ponto** vetorPonto = leEntrada(&count);
    printf("Distancia entre os dois primeiros pontos eh: %Lf\n\n", distanciaEuclidiana(vetorPonto[1], vetorPonto[0]));
    Arestas* arestas = criaArestas(vetorPonto, count);

    for(i = 0; i < count; i++){
        printf("%s, %Lf, %Lf, %d\n", retornaNome(vetorPonto[i]), retornaX(vetorPonto[i]), retornaY(vetorPonto[i]), retornaIndex(vetorPonto[i]));
        destroiPonto (vetorPonto[i]);
    }

    destroiArestas(arestas);
    free(vetorPonto);
    return 0;
}