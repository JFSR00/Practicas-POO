#define _XOPEN_SOURCE
extern "C" {
#include <unistd.h>
}
#include <cstring>
#include <random>
#include "usuario.hpp"

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
