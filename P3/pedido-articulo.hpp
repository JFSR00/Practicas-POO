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

};

class OrdenaArticulos{

};

class Pedido_Articulo{
public:
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

	void pedir(Pedido&, Articulo&, double, unsigned =1);
	void pedir(Articulo&, Pedido&, double, unsigned =1);

private:
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
	std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
};

/*
Los atributos de la clase serán dos diccionarios, uno por cada sentido de la relación:
	• El que representa la asociación desde Pedido a Articulo será del tipo
	std::map<Pedido*, ItemsPedido, OrdenaPedidos>
	donde ItemsPedido será un tipo público de la clase Pedido_Articulo definido como
	un diccionario std::map<Articulo*, LineaPedido, OrdenaArticulos>.
	OrdenaPedidos es una clase de objetos función para ordenar los pedidos ascendentemente
	por número, y OrdenaArticulos es otra clase de objetos función para
	ordenar los artículos ascendentemente por referencia.

	• La asociación en el sentido inverso (desde Articulo a Pedido) se representará por un
	diccionario del tipo std::map<Articulo*, Pedidos, OrdenaArticulos>, donde
	Pedidos será un tipo público de la clase Pedido_Articulo definido como
	std::map<Pedido*, LineaPedido, OrdenaPedidos>.

Para la creación de enlaces bidireccionales entre pedidos y artículos la clase proporcionará
el método pedir, que tendrá cuatro parámetros en el orden: pedido, articulo,
precio, cantidad (por omisión, 1). Este método se sobrecargará invirtiendo los dos primeros
parámetros. No devolverá nada.

El método detalle devolverá la colección de artículos de un pedido (que se le pasa,
por referencia) junto a su precio de venta y cantidad comprada; o sea, una referencia
constante a ItemsPedido.

Para obtener los enlaces en el sentido contrario se proporcionará un método ventas, que
devolverá todos los pedidos de un artículo (que se le pasa, por referencia) con precio
de venta y cantidad; o sea, un Pedidos.

Se sobrecargará el operador de inserción en flujo de salida << para los tipos Pedido_
Articulo::ItemsPedido y Pedido_Articulo::Pedidos. El primero, además de los detalles
del pedido, mostrará el importe total y el número de ejemplares del pedido. El segundo
mostrará precio, cantidad y fecha de cada venta y el importe total de las ventas del
artículo. Ejemplo de salida de los detalles de un pedido:

PVP 	Cantidad	Artículo
==================================================================
35,20 €	2			[100] "Programación Orientada a Objetos"
29,95 €	1			[110] "Fundamentos de C++"
==================================================================
Total	100,35 €

Ejemplo de salida de pedidos:

[Pedidos: 3]
==================================================================
PVP		Cantidad	Fecha de venta
==================================================================
39,95 €	2			miércoles 19 de abril de 2017
34,90 €	1			jueves 20 de abril de 2017
34,90 €	1			lunes 5 de abril de 2010
==================================================================
149,70 €	4

Un método llamado mostrarDetallePedidos imprimirá en el flujo de salida proporcionado
el detalle de todos los pedidos realizados hasta la fecha, así como el importe de todas
las ventas. Ejemplo:

Pedido núm. 1
Cliente: lucas Fecha: viernes 10 de marzo de 2017

detalle de ese pedido, como en ejemplo anterior
Resto de los pedidos ...

TOTAL VENTAS 981,60 €

El método mostrarVentasArticulos visualizará en el flujo de salida proporcionado todas
las ventas agrupadas por artículos. Ejemplo:

Ventas de [110] "Fundamentos de C++"

pedidos de ese artículo, como en ejemplo anterior
Resto de los artículos vendidos ...
 */
#endif /* PEDIDO_ARTICULO_HPP_ */
