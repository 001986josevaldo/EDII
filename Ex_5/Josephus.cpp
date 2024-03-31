//
// Created by josevaldo on 26/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura do nó da lista circular
typedef struct Node {
    int soldado;
    struct Node* prox;
} Node;

// Função para criar um novo nó
Node* criarNovoNo(int soldado) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->soldado = soldado;
    novoNo->prox = NULL;
    return novoNo;
}

// Função para inserir um novo nó no final da lista
void inserirNoFinal(Node** inicio, int soldado) {
    Node* novoNo = criarNovoNo(soldado);
    if (*inicio == NULL) {
        *inicio = novoNo;
        novoNo->prox = *inicio;
    } else {
        Node* atual = *inicio;
        while (atual->prox != *inicio) {
            atual = atual->prox;
        }
        atual->prox = novoNo;
        novoNo->prox = *inicio;
    }
}

// Função para remover um nó da lista
void removerNo(Node** inicio, Node* alvo) {
    if (*inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Node* atual = *inicio;
    Node* anterior = NULL;

    while (atual->prox != *inicio) {
        if (atual == alvo) {
            if (anterior == NULL) { // Se for o primeiro nó da lista
                Node* temp = *inicio;
                while (temp->prox != *inicio) {
                    temp = temp->prox;
                }
                temp->prox = (*inicio)->prox;
                *inicio = (*inicio)->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Verifica o último nó da lista
    if (atual == alvo) {
        if (anterior == NULL) { // Se houver apenas um nó na lista
            free(*inicio);
            *inicio = NULL;
        } else {
            anterior->prox = *inicio;
            free(atual);
        }
    }
}

// Função para imprimir a lista circular
void imprimirLista(Node* inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Node* atual = inicio;
    do {
        printf("%d ", atual->soldado);
        atual = atual->prox;
    } while (atual != inicio);
    printf("\n");
}

int main() {
    Node* lista = NULL;
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int tamanho;
    printf("Digite o tamanho da lista de soldados: ");
    scanf("%d", &tamanho);

    // Preenche a lista com números de 1 a tamanho
    for (int i = 1; i <= tamanho; i++) {
        inserirNoFinal(&lista, i);
    }

    printf("Lista de soldados inicial: ");
    imprimirLista(lista);

    int rodada = 1;
    while (lista != NULL && lista->prox != lista) {
        int passos = (rand() % (2 * tamanho)) - tamanho; // Sorteia número de -tamanho a tamanho
        if (passos == 0) {
            printf("Valor inválido, realizando novo sorteio.\n");
            continue;
        }

        // Realiza a contagem para a esquerda ou direita
        Node* atual = lista;
        if (passos > 0) {
            for (int i = 1; i < passos; i++) {
                atual = atual->prox;
            }
        } else {
            for (int i = 0; i < (-passos); i++) {
                atual = atual->prox;
            }
        }

        Node* proximo = atual->prox;
        printf("Rodada %d: Soldado eliminado: %d\n", rodada, proximo->soldado);
        removerNo(&lista, proximo);

        rodada++;
    }

    if (lista != NULL) {
        printf("Soldado escolhido para a tarefa: %d\n", lista->soldado);
        free(lista);
    }

    return 0;
}