#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int valor;
    struct elem *prox;
}elem;

typedef struct{
    elem *topo;
    elem *p;
    int tamanho;
} PILHA;

PILHA* Cria() {
    PILHA *tmp = (PILHA*)malloc(sizeof(PILHA));
    tmp->topo = NULL;
    tmp->tamanho = 0;
    return tmp;
}

int Libera(PILHA *P) {
    if (P == NULL) return 0;
    elem *tmp;
    tmp = P->topo;
    while (tmp != NULL) {
        P->topo = tmp->prox;
        free(tmp);
        tmp = P->topo;
    }
    free(P);
    return 1;
}

int Insere(PILHA *P, int x) {
    elem *novo = (elem*)malloc(sizeof(elem));
    if (P->tamanho != 0) novo->prox = P->topo;
    else novo->prox = NULL;
    P->topo = novo;
    novo->valor = x;
    P->tamanho++;

    return 1;
}

int Remove(PILHA *P, int *x) {
    elem *tmp;

    if(PilhaVazia(P)) return 0;

    tmp = P->topo;
    *x = tmp->valor;
    P->topo = tmp->prox;
    P->tamanho--;
    free(tmp);

    return 1;
}

int RetornaTopo(PILHA *P){
    if(PilhaVazia(P))   return NULL;
    return P->topo->valor;
}

void ImprimePilha(PILHA *P) {
    if (P->topo == NULL) {printf("Pilha vazia\n"); return;}
    elem *tmp = P-> topo;
    while (tmp != NULL) {
        if(tmp->prox == NULL)   printf("%d",tmp->valor);
        else    printf("%d, ",tmp->valor);
        tmp = tmp->prox;
    }
    printf("\n");
}

int PilhaVazia(PILHA *P){
    return P->tamanho==0;
}

int BuscaPilha(PILHA *P,int x){
    elem *tmp = P->topo;
    while(tmp!=NULL){
        if(tmp->valor == x) return 1;
        tmp = tmp->prox;
    }
    return 0;
}

PILHA* Ordena(PILHA *P,int *valores){
    PILHA *aux = Cria();
    PILHA *aux2 = Cria();
    int tmp, tmp2,removed;

    if(PilhaVazia(P)) return 0;

    Remove(P,&tmp);
    Insere(aux,tmp);


    while(!PilhaVazia(P)){
        Remove(P,&tmp);
        if(valores[tmp] <= valores[aux->topo->valor])   Insere(aux,tmp);
        else{
            while(!PilhaVazia(aux)&&(valores[tmp] > valores[aux->topo->valor])){
                Remove(aux,&tmp2);
                Insere(aux2,tmp2);
            }
            Insere(aux,tmp);
            while(!PilhaVazia(aux2)){
                Remove(aux2,&tmp2);
                Insere(aux,tmp2);
            };
        }
    }
    Libera(aux2);

    return aux;
}

