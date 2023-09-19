#include "cadastro.hpp"
#include "../../Dialog/Windows/dialog_win.hpp"
#include "../../Dialog/Linux/dialog_linux.hpp"

using namespace std;

Cliente *cadastrarCliente(Cliente clientes[], int &clienteIndex)
{
    while (true)
    {
        if (clienteIndex >= MAX_CLIENTES)
        {
            dialogBox << L"Erro: Não é possível cadastrar mais clientes.";
            break;
        }

        Cliente novoCliente;
        novoCliente.numeroCadastro = clienteIndex + 1;

        dialogBox >> L"Informe o nome do cliente: " >> novoCliente.nome;
        dialogBox >> L"Informe a data de cadastro: " >> novoCliente.dataCadastro;
        dialogBox >> L"Informe o e-mail do cliente: " >> novoCliente.email;
        dialogBox >> L"Informe o telefone do cliente: " >> novoCliente.telefone;

        clientes[clienteIndex] = novoCliente;
        clienteIndex++;

        listarClientes(clientes, clienteIndex);

        if (!respostaSim(L"Deseja cadastrar mais clientes? (s/N)"))
        {
            break;
        }
    }
    return clientes;
}

Produto *cadastrarProduto(Produto estoque[], int &produtoIndex, int &codigoProduto)
{
    while (true)
    {
        if (produtoIndex >= MAX_PRODUTOS)
        {
            dialogBox << L"Erro: Não é possível cadastrar mais produtos.";
            break;
        }

        Produto novoProduto;
        novoProduto.codigoProduto = codigoProduto++;

        dialogBox >> L"Informe o nome do produto: " >> novoProduto.nomeProduto;
        while (true)
        {
            float valorProduto = pedirFloat(L"Informe o valor do produto: ");
            novoProduto.valorProduto = valorProduto;
            if (valorProduto == -1)
            {
                dialogBox << L"Valor inválido!";
            }
            else
            {
                break;
            }
        }

        while (true)
        {
            int quantidadeProduto = pedirInt(L"Informe a quantidade do produto: ");
            novoProduto.quantidadeProduto = quantidadeProduto;
            if (quantidadeProduto == -1)
            {
                dialogBox << L"Quantidade inválida!";
            }
            else
            {
                break;
            }
        }

        estoque[produtoIndex] = novoProduto;
        produtoIndex++;

        listarProdutos(estoque, produtoIndex);

        if (!respostaSim(L"Deseja cadastrar mais produtos? (s/N)"))
        {
            break;
        }
    }

    return estoque;
}

RetornoPedido *cadastrarPedido(Pedido pedidos[], Produto produtos[], int &pedidoIndex, Produto estoque[], int produtoIndex, int clienteIndex, RetornoPedido *retorno)
{
    while (true)
    {
        if (clienteIndex == 0 || produtoIndex == 0)
        {
            dialogBox << L"Erro: Não é possível cadastrar pedidos sem clientes e/ou produtos cadastrados.";
            break;
        }
        if (pedidoIndex >= MAX_PEDIDOS)
        {
            dialogBox << L"Erro: Não é possível cadastrar mais pedidos.";
            break;
        }

        Pedido novoPedido;
        novoPedido.numeroPedido = pedidoIndex++;

        while (true)
        {
            wstring codigoProdutoStr;
            int codigoProdutoEscolhido;

            dialogBox >> L"Informe o código do produto desejado (L para listar produtos): " >> codigoProdutoStr;

            if (codigoProdutoStr == L"L" || codigoProdutoStr == L"l")
            {
                listarProdutos(estoque, produtoIndex);
            }
            else
            {
                try
                {
                    codigoProdutoEscolhido = stoi(codigoProdutoStr);
                }
                catch (invalid_argument &)
                {
                    dialogBox << L"Código inválido!";
                    continue;
                }
                bool produtoEncontrado = false;
                for (int i = 0; i < produtoIndex; i++)
                {
                    if (estoque[i].codigoProduto == codigoProdutoEscolhido)
                    {
                        novoPedido.codigoProduto = codigoProdutoEscolhido;
                        produtoEncontrado = true;
                        break;
                    }
                }

                if (!produtoEncontrado)
                {
                    dialogBox << L"Produto não encontrado!";
                    continue;
                }

                break;
            }
        }

        wstring quantidadeProdutoStr;
        int quantidadeProduto = pedirInt(L"Informe a quantidade desejada: ");

        if (quantidadeProduto <= 0)
        {
            dialogBox << L"Quantidade inválida!";
            break;
        }

        // Verificar se há estoque suficiente
        int estoqueDisponivel = 0;
        for (int i = 0; i < produtoIndex; i++)
        {
            if (estoque[i].codigoProduto == novoPedido.codigoProduto)
            {
                estoqueDisponivel = estoque[i].quantidadeProduto;
                break;
            }
        }

        if (quantidadeProduto > estoqueDisponivel)
        {
            dialogBox << L"Quantidade indisponível em estoque!";
            break;
        }

        // Dar baixa no estoque
        for (int i = 0; i < produtoIndex; i++)
        {
            if (estoque[i].codigoProduto == novoPedido.codigoProduto)
            {
                estoque[i].quantidadeProduto -= quantidadeProduto;
                break;
            }
        }

        float valorTotalPedido = 0.0f;
        for (int i = 0; i < produtoIndex; i++)
        {
            if (estoque[i].codigoProduto == novoPedido.codigoProduto)
            {
                valorTotalPedido = estoque[i].valorProduto * quantidadeProduto;
                break;
            }
        }

        novoPedido.quantidadeProduto = quantidadeProduto;
        novoPedido.valorTotalPedido = valorTotalPedido;
        wstring dataEntrega = L"";

        dialogBox >> L"Informe a data de entrega: " >> dataEntrega;

        pedidos[pedidoIndex - 1] = novoPedido;

        retorno->pedido[pedidoIndex - 1] = novoPedido;
        for (int i = 0; i < produtoIndex; i++)
        {
            retorno->estoque[i] = estoque[i];
        }

        listarPedidos(retorno->pedido, pedidoIndex);

        if (!respostaSim(L"Deseja cadastrar mais pedidos? (s/N)"))
        {
            break;
        }
    }
    pedidoIndex++;
    return retorno;
}
