#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ponto** leEntrada(int* count){

    FILE* file = fopen("entrada.txt", "r");
    if (file == NULL){
        printf("Arquivo de entrada não encontrado\n");
        return NULL;
    }

    size_t buffer = 100; //unsigned int contendo o tamanho da string que recebera as linhas da entrada (tipo padrao do getiline)
    char* linha = malloc(sizeof(char)*buffer);
    char* token;
    char* nome;
    double X, Y;

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
    }

    free(linha);
    
    return ponto;
}


int main(){

    int* count = malloc(sizeof(int));
    *count = 0;
    Ponto** vetorPonto = leEntrada(count);
    for(int i = 0; i < *count; i++){
        printf("%s, %f, %f, %d\n", retornaNome(vetorPonto[i]), retornaX(vetorPonto[i]), retornaY(vetorPonto[i]), retornaIndex(vetorPonto[i]));
    }
    free(count);
    return 0;
}