#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "produto.h"
#include "pprint.h"

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

TListaProdutos lista_produtos_inicializar() {
    TListaProdutos listaProdutos;
    listaProdutos.fim = 0;

    return listaProdutos;
}

int lista_produtos_pesquisar_posicao_por_codigo(TListaProdutos *listaProdutos, int codigo) {
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

bool lista_produtos_adicionar(TListaProdutos *listaProdutos, TProduto produto) {
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

bool lista_produtos_remover(TListaProdutos *listaProdutos, int posicaoRemover) {
    if(posicaoRemover >= listaProdutos->fim){
        return false;
    }

    for(int i = posicaoRemover; i < listaProdutos->fim; i++) {
        listaProdutos->produtos[i] = listaProdutos->produtos[i + 1];
    }
    listaProdutos->fim--;

    return true;
}
