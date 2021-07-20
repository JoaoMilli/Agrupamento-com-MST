#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "arestas.h"
#include "grupos.h"

Ponto** leEntrada(char* entrada, int* count){

    FILE* file = fopen(entrada, "r");
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

/*algorithm Kruskal(G) is
    F:= ∅
    for each v ∈ G.V do
        MAKE-SET(v)
    for each (u, v) in G.E ordered by weight(u, v), increasing do
        if FIND-SET(u) ≠ FIND-SET(v) then
            F:= F ∪ {(u, v)} ∪ {(v, u)}
            UNION(FIND-SET(u), FIND-SET(v))
    return F*/

void Kruskal (Grupos* grupos, int k){
    Arestas* arestas = criaArestas(grupos);
    int numeroArvores = retornaNumeroPontos(grupos), idVertice1, idVertice2;
    
    while(numeroArvores > k){
        removeMenorAresta(arestas, &idVertice1, &idVertice2);
        
        if (UF_Find(grupos, idVertice1) != UF_Find(grupos, idVertice2)){
            UF_Union(grupos, retornaPontoPorIndex(grupos, idVertice1), retornaPontoPorIndex(grupos, idVertice2));
            
            numeroArvores--;
        }
    }

    destroiArestas(arestas);
}

int main(int argc, char** argv){

    char *entrada, *saida;
    entrada = argv[1];
    saida = argv[3];
    
    int k = atoi(argv[2]);

    int i, count = 0;
    Ponto** pontos = leEntrada(entrada, &count);
    Grupos* grupos = inicializaGrupos(pontos, count);

    Kruskal(grupos, k);
    
    ////////testes/////////
    //printf("%d\n", retornaNumeroPontos(grupos));
    //printf("Distancia entre os dois primeiros pontos eh: %Lf\n\n", distanciaEuclidiana(retornaPontoPorIndex(grupos, 1), retornaPontoPorIndex(grupos, 0)));


    printf("------\nTodos os pontos:\n");
    for(i = 0; i < count; i++){
        imprimePonto(retornaPontoPorIndex(grupos, i));
    }


    //Liberar a memória
    destroiGrupos(grupos);
    return 0;
}