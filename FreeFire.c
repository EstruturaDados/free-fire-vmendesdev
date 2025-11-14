#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// ========================= PROTÓTIPOS =========================
void exibirMenu();
void limparTela();
void inserirItem();
void removerItem();
void listarItens();
void buscarItemPorNome();   // Nova função do nível Aventureiro

// ========================= FUNÇÃO PRINCIPAL =========================
int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Buscar item por nome (Nível Aventureiro)
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        limparTela();

        switch (opcao) {
            case 1:
                inserirItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                buscarItemPorNome();  // Inclusão do Nível Aventureiro
                break;

            case 0:
                printf("\nSaindo do sistema... Ate a proxima missao.\n");
                break;

            default:
                printf("\n Opcao invalida! Tente novamente.\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); // absorve '\n' anterior
        getchar(); // aguarda ENTER
        limparTela();

    } while (opcao != 0);

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochila[10];
int numItens = 0;

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 40; i++) {
        printf("\n");
    }
}

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu() {
    printf("===============================================\n");
    printf("        Codigo da Ilha – Mochila Aventureiro   \n");
    printf("===============================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item por nome\n"); // Opção adicionada no nível Aventureiro
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem() {
    if (numItens >= 10) {
        printf("\nA mochila esta cheia! Nao e possivel adicionar mais itens.\n");
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

    printf("\nItem adicionado com sucesso!\n");
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
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
            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem nao encontrado na mochila.\n");
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia!\n");
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

// buscarItemPorNome():
// Realiza busca sequencial por nome (Nível Aventureiro).
// Se encontrar, exibe os dados do item.
// Caso contrário, informa que não encontrou o item.
void buscarItemPorNome() {

    if (numItens == 0) {
        printf("\nA mochila esta vazia. Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[50];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %49[^\n]", nomeBusca);

    bool encontrado = false;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);

            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado na mochila.\n");
    }
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
