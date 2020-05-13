#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

int Pedido::N_pedidos=0;

Pedido::Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& u, Tarjeta& t, Fecha f)
:num_(N_pedidos+1),tarjeta_(&t),fecha_(f),total_(0){
	UP.asocia(*this,u);
}

/*
int N_pedido;
Tarjeta* tarjeta_;
Fecha fecha_;
double total_;
int num_;

Los cinco atributos de la clase Pedido son: el número del pedido (número correlativo
empezando en 1), tarjeta de pago (puntero a Tarjeta constante), fecha del pedido, importe
total de la venta y número del último pedido realizado, o cantidad de pedidos
hechos.

Cuando se genera un pedido de los artículos que contiene el carrito, este quedará vacío y
las existencias de los artículos vendidos actualizadas. El nuevo pedido quedará asociado
al usuario que lo realiza, a la tarjeta de pago y a los artículos incluidos en la compra.
Se llamará a los métodos apropiados de la clases de asociación para crear los enlaces
(véanse § 5.4 y § 5.5).

Si el carrito no tiene ningún artículo, para evitar crear un pedido vacío, el constructor
terminará con la excepción Pedido::Vacio. Esta clase tiene un atributo que es un puntero
al usuario que realiza el pedido, un constructor que recibe el usuario y un método
observador usuario que lo devuelve.

Se comprobará también que el titular de la tarjeta es quien hace el pedido. De no ser
así se lanzará la excepción Pedido::Impostor. Al igual que en la clase de excepción anterior,
el atributo almacena un puntero al usuario, el constructor recibe el usuario y el
observador lo devuelve.

En el caso de que la cantidad de alguno de los artículos del carrito supere las existencias
en almacén (stock), se vacía el carrito y se anula el pedido lanzando la excepción Pedido::
SinStock. Esta clase de excepción consta de un atributo de tipo puntero a Articulo,
un constructor que recibe el primer artículo del carrito sin existencias suficientes y un
método observador articulo que lo devuelve.

Además, el constructor lanzará la excepción Tarjeta::Caducada si la fecha de caducidad
de la tarjeta de pago es anterior a la fecha del pedido, o Tarjeta::Desactivada si la tarjeta
de pago no está activa.

Proporcionará métodos observadores para sus atributos, cuyos nombres serán numero,
tarjeta, fecha, total y n_total_pedidos.

Se sobrecargará el operador de inserción en flujo (<<) para mostrar o imprimir un Pedido
en un flujo de salida con el formato del ejemplo:

Núm. pedido: 1
Fecha: jueves 10 de marzo de 2016
Pagado con: VISA n.º: 4539451203987356
Importe: 149,95 €
 */
