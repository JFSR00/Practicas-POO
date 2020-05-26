#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iomanip>
#include <typeinfo>

int Pedido::N_pedidos=0;

Pedido::Vacio::Vacio(Usuario* u):us_(u){}

Pedido::Impostor::Impostor(Usuario* u):us_(u){}

Pedido::SinStock::SinStock(Articulo* a):art_(a){}

Pedido::Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& u, const Tarjeta& t, const Fecha& f)
:num_(N_pedidos+1),tarjeta_(&t),fecha_(f),total_(0){
	if(!u.n_articulos()){throw Pedido::Vacio{&u};}
	if(t.titular() != &u){throw Pedido::Impostor{&u};}
	if(t.caducidad() < fecha_){throw Tarjeta::Caducada{t.caducidad()};}
	if(!t.activa()){throw Tarjeta::Desactivada{};}

	bool vacio = true;
	Usuario::Articulos carro{u.compra()};
	for(auto i: u.compra()){
		if(ArticuloAlmacenable *aa{dynamic_cast<ArticuloAlmacenable*>(i.first)}){
			if((unsigned int)aa->stock() < i.second){
				const_cast<Usuario::Articulos&>(u.compra()).clear();
				throw Pedido::SinStock{i.first};
			}
			vacio=false;
			aa->stock() -= i.second;
			total_ += i.first->precio()*i.second;
		}else if(LibroDigital *ld{dynamic_cast<LibroDigital*>(i.first)}){
			if(ld->f_expir()>Fecha(0)){
				vacio=false;
				total_ += i.first->precio()*i.second;
			}else{
				carro.erase(i.first);
			}
		}else{
			throw std::logic_error("Pedido: Artículo no reconocido");
		}
	}

	if(vacio){throw Pedido::Vacio{&u};}

	for(auto i: carro){
		PA.pedir(*this, *i.first, i.first->precio(), i.second);
		u.compra(*i.first, 0);
	}

	UP.asocia(*this,u);
	N_pedidos++;
}

std::ostream& operator <<(std::ostream& os, const Pedido& p){
	os<<"Núm. pedido:\t"<<p.numero()<<"\nFecha:\t"<<p.fecha()<<"\nPagado con:\t"<<*p.tarjeta()
	<<"\nImporte:\t"<<std::fixed<<std::setprecision(2)<<p.total()<<" €";
	return os;
}
