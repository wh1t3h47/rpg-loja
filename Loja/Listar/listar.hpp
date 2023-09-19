#ifndef LISTAR_HPP
#define LISTAR_HPP

#include "../../Dialog/dialog.hpp"
#include "../utils.hpp"
#include "../loja.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>

extern void listarClientes(Cliente clientes[], int count);
extern void listarProdutos(Produto estoque[], int count);
extern void listarPedidos(Pedido pedidos[], int count);

#endif // LISTAR_HPP
