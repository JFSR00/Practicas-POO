/*
 * usuario_pedido.hpp
 *
 *  Created on: 7 may. 2020
 *      Author: Juan Francisco
 */

#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include <map>
#include <set>
#include "usuario.hpp"
#include "pedido.hpp"

class Usuario;
class Pedido;

class Usuario_Pedido{
public:
	typedef std::set<Pedido*> Pedidos;

	void asocia(Usuario&, Pedido&);
	void asocia(Pedido&, Usuario&);

	const Pedidos& pedidos(Usuario&);
	const Usuario* cliente(Pedido&);

private:
	std::map<Usuario*, Pedidos> UsuPed;
	std::map<Pedido*, Usuario*> PedUsu;
};

#endif /* USUARIO_PEDIDO_HPP_ */
