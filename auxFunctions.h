#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//
// Created by Luis Eduardo Boiko Ferreira on 10/09/2018.
//

#ifndef SGBD_AUXFUNCTIONS_H
#define SGBD_AUXFUNCTIONS_H

#endif //SGBD_AUXFUNCTIONS_H

//
// Created by Luis Eduardo Boiko Ferreira on 10/09/2018.
//
//
//struct node
//{
//    int vertex;
//    struct node* next;
//};
//
//struct node* createNode(int v);
//
//struct Graph
//{
//    int numVertices;
//    int* visited;
//    struct node** adjLists; // we need int** to store a two dimensional array. Similary, we need struct node** to store an array of Linked lists
//};

//struct Graph* createGraph(int);
//extern void addEdge(struct Graph*, int, int);
//extern void printGraph(struct Graph*);
//extern void DFS(struct Graph*, int);

typedef struct tTuple {
    int ti, tj;
}tTuple;

typedef struct Processo {
    int tempo, id;
    char operacao[10], atributo[10];
}Processo;

typedef struct Vida
{
    int id;
    int nascimento;
    int morte;
}Vida;

extern bool isRepeated(int toCompare, int *lista, int size) {
    bool status = false;
    for (int i = 0; i < size; ++i) {
//        printf("-- %d\n", lista[i]);
        if (lista[i] == toCompare) {
            status = true;
        }
    }

    return status;
}

extern bool compare_strings(char a[], char b[])
{
    int c = 0;

    while (a[c] == b[c]) {
        if (a[c] == '\0' || b[c] == '\0')
            break;
        c++;
    }

    if (a[c] == '\0' && b[c] == '\0')
        return true;
    else
        return false;
}

extern void checkTransactions(int chao, int teto, int size, int *realSize, int * arr, Processo *struct_transactions)
{
    for (int i = chao; i < teto; ++i) {
        if (!isRepeated(struct_transactions[i].id, arr, size)) {
            arr[*realSize] = struct_transactions[i].id;
            *realSize += 1;
        }
    }
}

extern void buildGraph(int chao, int teto, Processo *struct_transactions, int *sizeTuple, tTuple *struct_tuples,
        char op1[10], char op2[10], int maxArr, int adj[][maxArr]) {
    tTuple newTuple;
    for (int i = chao; i < teto; ++i) {
//        printf("\nTempo chegando %d\n", struct_transactions[i].tempo);
        if(compare_strings(struct_transactions[i].operacao, op1)) {
            for (int j = i + 1; j < teto; ++j) {
                if(compare_strings(struct_transactions[j].operacao, op2) &&
                        compare_strings(struct_transactions[j].atributo, struct_transactions[i].atributo) &&
                        ((struct_transactions[j].id != struct_transactions[i].id))) {
                    newTuple.ti = struct_transactions[i].id;
                    newTuple.tj = struct_transactions[j].id;
                    struct_tuples[*sizeTuple] = newTuple;
                    *sizeTuple += 1;
//                    printf("\nAchou em %d %d\n", struct_transactions[i].id, struct_transactions[j].id);
//                    addEdge(graph, struct_transactions[i].id, struct_transactions[j].id);
                    adj[struct_transactions[i].id-1][struct_transactions[j].id-1] = 1;
                    printf("\n\n(%d -> %d)\n\n", struct_transactions[i].id, struct_transactions[j].id);
                }
            }
        }
    }
}

extern void printTransactions(int n, Processo *struct_transactions)
{
    printf("Tempo\t T\t Op.\t At.\n");
    int i;
    for (i = 0; i < n; i++){
        printf("%d\t %d\t %s\t %s\n", struct_transactions[i].tempo, struct_transactions[i].id,
               struct_transactions[i].operacao, struct_transactions[i].atributo);
    }
    printf("\n");
}

//extern void fillGraph(int *n, int j, int limit, char op1[10], char op2[10], Processo *struct_array,
//        tTuple *struct_tuples) {
//    tTuple pair;
//    if(compare_strings(struct_array[j].operacao, op1)) {
//        // verifico se tem ocorrencia nos seguintes
//        for (int l = j+1; l < limit; ++l) {
//            if(compare_strings(struct_array[l].operacao, op2) &&
//               (struct_array[j].id != struct_array[l].id) &&
//               (struct_array[j].atributo == struct_array[l].atributo)) {
//
//                pair.ti = struct_array[j].id;
//                pair.tj = struct_array[l].id;
//
//                printf("\nT%d -> T%d\n", pair.ti, pair.tj);
//                struct_tuples[*n] = pair;
//                *n+= 1;
//
//            }
//        }
//
//    }
//}
//
//extern void DFSs(struct Graph* graph, int vertex) {
//    struct node* adjList = graph->adjLists[vertex];
//    struct node* temp = adjList;
//
//    graph->visited[vertex] = 1;
//    printf("Visited %d \n", vertex);
//
//    while(temp!=NULL) {
//        int connectedVertex = temp->vertex;
//
//        if(graph->visited[connectedVertex] == 0) {
//            DFS(graph, connectedVertex);
//        }
//        temp = temp->next;
//    }
//}
//
//extern struct node* createNode(int v)
//{
//    struct node* newNode = malloc(sizeof(struct node));
//    newNode->vertex = v;
//    newNode->next = NULL;
//    return newNode;
//}
//
//extern struct Graph* createGraph(int vertices)
//{
//    struct Graph* graph = malloc(sizeof(struct Graph));
//    graph->numVertices = vertices;
//
//    graph->adjLists = malloc(vertices * sizeof(struct node*));
//
//    graph->visited = malloc(vertices * sizeof(int));
//
//    int i;
//    for (i = 0; i < vertices; i++) {
//        graph->adjLists[i] = NULL;
//        graph->visited[i] = 0;
//    }
//    return graph;
//}
//
//extern void addEdge(struct Graph* graph, int src, int dest)
//{
//    // Add edge from src to dest
//    struct node* newNode = createNode(dest);
//    newNode->next = graph->adjLists[src];
//    graph->adjLists[src] = newNode;
//
//    // Add edge from dest to src
//    newNode = createNode(src);
//    newNode->next = graph->adjLists[dest];
//    graph->adjLists[dest] = newNode;
//}
//
//
