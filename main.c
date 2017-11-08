#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib/common.h"
#include "lib/pprint.h"
#include "lib/produto.h"
#include "lib/cliente.h"
#include "lib/caixa.h"

void menu_atendimento_loop(TListaClientes *listaClientes, TListaProdutos *listaProdutos, TCaixa *caixa) {
    char cpf[12];
    char opcaoCliente;
    int opcao;
    int codigo;
    int posicao;
    float totalAtendimento;
    TCliente cliente;
    TAtendimento atendimento;

    do {

        system("clear");
        ptitulo("Pesquisar Cliente para Atendimento");
        printf("\nInforme o CPF do cliente:\n");
        scanf(" %[0-9]11s", cpf);
        posicao = lista_clientes_pesquisar_posicao_por_cpf(listaClientes, cpf);
        opcaoCliente = 'n';

        /**
         * Se não encontrou resultado pergunta se o usuário deseja tentar procurar novamente.
         */
        if (posicao == SEM_RESULTADO) {
            printf("\nCliente não encontrado. Deseja tentar novamente (digite s)?\n");
            scanf(" %c", &opcaoCliente);
            /**
             * Caso negativo retorna ao menu inicial..
             */
            if (opcaoCliente != 's') {
                return;
            }
        }

    /**
     * Enquanto não houver resultado e o usuário desejar procurar um cliente.
     */
    } while (posicao == SEM_RESULTADO && opcaoCliente == 's');

    atendimento = atendimento_inicializar();
    atendimento.codigoCliente = posicao;

    do {
        system("clear");
        ptitulo("Atendimento de Cliente");

        /**
         * Adiciona produto na pilha
         */
        printf("1 - Adicionar produto na pilha \n");
        /**
         * Remove um produto da pilha
         */
        printf("2 - Remover produto da pilha \n");
        /**
         * Listar produtos
         */
        printf("3 - Mostrar produtos na pilha \n");
        /**
         * Fechar atendimento
         */
        printf("4 - Fechar atendimento \n");
        /**
         * Totaliza pedido no registro do cliente, limpa a pilha de produtos e exibe os valores em tela
         */
        printf("0 - Cancelar atendimento \n");
        scanf(" %d", &opcao);

        switch (opcao) {

            case 0:
                break;

            case 1:
                ptitulo("Adicionar produto na pilha");
                printf("\nInforme o código do produto:\n");
                scanf(" %d", &codigo);
                posicao = lista_produtos_pesquisar_posicao_por_codigo(listaProdutos, codigo);

                if (posicao != SEM_RESULTADO) {
                    atendimento_push(&atendimento, listaProdutos->produtos[posicao].codigo);
                } else {
                    printf("\nProduto não encontrado.\n");
                }

                pseparador();
                break;

            case 2:
                ptitulo("Remover produto da pilha");
                atendimento_pop(&atendimento);
                printf("\nProduto no topo da pilha removido do atendimento.\n");
                pseparador();
                break;

            case 3:
                ptitulo("Mostrar produtos na pilha");
                if (atendimento.topo == 0) {
                    printf("\nNenhum produto foi adicionado ao atendimento.\n");
                } else {
                    atendimento_exibir(atendimento, *listaProdutos);
                }

                pseparador();
                break;

            case 4:
                ptitulo("Fechar atendimento");
                printf("\nAtendimento fechado.\n");
                totalAtendimento = caixa_contabilizar_atendimento(caixa, listaProdutos, listaClientes, atendimento);
                printf("\n\nTotal em compras: %.2f\n\n", totalAtendimento);
                return;

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

    TListaProdutos listaProdutos = lista_produtos_inicializar();
    TListaClientes listaClientes = lista_clientes_inicializar();
    TCaixa caixa = caixa_inicializar();

    do {
        operacao = -1;

        system("clear");
        ptitulo("Operações do Sistema");

        printf("Cliente \n");
        printf(" 1 - Cadastrar \n");
        printf(" 2 - Alterar \n");
        printf(" 3 - Remover \n");
        printf(" 4 - Lista \n");
        printf(" 5 - Pesquisar \n\n");

        printf("Produto \n");
        printf(" 6 - Cadastrar \n");
        printf(" 7 - Alterar \n");
        printf(" 8 - Remover \n");
        printf(" 9 - Lista \n");
        printf("10 - Pesquisar \n\n");

        printf("Atendimento \n");
        printf("11 - Atender cliente \n\n");

        printf("Caixa \n");
        printf("12 - Vendas por cliente \n");
        printf("13 - Vendas por produto \n");
        printf("14 - Total em Vendas \n\n");

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

            case 8:

                ptitulo("Remover Produto");
                printf("\nInforme o código do produto:\n");
                scanf(" %d", &codigo);
                posicao = lista_produtos_pesquisar_posicao_por_codigo(&listaProdutos, codigo);

                if (posicao != SEM_RESULTADO) {
                    lista_produtos_remover(&listaProdutos, posicao);
                    printf("\nProduto removido.\n");
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

                menu_atendimento_loop(&listaClientes, &listaProdutos, &caixa);
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
