#include "common.h"
#include <stdbool.h>

typedef struct SCliente {
    char nome[50];
    char endereco[50];
    char telefone[20];
    char cpf[12];
    float totalCompras;
} TCliente;

typedef struct SListaClientes {
    int fim;
    TCliente clientes[MAX];
} TListaClientes;

TCliente cliente_inicializar();

TCliente cliente_criar(TCliente cliente);

void cliente_exibir(TCliente cliente);

TListaClientes lista_clientes_inicializar();

int lista_clientes_pesquisar_posicao_por_cpf(TListaClientes *listaClientes, char* cpf);

void lista_clientes_exibir(TListaClientes listaClientes);

bool lista_clientes_adicionar(TListaClientes *listaClientes, TCliente cliente);

bool lista_clientes_remover(TListaClientes *listaClientes, int posicaoRemover);
