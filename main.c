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
    float totalCompras;
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

typedef struct {
    float total;
    TListaProdutos produtosVendidos;
} TCaixa;

void pseparador() {
    printf("\n----------------------------\n");
}

void ptitulo(char* message) {
    pseparador();
    printf("\n %s\n", message);
    pseparador();
}

void psubtitulo(char* message) {
    printf("\n# %s\n", message);
}

TCliente cliente_inicializar() {
    TCliente cliente;

    strcpy(cliente.nome, "");
    strcpy(cliente.endereco, "");
    strcpy(cliente.telefone, "");
    strcpy(cliente.cpf, "");
    cliente.totalCompras = 0;

    return cliente;
}

TCliente cliente_criar(TCliente cliente) {
    ptitulo("Cadastro de Cliente");

    /**
     * Não pede o CPF na alteração.
     */
    if (strcmp(cliente.cpf, "") == 0) {
        printf("\nInforme o CPF: \n");
        scanf(" %[0-9]11s", cliente.cpf);
    }

    printf("\nInforme o nome: \n");
    scanf(" %[^\n]49s", cliente.nome);
    printf("\nInforme o endereço: \n");
    scanf(" %[^\n]49s", cliente.endereco);
    printf("\nInforme o telefone: \n");
    scanf(" %[0-9 .-]19s", cliente.telefone);
    pseparador();

    return cliente;
}

void cliente_exibir(TCliente cliente) {
    ptitulo("Informações do Cliente");

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

TProduto produto_criar(TProduto produto) {
    ptitulo("Cadastro de Produto");

    if (produto.codigo == 0) {
        printf("\nInforme o código:\n");
        scanf(" %d", &produto.codigo);
    }

    printf("\nInforme a descrição:\n");
    scanf(" %s", produto.descricao);
    printf("\nInforme o valor:\n");
    scanf(" %f", &produto.valor);
    pseparador();

    return produto;
}

void produto_exibir(TProduto produto) {
    ptitulo("Informações do Produto");

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
    if (listaClientes.fim > 0) {

        for (int i = 0; i < listaClientes.fim; i++){
            cliente_exibir(listaClientes.clientes[i]);
        }
    } else {
        printf("\nNenhum cliente cadastrado.\n");
    }
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

    for (int i = posicaoRemover; i < listaClientes->fim; i++) {
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
    if (listaProdutos.fim > 0) {

        for (int i = 0; i < listaProdutos.fim; i++) {
            produto_exibir(listaProdutos.produtos[i]);
        }
    } else {
        printf("\nNenhum produto cadastrado.\n");
    }
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

void menu_loop() {
    char cpf[12];
    int operacao;
    int posicao;
    int codigo;
    TCliente cliente;
    TProduto produto;
    TListaClientes listaClientes;
    TListaProdutos listaProdutos;

    listaProdutos = lista_produtos_inicializar();
    listaClientes = lista_clientes_inicializar();

    do {
        system("clear");
        ptitulo("Operações do Sistema");

        printf(" 1 - Cliente: Cadastrar \n");
        printf(" 2 - Cliente: Alterar \n");
        printf(" 3 - Cliente: Remover \n");
        printf(" 4 - Cliente: Lista \n");
        printf(" 5 - Cliente: Pesquisar \n\n");

        printf(" 6 - Produto: Cadastrar \n");
        printf(" 7 - Produto: Alterar \n");
        printf(" 8 - Produto: Remover \n");
        printf(" 9 - Produto: Lista \n");
        printf("10 - Produto: Pesquisar \n\n");

        printf("11 - Atender cliente \n\n");
        printf("12 - Relatório: Vendas por cliente \n");
        printf("13 - Relatório: Total do Dia \n");
        printf("14 - Relatório: Produtos Vendidos \n\n");

        printf("0 - Sair\n");
        scanf(" %d", &operacao);

        switch (operacao) {

            case 1:

                cliente = cliente_criar(cliente_inicializar());
                lista_clientes_adicionar(&listaClientes, cliente);
                printf("\nCliente cadastrado.\n");

                pseparador();
                break;

            case 2:

                ptitulo("Alterar Cliente");
                printf("\nInforme o CPF do cliente:\n");
                scanf(" %[0-9]11s", cpf);
                posicao = lista_clientes_pesquisar_posicao_por_cpf(&listaClientes, cpf);

                if (posicao != SEM_RESULTADO) {
                    printf("\nCliente encontrado, informe os novos dados.\n");
                    /**
                     * Guarda o cliente na memória.
                     */
                    cliente = cliente_criar(listaClientes.clientes[posicao]);
                    /**
                     * Remove o cliente da lista...
                     */
                    lista_clientes_remover(&listaClientes, posicao);
                    /**
                     * E adiciona o objeto alterado na lista.
                     */
                    lista_clientes_adicionar(&listaClientes, cliente);
                    printf("\nCliente alterado.\n");
                } else {
                    printf("\nCliente não encontrado.\n");
                }

                pseparador();
                break;

            case 3:

                ptitulo("Remover Cliente");
                printf("\nInforme o CPF do cliente:\n");
                scanf(" %[0-9]11s", cpf);
                posicao = lista_clientes_pesquisar_posicao_por_cpf(&listaClientes, cpf);

                if (posicao != SEM_RESULTADO) {
                    lista_clientes_remover(&listaClientes, posicao);
                    printf("\nCliente removido.\n");
                } else {
                    printf("\nCliente não encontrado.\n");
                }

                pseparador();
                break;

            case 4:

                ptitulo("Lista de Clientes");
                lista_clientes_exibir(listaClientes);

                pseparador();
                break;
                
            case 5:

                ptitulo("Pesquisar Cliente");
                scanf(" %[0-9]11s", cpf);
                posicao = lista_clientes_pesquisar_posicao_por_cpf(&listaClientes, cpf);

                if (posicao != SEM_RESULTADO) {
                    cliente_exibir(listaClientes.clientes[posicao]);
                } else {
                    printf("\nCliente não encontrado.\n");
                }
                        
                pseparador();
                break;
                
            case 6:

                produto = produto_criar(produto_inicializar());
                lista_produtos_adicionar(&listaProdutos, produto);
                printf("\nProduto cadastrado.\n");

                pseparador();
                break;
                
            case 7:

                ptitulo("Alterar Produto");
                printf("\nInforme o código do produto:\n");
                scanf(" %d", &codigo);
                posicao = lista_produtos_pesquisar_posicao_por_codigo(&listaProdutos, codigo);

                if (posicao != SEM_RESULTADO) {
                    printf("\nProduto encontrado, informe os novos dados.\n");
                    produto = produto_criar(listaProdutos.produtos[posicao]);
                    lista_produtos_remover(&listaProdutos, posicao);
                    lista_produtos_adicionar(&listaProdutos, produto);
                    printf("\nProduto alterado.\n");
                } else {
                    printf("\nProduto não encontrado.\n");
                }

                pseparador();
                break;
                
            case 9:
                
                ptitulo("Lista de Produtos");
                lista_produtos_exibir(listaProdutos);

                pseparador();
                break;
            
            case 10:

                ptitulo("Pesquisar Produto");
                printf("\nInforme o código do produto:\n");
                scanf(" %d", &codigo);
                posicao = lista_produtos_pesquisar_posicao_por_codigo(&listaProdutos, codigo);

                if (posicao != SEM_RESULTADO) {
                    produto_exibir(listaProdutos.produtos[posicao]);
                } else {
                    printf("\nProduto não encontrado.\n");
                }

                pseparador();
                break;

            case 0:
                break;

            default:

                printf("\nA opção informada é inválida.\n\n");
        }
        if (operacao != 0) {
            system("echo 'Pressione ENTER para voltar ao menu.'; read x");
        }
    } while (operacao != 0);
}

int main(void) {
    menu_loop();
    return (EXIT_SUCCESS);
}
