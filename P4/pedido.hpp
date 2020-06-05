/* Juan Francisco Santos Relinque */

#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <ostream>

// Declararación adelantada de las clases Usuario_Pedido y Pedido_Articulo
class Usuario_Pedido;
class Pedido_Articulo;

// ---------------| Clase Pedido |---------------
class Pedido{
public:
	// Constructor
	Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha& =Fecha());

	// Métodos observadores
	int numero() const;
	const Tarjeta* tarjeta() const;
	Fecha fecha() const;
	double total() const;
	static int n_total_pedidos();

	// Clases de error de la clase Pedido
	// Clase Vacio usada en caso de que el pedido esté vacío
	class Vacio{
		Usuario *us_;
	public:
		Vacio(Usuario*);
		Usuario& usuario() const;
	};

	// Clase Impostor usada en caso de que el Usuario y el titular de la Tarjeta sean distintos
	class Impostor{
		Usuario *us_;
	public:
		Impostor(Usuario*);
		Usuario& usuario() const;
	};

	// Clase SinStock usada en caso de que un artículo no tenga stock
	class SinStock{
		Articulo *art_;
	public:
		SinStock(Articulo*);
		Articulo& articulo() const;
	};

private:
	// Atributos de la clase Pedido
	static int N_pedidos;		// Variable estática contadora del número total de pedidos
	int num_;					// Número de identificación del pedido en cuestión
	const Tarjeta* tarjeta_;	// Tarjeta asociada a este pedido
	Fecha fecha_;				// Fecha de realización del pedido
	double total_;				// Coste total del pedido
};

// Inline de los métodos observadores de la clase Pedido
inline int Pedido::numero() const{return num_;}
inline const Tarjeta* Pedido::tarjeta() const{return tarjeta_;}
inline Fecha Pedido::fecha() const{return fecha_;}
inline double Pedido::total() const{return total_;}
inline int Pedido::n_total_pedidos(){return N_pedidos;}

// Inline de los métodos observadores de las clases de error de la clase Pedido
inline Usuario& Pedido::Vacio::usuario() const{return *us_;}
inline Usuario& Pedido::Impostor::usuario() const{return *us_;}
inline Articulo& Pedido::SinStock::articulo() const{return *art_;}

// Sobrecarga del operador de inserción de flujo
std::ostream& operator <<(std::ostream&, const Pedido&);

#endif
