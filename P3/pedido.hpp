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
#include <ostream>

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
public:
	Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha& =Fecha());

	int numero() const;
	const Tarjeta* tarjeta() const;
	Fecha fecha() const;
	double total() const;
	static int n_total_pedidos();

	class Vacio{
		Usuario *us_;
	public:
		Vacio(Usuario*);
		Usuario& usuario() const;
	};

	class Impostor{
		Usuario *us_;
	public:
		Impostor(Usuario*);
		Usuario& usuario() const;
	};

	class SinStock{
		Articulo *art_;
	public:
		SinStock(Articulo*);
		Articulo& articulo() const;
	};

private:
	static int N_pedidos;
	int num_;
	const Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
};

inline int Pedido::numero() const{return num_;}
inline const Tarjeta* Pedido::tarjeta() const{return tarjeta_;}
inline Fecha Pedido::fecha() const{return fecha_;}
inline double Pedido::total() const{return total_;}
inline int Pedido::n_total_pedidos(){return N_pedidos;}

inline Usuario& Pedido::Vacio::usuario() const{return *us_;}
inline Usuario& Pedido::Impostor::usuario() const{return *us_;}
inline Articulo& Pedido::SinStock::articulo() const{return *art_;}

std::ostream& operator <<(std::ostream&, const Pedido&);

#endif /* PEDIDO_HPP_ */
