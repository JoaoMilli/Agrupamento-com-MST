#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ponto.h"
#include "arestas.h"
#include "grupos.h"


int comparadorPrimeiraLetra(const void *a, const void *b) {
    //Verifica se são entradas válidas
    if(!(Ponto**)a || !(Ponto**)b){
        printf("Erro na comparação!");
        return 0;
    }
    
    //Pega o primeiro elemento dos grupos a serem comparados
    Ponto* a1 = ((Ponto**)a)[0];
    Ponto* b1 = ((Ponto**)b)[0];

    //Compara os nomes dos primeiros elementos
    return strcmp(retornaNome(a1), retornaNome(b1));
}

void merge(Ponto** pontos, int lo, int m, int hi) {

    int i, j, k;
    int n1 = m - lo + 1;
    int n2 = hi - m;

    // Cria vetores de ponteiros para ponto auxiliares, um para cada metade do vetor

    Ponto** L = malloc(sizeof(Ponto*) * n1);
    Ponto** R = malloc(sizeof(Ponto*) * n2);

    // Copia os dados de cada metade do vetor pontos para o auxiliar correspondente
    for (i = 0; i < n1; i++) L[i] = pontos[lo + i];
    for (j = 0; j < n2; j++) R[j] = pontos[m + 1+ j];

    // Merge os vetores auxiliares
    i = 0;
    j = 0;
    k = lo;
    while (i < n1 && j < n2) {
        if (strcmp(retornaNome(L[i]), retornaNome(R[j])) <= 0) {
            pontos[k] = L[i];
            i++;
        }
        else {
            pontos[k] = R[j];
            j++;
        }
        k++;
    }
    // Copia os elementos restantes de L
    while (i < n1) {
        pontos[k] = L[i];
        i++;
        k++;
    }
    // Copia os elementos restantes de R
    while (j < n2) {
        pontos[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}


void mergeSort(Ponto** pontos, int lo, int hi) {

    /*Aplicação do algoritmo mergeSort recursivo visto em aula*/
    if (lo < hi) {
        int m = lo+(hi-lo)/2;
        mergeSort(pontos, lo, m);
        mergeSort(pontos, m+1, hi);
        merge(pontos, lo, m, hi);
    }
}

void imprimeSaida(Grupos* grupos, int k, char* saida){
    
    FILE *file = fopen(saida, "w");
    Ponto ***pGrupos; // k vetores de ponteiros para ponto, cada k representa um grupo
    Ponto **Copia = malloc(sizeof(Ponto*) * retornaNumeroPontos(grupos)); // Vetor de ponteiros para ponto que conterá a cópia do endereço de todos os pontos
    int ID, i, j=0, index, tamanho;

    fclose(file);
    /*Preenche o vetor Copia com os endereços de todos os pontos*/
    for (i = 0; i<retornaNumeroPontos(grupos); i++){
        Copia[i] = retornaPontoPorIndex(grupos, i);
    }

    /*Obtém-se o vetor contendo os tamanhos dos grupos*/
    int* tamanhoGrupos = retornaTamanhoGrupos(grupos);

    /*Aloca espaço para os k grupos*/
    pGrupos = malloc(sizeof(Ponto**)*k);

    /*Passa por todos os k grupos*/
    for (i = 0; i<k; i++){
        index = 0;
        /*Os endereços do vetor Copia são removidos quando já analisados*/
        while(Copia[j] == NULL) j++;

        /*Obtém-se o ID do próximo grupo a ser analisado*/
        ID = retornaID(UF_Find(grupos,j));

        /*Obtém-se o tamanho do grupo para alocação de memória*/
        tamanho = tamanhoGrupos[ID];
        int aux_tamanho = tamanho;
        pGrupos[i] = malloc(sizeof(Ponto*) * tamanho);

        /*Preenche o vetor alocado com os pontos do mesmo grupo*/
        for(int l=0; l<retornaNumeroPontos(grupos); l++){
            if (ID == retornaID(UF_Find(grupos,l))){
                aux_tamanho--;
                pGrupos[i][index] = retornaPontoPorIndex(grupos,l);
                index++;
                Copia[l] = NULL;

                if (aux_tamanho < 1){
                    /*Apos preencher o vetor com pontos do mesmo grupo, ordena o grupo por ordem alfabética*/
                    mergeSort(pGrupos[i], 0, tamanho-1);

                    j=0;
                    break;
                } 
            }
        }
    }

    /*Ordena os grupos pelo primeiro elemento de cada*/
    qsort(pGrupos, k, sizeof(Ponto**), comparadorPrimeiraLetra);


    /*Imprime os grupos na ordem certa*/
    file = fopen(saida, "a");

    for(i=0; i<k; i++){
        tamanho = tamanhoGrupos[retornaID(pGrupos[i][0])];
        for(j = 0; j<tamanho; j++){
            fprintf(file, "%s",retornaNome(pGrupos[i][j]));
            if (j<tamanho-1) fprintf(file, ",");
        }
        if(i < k-1){
            fprintf(file, "\n");
        }
    }
    fclose(file);

    /*Libera os recursos de memória utilizados na função*/

    free(Copia);
    
    for (i = 0; i<k; i++){
        free(pGrupos[i]);
    }

    free(pGrupos);
}

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

    /*clock_t start, stop;

    start = clock();
    //TUDO QUE FOR CONTAR NO TEMPO AQUI
    stop = clock();

    double time_taken = ((double) stop - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.3f\n", time_taken);
    */

    if(argc < 4){
        printf("Erro: São necessários 3 parâmetros para a execução: nome_arquivo_entrada.txt numero_de_grupos nome_arquivo_saida.txt");
        return 1;
    }

    char *entrada, *saida;
    entrada = argv[1];
    saida = argv[3];
    
    int k = atoi(argv[2]);
    int i, count = 0;

    //Le o arquivo de entrada e cria um vetor com todos os pontos
    Ponto** pontos = leEntrada(entrada, &count);                          
    
    //Cria o TAD que contém todos os pontos e a qual grupo eles pertencem (Com os grupos inicialmente sendo apenas o ponto)
    //Também calcula as distâncias entre os pontos e as ordena por tamanho
    Grupos* grupos = inicializaGrupos(pontos, count);

    //Baseado nas distâncias já calculadas, já encontra os k grupos por meio do algoritmo de Kruskal modificado para parar antes do final
    Kruskal(grupos, k);
    
    //Ordena os grupos criados por ordem alfabética e os imprime no arquivo de texto passado
    imprimeSaida(grupos, k, saida);

    //Liberar a memória
    destroiGrupos(grupos);
    return 0;
}