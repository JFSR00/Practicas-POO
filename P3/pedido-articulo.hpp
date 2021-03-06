/*
 * pedido-articulo.hpp
 *
 *  Created on: 7 may. 2020
 *      Author: Juan Francisco
 */

#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <ostream>
#include <map>
#include <set>
#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;
class Articulo;

// ---------------| Clase LineaPedido |---------------
class LineaPedido{
public:
	explicit LineaPedido(double,unsigned =1);

	double precio_venta() const;
	unsigned cantidad() const;

private:
	double precio_venta_;
	unsigned cantidad_;

};

inline double LineaPedido::precio_venta() const{return precio_venta_;}
inline unsigned LineaPedido::cantidad() const{return cantidad_;}

std::ostream& operator <<(std::ostream&, const LineaPedido&);

// ---------------| Clase Pedido_Articulo |---------------

class OrdenaPedidos{
public:
	bool operator()(Pedido*, Pedido*) const;
};

class OrdenaArticulos{
public:
	bool operator()(Articulo*, Articulo*) const;
};

class Pedido_Articulo{
public:
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

	void pedir(Pedido&, Articulo&, double, unsigned =1);
	void pedir(Articulo&, Pedido&, double, unsigned =1);

	ItemsPedido detalle(Pedido&) const;
	Pedidos ventas(Articulo&) const;

	std::ostream& mostrarDetallePedidos(std::ostream&);
	std::ostream& mostrarVentasArticulos(std::ostream&);

private:
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
	std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
};

std::ostream& operator <<(std::ostream&, const Pedido_Articulo::ItemsPedido&);
std::ostream& operator <<(std::ostream&, const Pedido_Articulo::Pedidos&);

#endif /* PEDIDO_ARTICULO_HPP_ */
