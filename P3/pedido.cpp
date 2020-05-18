#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iomanip>

int Pedido::N_pedidos=0;

Pedido::Vacio::Vacio(Usuario* u):us_(u){}

Pedido::Impostor::Impostor(Usuario* u):us_(u){}

Pedido::SinStock::SinStock(Articulo* a):art_(a){}

Pedido::Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& u, Tarjeta& t, Fecha f)
:num_(N_pedidos+1),tarjeta_(&t),fecha_(f),total_(0){
	if(!u.n_articulos()){throw Pedido::Vacio{&u};}
	if(t.titular() != &u){throw Pedido::Impostor{&u};}
	if(t.caducidad() < fecha_){throw Tarjeta::Caducada{t.caducidad()};}
	if(!t.activa()){throw Tarjeta::Desactivada{};}

	Usuario::Articulos carro{u.compra()};
	for(auto i: carro){
		if((unsigned int)i.first->stock() < i.second){throw Pedido::SinStock{i.first};}
		i.first->stock() -= i.second;
		PA.pedir(*this, *i.first, i.first->precio(), i.second);
		total_ += i.first->precio()*i.second;
		u.compra(*i.first, 0);
	}

	UP.asocia(*this,u);
	N_pedidos++;
}

std::ostream& operator <<(std::ostream& os, Pedido& p){
	os<<"Núm. pedido:\t"<<p.numero()<<"\nFecha:\t"<<p.fecha()<<"\nPagado con:\t"<<*p.tarjeta()
	<<"\nImporte:\t"<<std::fixed<<std::setprecision(2)<<p.total()<<" €";
	return os;
}
/*
Se sobrecargará el operador de inserción en flujo (<<) para mostrar o imprimir un Pedido
en un flujo de salida con el formato del ejemplo:

Núm. pedido: 1
Fecha: jueves 10 de marzo de 2016
Pagado con: VISA n.º: 4539451203987356
Importe: 149,95 €
 */
