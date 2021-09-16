#include <stdio.h>
#include <stdlib.h>
#include "deletion.h"
#include "insertion.h"
#include "testing.h"
#include "rotations.h"

/*
    Função que realiza a remoção de um nó da ABB RN
    Retorna:
    1, caso o nó tenha sido removido
    0, caso contrário
*/
int removeNode(int key, Node **root) {
    Node *Z = searchNode(key, (*root)); // Procurando a chave na RN
    if(Z == NULL) return 0; // Quando o nó não está na árvore ou a RN está vazia
    Node *Y = Z;
    char yColor = Y -> color; // Variável para saber se o nó removido era de cor NEGRA
    Node *X; // Nó para o qual será feita a avalização após remoção
    // Se Z tem filho a direita, ou Z é folha
    if(Z -> left == NULL) {
        X = Z -> right;
        verifyXNode(&X); // Caso Z seja folha, X vira um nó auxiliar NIL(externo)
        moveParent(Z, X, root); // Movendo o pai de Z para X
        free(Z); // Excluindo nó Z da memória
    }else if(Z -> right == NULL) { // Caso Z tenha somente filho a esquerda
        X = Z -> left;
        verifyXNode(&X);
        moveParent(Z, X, root); // Movendo o pai de Z para X
        free(Z); // Excluindo nó Z da memória
    }else { // Caso Z seja nó com dois filhos
        Y = getSuccessor(Z); // Y vira o sucessor de Z
        yColor = Y -> color; // Atualizando a cor do Y
        X = Y -> right;
        verifyXNode(&X); // Se X for NULL, X vira NIL
        X -> parent = Y;
        // Se Y não for filho de Z, move o pai de Y para X
        if(Y -> parent != Z) {
            moveParent(Y, X, root);
            Y -> right = Z -> right;
            Y -> right -> parent = Y;
        }
        // Movendo lado esquerdo de Z, fazendo a troca de infos
        moveParent(Z, Y, root);
        Y -> left = Z -> left;
        Y -> left -> parent = Y;
        Y -> color = Z -> color; // Trocando a cor
        free(Z);
    }
    
    // Caso a árvore só tenha 1 nó, a raiz vira NULL
    if(isNIL((*root), root)) {
        (*root) = NULL;
    }else if(yColor == 'N') { // Se o nó removido era de cor NEGRA, chama a correção
        removeFixup(X, root);
    }else {
        if(isNIL(X, root)) free(X); // Tirando o nó NIL da arvore
    }
    return 1;
}

/*
    Procedimento para corrigir as cores da RN após a remoção de um nó NEGRO
*/
void removeFixup(Node *X, Node **root) {
    if(X == NULL) return;
    // Enquanto X for diferente da raiz e for de cor NEGRA
    while (X != (*root) && X -> color == 'N') {
        // Se X é o filho da esquerda de seu pai
        if(X == X -> parent -> left) {
            Node *W = X -> parent -> right; // Irmão de X
            // CASO 1: W tem cor RUBRO
            if(W -> color == 'R') {
                // Troca de cores e rotação a esquerda
                X -> parent -> color = 'R';
                W -> color = 'N';
                leftRotation(X -> parent, root);
                W = X -> parent -> right; // Atualizando o W
            }

            // CASO 2: W tem dois filhos com cor NEGRA
            int cont = verifyWNode(W);
            if(cont == 2) {
                W -> color = 'R'; // Troca a cor de W, reduzindo a quantidade de nós NEGROS
                // Verificando se X é NIL, antes de X se mover
                if(isNIL(X, root)) {
                    Node *aux = X;
                    X = X -> parent;
                    free(aux);
                }else X = X -> parent;
            }else {
                // Caso 3: W tem filho esquerdo RUBRO
                if(W -> left != NULL) {
                    if(W -> left -> color == 'R') {
                        // Troca de cores e rotação a direita
                        W -> left -> color = 'N';
                        W -> color = 'R';
                        rightRotation(W, root);
                        W = X -> parent -> right;
                    }
                }
                // CASO 4:
                // Troca de cores e rotação a esquerda
                W -> color = X -> parent -> color;
                W -> right -> color = 'N';
                W -> parent -> color = 'N';
                leftRotation(X -> parent, root);
                if(isNIL(X, root)) free(X);
                X = (*root); // X vira a raiz
            }
        }else { // Caso onde X é o filho da direita de seu pai | Análogo ao anterior
            Node *W = X -> parent -> left; // Irmão de X

            // CASO 1
            if(W -> color == 'R') {
                X -> parent -> color = 'R';
                W -> color = 'N';
                rightRotation(X -> parent, root);
                W = X -> parent -> left;
            }

            // Verificando os filhos de W
            int cont = verifyWNode(W);
            // CASO 2
            if(cont == 2) { 
                W -> color = 'R'; // Troca a cor de W, reduzindo a quantidade de nós NEGROS
                if(isNIL(X, root)) {
                    Node *aux = X;
                    X = X -> parent;
                    free(aux);
                }else X = X -> parent;
            }else {
                // CASO 3
                if(W -> right != NULL) {
                    if(W -> right -> color == 'R') {
                        W -> right -> color = 'N';
                        W -> color = 'R';
                        leftRotation(W, root);
                        W = X -> parent -> left;
                    }
                }
                // CASO 4
                // Troca de cores e rotação a direita
                W -> color = X -> parent -> color;
                W -> left -> color = 'N';
                W -> parent -> color = 'N';
                rightRotation(X -> parent, root);
                if(isNIL(X, root)) free(X);;
                X = (*root);
            }
        }
    }
    X -> color = 'N';
}

// Busca um nó na ABB, de acordo com a chave
Node *searchNode(int key, Node *node) {
    if(node == NULL) return node;

    if(key == node -> key) {
        return node; // Retorna o nó encontrado
    }else if(key < node -> key) {
        return searchNode(key, node -> left);
    }else {
        return searchNode(key, node -> right);
    }
} 

// Retorna o sucessor de um nó na ABB
Node *getSuccessor(Node *Z) {
    Node *Y = Z -> right;
    // Nó mais a esquerda da sub-arvore direita de Z
    while(Y -> left != NULL) {
        Y = Y -> left;
    }
    return Y;
}

/* Transforma o nó X em NIL(externo), caso ele seja NULL.
   Isso é necessário para não se ter problemas na correção do remover.
*/
void verifyXNode(Node **ptX) {
    if((*ptX) == NULL) {
        (*ptX) = initializeNode(RAND_LIMITER + 1); // Valor máximo da arvore +1, para poder diferenciar
        (*ptX) -> color = 'N'; // NIL(externo) tem cor NEGRA
    }
}

/*
    Função para saber se o nó é o nó NIL(externo)
*/
int isNIL(Node *X, Node **root) {
    if(X -> key == (RAND_LIMITER + 1)) {
        moveParent(X, X -> right, root); //Removendo o nó NIL da RN, movendo o pai
        return 1;
    }
    return 0;
}

/*
    Verificação para saber a cor dos filhos do nó W
    Retorna:
    0, caso seus filhos sejam RUBROS
    1, caso um de seus filhos seja RUBRO
    2, caso seus filhos sejam NEGROS
*/
int verifyWNode(Node *W) {
    int cont = 0;
    if(W -> left != NULL) {
        if(W -> left -> color == 'N') {
            cont++;
        }
    }else {
        //Caso seja NULL, conta como nó NIL(externo) de cor NEGRA
        cont++;
    }

    if(W -> right != NULL) {
        if(W -> right -> color == 'N') {
            cont++;
        }
    }else {
        //Caso seja NULL, conta como nó NIL(externo) de cor NEGRA
        cont++;
    }

    return cont;
}