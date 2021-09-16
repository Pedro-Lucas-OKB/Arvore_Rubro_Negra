#include <stdlib.h>
#include "rotations.h"

// Rotação a esquerda
void leftRotation(Node *pointer, Node **root) {
    if(pointer == NULL) return;
    Node *U = pointer -> right;
    pointer -> right = U -> left;
    if(U -> left != NULL) {
        U -> left -> parent = pointer; // Ligando o pai a pointer
    }
    moveParent(pointer, U, root); // Ajustando o pai
    U -> left = pointer;
    pointer -> parent = U;
}

// Rotação a direita
void rightRotation(Node *pointer, Node **root) {
    if(pointer == NULL) return;
    Node *U = pointer -> left;
    pointer -> left = U -> right;
    if(U -> right != NULL) {
        U -> right -> parent = pointer; // Ligando o pai a pointer
    }
    moveParent(pointer, U, root); // Ajustando o pai
    U -> right = pointer;
    pointer -> parent = U;
}

// Move o pai de U para V
void moveParent(Node *U, Node *V, Node **root) {
    if(V != NULL) V -> parent = U -> parent; // Atualizando pai de V

    if(U -> parent == NULL) {
        (*root) = V; // Caso U seja a raiz
    }else {
        if(U -> parent -> left == U) { // Se U é o filho da esquerda
            U -> parent -> left = V;
        }else { // Se U é o filho da direita
            U -> parent -> right = V;
        }
    }
}