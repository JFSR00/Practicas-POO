#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario& u, Pedido& p){UsuPed[&u].insert(&p); PedUsu[&p] = &u;}
void Usuario_Pedido::asocia(Pedido& p, Usuario& u){asocia(u,p);}

const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& u){return UsuPed[&u];}
const Usuario* Usuario_Pedido::cliente(Pedido& p){return PedUsu[&p];}
