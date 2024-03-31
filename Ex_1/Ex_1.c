#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição dos tipos de dados
typedef struct {
    int id; // Para simplificar, apenas um campo "id" inteiro está sendo considerado
} DataNode;

typedef struct Node {
    DataNode data;
    struct Node* next;
} Node;

typedef struct {
    int size;
    Node* head;
} List;

// Protótipos das funções
List* createList();
void push(List* list, DataNode data);
void printList(List* list);
bool isEmpty(List* list);
void pop(List* list);
Node* atPos(List* list, int index);
int indexOff(List* list, Node* node);
void erase(List* list, int index);
void insert(List* list, DataNode data, int index);
void xchgNodes(List* list, Node* nodeA, Node* nodeB);
Node* min(List* list, int index);
Node* max(List* list, int index);
void incShort(List* list);
void decShort(List* list);

// Função principal
int main() {
    List* deque = createList();
    int choice;
    DataNode data;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Inserir no topo\n");
        printf("2. Inserir no final\n");
        printf("3. Remover do topo\n");
        printf("4. Remover do final\n");
        printf("5. Verificar valor inicial\n");
        printf("6. Verificar valor final\n");
        printf("7. Imprimir DEQUE\n");
        printf("8. Encerrar programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o valor a ser inserido no topo: ");
                scanf("%d", &data.id);
                push(deque, data);
                break;
            case 2:
                printf("Digite o valor a ser inserido no final: ");
                scanf("%d", &data.id);
                insert(deque, data, deque->size);
                break;
            case 3:
                pop(deque);
                break;
            case 4:
                erase(deque, deque->size - 1);
                break;
            case 5:
                if (!isEmpty(deque)) {
                    printf("Valor inicial: %d\n", deque->head->data.id);
                } else {
                    printf("O DEQUE esta vazio.\n");
                }
                break;
            case 6:
                if (!isEmpty(deque)) {
                    Node* lastNode = atPos(deque, deque->size - 1);
                    printf("Valor final: %d\n", lastNode->data.id);
                } else {
                    printf("O DEQUE esta vazio.\n");
                }
                break;
            case 7:
                printList(deque);
                break;
            case 8:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 8);

    // Libera memória alocada
    Node* current = deque->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(deque);

    return 0;
}

// Implementações das funções

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    return list;
}

void push(List* list, DataNode data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

void printList(List* list) {
    if (isEmpty(list)) {
        printf("Lista vazia.\n");
        return;
    }

    Node* pointer = list->head;
    printf("\nDEQUE: ");
    while (pointer != NULL) {
        printf("%d ", pointer->data.id);
        pointer = pointer->next;
    }
    printf("\n");
}

bool isEmpty(List* list) {
    return (list->size == 0);
}

void pop(List* list) {
    if (!isEmpty(list)) {
        Node* pointer = list->head;
        list->head = pointer->next;
        free(pointer);
        list->size--;
    } else {
        printf("O DEQUE esta vazio.\n");
    }
}

Node* atPos(List* list, int index) {
    if (index >= 0 && index < list->size) {
        Node* node = list->head;
        int i;
        for (i = 0; i < index; i++) {
            node = node->next;
        }
        return node;
    }
    printf("\nIndice invalido.");
    return NULL;
}

int indexOff(List* list, Node* node) {
    if (node != NULL) {
        Node* pointer = list->head;
        int index = 0;
        while (pointer != node && pointer != NULL) {
            pointer = pointer->next;
            index++;
        }
        if (pointer != NULL) {
            return index;
        }
    }
    printf("No nao pertence a lista.\n");
    return -1;
}

void erase(List* list, int index) {
    if (index == 0) {
        pop(list);
    } else {
        Node* current = atPos(list, index);
        if (current != NULL) {
            Node* previous = atPos(list, index - 1);
            previous->next = current->next;
            free(current);
            list->size--;
        }
    }
}

void insert(List* list, DataNode data, int index) {
    if (index == 0) {
        push(list, data);
    } else {
        Node* current = atPos(list, index - 1); // Busca o nó anterior ao índice
        if (current != NULL) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = data;
            newNode->next = NULL;

            current->next = newNode;
            list->size++;
        }
    }
}

void xchgNodes(List* list, Node* nodeA, Node* nodeB) {
    if (nodeA == nodeB) {
        return;
    }
    int indexA = indexOff(list, nodeA);
    int indexB = indexOff(list, nodeB);
    if (indexA == -1 || indexB == -1) {
        return;
    }
    if (indexA > indexB) {
        nodeA = nodeB;
        nodeB = atPos(list, indexA);
        indexA = indexB;
        indexB = indexOff(list, nodeB);
    }
}