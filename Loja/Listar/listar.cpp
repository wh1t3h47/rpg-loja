#include "listar.hpp"
#include "../../Dialog/dialog.hpp"

using namespace std;

void listarClientes(Cliente clientes[], int count)
{
    wstring output;
    output += L"---- Lista de Clientes ----\n";

    for (int i = 0; i < count; i++)
    {
        if (i > 0)
            output += L"\n------------\n";
        output += L"Número de Cadastro: " + to_wstring(clientes[i].numeroCadastro) + L"\n";
        output += L"Nome: " + clientes[i].nome + L"\n";
        output += L"Data de Cadastro: " + clientes[i].dataCadastro + L"\n";
        output += L"E-mail: " + clientes[i].email + L"\n";
        output += L"Telefone: " + clientes[i].telefone;
    }

    dialogBox << output;
}

void listarProdutos(Produto estoque[], int count)
{
    wstring output;
    output += L"---- Lista de Produtos ----\n";

    for (int i = 0; i < count; i++)
    {
        if (i > 0)
            output += L"\n------------\n";
        output += L"Código do Produto: " + to_wstring(estoque[i].codigoProduto) + L"\n";
        output += L"Nome do Produto: " + estoque[i].nomeProduto + L"\n";
        output += L"Valor do Produto: " + floatParaReais(estoque[i].valorProduto);
        output += L"\nQuantidade: " + to_wstring(estoque[i].quantidadeProduto);
    }

    dialogBox << output;
}

void listarPedidos(Pedido pedidos[], int count)
{
    wstring output;
    output += L"---- Lista de Pedidos ----\n";

    for (int i = 0; i < count; i++)
    {
        if (i > 0)
            output += L"\n------------\n";
        output += L"Número do Pedido: " + to_wstring(pedidos[i].numeroPedido) + L"\n";
        output += L"Código do Produto: " + to_wstring(pedidos[i].codigoProduto) + L"\n";
        output += L"Quantidade: " + to_wstring(pedidos[i].quantidadeProduto) + L"\n";
        output += L"Valor Total: " + floatParaReais(pedidos[i].valorTotalPedido) + L"\n";
        output += L"Data de Entrega: " + pedidos[i].dataEntrega;
    }

    dialogBox << output;
}