//
// Created by josevaldo on 26/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura do nó da lista encadeada
typedef struct No {
    int dado;
    struct No* prox;
} No;

// Função para inserir um novo nó no início da lista
void inserirNoInicio(No** inicio, int novoDado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = novoDado;
    novoNo->prox = *inicio;
    *inicio = novoNo;
}

// Função para remover e retornar o maior elemento da lista
int removerMaximo(No** inicio) {
    if (*inicio == NULL) {
        printf("Lista vazia.\n");
        return -1;
    }

    No* atual = *inicio;
    No* prev = NULL;
    No* maxNo = *inicio;
    No* prevMaxNo = NULL;

    while (atual->prox != NULL) {
        if (atual->prox->dado > maxNo->dado) {
            maxNo = atual->prox;
            prevMaxNo = atual;
        }
        atual = atual->prox;
    }

    int maxDado = maxNo->dado;

    if (prevMaxNo != NULL) {
        prevMaxNo->prox = maxNo->prox;
    } else {
        *inicio = maxNo->prox;
    }

    free(maxNo);
    return maxDado;
}

// Função para imprimir os elementos da lista
void imprimirLista(No* inicio) {
    No* atual = inicio;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    No* L = NULL; // Lista L
    No* K = NULL; // Lista K

    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int n;
    printf("Digite a quantidade de elementos a serem inseridos na lista L: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Quantidade inválida.\n");
        return 1;
    }

    // Preenche a lista L com números aleatórios não repetidos
    for (int i = 0; i < n; i++) {
        int novoDado;
        do {
            novoDado = rand() % 100; // Números aleatórios de 0 a 99
        } while (L != NULL && novoDado == L->dado); // Garante que não seja repetido
        inserirNoInicio(&L, novoDado);
    }

    printf("\nLista L desordenada: ");
    imprimirLista(L);

    // Remove elementos de L e insere em K de forma ordenada
    while (L != NULL) {
        int max = removerMaximo(&L);
        inserirNoInicio(&K, max);
    }

    printf("\nLista K ordenada: ");
    imprimirLista(K);

    // Libera memória
    No* temp;
    while (K != NULL) {
        temp = K;
        K = K->prox;
        free(temp);
    }

    return 0;
}