#include "main.hpp"

using namespace std;

RpgDialogBox dialogBox;

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        cout << "Uso: " << argv[0] << endl;
        return 127;
    }

    Cliente *clientes = new Cliente[MAX_CLIENTES];
    Produto *produtos = new Produto[MAX_PRODUTOS];
    Pedido *pedidos = new Pedido[MAX_PEDIDOS];

    /* Pedidos e produtos no mesmo agrupamento */
    auto pedidosProdutos = new RetornoPedido;

    dialogBox << L"Seja bem-vindo ao sistema de cadastro de clientes, produtos e pedidos!";

    int clienteIndex = 0;
    int produtoIndex = 0;
    int pedidoIndex = 0;
    int codigoProduto = 1;

    while (true)
    {
        switch (pedirInt(L"1. Cadastro de cliente"
                         L"   2. Cadastro de produtos\n"
                         L"3. Cadastro de pedidos"
                         L"   4. Listar clientes\n"
                         L"5. Listar produtos"
                         L"       6. Listar pedidos\n"
                         L"7. Sair"))
        {
        case 1:
            clientes = cadastrarCliente(clientes, clienteIndex);
            break;
        case 2:
            produtos = cadastrarProduto(produtos, produtoIndex, codigoProduto);
            break;
        case 3:
            pedidosProdutos = cadastrarPedido(pedidos, produtos, pedidoIndex, produtos, produtoIndex, clienteIndex, pedidosProdutos);
            produtos = pedidosProdutos->estoque;
            pedidos = pedidosProdutos->pedido;
            break;
        case 4:
            listarClientes(clientes, clienteIndex);
            break;
        case 5:
            listarProdutos(produtos, produtoIndex);
            break;
        case 6:
            listarPedidos(pedidos, pedidoIndex - 1);
            break;
        case 7:
            dialogBox << L"Programa encerrado.";
            return 0;
        case -1: // erro
            dialogBox << L"Erro!!! Não foi inserído um NÚMERO.";
        default:
            dialogBox << L"Opção inválida. Tente novamente.";
            break;
        }
    }

    delete[] clientes;
    delete[] produtos;
    delete[] pedidos;
    delete pedidosProdutos;

    return 0;
}
