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
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->dado = novoDado;
    novoNo->prox = *inicio;
    *inicio = novoNo;
}

// Função para inverter a direção dos ponteiros na lista
void inverterLista(No** inicio) {
    No* atual = *inicio;
    No* proximo = NULL;
    No* anterior = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    *inicio = anterior;
}

// Função para imprimir os elementos da lista
void imprimirLista(No* inicio) {
    No* atual = inicio;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->prox;
    }
    printf("NULL\n");
}

int main() {
    No* lista = NULL;
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int quantidade;
    printf("Digite a quantidade de elementos para a lista: ");
    scanf("%d", &quantidade);

    // Insere elementos aleatórios na lista
    for (int i = 0; i < quantidade; i++) {
        int novoDado = rand() % 100; // Números aleatórios de 0 a 99
        inserirNoInicio(&lista, novoDado);
    }

    printf("Lista original: ");
    imprimirLista(lista);

    // Inverte a direção dos ponteiros na lista
    inverterLista(&lista);

    printf("Lista com ligacoes invertidas: ");
    imprimirLista(lista);

    // Libera a memória alocada para a lista
    No* atual = lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}