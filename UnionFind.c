#include "ponto.h"

Ponto* UF_find(Ponto** vetor, int ID){
    int chave = ID;
    while(ID != retornaIndex(vetor[chave])){
        chave = retornaIndex(vetor[chave]);
    }
    return vetor[chave];
}

void UF_Union(Ponto** vetor, int size, Ponto* p1, Ponto* p2){
    if (retornaIndex(p1) == retornaIndex(p2)) return;

    for(int i = 0; i<size; i++){
        if(retornaID(vetor[i]) == retornaID(p2)){
            mudaID(vetor[i], retornaID(p1));
        }
    }

}