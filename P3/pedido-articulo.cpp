#include <iomanip>
#include <utility>
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

std::ostream& operator <<(std::ostream& os, Pedido_Articulo::ItemsPedido& itm_){
	double total_=0;
	os<<"PVP\tCantidad\tArtículo\n==================================================================\n";
	for(auto i: itm_){
		os<<i.second<<"\t["<<i.first->referencia()<<"] \""<<i.first->titulo()<<"\"\n";
		total_+=(i.second.cantidad()*i.second.precio_venta());
	}
	os<<"==================================================================\nTotal\t"
	<<std::fixed<<std::setprecision(2)<<total_<<" €";
	return os;
}

std::ostream& operator <<(std::ostream& os, Pedido_Articulo::Pedidos& ped_){
	unsigned cantTotal_=0;
	double total_=0;
	os<<"[Pedidos: "<<ped_.size()<<"]\n=================================================================="
	<<"PVP\tCantidad\tFecha de venta"<<"==================================================================\n";
	for(auto i: ped_){
		os<<i.second<<i.first->fecha()<<std::endl;
		cantTotal_+=i.second.cantidad();
		total_+=i.second.precio_venta();
	}
	os<<"=================================================================="<<std::fixed<<std::setprecision(2)
	<<total_<<" €\t"<<cantTotal_;
	return os;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
	double total_=0;
	for(auto i: PedArt){
		os<<"Pedido núm. "<<i.first->numero()<<"\nCliente: "<<i.first->tarjeta()->titular()->nombre()<<"\t\t"
		<<i.first->fecha()<<std::endl;
		total_+=i.first->total();
	}
	os<<"\nTOTAL VENTAS\t\t"<<std::fixed<<std::setprecision(2)<<total_<<" €";
	return os;
}
std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
	for(auto i: ArtPed){
		os<<"Ventas de ["<<i.first->referencia()<<"] \""<<i.first->titulo()<<"\"\n"<<i.second<<std::endl;
	}
	return os;
}

