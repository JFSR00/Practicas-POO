/*
 * main.cpp
 *
 *  Created on: 21 abr. 2020
 *      Author: Juan Francisco
 */

#include <iostream>
#include "articulo.hpp"
#include "usuario.hpp"

using namespace std;

int main(){
	Articulo a(12,"Pablito clavo un clavito","12/12/2020",12.3456);
	Articulo b(13,"Pablito se partio la mano por subnormal","13/12/2020",13.58999);
	cout<<a<<endl<<a.stock();
	a.precio()=1.45;
	a.stock()=40332;
	cout<<endl<<a<<endl<<a.stock();

	Clave key("medion");
	cout<<endl<<key.clave()<<endl<<key.verifica("holasdfas")<<endl<<key.verifica("medion");

	Usuario user("JFSR00","Juan Francisco","Santos Relinque","C/ Mirador de la Janda, 15","medion");
	user.compra(a,4);
	user.compra(b,0);
	cout<<endl;
	mostrar_carro(std::cout,user);
	user.compra(a,0);
	mostrar_carro(std::cout,user);
	return 0;
}
