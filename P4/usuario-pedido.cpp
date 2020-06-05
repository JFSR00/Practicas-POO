#include "usuario-pedido.hpp"

// ---------------| Clase Usuario_Pedido |---------------
// Implementación de los métodos de asociación de la clase Usuario_Pedido
void Usuario_Pedido::asocia(Usuario& u, Pedido& p){UsuPed[&u].insert(&p); PedUsu[&p] = &u;}
void Usuario_Pedido::asocia(Pedido& p, Usuario& u){asocia(u,p);}

// Implementación de los métodos observadores de la clase Usuario_Pedido
const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& u){return UsuPed[&u];}
const Usuario* Usuario_Pedido::cliente(Pedido& p){return PedUsu[&p];}
