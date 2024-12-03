// Matheus Correa Fiori
// GRR - 20211618
// Trabalho Estrutura de Dados II - Tabela Hash

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100

typedef struct Contato {
    char nome[50];
    char telefone[20];
    struct Contato* proximo;
} Contato;

Contato* tabelaHash[TABLE_SIZE];

unsigned int hashFunction(const char* nome) {
    unsigned int hash = 0;
    while (*nome) {
        hash += *nome++;
    }
    return hash % TABLE_SIZE;
}

void adicionarContato() {
    char nome[50], telefone[20];
    printf("Nome: ");
    scanf(" %[^\n]s", nome);
    printf("Telefone: ");
    scanf(" %[^\n]s", telefone);

    unsigned int indice = hashFunction(nome);

    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = NULL;

    if (tabelaHash[indice] == NULL) {
        tabelaHash[indice] = novoContato;
    } else {
        novoContato->proximo = tabelaHash[indice];
        tabelaHash[indice] = novoContato;
    }

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char nome[50];
    printf("Nome: ");
    scanf(" %[^\n]s", nome);

    unsigned int indice = hashFunction(nome);
    Contato* atual = tabelaHash[indice];

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Telefone de %s: %s\n", atual->nome, atual->telefone);
            return;
        }
        atual = atual->proximo;
    }

    printf("Contato nao encontrado.\n");
}

void removerContato() {
    char nome[50];
    printf("Nome: ");
    scanf(" %[^\n]s", nome);

    unsigned int indice = hashFunction(nome);
    Contato* atual = tabelaHash[indice];
    Contato* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                tabelaHash[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Contato nao encontrado.\n");
}

void exibirContatos() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato* atual = tabelaHash[i];
        if (atual != NULL) {
            printf("Indice %d:\n", i);
            while (atual != NULL) {
                printf("  Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
                atual = atual->proximo;
            }
        }
    }
}

int main() {
    int opcao;

    for (int i = 0; i < TABLE_SIZE; i++) {
        tabelaHash[i] = NULL;
    }

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato* atual = tabelaHash[i];
        while (atual != NULL) {
            Contato* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    return 0;
}