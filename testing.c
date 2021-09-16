#include <stdio.h>
#include <stdlib.h>
#include "testing.h"
#include "insertion.h"
#include "deletion.h"
#include "verification.h"

// Prepara as arvores a serem criadas
void testInsertions(Node ***root) {
    int i;
    // Alocando memória para o vetor de raizes
    (*root) = (Node**)malloc(sizeof(Node*) * QTD_RN);
    if((*root) == NULL) {
        printf("AVISO: FALHA NA ALOCACAO DE MEMORIA\n");
        exit(1);
    }
    
    // Inicializando cada raiz para apontar para NULL
    for (i = 0; i < QTD_RN; i++) {
        (*root)[i] = NULL;
    }

    // Inserindo a quantidade definida de nós em cada árvore
    for(i = 0; i < QTD_RN; i++) {
        int count = 0;
        // Laço while não para enquanto houverem as inserções desejadas
        while(count < QTD_NODES) {
            // Gerando valores aleatórios
            // Em minha máquina, o RAND_MAX é 2^15 (32768)
            int key = (rand() * (rand() % RAND_MAX)) % RAND_LIMITER;
            count += insertNode(key, &((*root)[i]));
        }
    }
}

// Procedimento que realiza as remocoes exigidas
void testRemoves(Node **root) {
    int i;
    int count; // contador
    for(i = 0; i < QTD_RN; i++) {
        count = 0;
        while(count < QTD_REMOVES) {
            // Gerando valores aleatórios
            // Em minha máquina, o RAND_MAX é 2^15 (32768)
            int key = (rand() * (rand() % RAND_MAX)) % RAND_LIMITER;
            count += removeNode(key, &(root[i]));
        }
    }
}

// Verifica se as arvores são todas arvores rubro-negra
void verifyTrees(Node **root, int fase) {
    int resultRN;
    int countRN = 0;
    int i;
    int qtd;
    // Muda dependendo da fase de teste
    if(fase == 2) {
        qtd = QTD_NODES;
    }else {
        qtd = (QTD_NODES - QTD_REMOVES);
    }
    // Laco que passa por cada arvore verificando se e RN ou nao
    for(i = 0; i < QTD_RN; i++) {
        resultRN = 1; // Variavel e passada para a funcao como 1
        verifyRB(root[i], &resultRN, root[i]);
        int nodes = nodesCount(root[i]);
        
        if(resultRN == 1 && (nodes == qtd)) {
            countRN++;
        }
    }
    printf("\nRESULTADO: %d arvores de um total de %d sao arvores RUBRO-NEGRA com %d nos cada\n",
    countRN, QTD_RN, qtd);
}

// Mostra as primeiras N arvores e suas infos
void showTrees(Node **root) {
    int i;
    printf("\nPRIMEIRAS %d ARVORES RUBRO-NEGRA\n", PRINT_LIMIT);
    for(i = 0; i < PRINT_LIMIT && i < QTD_RN; i++) {
        if(root[i] != NULL) {
            int nodes = nodesCount(root[i]); // contando os nos
            printf("Arvore %d | Quantidade de nos = %d\n", i, nodes);
        }else printf("Arvore %d | NULL\n", i);
    }
}