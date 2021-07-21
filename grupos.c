#include "grupos.h"
#include "ponto.h"
#include <stdlib.h>


struct grupos{
    Ponto **vetorPontos;
    int *tamanhoGrupos;
    int numeroDePontos;
};

Grupos* inicializaGrupos(Ponto** vetorPontos, int numeroDePontos){
    Grupos *grupos = (Grupos*) malloc(sizeof(Grupos));
    grupos->numeroDePontos = numeroDePontos;
    grupos->vetorPontos = vetorPontos;
    grupos->tamanhoGrupos = (int*)malloc(numeroDePontos*sizeof(int));

    //Inicializa os tamanhos dos grupos com 1
    int i;
    for(i=0; i<numeroDePontos; i++){
        grupos->tamanhoGrupos[i] = 1;
    }

    return grupos;
}


Ponto* UF_Find(Grupos* grupos, int index){
    Ponto** vetor = grupos->vetorPontos;
    int indexProximoElemento;
    while(index != retornaID(vetor[index])){
        //Encontra a posição do próximo elemento no grupo
        indexProximoElemento = retornaID(vetor[index]);
        
        //Altera o identificador do elemento mais acima deste ponto para o identificador do ponto um passo mais próximo do root
        mudaID(vetor[index], retornaID(vetor[indexProximoElemento]));
        
        //Próximo elemento a ser verificado:
        index = retornaID(vetor[indexProximoElemento]); 
    }
    return vetor[index];
}


void UF_Union(Grupos* grupos, Ponto* p1, Ponto* p2){
    Ponto** vetor = grupos->vetorPontos;
    
    //Descobre os grupos de p1 e p2
    int i = retornaID(UF_Find(grupos, retornaIndex(p1)));
    int j = retornaID(UF_Find(grupos, retornaIndex(p2)));

    //Se ambos forem do mesmo grupo, só retorna
    if(i==j) return;

    //Se o tamanho do grupo i for menor do que o do j, junta o grupo i ao grupo j
    if (grupos->tamanhoGrupos[i] < grupos->tamanhoGrupos[j]){
        //Muda o id do root de i para a root de j
        mudaID(vetor[i], j);
        grupos->tamanhoGrupos[j] += grupos->tamanhoGrupos[i];
    }
    else { //Se o tamanho do grupo j for menor/igual do que o do i, junta o grupo j ao grupo i
        //Muda o id do root de j para a root de i
        mudaID(vetor[j], i);
        grupos->tamanhoGrupos[i] += grupos->tamanhoGrupos[j];
    }
}



Ponto* retornaPontoPorIndex(Grupos* grupos, int index){
    return grupos->vetorPontos[index];
}
int retornaNumeroPontos(Grupos* grupos){
    return grupos->numeroDePontos;
}

int* retornaTamanhoGrupos(Grupos* grupos){
    return grupos->tamanhoGrupos;
}

Grupos* destroiGrupos(Grupos *grupos){
    if(!grupos) return NULL;
    int i;

    //Libera todos os pontos
    for(i = 0; i < grupos->numeroDePontos; i++){
        destroiPonto(grupos->vetorPontos[i]);
    }

    //Libera os vetores alocados dinamicamente
    free(grupos->tamanhoGrupos);
    free(grupos->vetorPontos);

    //Libera a struct
    free(grupos);
    
    return NULL;
}