/* Juan Francisco Santos Relinque */

#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <ostream>
#include <map>
#include <set>
#include "pedido.hpp"
#include "articulo.hpp"

// Declaración anticipada de las clases Pedido y Articulo
class Pedido;
class Articulo;

// ---------------| Clase LineaPedido |---------------
class LineaPedido{
public:
	// Constructor explícito de la clase LineaPedido
	explicit LineaPedido(double,unsigned =1);

	// Métodos observadores de la clase LineaPedido
	double precio_venta() const;
	unsigned cantidad() const;

private:
	// Atributos de la clase LineaPedido
	double precio_venta_;	// Precio de venta del artículo
	unsigned cantidad_;		// Cantidad de artículos

};

// Inline de los métodos observadores de la clase LineaPedido
inline double LineaPedido::precio_venta() const{return precio_venta_;}
inline unsigned LineaPedido::cantidad() const{return cantidad_;}

// Sobrecarga del operador de inserción de flujo de la clase LineaPedido
std::ostream& operator <<(std::ostream&, const LineaPedido&);

// Clases función para la ordenación de las clases Pedido y Articulo dentro de los std::map
class OrdenaPedidos{
public:
	bool operator()(Pedido*, Pedido*) const;
};

class OrdenaArticulos{
public:
	bool operator()(Articulo*, Articulo*) const;
};

// ---------------| Clase Pedido_Articulo |---------------
class Pedido_Articulo{
public:
	// Esta clase hace uso del constructor por defecto

	// Definición de los tipos std::map para almacenar los artículos y los pedidos a asociar
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

	// Métodos usados para la asociación de las clases Pedido y Artículo
	void pedir(Pedido&, Articulo&, double, unsigned =1);
	void pedir(Articulo&, Pedido&, double, unsigned =1);

	// Métodos observadores de la clase Pedido_Articulo
	ItemsPedido detalle(Pedido&) const;
	Pedidos ventas(Articulo&) const;

	// Métodos para la inserción en un flujo la información contenida en un objeto de esta clase
	std::ostream& mostrarDetallePedidos(std::ostream&);
	std::ostream& mostrarVentasArticulos(std::ostream&);

private:
	// Atributos de la clase Pedido_Articulo para la asociación de las clases Pedido y Artículo
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
	std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
};

// Sobrecarga del operador de inserción de flujo para los tipos ItemsPedido y Pedidos
std::ostream& operator <<(std::ostream&, const Pedido_Articulo::ItemsPedido&);
std::ostream& operator <<(std::ostream&, const Pedido_Articulo::Pedidos&);

#endif
