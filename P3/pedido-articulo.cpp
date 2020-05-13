#include <iomanip>
#include "pedido-articulo.hpp"

// ---------------| Clase LineaPedido |---------------
LineaPedido::LineaPedido(double p, unsigned c):precio_venta_(p), cantidad_(c){}

std::ostream& operator <<(std::ostream& os, LineaPedido& l){
	os<<std::fixed<<std::setprecision(2)<<l.precio_venta()<<" €"<<"\t"<<l.cantidad();
	return os;
}

// ---------------| Clase Pedido_Articulo |---------------
void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double pr, unsigned c){
	PedArt[&p].insert(std::make_pair(&a,LineaPedido(pr,c)));
	ArtPed[&a].insert(std::make_pair(&p,LineaPedido(pr,c)));
}
