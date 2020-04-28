#define _XOPEN_SOURCE
extern "C" {
#include <unistd.h>
}
#include <cstring>
#include <random>
#include <iostream>
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

bool Clave::verifica(const char* c) const{
	char* key = crypt(c,key_.c_str());
	if(key!=nullptr){
		return key==key_;
	}else{throw Clave::Incorrecta(ERROR_CRYPT);}
}

// ------------| Clase Usuario |------------

std::unordered_set<Cadena> Usuario::users_;

Usuario::Usuario(Cadena i, Cadena n, Cadena a, Cadena d, Clave c):id_(i),nom_(n),apell_(a),dir_(d),cont_(c){
	if(!users_.insert(i).second){throw Id_duplicado(i);}
}

void Usuario::es_titular_de(Tarjeta& t){
	if(this == t.titular()){cards_.insert(std::make_pair(t.numero(),&t));}
}
void Usuario::no_es_titular_de(Tarjeta& t){
	t.anula_titular();
	cards_.erase(t.numero());
}

Usuario::~Usuario(){
	for(auto i=cards_.begin();i!=cards_.end();i++){
		i->second->anula_titular();
	}
	users_.erase(id_);
}

void Usuario::compra(Articulo& a, unsigned int cant){
	if(cant){arts_[&a] = cant;}
	else{arts_.erase(&a);}
}

std::ostream& operator <<(std::ostream& os, const Usuario& u){
	os<<u.id_<<" ["<<u.cont_.clave()<<"] "<<u.nom_<<" "<<u.apell_<<std::endl<<u.dir_<<std::endl<<"Tarjetas:\n\n";
	for(auto i=u.cards_.begin();i!=u.cards_.end();i++){
		os<<*i->second<<std::endl<<std::endl;
	}
	return os;
}
/*
Se sobrecargará el operador de inserción en flujo (<<) para mostrar o imprimir un Usuario
en un flujo de salida. El formato será:

	identificador [clave cifrada] nombre apellidos
	dirección
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
	os<<"Carrito de compra de "<<u.id()<<" [Artículos: "<<u.n_articulos()<<"]\nCant.\tArtículo\n===========================================================\n";

	Usuario::Articulos::const_iterator it = u.compra().begin();
	while(it != u.compra().end())
	{
		os<<it->second<<"\t"<<*it->first<<std::endl;
		it++;
	}
	return os;
}
