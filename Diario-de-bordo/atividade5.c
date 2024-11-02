#Maria Eduarda Santos Pereira CC6N

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3  // Ordem da árvore B (máximo de filhos por nó)

// Estrutura do nó da árvore B
typedef struct NoB {
    int numChaves;              // Número atual de chaves no nó
    int chaves[ORDEM - 1];      // Vetor de chaves
    struct NoB* filhos[ORDEM];  // Ponteiros para os filhos
    int folha;                  // 1 se o nó for folha, 0 caso contrário
} NoB;

// Função para criar um novo nó da árvore B
NoB* criarNo(int folha) {
    NoB* novoNo = (NoB*)malloc(sizeof(NoB));
    novoNo->numChaves = 0;
    novoNo->folha = folha;
    for (int i = 0; i < ORDEM; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

// Função para percorrer a árvore B em ordem
void percorrer(NoB* raiz) {
    if (raiz != NULL) {
        for (int i = 0; i < raiz->numChaves; i++) {
            if (!raiz->folha) {
                percorrer(raiz->filhos[i]);
            }
            printf("%d ", raiz->chaves[i]);
        }
        if (!raiz->folha) {
            percorrer(raiz->filhos[raiz->numChaves]);
        }
    }
}

// Função para inserir uma chave na árvore B (raiz não cheia)
void inserirNaoCheio(NoB* no, int chave) {
    int i = no->numChaves - 1;
    if (no->folha) {
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        i++;
        if (no->filhos[i]->numChaves == ORDEM - 1) {
            dividirFilho(no, i);
            if (no->chaves[i] < chave) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}

// Função para dividir um filho em dois nós
void dividirFilho(NoB* pai, int i) {
    NoB* filho = pai->filhos[i];
    NoB* novoNo = criarNo(filho->folha);
    novoNo->numChaves = ORDEM / 2 - 1;

    for (int j = 0; j < ORDEM / 2 - 1; j++) {
        novoNo->chaves[j] = filho->chaves[j + ORDEM / 2];
    }
    if (!filho->folha) {
        for (int j = 0; j < ORDEM / 2; j++) {
            novoNo->filhos[j] = filho->filhos[j + ORDEM / 2];
        }
    }
    filho->numChaves = ORDEM / 2 - 1;
    for (int j = pai->numChaves; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = novoNo;
    for (int j = pai->numChaves - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[i] = filho->chaves[ORDEM / 2 - 1];
    pai->numChaves++;
}

// Função para inserir uma chave na árvore B
void inserir(NoB** raiz, int chave) {
    if (*raiz == NULL) {
        *raiz = criarNo(1);
        (*raiz)->chaves[0] = chave;
        (*raiz)->numChaves = 1;
    } else {
        if ((*raiz)->numChaves == ORDEM - 1) {
            NoB* novaRaiz = criarNo(0);
            novaRaiz->filhos[0] = *raiz;
            dividirFilho(novaRaiz, 0);
            inserirNaoCheio(novaRaiz, chave);
            *raiz = novaRaiz;
        } else {
            inserirNaoCheio(*raiz, chave);
        }
    }
}

// Função para exibir o menu
void menu() {
    printf("\n--- Menu Árvore B ---\n");
    printf("1. Inserir uma chave\n");
    printf("2. Exibir a árvore (em ordem)\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

// Função principal
int main() {
    NoB* raiz = NULL;
    int opcao, chave;

    do {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%d", &chave);
                inserir(&raiz, chave);
                break;
            case 2:
                printf("Árvore em ordem: ");
                percorrer(raiz);
                printf("\n");
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
