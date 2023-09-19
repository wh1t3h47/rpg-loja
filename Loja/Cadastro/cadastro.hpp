#ifndef CADASTRO_HPP
#define CADASTRO_HPP

#include "../../Dialog/dialog.hpp"
#include "../Listar/listar.hpp"
#include "../loja.hpp"
#include "../utils.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>

extern Cliente *cadastrarCliente(Cliente clientes[], int &clienteIndex);
extern Produto *cadastrarProduto(Produto estoque[], int &produtoIndex, int &codigoProduto);
extern RetornoPedido *cadastrarPedido(Pedido pedidos[], Produto produtos[], int &pedidoIndex, Produto estoque[], int produtoIndex, int clienteIndex, RetornoPedido *retorno);

#endif // CADASTRO_HPP
