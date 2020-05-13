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

inline void Usuario_Pedido::asocia(Usuario& u, Pedido& p){UsuPed[&u].insert(&p); PedUsu[&p] = &u;}
inline void Usuario_Pedido::asocia(Pedido& p, Usuario& u){asocia(u,p);}

inline const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& u){return UsuPed[&u];}
inline const Usuario* Usuario_Pedido::cliente(Pedido& p){return PedUsu[&p];}

#endif /* USUARIO_PEDIDO_HPP_ */
