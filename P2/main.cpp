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
	cout<<a<<endl<<a.stock();
	a.precio()=1.45;
	a.stock()=40332;
	cout<<endl<<a<<endl<<a.stock();

	Clave key("medion");
	cout<<endl<<key.clave()<<endl<<key.verifica("holasdfas")<<endl<<key.verifica("medion");
	return 0;
}
