#include <iomanip>
#include <utility>
#include "pedido-articulo.hpp"

// ---------------| Clase LineaPedido |---------------
// Constructor de la clase LineaPedido
LineaPedido::LineaPedido(double p, unsigned c):precio_venta_(p), cantidad_(c){}

// Implementación de la sobrecarga del operador de inserción de flujo para LineaPedido
std::ostream& operator <<(std::ostream& os, const LineaPedido& l){
	os<<std::fixed<<std::setprecision(2)<<l.precio_venta()<<" €"<<"\t"<<l.cantidad();
	return os;
}

// ---------------| Clase Pedido_Articulo |---------------

// Implementación de los métodos de los objetos función OrdenaPedidos y OrdenaArticulos
bool OrdenaPedidos::operator ()(Pedido* p1, Pedido* p2) const{return p1->numero() < p2->numero();}
bool OrdenaArticulos::operator ()(Articulo* a1, Articulo* a2) const{return a1->referencia() < a2->referencia();}

// Implementación de los métodos de enlace de la clase Pedido_Articulo
void Pedido_Articulo::pedir(Articulo& a,Pedido& p, double pr, unsigned c){pedir(p,a,pr,c);}
void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double pr, unsigned c){
	PedArt[&p].insert(std::make_pair(&a,LineaPedido(pr,c)));
	ArtPed[&a].insert(std::make_pair(&p,LineaPedido(pr,c)));
}

// Implementación de los métodos observadores de la clase Pedido_Articulo
Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& p) const{return PedArt.find(&p)->second;}
Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) const{
	auto i = ArtPed.find(&a);
	return (i != ArtPed.end())?i->second:Pedidos{};
}

// Implementación de la sobrecarga del operador de inserción de flujo para ItemsPedido
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& itm_){
	setlocale(LC_ALL, "es_ES");
	os.imbue(std::locale(""));
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

// Implementación de la sobrecarga del operador de inserción de flujo para Pedidos
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& ped_){
	setlocale(LC_ALL, "es_ES");
	os.imbue(std::locale(""));
	unsigned cantTotal_=0;
	double total_=0;
	os<<"[Pedidos: "<<ped_.size()<<"]\n==================================================================\n"
	<<"PVP\tCantidad\tFecha de venta\n==================================================================\n";
	for(auto i: ped_){
		os<<i.second<<"\t\t"<<i.first->fecha()<<std::endl;
		cantTotal_+=i.second.cantidad();
		total_+=i.second.precio_venta()*i.second.cantidad();
	}
	os<<"==================================================================\n"<<std::fixed<<std::setprecision(2)
	<<total_<<" €\t"<<cantTotal_;
	return os;
}

// Implementación para la inserción en flujo de los datos de los Pedidos
std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
	setlocale(LC_ALL, "es_ES");
	os.imbue(std::locale(""));
	double total_=0;
	for(auto i: PedArt){
		os<<"Pedido núm. "<<i.first->numero()<<"\nCliente: "<<i.first->tarjeta()->titular()->nombre()<<"\t\t"
		<<i.first->fecha()<<std::endl<<std::endl<<i.second<<std::endl<<std::endl;
		total_+=i.first->total();
	}
	os<<"TOTAL VENTAS\t\t"<<std::fixed<<std::setprecision(2)<<total_<<" €";
	return os;
}

// Implementación para la inserción en flujo de los datos de las ventas de artículos
std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
	setlocale(LC_ALL, "es_ES");
	os.imbue(std::locale(""));
	for(auto i: ArtPed){
		os<<"Ventas de ["<<i.first->referencia()<<"] \""<<i.first->titulo()<<"\"\n"<<i.second<<std::endl;
	}
	return os;
}

