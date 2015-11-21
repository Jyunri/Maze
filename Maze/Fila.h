#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int valor;
    struct felem *prox;
}felem;

typedef struct{
    felem *inicio;
    felem *fim;
    felem *p;
    int tamanho;
} FILA;

FILA* CriaFila() {
    FILA *tmp = (FILA*)malloc(sizeof(FILA));
    tmp->inicio = NULL;
    tmp->fim = NULL;
    tmp->tamanho = 0;
    return tmp;
}

int LiberaFila(FILA *F) {
    if (F == NULL) return 0;
    felem *tmp;
    tmp = F->inicio;
    while (tmp != NULL) {
        F->inicio = tmp->prox;
        free(tmp);
        tmp = F->inicio;
    }
    free(F);
    return 1;
}

int InsereFila(FILA *F, int x) {
    felem *novo = (felem*)malloc(sizeof(felem));
    if (F->tamanho == 0){
        F->inicio = novo;
    }
    else{
        F->fim->prox = novo;
    }
    F->fim = novo;
    novo -> prox = NULL;
    novo -> valor = x;
    F->tamanho++;

    return 1;
}

int RemoveUltimoFila(FILA *F, int *x) {
    felem *tmp;

    if(FilaVazia(F)) return 0;

    tmp = F->inicio;
    *x = F->fim->valor;

    if(tmp == F->fim)   free(tmp);

    else{
        while(tmp->prox != F->fim){
            tmp = tmp->prox;
        }

       tmp->prox = NULL;
       free(F->fim);
       F->fim = tmp;

    }

    F->tamanho--;

    return 1;
}

int RetornaInicioFila(FILA *F){
    if(FilaVazia(F))   return NULL;
    return F->inicio->valor;
}

void ImprimeFila(FILA *F) {
    if (F->inicio == NULL) {printf("Fila vazia\n"); return;}
    felem *tmp = F->inicio;
    while (tmp != NULL) {
        if(tmp->prox == NULL)   printf("%d",tmp->valor);
        else    printf("%d, ",tmp->valor);
        tmp = tmp->prox;
    }
    printf("\n");
}

int FilaVazia(FILA *F){
    return F->tamanho==0;
}

int BuscaFila(FILA *F,int x){
    felem *tmp = F->inicio;
    while(tmp!=NULL){
        if(tmp->valor == x) return 1;
        tmp = tmp->prox;
    }
    return 0;
}


