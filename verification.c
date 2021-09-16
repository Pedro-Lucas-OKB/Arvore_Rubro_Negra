#include "verification.h"

/*
 Verifica se uma ABB é RUBRO-NEGRA
*/
void verifyRB(Node *node, int *result, Node *root) {
    int h1, h2;
    // Caso a arvore esteja vazia
    if(root == NULL) {
        *result = 0;
    }
    if(node == NULL) return;
    // Calculando a altura negra de cada sub-árvore
    h1 = getBlackHeight(node -> left);
    h2 = getBlackHeight(node -> right);

    // Se as alturas negras forem diferentes, então não é RN
    if(h1 != h2) {
        *result = 0;
    }
    verifyRB(node -> left, result, root);
    verifyRB(node -> right, result, root);
}

/*
    Função que retorna a altura negra de um nó +1 | bh(x) +1
    Sem contar o nó NIL (externo)
*/
int getBlackHeight(Node *node) {
    int h = 0;
    if(node == NULL) return h;
    
    Node *aux = node;
    // Caminha até o maximo possivel a esquerda (tambem funcionaria para a direita)
    while(aux != NULL) {
        if(aux -> color == 'N') {
            h++; // Se for nó NEGRO, incrementa 
        }
        aux = aux -> left;
    }
    return h; // Retorna a altura
}

// Conta a quantidade de nós de uma ABB
int nodesCount(Node *p) {
    int count;
    if(p == NULL) {
        return 0;
    }else {
        count = nodesCount(p -> left);
        count += nodesCount(p -> right);
        count++; // por causa do no atual
    }
    return count;
}