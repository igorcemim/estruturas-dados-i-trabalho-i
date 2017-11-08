
typedef struct SAtendimento {
    int codigoCliente;
    int topo;
    int produtos[MAX]; // Códigos dos produtos
} TAtendimento;

typedef struct SCaixa {
    float total;
} TCaixa;

TAtendimento atendimento_inicializar();

void atendimento_pop(TAtendimento *atendimento);

void atendimento_push(TAtendimento *atendimento, int codigoProduto);

void atendimento_exibir(TAtendimento atendimento, TListaProdutos listaProdutos);

TCaixa caixa_inicializar();

float caixa_contabilizar_atendimento(
    TCaixa *caixa,
    TListaProdutos *listaProdutos,
    TListaClientes *listaClientes,
    TAtendimento atendimento
);