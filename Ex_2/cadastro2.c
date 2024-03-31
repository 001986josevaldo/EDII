#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os dados de cada funcionário
typedef struct {
    char nome[50];
    char hierarquia[20];
} DadosFuncionario;

// Nó da lista encadeada
typedef struct NoFuncionario {
    DadosFuncionario dados;
    struct NoFuncionario* proximo;
} NoFuncionario;

// Lista encadeada para os funcionários
typedef struct {
    NoFuncionario* cabeca;
    NoFuncionario* cabecaGerentes;
    NoFuncionario* cabecaAdministrativos;
    NoFuncionario* cabecaTecnicos;
} ListaFuncionarios;

// Protótipos das funções
ListaFuncionarios* criarLista();
void destruirLista(ListaFuncionarios* lista);
void inserirFuncionario(ListaFuncionarios* lista, DadosFuncionario dados);
void listarTodosFuncionarios(ListaFuncionarios* lista);
void listarFuncionariosPorHierarquia(ListaFuncionarios* lista, char hierarquia[]);
NoFuncionario* criarNo(DadosFuncionario dados);

int main() {
    ListaFuncionarios* listaFuncionarios = criarLista();

    int escolha;
    DadosFuncionario dados;
    char hierarquia[20];

    do {
        printf("\n=== MENU ===\n");
        printf("1. Inserir Funcionario\n");
        printf("2. Listar Todos os Funcionarios\n");
        printf("3. Listar Funcionarios Por Hierarquia\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o nome do funcionario: ");
                scanf("%s", dados.nome);
                printf("Digite a hierarquia (Gerente/Administrativo/Tecnico): ");
                scanf("%s", hierarquia);
                if (strcmp(hierarquia, "Gerente") != 0 && strcmp(hierarquia, "Administrativo") != 0 && strcmp(hierarquia, "Tecnico") != 0) {
                    printf("Hierarquia invalida.\n");
                    break;
                }
                strcpy(dados.hierarquia, hierarquia);
                inserirFuncionario(listaFuncionarios, dados);
                printf("Funcionario inserido com sucesso.\n");
                break;
            case 2:
                listarTodosFuncionarios(listaFuncionarios);
                break;
            case 3:
                printf("Digite a hierarquia (Gerente/Administrativo/Tecnico): ");
                scanf("%s", hierarquia);
                listarFuncionariosPorHierarquia(listaFuncionarios, hierarquia);
                break;
            case 4:
                printf("Encerrando programa.\n");
                destruirLista(listaFuncionarios);
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (1);

    return 0;
}

// Implementação das funções
ListaFuncionarios* criarLista() {
    ListaFuncionarios* lista = (ListaFuncionarios*)malloc(sizeof(ListaFuncionarios));
    if (lista == NULL) {
        printf("Erro ao alocar memoria para a lista.\n");
        exit(1);
    }

    lista->cabeca = NULL;
    lista->cabecaGerentes = NULL;
    lista->cabecaAdministrativos = NULL;
    lista->cabecaTecnicos = NULL;

    return lista;
}

void destruirLista(ListaFuncionarios* lista) {
    NoFuncionario* atual = lista->cabeca;
    NoFuncionario* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

NoFuncionario* criarNo(DadosFuncionario dados) {
    NoFuncionario* novoNo = (NoFuncionario*)malloc(sizeof(NoFuncionario));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o novo no.\n");
        exit(1);
    }

    strcpy(novoNo->dados.nome, dados.nome);
    strcpy(novoNo->dados.hierarquia, dados.hierarquia);
    novoNo->proximo = NULL;

    return novoNo;
}

void inserirFuncionario(ListaFuncionarios* lista, DadosFuncionario dados) {
    NoFuncionario* novoNo = criarNo(dados);

    if (strcmp(dados.hierarquia, "Gerente") == 0) {
        if (lista->cabecaGerentes == NULL) {
            lista->cabecaGerentes = novoNo;
        } else {
            NoFuncionario* atual = lista->cabecaGerentes;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novoNo;
        }
    } else if (strcmp(dados.hierarquia, "Administrativo") == 0) {
        if (lista->cabecaAdministrativos == NULL) {
            lista->cabecaAdministrativos = novoNo;
        } else {
            NoFuncionario* atual = lista->cabecaAdministrativos;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novoNo;
        }
    } else if (strcmp(dados.hierarquia, "Tecnico") == 0) {
        if (lista->cabecaTecnicos == NULL) {
            lista->cabecaTecnicos = novoNo;
        } else {
            NoFuncionario* atual = lista->cabecaTecnicos;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novoNo;
        }
    }

    if (lista->cabeca == NULL) {
        lista->cabeca = novoNo;
    } else {
        NoFuncionario* atual = lista->cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
}

void listarTodosFuncionarios(ListaFuncionarios* lista) {
    printf("\n=== Lista de Todos os Funcionarios ===\n");
    NoFuncionario* atual = lista->cabeca;
    while (atual != NULL) {
        printf("Nome: %s, Hierarquia: %s\n", atual->dados.nome, atual->dados.hierarquia);
        atual = atual->proximo;
    }
}
void listarFuncionariosPorHierarquia(ListaFuncionarios* lista, char hierarquia[]) {
    printf("\n=== Lista de Funcionarios da Hierarquia %s ===\n", hierarquia);
    NoFuncionario *atual = NULL;

    if (strcmp(hierarquia, "Gerente") == 0) {
        atual = lista->cabecaGerentes;
    } else if (strcmp(hierarquia, "Administrativo") == 0) {
        atual = lista->cabecaAdministrativos;
    } else if (strcmp(hierarquia, "Tecnico") == 0) {
        atual = lista->cabecaTecnicos;
    } else {
        printf("Hierarquia invalida.\n");
        return;
    }

    while (atual != NULL) {
        if (strcmp(atual->dados.hierarquia, hierarquia) == 0) {
            printf("Nome: %s, Hierarquia: %s\n", atual->dados.nome, atual->dados.hierarquia);
        }
        atual = atual->proximo;
    }
}