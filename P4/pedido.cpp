#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iomanip>
#include <typeinfo>

// Inicialización del contador estático de pedidos
int Pedido::N_pedidos=0;

// Constructores de las clases de error de la clase Pedido
Pedido::Vacio::Vacio(Usuario* u):us_(u){}

Pedido::Impostor::Impostor(Usuario* u):us_(u){}

Pedido::SinStock::SinStock(Articulo* a):art_(a){}

// Constructor de la clase pedido
Pedido::Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& u, const Tarjeta& t, const Fecha& f)
:num_(N_pedidos+1),tarjeta_(&t),fecha_(f),total_(0){
	// Realizamos primero una búsqueda de casos de error para lanzar las excepciones apropiadas
	if(!u.n_articulos()){throw Pedido::Vacio{&u};}
	if(t.titular() != &u){throw Pedido::Impostor{&u};}
	if(t.caducidad() < fecha_){throw Tarjeta::Caducada{t.caducidad()};}
	if(!t.activa()){throw Tarjeta::Desactivada{};}

	// Comprobamos que el carro no está vacío, que hay stock de todos los artículos del carro y que todos los artículos están reconocidos
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

	// Comprobamos el resultado de la comprobación de si el carro está vacio o no, y en caso de que estuviera vacío, lanzamos la excepción Pedido::Vacio
	if(vacio){throw Pedido::Vacio{&u};}

	// Añadimos los artículos del carro a la clase de asociación Pedido_Articulo
	for(auto i: carro){
		PA.pedir(*this, *i.first, i.first->precio(), i.second);
		u.compra(*i.first, 0);
	}

	UP.asocia(*this,u);	// Asociamos este pedido con su usuario
	N_pedidos++;		// Incrementamos el número total de pedidos
}

// Implementación de la sobrecarga del operador de inserción de flujo
std::ostream& operator <<(std::ostream& os, const Pedido& p){
	os<<"Núm. pedido:\t"<<p.numero()<<"\nFecha:\t"<<p.fecha()<<"\nPagado con:\t"<<*p.tarjeta()
	<<"\nImporte:\t"<<std::fixed<<std::setprecision(2)<<p.total()<<" €";
	return os;
}
