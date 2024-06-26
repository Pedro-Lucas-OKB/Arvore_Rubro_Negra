#include "structRB.h"

#define RAND_LIMITER 100000 // Valor para limitar o rand()
#define QTD_RN 10 // Quantidade de arvores RN
#define QTD_NODES 1000 // Quantiadde de nos em cada arvore
#define QTD_REMOVES 450 // Quantidade de remocoes
#define PRINT_LIMIT 10 // Limite para imprimir as arvores

// TESTAGEM

void testInsertions(Node ***root);
void verifyTrees(Node **root, int fase);
void showTrees(Node **root);
void testRemoves(Node **root);