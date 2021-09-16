#include <stdio.h>
#include <stdlib.h>
#include "insertion.h"
#include "rotations.h"

/*
    Função para inserir um novo nó na RN
    Retorna: 
    1, quando o nó foi inserido
    0, caso contrário
*/
int insertNode(int key, Node **root) {
    Node *Z = initializeNode(key); // Inicializando o nó Z
    Node *Y = NULL; // y
    Node *pointer = (*root); // pt
    
    // Tratamento para quando a árvore está vazia
    if((*root) == NULL) {
        Z -> color = 'N'; // Colocando a cor NEGRA
        (*root) = Z;
        return 1;
    }

    // Laço para a busca
    while(pointer != NULL) {
        Y = pointer; // Pai do nó que será inserido
        if(Z -> key == pointer -> key) { // Chave já está na arvore
            Y = NULL;
            pointer = NULL;
            return 0; // Não é possível inserir na RN
        }else if(Z -> key < pointer -> key) { // Chave está a esquerda
            pointer = pointer -> left;
        }else { // Chave está a direita
            pointer = pointer -> right;
        }
    }
    // Inserindo
    if(Y != NULL) {
        Z -> parent = Y;
        if(Z -> key < Y -> key) {
            Y -> left = Z;
        }else {
            Y -> right = Z;
        }
    }
    // Correção após inserção
    insertFixup(Z, root);
    return 1; // Inserção realizada
}

/*
    Procedimento para a correçao de cores após inserção de um nó
*/
void insertFixup(Node *Z, Node **root) {
    while (Z -> parent != NULL && Z -> parent -> color == 'R') {
        if(Z -> parent == Z -> parent -> parent -> left) { // Se o pai de Z é filho esquerdo de seu pai
            Node *Y = Z -> parent -> parent -> right; // Tio de Z
            if(Y != NULL && Y -> color == 'R') { // CASO 1
                Y -> color = 'N';
                Z -> parent -> color = 'N'; // Pai e Tio de Z com cor NEGRA
                Z -> parent -> parent -> color = 'R'; // Avô de Z com cor RUBRO
                Z = Z -> parent -> parent; // Z vira seu avô 
            }else {
                if(Z == Z -> parent -> right) { // CASO 2 -  Se Z é o filho da direita
                    Z = Z -> parent;
                    leftRotation(Z, root); // Rotação a esquerda para o pai de Z
                }
                // CASO 3
                // Atualizando as cores e fazendo a rotação
                Z -> parent -> color = 'N'; 
                Z -> parent -> parent -> color = 'R';
                rightRotation((Z -> parent -> parent), root); // Rotação a direita para o avô
            }
        }else {
            Node *Y = Z -> parent -> parent -> left; // Tio de Z
            if(Y != NULL && Y -> color == 'R') { // CASO 1
                Y -> color = 'N';
                Z -> parent -> color = 'N'; // Pai e Tio de Z com cor NEGRA
                Z -> parent -> parent -> color = 'R'; // Avô de Z com cor RUBRO
                Z = Z -> parent -> parent; // Z vira seu avô 
            }else {
                if(Z == Z -> parent -> left) { // CASO 2 - Se Z é o filho da esquerda
                    Z = Z -> parent;
                    rightRotation(Z, root); // Rotação a direita para o pai de Z
                }
                // CASO 3
                // Atualizando as cores e fazendo a rotação
                Z -> parent -> color = 'N'; 
                Z -> parent -> parent -> color = 'R';
                leftRotation((Z -> parent -> parent), root); // Rotação a esquerda para o avô
            }
        }
        (*root) -> color = 'N'; // Raiz com cor NEGRA
    }
}

// Inicializa um nó que poderá ser inserido na árvore
Node *initializeNode(int key) {
    Node *p = (Node*)malloc(sizeof(Node));
    if(p == NULL) {
        printf("AVISO: FALHA NA ALOCACAO DE MEMORIA\n");
        exit(1);
    }
    p -> key = key;
    p -> color = 'R'; // Cor RUBRO para novos nós
    p -> parent = p -> left = p -> right = NULL;
    return p;
}