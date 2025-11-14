#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Codigo da Ilha – Edicao Free Fire
// Nivel: Mestre
// Este programa simula o gerenciamento avancado de uma mochila com componentes coletados
// durante a fuga de uma ilha. No nivel Mestre, sao adicionadas funcionalidades de:
// - Ordenacao por criterios (nome, tipo, quantidade)
// - Busca binaria (exige ordenacao previa)
// O objetivo e otimizar a gestao dos recursos para uma sobrevivencia eficiente.

// ========================= PROTOTIPOS =========================
void exibirMenu();
void limparTela();
void inserirItem();
void removerItem();
void listarItens();
void buscarItemPorNome();           // Funcao de busca sequencial (Nivel Aventureiro)
void menuDeOrdenacao();             // Exibe opcoes de ordenacao (Nivel Mestre)
void insertionSort(int criterio);   // Ordenacao por insercao com criterios
void buscaBinariaPorNome();         // Busca binaria (Nivel Mestre)

// ========================= ENUM DE CRITERIOS =========================
// Criterios de ordenacao utilizados pelo nivel Mestre.
// Define como os itens serao comparados durante o insertionSort.
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_QUANTIDADE = 3
} CriterioOrdenacao;

// ========================= STRUCT =========================
// Representa um item carregado na mochila, contendo:
// nome   - nome do item
// tipo   - categoria do item
// quantidade - quantidade coletada
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
} Item;

// ========================= VARIAVEIS GLOBAIS =========================
// Vetor mochila armazena ate 10 itens.
// numItens controla quantos itens estao atualmente inseridos.
// ordenadoPorNome controla se a mochila esta ordenada por nome
// (requisito para busca binaria).
Item mochila[10];
int numItens = 0;
bool ordenadoPorNome = false;

// ========================= FUNCOES UTILITARIAS =========================

// limparTela():
// Simula a limpeza da tela imprimindo varias linhas em branco.
void limparTela() {
    for (int i = 0; i < 40; i++) {
        printf("\n");
    }
}

// exibirMenu():
// Mostra ao jogador todas as opcoes disponiveis no nivel Mestre,
// incluindo ordenacao e busca binaria.
void exibirMenu() {
    printf("===============================================\n");
    printf("        Codigo da Ilha – Mochila Mestre        \n");
    printf("===============================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item por nome (busca sequencial)\n");
    printf("5. Ordenar itens\n");
    printf("6. Buscar por nome (busca binaria)\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

// ========================= CRUD =========================

// inserirItem():
// Adiciona um item no vetor mochila se houver espaco.
// Qualquer insercao invalida a ordenacao por nome.
void inserirItem() {
    if (numItens >= 10) {
        printf("\nA mochila esta cheia. Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\nDigite o nome do item: ");
    scanf(" %49[^\n]", novo.nome);

    printf("Digite o tipo do item: ");
    scanf(" %49[^\n]", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[numItens] = novo;
    numItens++;

    ordenadoPorNome = false;
    printf("\nItem adicionado com sucesso.\n");
}

// removerItem():
// Remove um item buscando pelo nome.
// Move os itens posteriores para preencher o espaco vazio.
// Qualquer remocao invalida a ordenacao por nome.
void removerItem() {
    if (numItens == 0) {
        printf("\nNao ha itens para remover.\n");
        return;
    }

    char nomeRemover[50];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %49[^\n]", nomeRemover);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {

            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            numItens--;
            ordenadoPorNome = false;
            printf("\nItem removido com sucesso.\n");
            return;
        }
    }

    printf("\nItem nao encontrado na mochila.\n");
}

// listarItens():
// Exibe todos os itens em formato de tabela.
void listarItens() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n=========== ITENS NA MOCHILA ===========\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("----------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d\n",
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade);
    }

    printf("----------------------------------------\n");
}

// ========================= BUSCA SEQUENCIAL =========================

// buscarItemPorNome():
// Realiza uma busca simples percorrendo todos os itens.
// Ideal quando nao ha ordenacao.
void buscarItemPorNome() {

    if (numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    char nomeBusca[50];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %49[^\n]", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado.\n");
}

// ========================= MENU DE ORDENACAO =========================

// menuDeOrdenacao():
// Permite escolher entre os tres criterios de ordenacao
// e aplica o insertionSort conforme a escolha.
void menuDeOrdenacao() {

    if (numItens == 0) {
        printf("\nNao ha itens para ordenar.\n");
        return;
    }

    int opcao;

    printf("\nEscolha o criterio de ordenacao:\n");
    printf("1. Nome\n");
    printf("2. Tipo\n");
    printf("3. Quantidade\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    insertionSort(opcao);

    if (opcao == ORDENAR_NOME) {
        ordenadoPorNome = true;
    } else {
        ordenadoPorNome = false;
    }

    printf("\nItens ordenados com sucesso.\n");
}

// ========================= INSERTION SORT =========================

// insertionSort():
// Ordena o vetor mochila de acordo com o criterio escolhido.
// Implementacao classica do algoritmo de insercao.
void insertionSort(int criterio) {

    for (int i = 1; i < numItens; i++) {
        Item atual = mochila[i];
        int j = i - 1;

        while (j >= 0) {

            bool deveTrocar = false;

            if (criterio == ORDENAR_NOME) {
                deveTrocar = strcmp(atual.nome, mochila[j].nome) < 0;
            }
            else if (criterio == ORDENAR_TIPO) {
                deveTrocar = strcmp(atual.tipo, mochila[j].tipo) < 0;
            }
            else if (criterio == ORDENAR_QUANTIDADE) {
                deveTrocar = atual.quantidade < mochila[j].quantidade;
            }

            if (!deveTrocar)
                break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = atual;
    }
}

// ========================= BUSCA BINARIA =========================

// buscaBinariaPorNome():
// Encontra um item rapidamente caso a lista esteja ordenada por nome.
// Caso nao esteja ordenada, orienta o usuario a ordenar antes.
void buscaBinariaPorNome() {

    if (!ordenadoPorNome) {
        printf("\nA mochila precisa estar ordenada por nome antes da busca binaria.\n");
        return;
    }

    char nomeBusca[50];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %49[^\n]", nomeBusca);

    int inicio = 0;
    int fim = numItens - 1;

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;

        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            return;
        }

        if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nItem nao encontrado.\n");
}
