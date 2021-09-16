#include "structRB.h"

// Remover

int removeNode(int key, Node **root);
void removeFixup(Node *X, Node **root);
Node *searchNode(int key, Node *node);
Node *getSuccessor(Node *Z);
void verifyXNode(Node **ptX);
int isNIL(Node *X, Node **root);
int verifyWNode(Node *W);