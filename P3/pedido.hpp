/*
 * pedido.hpp
 *
 *  Created on: 7 may. 2020
 *      Author: Juan Francisco
 */

#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "tarjeta.hpp"

class Pedido{
public:
	Pedido();

	int numero() const;
	const Tarjeta* tarjeta();
	Fecha fecha() const;
	double total() const;

private:
	int N_pedido;
	Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
	int num_;
};
inline int Pedido::numero() const{return N_pedido;}
inline const Tarjeta* Pedido::tarjeta(){return tarjeta_;}
inline Fecha Pedido::fecha() const{return fecha_;}
inline double Pedido::total() const{return total_;}

#endif /* PEDIDO_HPP_ */

/*
El constructor realiza la compra de los artículos, para lo cual utiliza cinco parámetros:

	• La asociación entre usuarios y pedidos, representada por la clase Usuario_Pedido
	  (V. § 5.5),
	• la asociación entre pedidos y artículos, representada por la clase Pedido_Articulo
	  (V. § 5.4),
	• el Usuario que realiza la compra,
	• la Tarjeta con la que se realiza el pago, y
	• la Fecha del pedido, por omisión será la actual.

Cuando se genera un pedido de los artículos que contiene el carrito, este quedará vacío y
las existencias de los artículos vendidos actualizadas. El nuevo pedido quedará asociado
al usuario que lo realiza, a la tarjeta de pago y a los artículos incluidos en la compra.
Se llamará a los métodos apropiados de la clases de asociación para crear los enlaces
(véanse § 5.4 y § 5.5).
 */
