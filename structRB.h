#include<stdlib.h>

#ifndef RBTREE_H
#define RBTREE_H

// Estrutura de cada nó da RN
typedef struct node {
    int key; // Chave do nó
    char color; // Cor (RUBRO ou NEGRA)
    struct node *parent; // Pai do nó
    struct node *left, *right; // Ponteiros para esuqerda e direita
} Node;


#endif