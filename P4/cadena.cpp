#include <iostream>
#include <cstring>
#include <stdexcept>
#include "cadena.hpp"

Cadena::Cadena(unsigned long tam, char c):s_(new char[tam+1]),tam_(tam){
	for(unsigned i=0;i<tam;i++){
		s_[i]=c;
	}
	s_[tam_]='\0';
}

Cadena::Cadena(const Cadena& cad):s_(new char[cad.tam_+1]),tam_(cad.tam_){
	strcpy(s_,cad.s_);
}

Cadena::Cadena(Cadena&& cad):s_(cad.s_),tam_(cad.tam_){
	cad.s_ = nullptr;
	cad.tam_ = 0;
}

Cadena::Cadena(const char* cad):s_(new char[strlen(cad)+1]),tam_(strlen(cad)){
	strcpy(s_,cad);
}

Cadena::~Cadena() noexcept{
	delete[] s_;
}

Cadena& Cadena::operator =(const Cadena& cad) noexcept{
	if(&cad!=this){
		tam_=cad.tam_;
		delete[] s_;
		s_=new char[strlen(cad.s_)+1];
		strcpy(s_,cad.s_);
	}
	return *this;
}

Cadena& Cadena::operator =(Cadena&& cad) noexcept{
	if(cad!=*this){
		delete[] s_;
		s_ = cad.s_;
		tam_ = cad.tam_;
		cad.s_ = nullptr;
		cad.tam_ = 0;
	}
	return *this;
}

Cadena& Cadena::operator =(const char* cad) noexcept{
	*this=Cadena(cad);
	return *this;
}

Cadena Cadena::substr(unsigned i, unsigned tam) const{
	if(!(i>=tam_||(i+tam)>tam_||(i+tam)<i)){
		Cadena str(tam);
		for(unsigned j=0;j<tam;j++){
			str.s_[j]=this->s_[j+i];
		}
		str.s_[tam]='\0';
		return str;
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
}

Cadena& Cadena::operator +=(const Cadena& cad) noexcept{
	char *c=new char[1 + strlen(s_) + strlen(cad.s_)];
	strcpy(c,s_);
	strcat(c,cad.s_);
	*this=Cadena(c);
	delete[] c;
	return *this;
}

Cadena& Cadena::operator +=(const char* cad) noexcept{
	char *c=new char[1 + strlen(s_) + strlen(cad)];
	strcpy(c,s_);
	strcat(c,cad);
	*this=Cadena(c);
	delete[] c;
	return *this;
}

Cadena const Cadena::operator +(const Cadena& b) const noexcept{
	Cadena c(*this);
	return c+=b;
}

bool operator <(const Cadena& a, const Cadena& b) noexcept{
	return (strcmp(a.c_str(),b.c_str())<0)? true : false;
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
	return (strcmp(a.c_str(),b.c_str())==0)? true : false;
}

bool operator !=(const Cadena& a, const Cadena& b) noexcept{
	return !(a==b);
}

char const Cadena::at(unsigned i) const{
	if(i<tam_){
		return s_[i];
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
}

char& Cadena::at(unsigned i){
	if(i<tam_){
		return s_[i];
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
	char* str = new char[33];
	int i = 0;

	while(isspace(is.get())&&is.good()){}
	is.unget();

	while((!isspace(is.peek()))&&(i<32)&&is.good()){
		str[i]=is.get();
		i++;
	}

	str[i]='\0';
	cad = Cadena(str);

	delete[] str;
	return is;
}
