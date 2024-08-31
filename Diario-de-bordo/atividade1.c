// Aluna: Maria Eduarda Santos Pereira CC6N

#include <stdio.h>
#include <stdlib.h>

// 1 - Primeira coisa: estrutura de um nó da árvore binária
// cada nó tem: campo 'data' para armazenar o valor inteiro e dois ponteiros que apontam para filho à esquerda e filho à direita

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// 2 - Depois é estabelecido uma função para criar um novo nó
// Essa função aloca dinamicamente memória para um novo nó da árvore
// Malloc é usada para alocar memória. A função retorna um ponteiro para o novo nó.

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 3 - Função para inserção de um elemento na árvore
// Esta função insere um novo elemento na árvore binária de busca.
// Como? humm, lembra da pergunta "eu sou maior ou menor?" se árvore vazia, cria novo nó com o valor estabelecido. se o valor é menor -> esquerda. se o valor é maior -> direita

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// 4 - Função para pesquisa de um elemento na árvore
// Esta função procura um valor na árvore binária, obviamente hehe
// Como? bora lá! Se árvore vazia ou valor do nó igual o procurado - função retorna esse nó 
// Se valor procurado menor que o valor atual do nó - função pesquisa na subarvore à esquerda (lembra de menor)
// Se valor maior - pesquisa na subarvore direita 

Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// 5 - Início de uma exclusão
// Função para encontrar o nó com o MENOR valor (usado na exclusão)
// Navega pela subárvore ESQUERDA até encontrar o nó mais à esquerda, que é o menor.
Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}


// 6 - Função para exclusão de um elemento na árvore
// Encontra o nó a ser removido - se valor é menor que valor do nó atual, a função chama delete na subárvore esquerda.
// Se o valor é maior, chama delete na subárvore direita.
Node* delete(Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        // Caso 1: Nó sem filhos
        // Simplesmente libera o nó da memória = free
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Caso 2: Nó com um filho
        // Substitui o nó pelo seu único filho
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Caso 3: Nó com dois filhos
        // Encontra o menor nó da subárvore direita (findMin), copia seu valor para o nó atual e remove o menor nó da subárvore direita.
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }

    return root;
}

// 7 - Função para imprimir a árvore (ordem natural - crescente)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
// 8 - Função Principal: main
// Testa todas as operações da árvore binária.
int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Elementos da árvore: ");
    inorder(root);
    printf("\n");

    // Pesquisa de elementos
    Node* searchResult = search(root, 40);
    if (searchResult != NULL) {
        printf("Elemento 40 encontrado!\n");
    } else {
        printf("Elemento 40 não encontrado!\n");
    }

    // Exclusão de elementos
    root = delete(root, 20);
    printf("Árvore após deletar 20: ");
    inorder(root);
    printf("\n");

    root = delete(root, 30);
    printf("Árvore após deletar 30: ");
    inorder(root);
    printf("\n");

    root = delete(root, 50);
    printf("Árvore após deletar 50: ");
    inorder(root);
    printf("\n");

    return 0;
}
