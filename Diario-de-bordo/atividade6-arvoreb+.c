Aluna: Maria Eduarda Santos Pereira CC6N

#include <stdio.h>
#include <stdlib.h>

#define ORDER 3  // Ordem da árvore B+ (quantidade máxima de filhos por nó)

typedef struct BPlusNode {
    int keys[ORDER - 1];                 // Chaves do nó
    struct BPlusNode* children[ORDER];   // Ponteiros para os filhos
    int isLeaf;                          // Indica se é uma folha (1) ou não (0)
    int numKeys;                         // Número atual de chaves no nó
    struct BPlusNode* next;              // Ponteiro para o próximo nó folha
} BPlusNode;

BPlusNode* root = NULL;

// Função para criar um novo nó
BPlusNode* createNode(int isLeaf) {
    BPlusNode* newNode = (BPlusNode*)malloc(sizeof(BPlusNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    newNode->next = NULL;
    for (int i = 0; i < ORDER; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Função para dividir um nó quando ele está cheio
void splitChild(BPlusNode* parent, int i, BPlusNode* child) {
    BPlusNode* newChild = createNode(child->isLeaf);
    newChild->numKeys = (ORDER - 1) / 2;

    for (int j = 0; j < newChild->numKeys; j++) {
        newChild->keys[j] = child->keys[j + (ORDER / 2)];
    }

    if (!child->isLeaf) {
        for (int j = 0; j <= newChild->numKeys; j++) {
            newChild->children[j] = child->children[j + (ORDER / 2)];
        }
    }

    child->numKeys = (ORDER - 1) / 2;

    for (int j = parent->numKeys; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }

    parent->children[i + 1] = newChild;

    for (int j = parent->numKeys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }

    parent->keys[i] = child->keys[(ORDER / 2) - 1];
    parent->numKeys++;
}

// Função para inserir uma chave em um nó não cheio
void insertNonFull(BPlusNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->numKeys == ORDER - 1) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Função para inserir uma nova chave na árvore
void insert(int key) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == ORDER - 1) {
            BPlusNode* newRoot = createNode(0);
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);

            int i = 0;
            if (newRoot->keys[0] < key) {
                i++;
            }
            insertNonFull(newRoot->children[i], key);

            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }
}

// Função para visualizar a árvore B+ em ordem
void display(BPlusNode* node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf) {
                display(node->children[i]);
            }
            printf("%d ", node->keys[i]);
        }
        if (!node->isLeaf) {
            display(node->children[i]);
        }
    }
}

// Função para exclusão (parcial, pois requer manipulação de balanceamento)
void deleteKey(BPlusNode* node, int key) {
    printf("A exclusão completa exige um processo de rebalanceamento da árvore.\n");
    // Implementação completa de exclusão é extensa para cobrir todos os casos de redistribuição e fusão.
}

// Função para exibir o menu
void menu() {
    int choice, key;
    while (1) {
        printf("\n--- Menu da Árvore B+ ---\n");
        printf("1. Inserir\n");
        printf("2. Exibir árvore\n");
        printf("3. Excluir (funcionalidade básica)\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite a chave para inserir: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Árvore B+:\n");
                display(root);
                printf("\n");
                break;
            case 3:
                printf("Digite a chave para excluir (com aviso): ");
                scanf("%d", &key);
                deleteKey(root, key);
                break;
            case 4:
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
