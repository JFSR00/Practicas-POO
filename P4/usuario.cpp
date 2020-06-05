#define _XOPEN_SOURCE
extern "C" {
#include <unistd.h>
}
#include <cstring>
#include <random>
#include <iostream>
#include <iomanip>
#include "usuario.hpp"

// ------------| Clase Clave |------------
// Constructor de la clase Clave
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

// Implementación del método para la verificación de la clave pasada por parámetro coincide con la almacenada en el obejeto
bool Clave::verifica(const char* c) const{
	char* key = crypt(c,key_.c_str());
	if(key!=nullptr){
		return key==key_;
	}else{throw Clave::Incorrecta(ERROR_CRYPT);}
}

// ------------| Clase Usuario |------------
// Declaración del contenedor de números de identificación de los usuarios existentes
std::unordered_set<Cadena> Usuario::users_;

// Constructor de la clase Usuario
Usuario::Usuario(Cadena i, Cadena n, Cadena a, Cadena d, Clave c):id_(i),nom_(n),apell_(a),dir_(d),cont_(c){
	if(!users_.insert(i).second){throw Id_duplicado(i);}
}

// Destructor de la clase Usuario
Usuario::~Usuario(){
	for(auto i=cards_.begin();i!=cards_.end();i++){
		i->second->anula_titular();
	}
	users_.erase(id_);
}

// Implementación de los métodos de asociación y desasociación de la clase Usuario
void Usuario::es_titular_de(Tarjeta& t){
	if(this == t.titular()){cards_.insert(std::make_pair(t.numero(),&t));}
}
void Usuario::no_es_titular_de(Tarjeta& t){
	t.anula_titular();
	cards_.erase(t.numero());
}

// Implementación del método de asociación de usuario con un artículo y su cantidad
void Usuario::compra(Articulo& a, unsigned int cant){
	if(cant){arts_[&a] = cant;}
	else{arts_.erase(&a);}
}

// Implementación del operador de inserción de flujo para los datos de un objeto Usuario
std::ostream& operator <<(std::ostream& os, const Usuario& u){
	os<<u.id_<<" ["<<u.cont_.clave()<<"] "<<u.nom_<<" "<<u.apell_<<std::endl<<u.dir_<<std::endl<<"Tarjetas:\n\n";
	for(auto i=u.cards_.begin();i!=u.cards_.end();i++){
		os<<*i->second<<std::endl<<std::endl;
	}
	return os;
}

// Implementación de la función para inserción de flujo de los datos del carro de artículos de un objeto Usuario
std::ostream& mostrar_carro(std::ostream& os, const Usuario& u){
	os<<"Carrito de compra de "<<u.id()<<" [Artículos: "<<u.n_articulos()
	<<"]\nCant.\tArtículo\n===========================================================\n";
	for(auto i: u.compra())
	{
		os<<i.second<<"\t["<<i.first->referencia()<<"] \""<<i.first->titulo()<<"\", "<<i.first->f_publi().anno()<<". "
		<<std::fixed<<std::setprecision(2)<<i.first->precio()<<" €."<<std::endl;
	}
	return os;
}
