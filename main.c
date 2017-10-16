#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX 100
#define SEM_RESULTADO -1

typedef struct {
    char nome[50];
    char endereco[50];
    char telefone[20];
    char cpf[12];
} TCliente;

typedef struct {
    int codigo;
    char descricao[50];
    float valor;
} TProduto;

typedef struct {
    int fim;
    TCliente clientes[MAX];
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

TListaClientes listaClientes;
TListaProdutos listaProdutos;

void ptitulo(char* message) {
    printf("\n\n## %s\n\n", message);
}

void psubtitulo(char* message) {
    printf("\n\n### %s\n\n", message);
}

void pseparador() {
    printf("\n----------------------------\n");
}

TCliente cliente_inicializar() {
    TCliente cliente;

    strcpy(cliente.nome, "");
    strcpy(cliente.endereco, "");
    strcpy(cliente.telefone, "");
    strcpy(cliente.cpf, "");

    return cliente;
}

TCliente cliente_criar() {
    pseparador();
    TCliente cliente = cliente_inicializar();

    ptitulo("Cliente");

    printf("Informe seu CPF: \n");
    scanf(" %11s", cliente.cpf);
    printf("Informe seu nome: \n");
    scanf(" %49s", cliente.nome);
    printf("Informe seu endereço: \n");
    scanf(" %49s", cliente.endereco);
    printf("Informe seu telefone: \n");
    scanf(" %19s", cliente.telefone);
    pseparador();

    return cliente;
}

void cliente_exibir(TCliente cliente) {
    ptitulo("Cliente");

    printf("CPF: %s \n", cliente.cpf);
    printf("Nome: %s \n", cliente.nome);
    printf("Endereço: %s \n", cliente.endereco);
    printf("Telefone: %s \n", cliente.telefone);
}

TProduto produto_inicializar() {
    TProduto produto;

    produto.codigo = 0;
    strcpy(produto.descricao, "");
    produto.valor = 0;

    return produto;
}

TProduto produto_criar() {
    pseparador();
    TProduto produto=produto_inicializar();

    ptitulo("Produto");

    printf("Informe o código:\n");
    scanf("%d", &produto.codigo);
    printf("Informe a descrição:\n");
    scanf("%s", produto.descricao);
    printf("Informe o valor:\n");
    scanf("%f", &produto.valor);
    pseparador();

    return produto;
}

void produto_exibir(TProduto produto) {
    ptitulo("Produto");

    printf("Código: %d\n", produto.codigo);
    printf("Descrição: %s\n", produto.descricao);
    printf("Valor: %.2f\n", produto.valor);
}

TListaClientes lista_clientes_inicializar() {
    TListaClientes listaClientes;
    listaClientes.fim = 0;

    return listaClientes;
}

int lista_clientes_pesquisar_posicao_por_cpf(TListaClientes* listaClientes, char* cpf) {
    for (int i = 0; i < listaClientes->fim; i++) {
        if (strcmp(listaClientes->clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }

    return SEM_RESULTADO;
}

void lista_clientes_exibir(TListaClientes listaClientes){
    pseparador();
    ptitulo("Clientes");

    if (listaClientes.fim > 0) {

        for (int i = 0; i < listaClientes.fim; i++){
            pseparador();
            cliente_exibir(listaClientes.clientes[i]);
        }
    } else {
        printf("Nenhum cliente cadastrado.\n\n");
    }
    pseparador();
}

bool lista_clientes_adicionar(TListaClientes* listaClientes, TCliente cliente) {
    if (listaClientes->fim == MAX) {
        return false;
    }

    int posicaoInsercao;

    for (posicaoInsercao = 0; posicaoInsercao < listaClientes->fim; posicaoInsercao++) {
        if(atoi(listaClientes->clientes[posicaoInsercao].cpf) > atoi(cliente.cpf))
            break;
    }

    if (listaClientes->fim > 0) {
        for(int i = listaClientes->fim; i > posicaoInsercao; i--){
            listaClientes->clientes[i] = listaClientes->clientes[i - 1];
        }
    }

    listaClientes->clientes[posicaoInsercao] = cliente;
    listaClientes->fim++;

    return true;
}

bool lista_clientes_remover(TListaClientes* listaClientes, int posicaoRemover) {
    if(posicaoRemover >= listaClientes->fim){
        return false;
    }

    for(int i = posicaoRemover; i < listaClientes->fim; i++) {
        listaClientes->clientes[i] = listaClientes->clientes[i + 1];
    }
    listaClientes->fim--;

    return true;
}

TListaProdutos lista_produtos_inicializar() {
    TListaProdutos listaProdutos;
    listaProdutos.fim = 0;

    return listaProdutos;
}

int lista_produtos_pesquisar_posicao_por_codigo(TListaProdutos* listaProdutos, int codigo) {
    for (int i = 0; i < listaProdutos->fim; i++) {
        if (listaProdutos->produtos[i].codigo == codigo) {
            return i;
        }
    }

    return SEM_RESULTADO;
}

void lista_produtos_exibir(TListaProdutos listaProdutos) {
    pseparador();
    ptitulo("Produtos");

    if (listaProdutos.fim > 0) {

        for (int i = 0; i < listaProdutos.fim; i++) {
            pseparador();
            produto_exibir(listaProdutos.produtos[i]);
        }
    } else {
        printf("Nenhum produto cadastrado.\n\n");
    }
    pseparador();
}

bool lista_produtos_adicionar(TListaProdutos* listaProdutos, TProduto produto) {
    if (listaProdutos->fim == MAX) {
        return false;
    }

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

    return true;
}

bool lista_produtos_remover(TListaProdutos* listaProdutos, int posicaoRemover) {
    if(posicaoRemover >= listaProdutos->fim){
        return false;
    }

    for(int i = posicaoRemover; i < listaProdutos->fim; i++) {
        listaProdutos->produtos[i] = listaProdutos->produtos[i + 1];
    }
    listaProdutos->fim--;

    return true;
}

void menu() {
    char cpf[11];
    int operacao, posicao;
    TCliente cliente;

    do {
        printf("1 - Cliente: Cadastrar \n");
        printf("2 - Cliente: Alterar \n");
        printf("3 - Cliente: Remover \n");
        printf("4 - Cliente: Listar \n");
        printf("5 - Cliente: Pesquisar \n");
        printf("6 - Produto: Cadastrar \n");
        printf("7 - Produto: Alterar \n");
        printf("8 - Produto: Remover \n");
        printf("9 - Produto: Listar \n");
        printf("10 - Produto: Pesquisar \n");
        printf("0 - Sair\n");
        scanf(" %d", &operacao);

        switch (operacao) {

            case 1:
                cliente = cliente_criar();
                lista_clientes_adicionar(&listaClientes, cliente);
                break;

            case 2:
                printf("Informe o CPF do cliente:\n");
                scanf(" %s", cpf);
                posicao = lista_clientes_pesquisar_posicao_por_cpf(&listaClientes, cpf);
                if (posicao != SEM_RESULTADO) {
                    lista_clientes_remover(&listaClientes, posicao);
                    cliente = cliente_criar();
                    lista_clientes_adicionar(&listaClientes, cliente);
                    printf("Cliente removido.\n");
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;

            case 3:
                printf("Informe o CPF do cliente:\n");
                scanf(" %s", cpf);
                posicao = lista_clientes_pesquisar_posicao_por_cpf(&listaClientes, cpf);
                if (posicao != SEM_RESULTADO) {
                    lista_clientes_remover(&listaClientes, posicao);
                    printf("Cliente removido.\n");
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;

            case 4:
                lista_clientes_exibir(listaClientes);
                break;
        }
    } while (operacao != 0);
}

int main(void) {

    listaProdutos = lista_produtos_inicializar();
    listaClientes = lista_clientes_inicializar();

    menu();

    return (EXIT_SUCCESS);
}
