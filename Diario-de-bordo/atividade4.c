// Aluna: Maria Eduarda Santos Pereira CC6N

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definindo a estrutura de um nó da treap
typedef struct TreapNode {
    int key;             // Chave que será usada para manter a propriedade da árvore binária de busca
    int priority;       // Prioridade aleatória que manterá a propriedade da heap
    struct TreapNode* left;   // Ponteiro para o filho à esquerda
    struct TreapNode* right;  // Ponteiro para o filho à direita
} TreapNode;

// Função para criar um novo nó
TreapNode* createNode(int key) {
    TreapNode* newNode = (TreapNode*)malloc(sizeof(TreapNode)); // Aloca memória para o novo nó
    newNode->key = key; // Define a chave do nó
    newNode->priority = rand() % 100; // Atribui uma prioridade aleatória entre 0 e 99
    newNode->left = newNode->right = NULL; // Inicializa os filhos como nulos
    return newNode; // Retorna o novo nó criado
}

// Função para fazer uma rotação à direita
TreapNode* rightRotate(TreapNode* root) {
    TreapNode* newRoot = root->left; // O novo root será o filho à esquerda
    root->left = newRoot->right; // O filho à esquerda do root passa a ser o filho à direita do novo root
    newRoot->right = root; // O root atual se torna o filho à direita do novo root
    return newRoot; // Retorna o novo root
}

// Função para fazer uma rotação à esquerda
TreapNode* leftRotate(TreapNode* root) {
    TreapNode* newRoot = root->right; // O novo root será o filho à direita
    root->right = newRoot->left; // O filho à direita do root passa a ser o filho à esquerda do novo root
    newRoot->left = root; // O root atual se torna o filho à esquerda do novo root
    return newRoot; // Retorna o novo root
}

// Função para inserir um nó na treap
TreapNode* insert(TreapNode* root, int key) {
    // Se a árvore estiver vazia, cria um novo nó
    if (root == NULL) {
        return createNode(key);
    }

    // Inserção na subárvore esquerda ou direita com base na chave
    if (key < root->key) {
        root->left = insert(root->left, key); // Insere na subárvore esquerda
        // Verifica se a prioridade do novo nó é maior que a do root, se sim, realiza rotação à direita
        if (root->left->priority > root->priority) {
            root = rightRotate(root);
        }
    } else {
        root->right = insert(root->right, key); // Insere na subárvore direita
        // Verifica se a prioridade do novo nó é maior que a do root, se sim, realiza rotação à esquerda
        if (root->right->priority > root->priority) {
            root = leftRotate(root);
        }
    }
    return root; // Retorna a raiz atualizada da treap
}

// Função para realizar a travessia em ordem (in-order traversal)
void inorderTraversal(TreapNode* root) {
    if (root != NULL) { // Se o nó não for nulo
        inorderTraversal(root->left); // Percorre a subárvore esquerda
        printf("%d ", root->key); // Imprime a chave do nó atual
        inorderTraversal(root->right); // Percorre a subárvore direita
    }
}

// Função principal
int main() {
    TreapNode* root = NULL; // Inicializa a raiz da treap como nula
    srand(time(NULL)); // Inicializa o gerador de números aleatórios para a prioridade

    // Inserindo alguns valores na treap
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Realizando a travessia em ordem
    printf("Travessia em ordem da treap: ");
    inorderTraversal(root);
    printf("\n");
}
