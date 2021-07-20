#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "arestas.h"
#include "grupos.h"

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

    Ponto** pontos = malloc(sizeof(Ponto*) * (*count));

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

        pontos[i] = criaPonto(nome, X, Y, i);
        if(nome) free(nome);
    }

    if(linha) free(linha);
    fclose(file);
    
    return pontos;
}

int main(){

    int i, count = 0;
    Ponto** pontos = leEntrada(&count);
    Grupos* grupos = inicializaGrupos(pontos, count);
    printf("%d\n", retornaNumeroPontos(grupos));
    printf("Distancia entre os dois primeiros pontos eh: %Lf\n\n", distanciaEuclidiana(retornaPontoPorIndex(grupos, 1), retornaPontoPorIndex(grupos, 0)));
    Arestas* arestas = criaArestas(grupos);


    ///////////////// Teste do union find

    Ponto* teste1 = UF_Find(grupos, 0);
    Ponto* teste2 = UF_Find(grupos, 1);
    imprimePonto(teste1);
    imprimePonto(teste2);

    UF_Union(grupos, teste1, teste2);
    UF_Union(grupos, retornaPontoPorIndex(grupos, 2), teste2);

    UF_Union(grupos, retornaPontoPorIndex(grupos, 3), retornaPontoPorIndex(grupos, 4));
    UF_Union(grupos, retornaPontoPorIndex(grupos, 4), retornaPontoPorIndex(grupos, 0));

    printf("------\nTodos os pontos:\n");
    for(i = 0; i < count; i++){
        imprimePonto(retornaPontoPorIndex(grupos, i));
    }


    //Liberar a memória
    destroiArestas(arestas);
    destroiGrupos(grupos);
    return 0;
}