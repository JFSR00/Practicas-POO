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

std::ostream& operator <<(std::ostream&, LineaPedido&);

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

/*inline bool OrdenaPedidos::operator ()(Pedido* p1, Pedido* p2) const{return p1->numero() > p2->numero();}
inline bool OrdenaArticulos::operator ()(Articulo* a1, Articulo* a2) const{return a1->referencia()>a2->referencia();}*/

inline void Pedido_Articulo::pedir(Articulo& a,Pedido& p, double pr, unsigned c){pedir(p,a,pr,c);}
inline Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& p) const{return PedArt.find(&p)->second;}
inline Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) const{return ArtPed.find(&a)->second;}

std::ostream& operator <<(std::ostream&, Pedido_Articulo::ItemsPedido&);
std::ostream& operator <<(std::ostream&, Pedido_Articulo::Pedidos&);

#endif /* PEDIDO_ARTICULO_HPP_ */
