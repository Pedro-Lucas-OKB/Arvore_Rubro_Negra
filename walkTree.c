#include <stdio.h>
#include "walkTree.h"

// Percurso pré-ordem
void preOrder(Node *node) {
    if(node == NULL) return;

    printf("| No %d -> COR = %c |", node -> key, node -> color);
    // Filho esquerdo
    if (node -> left != NULL) {
        printf(" -> ESQUERDA: %d -> COR = %c |", node -> left -> key, node -> left -> color);
    }else{
        printf(" -> ESQUERDA: NULL");
    }

    // Filho direito
    if (node -> right != NULL) {
        printf(" -> DIREITA: %d -> COR = %c |", node -> right -> key, node -> right -> color);
    }else{
        printf(" -> DIREITA: NULL");
    }

    // Pai
    if (node -> parent != NULL) {
        printf(" -> PAI: %d -> COR = %c |", node -> parent -> key, node -> parent -> color);
    }else{
        printf(" -> PAI: NULL");
    }
    printf("\n\n");

    preOrder(node -> left);
    preOrder(node -> right);
}

// Percurso pós-ordem
void postOrder(Node *node) {
    if(node == NULL) return;
    postOrder(node -> left);
    postOrder(node -> right);

    printf("| No %d -> COR = %c |", node -> key, node -> color);
    printf("\n");
}