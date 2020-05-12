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
Los atributos de la clase ser�n dos diccionarios, uno por cada sentido de la relaci�n:
	� El que representa la asociaci�n desde Pedido a Articulo ser� del tipo
	std::map<Pedido*, ItemsPedido, OrdenaPedidos>
	donde ItemsPedido ser� un tipo p�blico de la clase Pedido_Articulo definido como
	un diccionario std::map<Articulo*, LineaPedido, OrdenaArticulos>.
	OrdenaPedidos es una clase de objetos funci�n para ordenar los pedidos ascendentemente
	por n�mero, y OrdenaArticulos es otra clase de objetos funci�n para
	ordenar los art�culos ascendentemente por referencia.

	� La asociaci�n en el sentido inverso (desde Articulo a Pedido) se representar� por un
	diccionario del tipo std::map<Articulo*, Pedidos, OrdenaArticulos>, donde
	Pedidos ser� un tipo p�blico de la clase Pedido_Articulo definido como
	std::map<Pedido*, LineaPedido, OrdenaPedidos>.

Para la creaci�n de enlaces bidireccionales entre pedidos y art�culos la clase proporcionar�
el m�todo pedir, que tendr� cuatro par�metros en el orden: pedido, articulo,
precio, cantidad (por omisi�n, 1). Este m�todo se sobrecargar� invirtiendo los dos primeros
par�metros. No devolver� nada.

El m�todo detalle devolver� la colecci�n de art�culos de un pedido (que se le pasa,
por referencia) junto a su precio de venta y cantidad comprada; o sea, una referencia
constante a ItemsPedido.

Para obtener los enlaces en el sentido contrario se proporcionar� un m�todo ventas, que
devolver� todos los pedidos de un art�culo (que se le pasa, por referencia) con precio
de venta y cantidad; o sea, un Pedidos.

Se sobrecargar� el operador de inserci�n en flujo de salida << para los tipos Pedido_
Articulo::ItemsPedido y Pedido_Articulo::Pedidos. El primero, adem�s de los detalles
del pedido, mostrar� el importe total y el n�mero de ejemplares del pedido. El segundo
mostrar� precio, cantidad y fecha de cada venta y el importe total de las ventas del
art�culo. Ejemplo de salida de los detalles de un pedido:

PVP 	Cantidad	Art�culo
==================================================================
35,20 �	2			[100] "Programaci�n Orientada a Objetos"
29,95 �	1			[110] "Fundamentos de C++"
==================================================================
Total	100,35 �

Ejemplo de salida de pedidos:

[Pedidos: 3]
==================================================================
PVP		Cantidad	Fecha de venta
==================================================================
39,95 �	2			mi�rcoles 19 de abril de 2017
34,90 �	1			jueves 20 de abril de 2017
34,90 �	1			lunes 5 de abril de 2010
==================================================================
149,70 �	4

Un m�todo llamado mostrarDetallePedidos imprimir� en el flujo de salida proporcionado
el detalle de todos los pedidos realizados hasta la fecha, as� como el importe de todas
las ventas. Ejemplo:

Pedido n�m. 1
Cliente: lucas Fecha: viernes 10 de marzo de 2017

detalle de ese pedido, como en ejemplo anterior
Resto de los pedidos ...

TOTAL VENTAS 981,60 �

El m�todo mostrarVentasArticulos visualizar� en el flujo de salida proporcionado todas
las ventas agrupadas por art�culos. Ejemplo:

Ventas de [110] "Fundamentos de C++"

pedidos de ese art�culo, como en ejemplo anterior
Resto de los art�culos vendidos ...
 */
#endif /* PEDIDO_ARTICULO_HPP_ */
