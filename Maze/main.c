#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include <time.h>
#include "Fila.h"
#include "Matriz.h"
#include "Labirinto.h"

int main(){
    FILA *resolucao;
    int x, n, **maze, **vizinhanca, **MazeFinal, inicio, fim, i, j;

    printf("Qual sera o tamanho do seu labirinto? ");
    scanf("%d",&n);
    printf("\n");

    //Gera matriz n*n
    maze = GeraMatriz(n);
//    printf("Matriz maze:\n");
//    ImprimeMatriz(maze,n,n);
//    printf("\n");

    //Cria matriz que informa os vizinhos de cada celula
    vizinhanca = (int**)calloc(n*n,sizeof(int*));

    for(i = 0; i < n*n; i++){
        vizinhanca[i] = (int*)calloc(n*n,sizeof(int));
    }

    for(i = 0; i < n; i++){
        for(j=0; j < n; j++){
            if(j+1<n){
                vizinhanca[maze[i][j]][maze[i][j+1]] = 1;
                vizinhanca[maze[i][j+1]][maze[i][j]] = 1;
            }
            if(i+1<n){
                vizinhanca[maze[i+1][j]][maze[i][j]] = 1;
                vizinhanca[maze[i][j]][maze[i+1][j]] = 1;
            }
        }
    }

//    printf("Matriz vizinhanca:\n");
//    ImprimeMatriz(vizinhanca,n*n,n*n);


    //Gera Labirinto
    MazeFinal = GeraLabirinto(maze,vizinhanca,n);

    //Resolve Labirinto por A*
    resolucao = ResolveLabirinto_A(maze,vizinhanca, MazeFinal, n, &inicio, &fim);

    printf("\nLabirinto Gerado:\n");
    ImprimeLabirinto(maze,MazeFinal,n);

    printf("O caminho de %d ate %d do labirinto gerado eh:\n",inicio,fim);
    ImprimeFila(resolucao);

    LiberaFila(resolucao);

    LiberaMatriz(maze,n);
    LiberaMatriz(vizinhanca,n*n);
    LiberaMatriz(MazeFinal,n*n);

    return 1;
}
