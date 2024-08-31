#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int value;          // Valor armazenado no nó
    struct Node* left;  // Ponteiro para o filho à esquerda
    struct Node* right; // Ponteiro para o filho à direita
} Node;

// Função para criar um novo nó
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na árvore
Node* insertNode(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

// Se o valor for menor que o valor da raiz, vou inserir ele à esquerda... sempre me perguntando "ele é maior ou menor?"
    if (value < root->value) {
        root->left = insertNode(root->left, value);
    } else if (value > root->value) {

// Se o valor for maior que o valor da raiz, vou inserir ele à direita... sempre me perguntando "ele é maior ou menor?"
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Função principal
int main() {
    Node* root = NULL;

    // Inserindo um valor na árvore
    root = insertNode(root, 10);
    root = insertNode(root, 5);
    root = insertNode(root, 15);

    // Opcional: Print para verificar a estrutura da árvore
    // (não incluído aqui para manter o código minimalista)

    return 0;
}
