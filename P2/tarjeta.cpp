#include <algorithm>
#include <cctype>
#include "tarjeta.hpp"

bool luhn(const Cadena&);

Numero::Numero(Cadena c):num_(c){
	Cadena::iterator begin{c.begin()},end{c.end()};

	std::remove_if(begin, end, isspace);
	Cadena aux{c.substr(0,end-begin)};

	if(aux.length() < 13 || aux.length() > 19){throw Incorrecto(Razon::LONGITUD);}
	if(std::count_if(aux.begin(), aux.end(), isdigit) != aux.length()){throw Incorrecto(Razon::DIGITOS);}

	if(!luhn(aux)){throw Incorrecto(Razon::NO_VALIDO);}
	num_ = aux;
}

/*
Por tanto su constructor recibir� como par�metro esa Cadena con el n�mero. Tendr�
que quitarle los blancos y comprobar que es un n�mero v�lido. Si no lo fuera lanzar�
la excepci�n Numero::Incorrecto. Vea la secci�n 5.6 para saber c�mo averiguar si un
n�mero de tarjeta de cr�dito es v�lido.
*/
