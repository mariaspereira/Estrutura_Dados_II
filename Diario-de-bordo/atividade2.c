// Aluna: Maria Eduarda Santos Pereira CC6N - Segunda atividade (AVL)

#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da Árvore AVL
struct NoAVL {
    int dado;                // Valor armazenado no nó
    struct NoAVL *esquerda;  // Ponteiro para o filho à esquerda
    struct NoAVL *direita;   // Ponteiro para o filho à direita
    int altura;              // Altura do nó
};

// Função para criar um novo nó
struct NoAVL *criarNo(int dado) {
    struct NoAVL *novoNo = (struct NoAVL *)malloc(sizeof(struct NoAVL)); // Aloca memória para um novo nó
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(-1); // Encerra o programa em caso de erro
    }
    novoNo->dado = dado;      // Define o valor do nó
    novoNo->esquerda = NULL; // Inicializa o filho à esquerda como NULL
    novoNo->direita = NULL;  // Inicializa o filho à direita como NULL
    novoNo->altura = 0;      // Inicializa a altura do nó como 0
    return novoNo;           // Retorna o novo nó criado
}

// Função para calcular a altura de um nó
int altura(struct NoAVL *no) {
    if (no == NULL) {
        return -1; // Se o nó for NULL, retorna -1
    }
    return no->altura; // Retorna a altura do nó
}

// Função para calcular o fator de balanceamento de um nó
int fatorBalanceamento(struct NoAVL *no) {
    if (no == NULL) {
        return 0; // Se o nó for NULL, o fator de balanceamento é 0
    }
    // Calcula a diferença entre a altura da subárvore esquerda e a subárvore direita
    return altura(no->esquerda) - altura(no->direita);
}

// Rotação para a direita
struct NoAVL *rotacaoDireita(struct NoAVL *no) {
    struct NoAVL *novaRaiz = no->esquerda;       // Nova raiz será o nó à esquerda
    struct NoAVL *subArvore = novaRaiz->direita; // Subárvore da nova raiz

    // Realiza a rotação
    novaRaiz->direita = no;
    no->esquerda = subArvore;

    // Atualiza a altura dos nós após a rotação
    no->altura = 1 + (altura(no->esquerda) > altura(no->direita) ? altura(no->esquerda) : altura(no->direita));
    novaRaiz->altura = 1 + (altura(novaRaiz->esquerda) > altura(novaRaiz->direita) ? altura(novaRaiz->esquerda) : altura(novaRaiz->direita));

    return novaRaiz; // Retorna a nova raiz
}

// Rotação para a esquerda
struct NoAVL *rotacaoEsquerda(struct NoAVL *no) {
    struct NoAVL *novaRaiz = no->direita;         // Nova raiz será o nó à direita
    struct NoAVL *subArvore = novaRaiz->esquerda; // Subárvore da nova raiz

    // Realiza a rotação
    novaRaiz->esquerda = no;
    no->direita = subArvore;

    // Atualiza a altura dos nós após a rotação
    no->altura = 1 + (altura(no->esquerda) > altura(no->direita) ? altura(no->esquerda) : altura(no->direita));
    novaRaiz->altura = 1 + (altura(novaRaiz->esquerda) > altura(novaRaiz->direita) ? altura(novaRaiz->esquerda) : altura(novaRaiz->direita));

    return novaRaiz; // Retorna a nova raiz
}

// Função para balancear a árvore após uma inserção
struct NoAVL *balancear(struct NoAVL *raiz, int dado) {
    // Atualiza a altura do nó atual
    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    // Calcula o fator de balanceamento do nó
    int balanceamento = fatorBalanceamento(raiz);

    // Rotação para a direita se a árvore estiver desbalanceada à esquerda
    if (balanceamento > 1 && dado < raiz->esquerda->dado) {
        return rotacaoDireita(raiz);
    }

    // Rotação para a esquerda se a árvore estiver desbalanceada à direita
    if (balanceamento < -1 && dado > raiz->direita->dado) {
        return rotacaoEsquerda(raiz);
    }

    // Rotação dupla à esquerda-direita
    if (balanceamento > 1 && dado > raiz->esquerda->dado) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    // Rotação dupla à direita-esquerda
    if (balanceamento < -1 && dado < raiz->direita->dado) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    // Retorna o nó atual se não houver necessidade de rotação
    return raiz;
}

// Função para inserir um novo nó na árvore AVL
struct NoAVL *inserir(struct NoAVL *raiz, int dado) {
    if (raiz == NULL) {
        return criarNo(dado); // Cria um novo nó se a raiz for NULL
    }

    // Insere o nó na subárvore esquerda ou direita
    if (dado < raiz->dado) {
        raiz->esquerda = inserir(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = inserir(raiz->direita, dado);
    }

    // Balanceia a árvore após a inserção
    return balancear(raiz, dado);
}

// Função para percorrer a árvore em ordem
void percorrerEmOrdem(struct NoAVL *raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda); // Percorre a subárvore esquerda
        printf("%d ", raiz->dado);        // Imprime o valor do nó
        percorrerEmOrdem(raiz->direita);  // Percorre a subárvore direita
    }
}

// Função principal
int main() {
    struct NoAVL *raiz = NULL; // Inicializa a árvore vazia

    // Insere alguns valores na árvore
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 25);

    printf("Árvore em ordem: ");
    percorrerEmOrdem(raiz); // Mostra a árvore em ordem
    printf("\n");

    return 0;
}
