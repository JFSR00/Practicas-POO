/*
 * main.cpp
 *
 *  Created on: 21 abr. 2020
 *      Author: Juan Francisco
 */

#include <iostream>
#include "articulo.hpp"

using namespace std;

int main(){
	Articulo a(12,"Pablito clavo un clavito","12/12/2020",12.3456);
	cout<<a<<endl<<a.stock();

	return 0;
}
