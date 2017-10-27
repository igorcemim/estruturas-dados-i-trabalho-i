#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib/common.h"
#include "lib/pprint.h"
#include "lib/produto.h"
#include "lib/cliente.h"

typedef struct SAtendimento {
    TCliente cliente;
    int fim;
    TProduto produtos[MAX];
} TAtendimento;

typedef struct SCaixa {
    float total;
    TListaProdutos produtosVendidos;
} TCaixa;

void menu_atendimento_loop(TListaClientes *listaClientes, TListaProdutos *listaProdutos) {
    char cpf[12];
    char opcaoCliente;
    int opcao;
    int posicao;
    TCliente cliente;

    do {

        system("clear");
        ptitulo("Pesquisar Cliente para Atendimento");
        printf("\nInforme o CPF do cliente:\n");
        scanf(" %[0-9]11s", cpf);
        posicao = lista_clientes_pesquisar_posicao_por_cpf(listaClientes, cpf);
        opcaoCliente = 'n';

        if (posicao != SEM_RESULTADO) {
            cliente = listaClientes->clientes[posicao];
        } else {
            printf("\nCliente não encontrado. Deseja tentar novamente (digite s)?\n");
            scanf(" %c", &opcaoCliente);
            if (opcaoCliente != 's') {
                return;
            }
        }
    } while (posicao == SEM_RESULTADO && opcaoCliente == 's');

    do {
        system("clear");
        ptitulo("Atendimento de Cliente");

        /**
         * Adiciona produto na pilha
         */
        printf("1 - Adicionar produto \n");
        /**
         * Remove um produto da pilha
         */
        printf("2 - Remover produto \n");
        /**
         * Totaliza pedido no registro do cliente, limpa a pilha de produtos e exibe os valores em tela
         */
        printf("0 - Finalizar atendimento \n");
        scanf(" %d", &opcao);

        switch (opcao) {

            case 0:
                break;

            default:
                printf("\nOpção inválida.\n");

        }
        if (opcao != 0) {
            system("echo 'Pressione ENTER para voltar ao menu.'; read x");
        }
    } while (opcao != 0);
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

            case 11:

                menu_atendimento_loop(&listaClientes, &listaProdutos);
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
