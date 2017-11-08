#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "produto.h"
#include "cliente.h"
#include "pprint.h"
#include "caixa.h"

TAtendimento atendimento_inicializar() {
    TAtendimento atendimento;
    atendimento.topo = 0;
    return atendimento;
}

void atendimento_pop(TAtendimento *atendimento) {
    atendimento->produtos[atendimento->topo - 1] = 0;
    atendimento->topo--;
}

void atendimento_push(TAtendimento *atendimento, int codigoProduto) {
    atendimento->produtos[atendimento->topo] = codigoProduto;
    atendimento->topo++;
}

void atendimento_exibir(TAtendimento atendimento, TListaProdutos listaProdutos) {
    TProduto produto;
    int posicao;
    float totalAtendimento = 0;

    for (int i = atendimento.topo - 1; i >= 0; i--) {
        posicao = lista_produtos_pesquisar_posicao_por_codigo(&listaProdutos, atendimento.produtos[i]);
        produto = listaProdutos.produtos[posicao];
        totalAtendimento += produto.valor;
        produto_exibir(produto);
        pseparador();
    }
    printf("\n\nTotal em compras: %.2f\n\n", totalAtendimento);
}

TCaixa caixa_inicializar() {
    TCaixa caixa;
    caixa.total = 0;
    return caixa;
}

float caixa_contabilizar_atendimento(
    TCaixa *caixa,
    TListaProdutos *listaProdutos,
    TListaClientes *listaClientes,
    TAtendimento atendimento
) {
    int codigoProduto;
    int codigoCliente;
    int posicao;
    float totalAtendimento;
    TProduto produto;

    for (int i = atendimento.topo - 1; i >= 0; i--) {
        codigoProduto = atendimento.produtos[i];
        posicao = lista_produtos_pesquisar_posicao_por_codigo(listaProdutos, codigoProduto);
        produto = listaProdutos->produtos[posicao];

        listaProdutos->produtos[codigoProduto].totalVendas += produto.valor;
        totalAtendimento += produto.valor;
    }
    listaClientes->clientes[codigoCliente].totalCompras += totalAtendimento;
    caixa->total += totalAtendimento;

    return totalAtendimento;
}
