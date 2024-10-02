#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_PRODUTOS 50
#define MAX_CARRINHO 50

typedef struct {
    int id;
    char nome[50];
    float preco;
} Produto;

typedef struct {
    int idProduto;
    int quantidade;
} Carrinho;

Produto produtos[MAX_PRODUTOS];
Carrinho carrinho[MAX_CARRINHO];
int contadorProdutos = 0;
int contadorCarrinho = 0;

int produtoJaCadastrado(int id, const char *nome) { // funcao que verifica e impede a duplicagem de produtos com o mesmo ID
    for (int i = 0; i < contadorProdutos; i++) {
        if (produtos[i].id == id) {
            printf("Produto com ID %d ja cadastrado.\n", id);
            return 1;
        }
        if (strcmp(produtos[i].nome, nome) == 0) {
            printf("Produto com nome \"%s\" ja cadastrado.\n", nome);
            return 2;
        }
    }
    return 0;
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarProduto() { // o cadastro se limita em 50 produtos
    if (contadorProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    Produto newProduct;
    int resultado;

    // Leitura do ID
    do {
        printf("ID: ");
        if (scanf("%d", &newProduct.id) != 1) {
            printf("NUMERO INVALIDO. TENTE NOVAMENTE!!!\n\n");
            limparBufferEntrada();
        } else {
            limparBufferEntrada();
            break;
        }
    } while (1);

    // Leitura do nome do produto
    do {
        int isValid = 1;

        printf("NOME DO PRODUTO: ");
        fgets(newProduct.nome, sizeof(newProduct.nome), stdin);
        newProduct.nome[strcspn(newProduct.nome, "\n")] = 0;

        for (int i = 0; newProduct.nome[i] != '\0'; i++) {
            if (!((newProduct.nome[i] >= 'A' && newProduct.nome[i] <= 'Z') ||
                    (newProduct.nome[i] >= 'a' && newProduct.nome[i] <= 'z') ||
                    newProduct.nome[i] == ' ')) {
                isValid = 0;
                printf("NOME INVALIDO. TENTE NOVAMENTE!!!\n\n");
                break;
            }
        }

        if (isValid) {
            break;
        }

    } while (1);

    // Leitura do preço
    do {
        printf("PRECO: ");
        if (scanf("%f", &newProduct.preco) != 1) {
            printf("VALOR INVALIDO. TENTE NOVAMENTE!!!\n\n");
            limparBufferEntrada();
        } else {
            limparBufferEntrada();
            break;
        }
    } while (1);

    resultado = produtoJaCadastrado(newProduct.id, newProduct.nome);
    if (resultado == 0) {
        produtos[contadorProdutos] = newProduct;
        contadorProdutos++;
        printf("\nPRODUTO CADASTRADO COM SUCESSO!\n\n\n");
    } else {
        printf("Por favor, insira um novo produto.\n\n");
    }
}

void listarProdutos() { // listagem de produtos cadastrados
    if (contadorProdutos == 0) {
        printf("\nNenhum Produto Cadastrado ainda...\n\n");
        return;
    }
    printf("LISTA DE PRODUTOS:\n\n ");
    for (int i = 0; i < contadorProdutos; i++) {
        printf("ID: %d\nNome: %s\nPreco: %.2f\n\n", produtos[i].id, produtos[i].nome, produtos[i].preco);
    }

    // Oferecer a opção de alterar produto
    int opcao, id;
    printf("Deseja alterar algum produto? (1 - Sim, 2 - Nao): ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Digite o ID do produto que deseja alterar: ");
        scanf("%d", &id);
        alterarProduto(id);
    }
}

void comprarProdutos() {
    if (contadorProdutos == 0) {
        printf("\nNenhum produto disponivel para compra.\n\n");
        return;
    }

    int id, quantidade, i, encontrado = 0;

    listarProdutos(); // antes de comprar, os produtos cadastrados aparecem para facilitar a escolha do usuario
    printf("Digite o ID do PRODUTO que deseja adicionar ao carrinho: ");
    scanf("%d", &id);

    for (i = 0; i < contadorProdutos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("\nProduto com ID %d nao encontrado.\n\n", id);
        return;
    }

    printf("Digite a quantidade que deseja: ");
    scanf("%d", &quantidade);

    for (i = 0; i < contadorCarrinho; i++) {
        if (carrinho[i].idProduto == id) {
            carrinho[i].quantidade += quantidade;
            printf("Produto atualizado no carrinho.\n\n");
            return;
        }
    }

    carrinho[contadorCarrinho].idProduto = id;
    carrinho[contadorCarrinho].quantidade = quantidade;
    contadorCarrinho++;

    printf("\nProduto adicionado ao carrinho.\n\n");
}

void visualizarCarrinho() {
    if (contadorCarrinho == 0) {
        printf("\nSeu carrinho esta vazio.\n\n");
        return;
    }

    printf("PRODUTOS NO CARRINHO:\n\n"); // é visualizado todas as informacoes do produto comprado
    for (int i = 0; i < contadorCarrinho; i++) {
        for (int j = 0; j < contadorProdutos; j++) {
            if (produtos[j].id == carrinho[i].idProduto) {
                printf("ID: %d\nNome: %s\nPreco: %.2f\nQuantidade: %d\n\n",
                       produtos[j].id, produtos[j].nome, produtos[j].preco, carrinho[i].quantidade);
            }
        }
    }

    // Oferecer opções para alterar ou remover produtos no carrinho
    int opcao;
    printf("Deseja alterar ou remover algum produto do carrinho? (1 - Alterar, 2 - Remover, 3 - Nao): ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        alterarQuantidadeCarrinho();
    } else if (opcao == 2) {
        removerProdutoDoCarrinho();
    }
}

// Função para remover produto do carrinho
void removerProdutoDoCarrinho() {
    int id, i, j, encontrado = 0;
    printf("Digite o ID do produto que deseja remover: ");
    scanf("%d", &id);

    for (i = 0; i < contadorCarrinho; i++) {
        if (carrinho[i].idProduto == id) {
            encontrado = 1;
            for (j = i; j < contadorCarrinho - 1; j++) {
                carrinho[j] = carrinho[j + 1];
            }
            contadorCarrinho--;
            printf("Produto removido do carrinho.\n\n");
            return;
        }
    }

    if (!encontrado) {
        printf("\nProduto com ID %d nao encontrado no carrinho.\n\n", id);
    }
}

// Função para alterar quantidade de produto no carrinho
void alterarQuantidadeCarrinho() {
    int id, novaQuantidade;
    printf("Digite o ID do produto que deseja alterar a quantidade: ");
    scanf("%d", &id);

    for (int i = 0; i < contadorCarrinho; i++) {
        if (carrinho[i].idProduto == id) {
            printf("Digite a nova quantidade: ");
            scanf("%d", &novaQuantidade);
            carrinho[i].quantidade = novaQuantidade;
            printf("Quantidade atualizada.\n\n");
            return;
        }
    }

    printf("Produto com ID %d nao encontrado no carrinho.\n\n", id);
}

  // Função para alterar dados de um produto já cadastrado
  void alterarProduto(int id) {
    int encontrado = 0;

    for (int i = 0; i < contadorProdutos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            printf("Digite o novo nome do produto: ");
            limparBufferEntrada();
            fgets(produtos[i].nome, sizeof(produtos[i].nome), stdin);
            produtos[i].nome[strcspn(produtos[i].nome, "\n")] = 0;

            printf("Digite o novo preco do produto: ");
            scanf("%f", &produtos[i].preco);

            printf("Produto atualizado com sucesso!\n\n");
            return;
        }
    }

    if (!encontrado) {
        printf("Produto com ID %d nao encontrado.\n\n", id);
    }
}

void fecharCompra() {
    if (contadorCarrinho == 0) {
        printf("\nSeu carrinho esta vazio.\n\n");
        return;
    }

    float valorTotal = 0;
    printf("ITENS COMPRADOS:\n\n");

    for (int i = 0; i < contadorCarrinho; i++) {
        for (int j = 0; j < contadorProdutos; j++) {
            if (produtos[j].id == carrinho[i].idProduto) {
                float subtotal = produtos[j].preco * carrinho[i].quantidade;
                valorTotal += subtotal;
                printf("ID: %d\nNome: %s\nQuantidade: %d\nPreco Unitario: %.2f\nSubtotal: %.2f\n\n",
                       produtos[j].id, produtos[j].nome, carrinho[i].quantidade, produtos[j].preco, subtotal);
            }
        }
    }

    printf("Valor total da compra: R$ %.2f\n", valorTotal);

    contadorCarrinho = 0;
    printf("\nPedido finalizado com sucesso!\n\n");
}
 void restart(){ // reiniciar o programa
    contadorCarrinho=0;
    contadorProdutos=0;
    menu();
 }

void menu() {
    int inicio;

    printf("BEM VINDO(A) AO MERCADO!! \n\n");
    do {
        printf("O QUE DESEJA FAZER A SEGUIR?\n\n");
        printf(" -> 1 para CADASTRAR PRODUTO\n");
        printf(" -> 2 para LISTAR PRODUTOS\n");
        printf(" -> 3 para COMPRAR PRODUTO\n");
        printf(" -> 4 para VISUALIZAR SEU CARRINHO\n");
        printf(" -> 5 para CONCLUIR PEDIDO\n");
        printf(" -> 0 para LIMPAR E REINICIAR O PROGRAMA\n\n");
        printf("Opcao Escolhida: ");
        scanf("%d", &inicio);
        system("cls");

        switch (inicio) {
        case 1:
            printf("CADASTRO DE PRODUTO!\n\n");
            cadastrarProduto();
            break;
        case 2:
            printf("LISTAGEM DE PRODUTOS CADASTRADOS:\n\n ");
            listarProdutos();
            break;
        case 3:
            printf("COMPRA DE PRODUTOS\n\n");
            comprarProdutos();
            break;
        case 4:
            printf("VISUALIZAR CARRINHO\n\n");
            visualizarCarrinho();
            break;
        case 5:
            printf("CONCLUIR PEDIDO\n\n");
            fecharCompra();
            break;
        case 0:
            restart();
            break;
        default:
            printf("NUMERO INVALIDO. TENTE NOVAMENTE!!!\n\n");
            break;
        }
    } while (inicio != 0);
}

int main() {
    menu();
    return 0;
}
