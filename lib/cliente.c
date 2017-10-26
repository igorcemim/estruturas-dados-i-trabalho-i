#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "cliente.h"
#include "pprint.h"

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

TListaClientes lista_clientes_inicializar() {
    TListaClientes listaClientes;
    listaClientes.fim = 0;

    return listaClientes;
}

int lista_clientes_pesquisar_posicao_por_cpf(TListaClientes *listaClientes, char* cpf) {
    for (int i = 0; i < listaClientes->fim; i++) {
        if (strcmp(listaClientes->clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }

    return SEM_RESULTADO;
}

void lista_clientes_exibir(TListaClientes listaClientes) {
    if (listaClientes.fim > 0) {
        for (int i = 0; i < listaClientes.fim; i++){
            cliente_exibir(listaClientes.clientes[i]);
        }
    } else {
        printf("\nNenhum cliente cadastrado.\n");
    }
}

bool lista_clientes_adicionar(TListaClientes *listaClientes, TCliente cliente) {
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

bool lista_clientes_remover(TListaClientes *listaClientes, int posicaoRemover) {
    if(posicaoRemover >= listaClientes->fim){
        return false;
    }

    for (int i = posicaoRemover; i < listaClientes->fim; i++) {
        listaClientes->clientes[i] = listaClientes->clientes[i + 1];
    }
    listaClientes->fim--;

    return true;
}
