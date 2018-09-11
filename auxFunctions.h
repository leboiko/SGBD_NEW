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
//        printf("\n TTT %d\n", arr[0]);
        if (i == chao){
            arr[*realSize] = struct_transactions[i].id;
            *realSize += 1;
//            printf("\n T%d encontrada\n", struct_transactions[i].id);
        }
        if (!isRepeated(struct_transactions[i].id, arr, size)) {
            arr[*realSize] = struct_transactions[i].id;
            *realSize += 1;
//            printf("\n T%d encontrada\n", struct_transactions[i].id);
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
                    adj[struct_transactions[i].id-1][struct_transactions[j].id-1] = 1;
//                    printf("\n\n(%d -> %d)\n\n", struct_transactions[i].id, struct_transactions[j].id);
                }
            }
        }
    }
}

extern void testeVisao(int chao, int teto, Processo *struct_transactions, int numTransacoes, int * arr) {
    Processo struct_batch[sizeof(Processo) * numTransacoes]; // array que vai receber apenas instancias da mesma transacao
    Processo instancia;
    int transacoesBatch = 0;

    for (int j = 0; j < numTransacoes; ++j) { // para cada transacao encontrada

        for (int i = chao; i < teto; ++i) { // para cada transacao do bloco
            if(struct_transactions[i].id == arr[j]) { // se tiver o mesmo id do primeiro for
                struct_batch[transacoesBatch] = struct_transactions[i];
                transacoesBatch += 1;
            }
        }

        printf("\n\n-----\n\n");

        for (int k = 0; k < transacoesBatch; ++k) {
            printf("\n %d %d %s %s\n", struct_batch[k].tempo, struct_batch[k].id,
                    struct_batch[k].operacao, struct_batch[k].atributo);
        }

        transacoesBatch = 0;

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
