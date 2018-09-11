#include<stdio.h>
#include<stdlib.h>
#include "auxFunctions.h"

#define initial 1
#define visited 2
#define finished 3
#define MAX 100
bool ciclo = false;
int current_array_size = 0;
int maxSize = 100;
int n;    /*Number of vertices in the graph */
int adj[MAX][MAX];
void create_graph( );

int state[MAX];

void DF_Traversal(int n);
void DFS(int v, int n);

int main() {
    Vida *struct_vida;
    Vida novaInstancia;
    Processo *struct_array;
    tTuple *struct_tuples;
    Processo novaTransacao;
    int numLinhas = 10;
    current_array_size = numLinhas;
    size_t i = 0;
    int idAtual = 0;
    int posicoesOcupadas = 0;
    int incidencia = 0;


    int* transacoes = (int*) malloc(numLinhas*sizeof(int));
    struct_array = (Processo*) malloc(sizeof(Processo) * numLinhas);
    struct_tuples = (tTuple*) malloc(sizeof(tTuple) * numLinhas);
    struct_vida = (Vida*) malloc(sizeof(Vida) * numLinhas);

    while (fscanf(stdin, "%d %d %c %c", &novaTransacao.tempo, &novaTransacao.id, novaTransacao.operacao,
                  novaTransacao.atributo) != EOF) {
        struct_array[i] = novaTransacao;

        if (i == 0) {
            transacoes[posicoesOcupadas] = struct_array[0].id;
            posicoesOcupadas = 1;
            novaInstancia.id = struct_array[0].id;
            novaInstancia.nascimento = struct_array[0].tempo;
            novaInstancia.morte = 0;
            struct_vida[0] = novaInstancia;

        } else {
            if (!isRepeated(struct_array[i].id, transacoes, i)) {
                transacoes[posicoesOcupadas] = struct_array[i].id;


                novaInstancia.id = struct_array[i].id;
                novaInstancia.nascimento = struct_array[i].tempo;
                novaInstancia.morte = 0;
                struct_vida[posicoesOcupadas] = novaInstancia;

                posicoesOcupadas += 1;
            } else {
                if ((compare_strings(struct_array[i].operacao, "C")) ||
                      (compare_strings(struct_array[i].operacao, "c"))) {
                    struct_vida[struct_array[i].id - 1].morte = struct_array[i].tempo;
                }
            }
        }

        i += 1;

        if (i % numLinhas == 0) { // realocação de memória dos arrays
            current_array_size += numLinhas;
            struct_array = (Processo *) realloc(struct_array, (current_array_size)*sizeof(Processo));
            struct_tuples = (tTuple *) realloc(struct_tuples, (current_array_size)*sizeof(tTuple));
            struct_vida = (Vida *) realloc(struct_vida, (current_array_size)*sizeof(Vida));
            transacoes = (int *) realloc(transacoes, (current_array_size)*sizeof(int));
        }
    }

    // Fim da leitura

    printTransactions(i, struct_array);



    int inicioBloco = 0;
    int numBatchs = 0;
    int fimBloco = struct_vida[0].morte;




    int batchLimits[posicoesOcupadas];



    for (int j = 1; j < posicoesOcupadas; ++j) {
        if (fimBloco == 0){ // nao tem commits
            fimBloco = i;
            break;
        } else {
            if(struct_vida[j].nascimento < fimBloco) {

                if(struct_vida[j].morte > fimBloco) {
                    fimBloco = struct_vida[j].morte;
                }
            } else {
//                printf("entrou aqui %d\n", struct_vida[j].morte);
                batchLimits[numBatchs] = fimBloco;
                numBatchs += 1;
                fimBloco = struct_vida[j].morte;
                // primeira vez que preencheu um batch
            }
        }
    }
    //     Adiciono o ultimo limite como sendo a ultima instancia
    batchLimits[numBatchs] = fimBloco;
    numBatchs += 1;
    int arrayDeTransacoesPorBloco[posicoesOcupadas];
    int realSize = 0;
    int n;
    int sizeTuple = 0;



    for (int k = 0; k < numBatchs; ++k) {

        checkTransactions(inicioBloco, batchLimits[k], posicoesOcupadas, &realSize, arrayDeTransacoesPorBloco,
                          struct_array);

        buildGraph(inicioBloco, batchLimits[k], struct_array, &sizeTuple, struct_tuples, "W", "R", MAX, adj);
        buildGraph(inicioBloco, batchLimits[k], struct_array, &sizeTuple, struct_tuples, "R", "W", MAX, adj);
        buildGraph(inicioBloco, batchLimits[k], struct_array, &sizeTuple, struct_tuples, "W", "W", MAX, adj);

        n = realSize;
        if (n > 0) {
            for (int j = 0; j < realSize; ++j) {
                for (int l = 0; l < realSize; ++l) {
                    printf("%d ", adj[j][l]);
                }
                printf("\n");
            }
            DF_Traversal(realSize);
        }

        // imprimo a transacao
        printf("\n%d ", k+1);
        for (int l = 0; l < realSize; ++l) {
            if (ciclo) {
                if (l == 0) {
                    printf("%d,", arrayDeTransacoesPorBloco[l]);
                } else {
                    if (l == realSize -1) {
                        printf("%d NS\n", arrayDeTransacoesPorBloco[l]);
                    } else {
                        printf("%d,", arrayDeTransacoesPorBloco[l]);
                    }
                }
            } else {
                if (l == 0) {
                    printf("%d,", arrayDeTransacoesPorBloco[l]);
                } else {
                    if (l == realSize -1) {
                        printf("%d SS\n", arrayDeTransacoesPorBloco[l]);
                    } else {
                        printf("%d,", arrayDeTransacoesPorBloco[l]);
                    }
                }
            }
        }

        ciclo = false;

        inicioBloco = batchLimits[k];

        // limpo o adj para o proximo batch
        for (int m = 0; m < realSize; ++m) {
            for (int j = 0; j < realSize; ++j) {
                adj[m][j] = 0;
            }
        }

        realSize = 0;

        memset(arrayDeTransacoesPorBloco, 0, posicoesOcupadas);
    }
}

void DF_Traversal(int n)
{
    int v;

//    printf("\n n vale %d\n", n);
    for(v=0; v<n; v++)
//        printf("\nv vale%d\n", v);
        state[v] = initial;

    DFS(0, n);/*start DFS from vertex 0*/

    for(v=1; v<n; v++)
    {
        if(state[v]==initial)
            DFS(v, n);
    }
//    printf("\nGraph is Acyclic\n");
}/*End of DF_Traversal( )*/

void DFS(int v, int n)
{
    int i;
    state[v] = visited;
//    printf("\nEstado é %d do vertice %d\n", state[v], v);

    for(i=0; i<n; i++)
    {
//        printf("\nProcurando em %d %d, valor é %d\n", v, i, adj[v][i]);

        if(adj[v][i]==1)
        {

            if(state[i]==initial){

                DFS(i, n);
            }

            else if(state[i]==visited)
            {
//                printf("\nBack edge  (%d -> %d) found\n", v+1, i+1);
//                printf("\nGraph is cyclic\n");
                ciclo = true;
                return;
            }
        }
    }
    state[v] = finished;
}/*End of DFS()*/