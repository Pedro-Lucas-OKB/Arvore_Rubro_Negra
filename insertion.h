#include "structRB.h"

// Inserir

int insertNode(int key, Node **root);
void insertFixup(Node *Z, Node **root);
Node *initializeNode(int key);