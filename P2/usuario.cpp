#define _XOPEN_SOURCE
extern "C" {
#include <unistd.h>
}
#include <cstring>
#include <random>
#include "usuario.hpp"

// ------------| Clase Clave |------------
Clave::Clave(const char* c){
	if(strlen(c)<5){throw Clave::Incorrecta(CORTA);}

	static const char* salt="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
	static std::random_device gen;
	static std::uniform_int_distribution<std::size_t> dist(0, 63);
	char sal[2]={salt[dist(gen)],salt[dist(gen)]};

	char* key = crypt(c,sal);
	if(key!=nullptr){
		key_=key;
	}else{throw Clave::Incorrecta(ERROR_CRYPT);}
}

bool Clave::verifica(const char* c){
	char* key = crypt(c,key_.c_str());
	if(key!=nullptr){
		return key==key_;
	}else{throw Clave::Incorrecta(ERROR_CRYPT);}
}

// ------------| Clase Usuario |------------
Usuario::Usuario(Cadena i, Cadena n, Cadena a, Cadena d, Clave c):id_(i),nom_(n),apell_(a),dir_(d),cont_(c){
	if(!users_.insert(i).second){throw Id_duplicado(i);}
}

void Usuario::es_titular_de(Tarjeta& t){}
void Usuario::no_es_titular_de(Tarjeta& t){}
/*
De la asociaci�n con la clase Tarjeta se encargar�n los m�todos de nombre es_titular_de
y no_es_titular_de, que recibir�n como par�metro una Tarjeta con la que el Usuario se
asociar� o de la que se desligar�.
*/

Usuario::~Usuario(){}
/*
El destructor tendr� que desligar sus tarjetas, llamando al m�todo Tarjeta::anula_titular
sobre cada una de ellas. Solamente la clase Usuario podr� llamar a este m�todo de
Tarjeta. Vea � 5.5.
*/

void Usuario::compra(Articulo& a, unsigned int cant){
	if(cant){arts_[&a] = cant;}
	else{arts_.erase(&a);}
}

std::ostream& operator <<(std::ostream& os, const Usuario& u){return os;}
/*
Se sobrecargar� el operador de inserci�n en flujo (<<) para mostrar o imprimir un Usuario
en un flujo de salida. El formato ser�:

	identificador [clave cifrada] nombre apellidos
	direcci�n
	Tarjetas:
	<lista de tarjetas>

Ejemplo:

	miguel [2456DJyasw0iY] Miguel Mares Miramontes
	C/ del Paseo, 59 (El Ronquillo)
	Tarjetas:
	 ________________________
	/						 \
	| Mastercard			 |
	| 5555555555554444		 |
	| MIGUEL MARES MIRAMONTES|
	| Caduca: 01/23			 |
	\________________________/
	 ________________________
	/						 \
	| Mastercard			 |
	| 5610591081018250		 |
	| MIGUEL MARES MIRAMONTES|
	| Caduca: 02/21			 |
	\________________________/
*/

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u){
	os<<"Carrito de compra de "<<u.id()<<" [Art�culos: "<<u.n_articulos()<<"]\nCant.\tArt�culo\n===========================================================\n";

	Usuario::Articulos::const_iterator it = u.compra().begin();
	while(it != u.compra().end())
	{
		os<<it->second<<"\t"<<*it->first<<std::endl;
		it++;
	}
	return os;
}
