/*
 * Estruturas de Dados Avançadas (EDA) - 2021.1
 * Aluno: Pedro Lucas da Costa Vidal
 * Ciência da Computação
 * Árvore Rubro-Negra - Implementação
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "testing.h"
#include "structRB.h"

int main() {
    srand(time(NULL));
    Node **root; // Vetor de raízes para as arvores RN exigidas
    clock_t time; // Variável para calcular o tempo de execução
    double totalTime;
    
    printf("\nTESTAGEM\n");
    // FASE 1
    printf("\nFASE 1: criando %d arvores RUBRO-NEGRA com %d nos cada.\n", QTD_RN, QTD_NODES);
    printf("Por favor, aguarde. . .\n");
    time = clock();
    testInsertions(&root);
    time = clock() - time;
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("\nFASE 1 - TEMPO DE CRIACAO: %.10lf segundos\n", totalTime);
    showTrees(root);

    // FASE 2
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\nFASE 2: Verificando se as %d arvores sao RUBRO-NEGRA"
    " e se cada arvore possui %d nos.\n", QTD_RN, QTD_NODES);
    printf("Por favor, aguarde. . .\n");
    time = clock(); // tempo inicial
    verifyTrees(root, 2);
    time = clock() - time; // Pegando tempo de execucao
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("FASE 2 - TEMPO DE EXECUCAO: %.10lf segundos\n", totalTime);
    
    // FASE 3 
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\nFASE 3: Remover %d nos de cada uma das %d arvores\n", QTD_REMOVES, QTD_RN);
    printf("Por favor, aguarde. . .\n");
    time = clock();
    testRemoves(root);
    time = clock() - time;
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("\nFASE 3 - TEMPO DE EXECUCAO DAS REMOCOES: %.10lf segundos\n", totalTime);
    showTrees(root);

    // FASE 4
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\nFASE 4: Verificar se, apos as remocoes, as arvores continuam sendo RUBRO-NEGRA"
    " e se cada uma possui %d nos.\n", (QTD_NODES - QTD_REMOVES));
    printf("Por favor, aguarde. . .\n");
    time = clock();
    verifyTrees(root, 4);
    time = clock() - time;
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("\nFASE 4 - TEMPO DE EXECUCAO: %.10lf segundos\n", totalTime);

    printf("\nFIM DO PROGRAMA . . . :D\n");
    return 0;
}