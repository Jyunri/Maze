#include <stdio.h>
#include <stdlib.h>

void ImprimeMatriz(int**m, int l, int c){
    int i, j;
    for(i = 0; i < l; i++){
        for( j = 0; j< c ; j++){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void LiberaMatriz(int**m,int n){
    int i;
    for(i = 0; i < n; i++){
        free(m[i]);
    }
    free(m);
}


//Cria matriz e preenche com valores numericos
int** GeraMatriz(int n){
    int **matriz, i, j;

    matriz = (int**)calloc(n,sizeof(int*));
    for(i = 0; i < n; i++){
        matriz[i] = (int*)calloc(n,sizeof(int));
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matriz[i][j] = (n * i)+ j;          //Relacao posicao-valor
        }
    }

    return matriz;
}
