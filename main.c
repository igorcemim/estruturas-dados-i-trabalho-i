#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct {
    char nome[50];
    char endereco[50];
    char telefone[11];
    char cpf[11];
} TCliente;

typedef struct {
    int codigo;
    char descricao[50];
    float valor;
} TProduto;

typedef struct {
    int fim;
    TCliente listaClientes[MAX];
} TListaClientes;

typedef struct {
    int fim;
    TProduto produtos[MAX];
} TListaProdutos;

typedef struct {
    TCliente cliente;
    int fim;
    TProduto produtos[MAX];
} TAtendimento;

TCliente cliente_inicializar() {
    TCliente cliente;

    strcpy(cliente.nome, "");
    strcpy(cliente.endereco, "");
    strcpy(cliente.telefone, "");
    strcpy(cliente.cpf, "");

    return cliente;
}

TCliente cliente_criar() {
    TCliente cliente = cliente_inicializar();

    printf("Informe seu CPF:\n");
    scanf(" %s", cliente.cpf);
    printf("Informe seu nome:\n");
    scanf(" %s", cliente.nome);
    printf("Informe seu endereço:\n");
    scanf(" %s", cliente.endereco);
    printf("Informe seu telefone:\n");
    scanf(" %s", cliente.telefone);

    return cliente;
}

void cliente_exibir(TCliente cliente) {
    printf("Cliente: \n");
    printf("CPF: %s\n", cliente.cpf);
    printf("Nome: %s\n", cliente.nome);
    printf("Endereço: %s\n", cliente.endereco);
    printf("Telefone: %s\n", cliente.telefone);
}

TProduto produto_inicializar() {
    TProduto produto;

    produto.codigo = 0;
    strcpy(produto.descricao, "");
    produto.valor = 0;

    return produto;
}

TProduto produto_criar() {
    TProduto produto=produto_inicializar();

    printf("Informe o código:\n");
    scanf("%d", &produto.codigo);
    printf("Informe a descrição:\n");
    scanf("%s", produto.descricao);
    printf("Informe o valor:\n");
    scanf("%f", &produto.valor);

    return produto;
}

void produto_exibir(TProduto produto) {
    printf("Produto: \n");
    printf("Código: %d\n", produto.codigo);
    printf("Descrição: %s\n", produto.descricao);
    printf("Valor: %.2f\n", produto.valor);
}

TListaProdutos lista_produtos_inicializar() {
    TListaProdutos listaProdutos;
    listaProdutos.fim = 0;

    return listaProdutos;
}

TProduto* lista_produtos_pesquisar_por_codigo(TListaProdutos* listaProdutos, int codigo) {
    for (int i = 0; i < listaProdutos->fim; i++) {
        if (listaProdutos->produtos[i].codigo == codigo) {
            return &listaProdutos->produtos[i];
        }
    }

    return NULL;
}

void lista_produtos_exibir(TListaProdutos listaProdutos) {
    printf("PRODUTOS\n");
    for (int i = 0; i < listaProdutos.fim; i++) {
        printf("----------------------------------\n");
        produto_exibir(listaProdutos.produtos[i]);
    }
}

void lista_produtos_adicionar(TListaProdutos* listaProdutos, TProduto produto) {
    if (listaProdutos->fim == MAX) {
        printf("Lista cheia.\n");
    } else {
        int posicaoInsercao;

        for (posicaoInsercao = 0; posicaoInsercao < listaProdutos->fim; posicaoInsercao++) {
            if(listaProdutos->produtos[posicaoInsercao].codigo > produto.codigo)
                break;
        }

        if (listaProdutos->fim > 0) {
            for(int i = listaProdutos->fim; i > posicaoInsercao; i--){
                listaProdutos->produtos[i] = listaProdutos->produtos[i - 1];
            }
        }

        listaProdutos->produtos[posicaoInsercao] = produto;
        listaProdutos->fim++;
        printf("Produto adicionado.\n");
    }
}

int main(void) {
    TListaProdutos listaProdutos = lista_produtos_inicializar();
    srand(time(NULL)); // Seed para números pseudo-aleatórios

    for (int i = 0; i < 5; i++) {
        int codigo = rand() % 10 + 1;
        TProduto produto = produto_inicializar();
        produto.codigo = codigo;
        strcpy(produto.descricao, "Teste");
        produto.valor = 10.50;

        lista_produtos_adicionar(&listaProdutos, produto);
    }

    lista_produtos_exibir(listaProdutos);

    TProduto* produto = lista_produtos_pesquisar_por_codigo(&listaProdutos, 5);
    if (produto) {
        printf("\n!-------------------------\n");
        printf("\n\nProduto encontrado!\n\n");
        strcpy(produto->descricao, "Produto encontrado!");
        produto_exibir(*produto);
        printf("\n!-------------------------\n");
    } else {
        printf("\n\nProduto não encontrado.\n\n");
    }

    lista_produtos_exibir(listaProdutos);

    return (EXIT_SUCCESS);
}
