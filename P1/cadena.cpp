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

Cadena::Cadena(Cadena&& cad):tam_(cad.tam_), cad_(cad.cad_){
	cad.cad_ = nullptr;
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

const char* Cadena::c_str() const noexcept{
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
	return (strcmp(a.cad_,b.cad_)<0)? true : false;
}

bool operator <=(const Cadena& a, const Cadena& b) noexcept{
	return ((a<b)||(a==b));
}

bool operator >(const Cadena& a, const Cadena& b) noexcept{
	return (b<a);
}

bool operator >=(const Cadena& a, const Cadena& b) noexcept{
	return ((b<a)||(a==b));
}

bool operator ==(const Cadena& a, const Cadena& b) noexcept{
	return (strcmp(a.cad_,b.cad_)==0)? true : false;
}

bool operator !=(const Cadena& a, const Cadena& b) noexcept{
	return !(a==b);
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

std::ostream& operator <<(std::ostream& os, const Cadena& cad){
	os<<cad.c_str();
	return os;
}

std::istream& operator >>(std::istream& is, Cadena& cad){
	char* str = new char[32];
	int i = 0;

	do{
		str[i]=is.get();
	}while(isspace(str[i]));

	do{
		i++;
		str[i]=is.get();
	}while((!isspace(str[i]))&&(i<31));
	is.unget();

	str[i]='\0';
	cad = Cadena(str);

	delete[] str;
	return is;
}
