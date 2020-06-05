#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include "tarjeta.hpp"

// ------------| Clase Numero |------------
// Declaración anticipada de la función luhn, contenida en el fichero proporcionado por los profesores luhn.cpp
bool luhn(const Cadena&);

// Implementación del objeto función EsDigito para su posterior uso en el constructor de la clase Numero
struct EsDigito{
	bool operator() (const char& c) const {return ((c>='0') && (c<='9'));}
	typedef char argument_type;
};

// Constructor de la clase Numero
Numero::Numero(const Cadena& c):num_(c){
	std::unary_negate<EsDigito> NoEsDigito ((EsDigito()));
	if(c.length()==0){throw Numero::Incorrecto(LONGITUD);}

	// Hago todas estas comaparaciones para que sea equivalente a "isspace", siendo así más correcto
	Cadena::iterator end{std::remove_if(num_.begin(), num_.end(), [](char x){return (x==' '||x=='\t'||x=='\n'||x=='\v'||x=='\f'||x=='\r');})};

	Cadena aux{num_.substr(0,end-num_.begin())};

	if(aux.length() < 13 || aux.length() > 19){throw Numero::Incorrecto(LONGITUD);}
	if(aux.end()!=std::find_if(aux.begin(),aux.end(),NoEsDigito)){throw Numero::Incorrecto(DIGITOS);}

	if(!luhn(aux)){throw Numero::Incorrecto(NO_VALIDO);}
	num_ = aux;
}

// ------------| Clase Tarjeta |------------
// Declaración del contenedor de números de las tarjetas existentes
std::set<Numero> Tarjeta::numeros_;

// Constructor de la clase Tarjeta
Tarjeta::Tarjeta(const Numero& t, Usuario& p, const Fecha& f):tarj_(t),prop_(&p),cad_(f),act_(true){
	Fecha hoy;
	if(f < hoy){throw Tarjeta::Caducada(f);}
	if(!numeros_.insert(t).second){throw Num_duplicado(t);}
	prop_->es_titular_de(*this);
}

// Destructor de la clase tarjeta
// Debe encargarse de desvincular la tarjeta con su propietario y eliminar el número de esta tarjeta del conjunto de números de
// tarjetas
Tarjeta::~Tarjeta(){
	if(prop_!=nullptr){prop_->no_es_titular_de(*this);}
	numeros_.erase(tarj_);
}

// Implementación del método observador tipo() para conocer el tipo de tarjeta en cuestión  apartir de su número
const Tarjeta::Tipo Tarjeta::tipo() const{
	Tipo ret;
	switch(Cadena(tarj_)[0]){
	case '3':
		if(Cadena(tarj_)[1]=='4'||Cadena(tarj_)[1]=='7'){ret= AmericanExpress;}
		else{ret = JCB;}
		break;
	case '4':
		ret = VISA;
		break;
	case '5':
		ret = Mastercard;
		break;
	case '6':
		ret = Maestro;
		break;
	default:
		ret = Otro;
		break;
	}
	return ret;
}

// Implementación del operador de inserción de flujo para el tipo de tarjeta
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& t){
	switch(t){
	case Tarjeta::Otro:
		os<<"Tipo indeterminado";
		break;
	case Tarjeta::VISA:
		os<<"VISA";
		break;
	case Tarjeta::Mastercard:
		os<<"Mastercard";
		break;
	case Tarjeta::Maestro:
		os<<"Maestro";
		break;
	case Tarjeta::JCB:
		os<<"JCB";
		break;
	case Tarjeta::AmericanExpress:
		os<<"American Express";
		break;
	}
	return os;
}

// Implementación del operador de inserción de flujo para los datos de la tarjeta
std::ostream& operator <<(std::ostream& os, const Tarjeta& t){
	os<<t.tipo()<<std::endl<<t.numero()<<std::endl;
	for(unsigned int i=0;i<t.titular()->nombre().length();i++){
		os.put(toupper(t.titular()->nombre()[i]));
	}
	os.put(' ');
	for(unsigned int i=0;i<t.titular()->apellidos().length();i++){
		os.put(toupper(t.titular()->apellidos()[i]));
	}
	os<<std::endl<<"Caduca: "<<std::setfill('0')<<std::setw(2)<<t.caducidad().mes()<<"/"<<t.caducidad().anno()%100<<std::endl;

	return os;
}
