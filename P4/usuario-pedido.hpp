/* Juan Francisco Santos Relinque */

#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include <map>
#include <set>
#include "usuario.hpp"
#include "pedido.hpp"

// Declaración anticipada de las clases Usuario y Pedido
class Usuario;
class Pedido;

// ---------------| Clase Usuario_Pedido |---------------
class Usuario_Pedido{
public:
	// Definición del tipo conjunto (std::set) de pedidos
	typedef std::set<Pedido*> Pedidos;

	// Métodos de asociación entre objetos Usuario y Pedido
	void asocia(Usuario&, Pedido&);
	void asocia(Pedido&, Usuario&);

	// Métodos observadores de las asociaciones de la clase clase Usuario_Pedido
	const Pedidos& pedidos(Usuario&);
	const Usuario* cliente(Pedido&);

private:
	// Atributos de la clase Usuario_Pedido
	std::map<Usuario*, Pedidos> UsuPed;	// Asociación entre objetos Usuario y Pedido
	std::map<Pedido*, Usuario*> PedUsu;	// Asociación inversa a la anterior, siendo esta entre Pedido y Usuario
};

#endif
