#include <algorithm>
#include <cctype>
#include "tarjeta.hpp"

// ------------| Clase Numero |------------
bool luhn(const Cadena&);

Numero::Numero(Cadena c):num_(c){
	Cadena::iterator end{std::remove_if(c.begin(), c.end(), isspace)};

	Cadena aux{c.substr(0,end-c.begin())};

	if(aux.length() < 13 || aux.length() > 19){throw Numero::Incorrecto(LONGITUD);}
	if((1 + std::count_if(aux.begin(), aux.end(), isdigit)) != aux.length()){throw Numero::Incorrecto(DIGITOS);}

	if(!luhn(aux)){throw Numero::Incorrecto(NO_VALIDO);}
	num_ = aux;
}

// ------------| Clase Tarjeta |------------
Tarjeta::Tarjeta(const Numero& t, const Usuario& p, const Fecha& f):tarj_(t),prop_(&p),cad_(f),act_(true){
	if(f < Fecha(0,0,0)){throw Tarjeta::Caducada(f);}
	if(!numeros_.insert(t).second){throw Num_duplicado(t);}
	p.es_titular_de(*this);
}

Tarjeta::~Tarjeta(){
	if(prop_!=nullptr){prop_->no_es_titular_de(*this);}
	numeros_.erase(tarj_);
}

Tarjeta::Tipo Tarjeta::tipo(){
	Tipo ret;
	switch(tarj_.Numero()[0]){
	case 3:
		if(tarj_.Numero()[1]=='4'||tarj_.Numero()[1]=='7'){ret= AmericanExpress;}
		else{ret = JCB;}
		break;
	case 4:
		ret = VISA;
		break;
	case 5:
		ret = Mastercard;
		break;
	case 6:
		ret = Maestro;
		break;
	default:
		ret = Otro;
		break;
	}
	return ret;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t){

	return os;
}

/*
• Se sobrecargará el operador de inserción en flujo (<<) para mostrar o imprimir una
Tarjeta en un flujo de salida. El formato será:

	tipo
	número
	titular facial
	Caduca: MM/AA

donde MM es el mes de la fecha de caducidad, expresado con dos dígitos y AA son los
dos últimos dígitos del año; por ejemplo: 05/09 sería mayo de 2009.

El titular facial es el nombre y apellidos del propietario de la tarjeta, en mayúsculas.

Si quiere, por estética, puede dibujar líneas rodeando la información impresa de la
tarjeta, simulando, aun pobremente, su aspecto. Esto es opcional.

Para imprimir el nombre del tipo de la tarjeta (VISA, American Express. . . ), deberá
sobrecargar también el operador de inserción para Tarjeta::Tipo.

Ejemplo de impresión de una Tarjeta (las líneas son opcionales):
 ____________________
/					 \
| American Express	 |
| 378282246310005	 |
| SISEBUTO RUSCALLEDA|
| Caduca: 11/23		 |
\____________________/
*/
