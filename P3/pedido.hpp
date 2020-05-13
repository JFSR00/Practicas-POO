/*
 * pedido.hpp
 *
 *  Created on: 7 may. 2020
 *      Author: Juan Francisco
 */

#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
public:
	Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, Tarjeta&, Fecha =Fecha{});

	int numero() const;
	const Tarjeta* tarjeta();
	Fecha fecha() const;
	double total() const;

private:
	static int N_pedidos;
	int num_;
	Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
};
inline int Pedido::numero() const{return num_;}
inline const Tarjeta* Pedido::tarjeta(){return tarjeta_;}
inline Fecha Pedido::fecha() const{return fecha_;}
inline double Pedido::total() const{return total_;}

#endif /* PEDIDO_HPP_ */
