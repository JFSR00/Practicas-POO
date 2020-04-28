#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include "tarjeta.hpp"

// ------------| Clase Numero |------------
bool luhn(const Cadena&);

Numero::Numero(const Cadena& c):num_(c){
	if(c.length()==0){throw Numero::Incorrecto(LONGITUD);}

	Cadena::iterator end{std::remove_if(num_.begin(), num_.end(), isspace)};

	Cadena aux{num_.substr(0,end-num_.begin())};

	if(aux.length() < 13 || aux.length() > 19){throw Numero::Incorrecto(LONGITUD);}
	if((std::count_if(aux.begin(), aux.end(), isdigit)) != aux.length()){throw Numero::Incorrecto(DIGITOS);}

	if(!luhn(aux)){throw Numero::Incorrecto(NO_VALIDO);}
	num_ = aux;
}

// ------------| Clase Tarjeta |------------
std::set<Numero> Tarjeta::numeros_;

Tarjeta::Tarjeta(const Numero& t, Usuario& p, const Fecha& f):tarj_(t),prop_(&p),cad_(f),act_(true){
	Fecha hoy;
	if(f < hoy){throw Tarjeta::Caducada(f);}
	if(!numeros_.insert(t).second){throw Num_duplicado(t);}
	prop_->es_titular_de(*this);
}

Tarjeta::~Tarjeta(){
	if(prop_!=nullptr){prop_->no_es_titular_de(*this);}
	numeros_.erase(tarj_);
}

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

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& t){
	switch(t){
	case Tarjeta::Otro:
		os<<"Otro";
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

/*
• Si quiere, por estética, puede dibujar líneas rodeando la información impresa de la
tarjeta, simulando, aun pobremente, su aspecto. Esto es opcional.
 ____________________
/					 \
| American Express	 |
| 378282246310005	 |
| SISEBUTO RUSCALLEDA|
| Caduca: 11/23		 |
\____________________/
*/
