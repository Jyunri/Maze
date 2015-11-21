#include <stdio.h>
#include <stdlib.h>
#define MAX_H 10000

int** GeraLabirinto(int **maze, int **vizinhanca, int n){
    int **muro, i, j, celcorrente, vizinho ;
    PILHA *P, *visitados;

    P = Cria();
    visitados = Cria();

    srand(time(NULL));

    //Matriz que indica os muros entre os vizinhos
    muro = (int**)calloc(n*n,sizeof(int*));

    for(i = 0; i < n*n; i++){
        muro[i] = (int*)calloc(n*n,sizeof(int));
    }

    for(i = 0; i < n*n; i++){
        for(j = 0; j < n*n; j++){
               muro[i][j] = vizinhanca[i][j];
        }
    }


    //printf("Matriz muro:\n");
    //ImprimeMatriz(muro,n*n,n*n);
    printf("\n");


    //Rotina de Busca em profundidade

    printf("Marcando o comeco do labirinto como visitado..\n");
    Insere(visitados,maze[0][0]);
//    printf("A pilha de visitados eh:\n");
//    ImprimePilha(visitados);
//    printf("\n");

    printf("Inserindo o comeco do labirinto na Pilha..\n");
    Insere(P,maze[0][0]);
//    printf("A pilha P eh:\n");
//    ImprimePilha(P);
//    printf("\n");

    while(!PilhaVazia(P)){
        printf("Pilha nao vazia\n");
        printf("Removendo o topo da Pilha..\n");
        Remove(P,&celcorrente);
//        printf("A pilha P eh:\n");
//        ImprimePilha(P);

        printf("\nCelula corrente eh %d\n\n",celcorrente);
        if(VizinhoNaoVisitado(vizinhanca,celcorrente,n*n,visitados)!=-1){         //verifica se tem vizinhos nao visitados
            printf("Escolhendo vizinho nao visitado..\n");
            //escolher vizinho nao visitado aleatoriamente
            do{
                vizinho = rand()%(n*n);
            }while(vizinhanca[celcorrente][vizinho]!=1||BuscaPilha(visitados,vizinho)==1);

            printf("Vizinho escolhido: %d\n\n",vizinho);

            //remover muro com o vizinho
            printf("Removendo o muro com vizinho..\n\n");
            muro[celcorrente][vizinho]=0;
            muro[vizinho][celcorrente]=0;

            //marcar vizinho como visitado
            printf("Marcando o vizinho como visitado..\n");
            Insere(visitados,vizinho);
//            printf("A pilha de visitados eh:\n");
//            ImprimePilha(visitados);
//            printf("\n");

            //Insere celula corrente na Pilha
            printf("Inserindo celula corrente na pilha..\n");
            Insere(P,celcorrente);
//            printf("A pilha P eh:\n");
//            ImprimePilha(P);
//            printf("\n");

            //Insere vizinho na Pilha
            printf("Inserindo vizinho na pilha..\n");
            Insere(P,vizinho);
//            printf("A pilha P eh:\n");
//            ImprimePilha(P);
//            printf("\n");

            printf("Fim-se\n\n\n");
        }
        else    printf("Nao tem mais vizinhos nao visitados\n\n");
    }

    //printf("Matriz muro:\n");
    //ImprimeMatriz(muro,n*n,n*n);
    printf("\n");

    Libera(P);
    Libera(visitados);

    printf("\nLabirinto Gerado:\n");
    ImprimeLabirinto(maze,muro,n);

    return muro;
}

//Verifica se todos os elementos de uma linha de uma matriz eh nula
int LinhaNula(int**m, int l, int n){
    int col;
    for(col = 0; col < n; col++){
        if(m[l][col]==1)    return 0;
    }
    return 1;
}

//Verifica se celula tem vizinhos nao visitados
int VizinhoNaoVisitado(int **vizinhanca, int l,int n, PILHA *visitados){
    int col;

    printf("Buscando vizinho nao visitado..\n");

    for(col = 0; col < n; col++){
        if(vizinhanca[l][col]==1){                                       //indica que eh vizinho
            printf("Verificando se vizinho %d nao foi visitado\n",col);
            if(!BuscaPilha(visitados,col)){
                printf("Vizinho %d nao foi visitado\n",col);
                return col;   //indica que encontrou um vizinho nao visitado, retornando o proprio
            }
            printf("Vizinho %d ja foi visitado..\n",col);
        }
    }
    return -1;                                                   //nao encontrou nenhum vizinho nao visitado
}

//Imprime Labirinto baseado na matriz de muros
void ImprimeLabirinto(int **maze,int **muro,int n){
    int i,j;

    for(i = 0; i < n; i++){
        printf("____");
    }
    printf("\n");

    for(i = 0; i < n; i++){
        for(j=0; j < n; j++){

            if(i+1<n){
                if(muro[maze[i+1][j]][maze[i][j]] == 1) printf("___");
                else    printf("   ");
            }
            else printf("   ");

            if(j+1<n){
                if(muro[maze[i][j+1]][maze[i][j]] == 1) printf("|");
                else    printf(" ");
            }
            else    printf("|");

        }
        printf("\n");
    }

    for(i = 0; i < n; i++){
        printf("----");
    }
    printf("\n");

    printf("\n\n");
}


//Resolve Labirinto
FILA* ResolveLabirinto(int **maze, int **vizinhanca, int **muro, int n, int *ini, int *fim){
    int celcorrente, inicio, objetivo, valcancavel, vizinho, i, j, remove;
    PILHA *P, *visitados;
    FILA *caminho;

    P = Cria();
    caminho = CriaFila();
    visitados = Cria();

    srand(time(NULL));

    printf("\n\nResolvendo o labirinto:\n\n");

    printf("Escolhendo um inicio aleatorio..\n");
    i = rand()%n;
    j = rand()%n;
    inicio = maze[i][j];
    printf("O inicio sera %d\n\n",inicio);

    printf("Escolhendo um objetivo aleatorio..\n");
    do{
        i = rand()%n;
        j = rand()%n;
        objetivo = maze[i][j];
    }while(inicio == objetivo);
    printf("O objetivo sera %d\n\n",objetivo);

    //Referencias para a funcao principal
    *ini = inicio;
    *fim = objetivo;

    //Rotina para resolver o labirinto

    printf("Celula corrente recebendo inicio..\n");
    celcorrente = inicio;
    printf("Celula corrente eh %d\n\n",celcorrente);

    printf("Inserindo celula corrente na pilha P ..\n");
    Insere(P,celcorrente);
//    printf("A pilha P eh:\n");
//    ImprimePilha(P);
//    printf("\n");

    //Enquanto a celula corrente nao eh o fim do labirinto
    while(celcorrente!=objetivo){
        //celula corrente recebe topo da pilha
        printf("Recebendo o topo da pilha..\n");
        celcorrente = RetornaTopo(P);
        printf("A celula corrente eh %d\n\n",celcorrente);

        //Marca celula corrente como visitado e como caminho
        printf("Marcando a celula corrente como visitado..\n");
        Insere(visitados,celcorrente);
//        printf("A pilha de visitados eh:\n");
//        ImprimePilha(visitados);
//        printf("\n");

        printf("Marcando a celula corrente como caminho..\n");
        if(!BuscaFila(caminho,celcorrente))    InsereFila(caminho,celcorrente);        //caso a celula ja ser um caminho, desconsiderar
//        printf("A fila de caminho eh:\n");
//        ImprimeFila(caminho);
//        printf("\n");

        valcancavel = 0;
        vizinho = -1;

        //Verificador de existencia de vizinho alcancavel
        for(j = 0; j < n*n; j++){
            if(vizinhanca[celcorrente][j]==1){              //sao vizinhos?
                if(!BuscaPilha(visitados,j)){               //vizinho ja foi visitado?
                    if(muro[celcorrente][j]!=1){             //tem muro entre eles?
                        valcancavel = 1;
                    }
                }
            }
        }

        j = 0;

        printf("Verificando se celula corrente possui um vizinho nao visitado alcancavel..\n");
        if(valcancavel == 1){
            printf("\nPossui! Escolhendo vizinho..\n");
            do{
                if(vizinhanca[celcorrente][j]==1){              //sao vizinhos?
                    if(!BuscaPilha(visitados,j)){               //vizinho ja foi visitado?
                        if(muro[celcorrente][j]!=1){            //tem muro entre eles?
                            vizinho = j;                    //Escolhe o primeiro vizinho alcancavel
                        }
                    }
                }
                j++;
            }   while((vizinho == -1));

            if(vizinho == -1)   printf("Nenhum vizinho escolhido(erro)\n\n");

            printf("Vizinho escolhido foi %d\n\n",vizinho);

            //Inserir vizinho na PILHA
            Insere(P,vizinho);
            printf("Inserindo vizinho na pilha..\n");
//            printf("A pilha P eh: \n");
//            ImprimePilha(P);
//            printf("\n");
        }
        else{
            printf("\nNao possui. Verificando se a celula corrente eh objetivo..\n");
            //Verifica se celula corrente eh objetivo
            if(celcorrente!=objetivo){
                //Tira a celula corrente do caminho
                printf("Celula corrente nao eh objetivo...removendo do caminho..\n");
                RemoveUltimoFila(caminho,&remove);
//                printf("O caminho atual eh\n");
//                ImprimeFila(caminho);
//                printf("\n");
            }
            //Remove celula corrente da Pilha
            printf("Removendo celula corrente da pilha..\n");
            Remove(P,&remove);
//            printf("A pilha P eh\n");
//            ImprimePilha(P);
//            printf("\n");
        }
        printf("Fim-se\n\n");

        //verificacao
        if(PilhaVazia(P))   scanf("%d",&remove);
    }

    Libera(visitados);
    Libera(P);

    return caminho;
}

//-----------------------------------------------------------------------------------------------------

//Calcula distancia Manhattan de cada ponto ate o objetivo
int* DistanciaRestante(int **maze, int n, int linha_obj, int col_obj ){
    int *heuristica, i, j, k, distl = 0, distc = 0;
    heuristica = (int*)calloc(n*n,sizeof(int));

    printf("i eh %d e j eh %d",linha_obj,col_obj);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i < linha_obj){
                for(k = i; k < linha_obj; k++) distl++;
            }
            else if(i > linha_obj){
                for(k = i; k > linha_obj; k--) distl++;
            }

            if(j < col_obj){
                for(k = j; k < col_obj; k++) distc++;
            }
            else if(j > col_obj){
                for(k = j; k > col_obj; k--) distc++;
            }

            heuristica[n*i+j] = distl + distc;

            distl = 0;
            distc = 0;
        }
    }

    return heuristica;
}

//------------------------------------------------------------------------------------------------------

//Resolve Labirinto por A*
FILA* ResolveLabirinto_A(int **maze, int **vizinhanca, int **muro, int n, int *ini, int *fim){
    int celcorrente, inicio, objetivo, valcancavel, vizinho, i, j, removed, *heuristica, escolhido;
    PILHA *P, *visitados;
    FILA *caminho;

    P = Cria();
    caminho = CriaFila();
    visitados = Cria();

    srand(time(NULL));

    printf("\n\nResolvendo o labirinto:\n\n");

    printf("Escolhendo um inicio aleatorio..\n");
    i = rand()%n;
    j = rand()%n;
    inicio = maze[i][j];
    printf("O inicio sera %d\n\n",inicio);

    printf("Escolhendo um objetivo aleatorio..\n");
    do{
        i = rand()%n;
        j = rand()%n;
        objetivo = maze[i][j];
    }while(inicio == objetivo);
    printf("O objetivo sera %d\n\n",objetivo);

    //Referencias para a funcao principal
    *ini = inicio;
    *fim = objetivo;

    //Calculando h(n) para cada ponto
    heuristica = DistanciaRestante(maze, n, i, j);

    printf("\nO vetor de h(n) eh\n");
    for(i = 0; i < n*n; i++){
        printf("%d, ",heuristica[i]);
    }

    printf("\n\n");

    //Rotina para resolver o labirinto

    printf("Celula corrente recebendo inicio..\n");
    celcorrente = inicio;
    printf("Celula corrente eh %d\n\n",celcorrente);

    printf("Inserindo celula corrente na pilha P ..\n");
    Insere(P,celcorrente);
//    printf("A pilha P eh:\n");
//    ImprimePilha(P);
//    printf("\n");

    //Enquanto a celula corrente nao eh o fim do labirinto
    while(celcorrente!=objetivo){
        //celula corrente recebe topo da pilha
        printf("Retirando o topo da pilha ordenada..\n");
        Remove(P,&celcorrente);
        printf("A celula corrente eh %d\n\n",celcorrente);

        //Marca celula corrente como visitado e como caminho
        printf("Marcando a celula corrente como visitado..\n");
        if(!BuscaPilha(visitados,celcorrente))   Insere(visitados,celcorrente);
//        printf("A pilha de visitados eh:\n");
//        ImprimePilha(visitados);
//        printf("\n");

        printf("Marcando a celula corrente como caminho..\n");
        if(!BuscaFila(caminho,celcorrente))    InsereFila(caminho,celcorrente);        //caso a celula ja ser um caminho, desconsiderar
//        printf("A fila de caminho eh:\n");
//        ImprimeFila(caminho);
//        printf("\n");



        valcancavel = 0;
        vizinho = -1;
        escolhido = -1;                             //desta vez, o escolhido nao precisa ser necessariamente um vizinho

        j = 0;

        //Verificador de existencia de vizinho alcancavel
        do{
            if(vizinhanca[celcorrente][j]==1){              //sao vizinhos?
                if(!BuscaPilha(visitados,j)){               //vizinho ja foi visitado?
                    if(muro[celcorrente][j]!=1){            //tem muro entre eles?
                        valcancavel = 1;
                        vizinho = j;            //recebe o primeiro vizinho alcancavel encontrado
                    }
                }
            }
            j++;
        }while(vizinho == -1 && j < n*n);

        j = 0;

        printf("Verificando se celula corrente possui um vizinho nao visitado alcancavel..\n");
        if(valcancavel == 1){
            printf("\nPossui! Expandindo vizinhos..\n");

            do{
                if(vizinhanca[celcorrente][j]==1){              //sao vizinhos? se sim..
                    if(!BuscaPilha(visitados,j)){               //vizinho ja foi visitado? se nao..
                        if(muro[celcorrente][j]!=1){            //tem muro entre eles? se nao..
                            heuristica[j] ++;                   //acrescentando g(n) a heuristica do vizinho
                            Insere(P,j);                        //insere vizinho na PILHA
                            //if(heuristica[j] < heuristica[vizinho] ){
                                //vizinho = j;                    //vizinho recebe a celula com heuristica mais otimizada
                            }
                        }
                    }
                    j++;
                }while(j < n*n);
                //printf("\nValor da heuristica otima eh %d com heuristica %d\n",vizinho,heuristica[vizinho]);

                //if(vizinho == -1)   printf("Nenhum vizinho escolhido(erro)\n\n");


            printf("\nAs heuristicas foram atualizadas!\n");
            //printf("Vizinho escolhido foi %d\n\n",vizinho);

            printf("\nO vetor de h(n) eh\n");
            for(i = 0; i < n*n; i++){
                printf("%d, ",heuristica[i]);
            }

            printf("\n\nA pilha nao ordenada eh: ");
            ImprimePilha(P);

            //Ordena PILHA de acordo com as heuristicas
            P = Ordena(P,heuristica);

            printf("A pilha ordenada eh: ");
            ImprimePilha(P);

            //verifica se o comeco da pilha é um filho da celula corrente. se nao for, exclui a celula corrente do caminho
            escolhido = RetornaTopo(P);
            if(!vizinhanca[celcorrente][escolhido]||muro[celcorrente][escolhido]){       //se nao forem vizinhos ou tiverem muro, entao nao eh filho
                RemoveUltimoFila(caminho,&removed);
            }

            printf("\n");

                //Inserir vizinho na PILHA
                //Insere(P,vizinho);
                //printf("Inserindo vizinho na pilha..\n");
    //            printf("A pilha P eh: \n");
    //            ImprimePilha(P);
    //            printf("\n");
        }
        else{
            printf("\nNao possui. Verificando se a celula corrente eh objetivo..\n");
            //Verifica se celula corrente eh objetivo
            if(celcorrente!=objetivo){
                //Tira a celula corrente do caminho
                printf("Celula corrente nao eh objetivo...removendo do caminho..\n");
                RemoveUltimoFila(caminho,&removed);
//                printf("O caminho atual eh\n");
//                ImprimeFila(caminho);
//                printf("\n");
            }
            //Remove celula corrente da Pilha
            printf("Removendo celula corrente da pilha..\n");
            Remove(P,&removed);
//            printf("A pilha P eh\n");
//            ImprimePilha(P);
//            printf("\n");

            //Insere vizinho alcancavel mesmo que visitado de volta a pilha
            for(i = 0; i < n*n; i++){
                if(vizinhanca[celcorrente][i]){
                    if(!muro[celcorrente][i]){
                        Insere(P,i);
                    }
                }
            }
        }
    }
    printf("\nDestino!\n");

    free(heuristica);

    Libera(visitados);
    Libera(P);

    return caminho;
}

