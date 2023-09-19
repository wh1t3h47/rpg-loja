#pragma once
#include <string>
#include "../defines.hpp"

struct Cliente
{
    int numeroCadastro;
    std::wstring nome;
    std::wstring dataCadastro;
    std::wstring email;
    std::wstring telefone;
    // dá um valor padrão caso não tenha sido inicializada
    Cliente() : numeroCadastro(0),
                nome(L""),
                dataCadastro(L""),
                email(L""),
                telefone(L"") {}
};

struct Produto
{
    int codigoProduto;
    std::wstring nomeProduto;
    float valorProduto;
    int quantidadeProduto;
    // dá um valor padrão caso não tenha sido inicializada
    Produto() : codigoProduto(0),
                nomeProduto(L""),
                valorProduto(0.0f),
                quantidadeProduto(0)
    {
    }
};

struct Pedido
{
    int numeroPedido;
    int codigoProduto;
    int quantidadeProduto;
    float valorTotalPedido;
    std::wstring dataEntrega;
    // dá um valor padrão caso não tenha sido inicializada
    Pedido() : numeroPedido(0),
               codigoProduto(0),
               quantidadeProduto(0),
               valorTotalPedido(0.0f),
               dataEntrega(L"") {}
};

struct _RetornoPedido
{
    Pedido pedido[MAX_PEDIDOS];
    Produto estoque[MAX_PRODUTOS];
};

typedef struct _RetornoPedido RetornoPedido;
