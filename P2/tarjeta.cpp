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
Por tanto su constructor recibirá como parámetro esa Cadena con el número. Tendrá
que quitarle los blancos y comprobar que es un número válido. Si no lo fuera lanzará
la excepción Numero::Incorrecto. Vea la sección 5.6 para saber cómo averiguar si un
número de tarjeta de crédito es válido.
*/
