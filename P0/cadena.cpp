#include <iostream>
#include <cstring>
#include <stdexcept>
#include "cadena.hpp"

Cadena::Cadena(int tam, char c):tam_(tam), cad_(new char[tam+1]){
	for(int i=0;i<tam;i++){
		cad_[i]=c;
	}
	cad_[tam_]='\0';
}

Cadena::Cadena(const Cadena& cad):tam_(cad.tam_), cad_(new char[cad.tam_+1]){
	strcpy(cad_,cad.cad_);
}

Cadena::Cadena(const char* cad):tam_(strlen(cad)), cad_(new char[strlen(cad)+1]){
	strcpy(cad_,cad);
}

Cadena::~Cadena() noexcept{
	delete[] cad_;
}

Cadena& Cadena::operator =(const Cadena& cad) noexcept{
	if(&cad!=this){
		tam_=cad.tam_;
		delete[] cad_;
		cad_=new char[strlen(cad.cad_)+1];
		strcpy(cad_,cad.cad_);
	}
	return *this;
}

Cadena& Cadena::operator =(const char* cad) noexcept{
	*this=Cadena(cad);
	return *this;
}

Cadena::operator const char *() const noexcept{
	char* str = new char[this->tam_];
	strcpy(str,this->cad_);
	return (const char*)str;
}

Cadena Cadena::substr(size_t i, size_t tam) const{
	if(!(i >= this->length() || i+tam > this->length() || i+tam < i)){
		Cadena str(tam + 1);
		for(unsigned j=0;j<tam;j++){
			str.cad_[j]=this->cad_[j+i];
		}
		str.cad_[tam]='\0';
		return str;
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
	/*if(i+tam<strlen(cad_)){
		char* str=new char[tam+1];
		for(unsigned int j=0;j<tam;j++){
			str[j]=cad_[j+i];
		}
		str[tam]='\0';
		return Cadena(str);
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}*/
}

Cadena& operator +=(Cadena& a, const Cadena& cad) noexcept{
	char *c=new char[1 + strlen(a.cad_) + strlen(cad.cad_)];
	strcpy(c,a.cad_);
	strcat(c,cad.cad_);
	a=Cadena(c);
	return a;
}

Cadena& operator +=(Cadena& a, const char* cad) noexcept{
	char *c=new char[1 + strlen(a.cad_) + strlen(cad)];
	strcpy(c,a.cad_);
	strcat(c,cad);
	a=Cadena(c);
	return a;
}

Cadena operator +(const Cadena& a, const Cadena& b) noexcept{
	Cadena c(a);
	return c+=b;
}

bool operator <(const Cadena& a, const Cadena& b) noexcept{
	/*bool ret_=false;
	int val_=strcmp(a.cad_,b.cad_);
	if(val_<0){
		val_=true;
	}
	return ret_;*/
	return (strcmp(a.cad_,b.cad_)<0)? true : false;
}

bool operator <=(const Cadena& a, const Cadena& b) noexcept{
	return ((a<b)||strcmp(a.cad_,b.cad_)==0)? true : false;
}

bool operator >(const Cadena& a, const Cadena& b) noexcept{
	return (strcmp(a.cad_,b.cad_)>0)? true : false;
}

bool operator >=(const Cadena& a, const Cadena& b) noexcept{
	return ((a>b)||strcmp(a.cad_,b.cad_)==0)? true : false;
}

bool operator ==(const Cadena& a, const Cadena& b) noexcept{
	return (strcmp(a.cad_,b.cad_)==0)? true : false;
}

bool operator !=(const Cadena& a, const Cadena& b) noexcept{
	return (strcmp(a.cad_,b.cad_)!=0)? true : false;
}

char const Cadena::at(unsigned int i) const{
	if(i<tam_){
		return cad_[i];
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
}

char& Cadena::at(unsigned int i){
	if(i<tam_){
		return cad_[i];
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
}
