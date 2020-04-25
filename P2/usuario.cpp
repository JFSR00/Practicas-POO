#include "usuario.hpp"
#include <unistd.h>
#include <cstring>
#include <random>

Clave::Clave(Cadena c){
	if(c.length()<5){throw Clave::Incorrecta(CORTA);}

	static const char* salt="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
	std::random_device r;
	std::uniform_int_distribution<int> dist(0,(int)strlen(salt)-1);

}
