#include "common.h"
#include <stdbool.h>

typedef struct SProduto {
    int codigo;
    char descricao[50];
    float valor;
} TProduto;

typedef struct SListaProdutos {
    int fim;
    TProduto produtos[MAX];
} TListaProdutos;

TProduto produto_inicializar();

TProduto produto_criar(TProduto produto);

void produto_exibir(TProduto produto);

TListaProdutos lista_produtos_inicializar();

int lista_produtos_pesquisar_posicao_por_codigo(TListaProdutos* listaProdutos, int codigo);

void lista_produtos_exibir(TListaProdutos listaProdutos);

bool lista_produtos_adicionar(TListaProdutos* listaProdutos, TProduto produto);

bool lista_produtos_remover(TListaProdutos* listaProdutos, int posicaoRemover);
