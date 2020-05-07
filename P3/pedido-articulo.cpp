#include <iomanip>
#include "pedido-articulo.hpp"

// ---------------| Clase LineaPedido |---------------
LineaPedido::LineaPedido(double p, unsigned c):precio_venta_(p), cantidad_(c){}

std::ostream& operator <<(std::ostream& os, LineaPedido& l){
	os<<std::fixed<<std::setprecision(2)<<l.precio_venta()<<" €"<<"\t"<<l.cantidad();
	return os;
}

// ---------------| Clase Pedido_Articulo |---------------
