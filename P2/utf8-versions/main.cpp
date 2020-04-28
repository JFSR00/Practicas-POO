/*
 * main.cpp
 *
 *  Created on: 21 abr. 2020
 *      Author: Juan Francisco
 */

#include <iostream>
#include <cstdio>
#include "articulo.hpp"
#include "usuario.hpp"
#include "cadena.hpp"

using namespace std;

int fun(){
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
	user.compra(b);
	cout<<endl;
	mostrar_carro(std::cout,user);
	user.compra(a,0);
	mostrar_carro(std::cout,user);
	try{
		Numero prueba_("23435  325 325234 5");
		cout<<endl<<endl<<prueba_;
	}catch(Numero::Incorrecto& e){
		Numero tarjeta_("4766 6492 1322 9784");
		cout<<endl<<tarjeta_;
	}

	Numero tarjeta_("4766 6492 1322 9784");
	Fecha f("0/4/2022");
	Tarjeta mia(tarjeta_,user,f);
	cout<<endl<<mia<<endl<<endl<<user;

	return 0;
}
