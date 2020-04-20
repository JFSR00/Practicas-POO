/*
 * cadena.cpp
 *
 *  Created on: 7 abr. 2020
 *      Author: JFSR00
 */

#include <iostream>
#include <cstring>
#include <stdexcept>
#include "cadena.hpp"

Cadena::Cadena(int tam, char c):cad_(new char[tam+1]){
	for(int i=0;i<tam;i++){
		cad_[i]=c;
	}
	cad_[tam+1]='\0';
}

Cadena::Cadena(const Cadena& cad):cad_(new char[strlen(cad.cad_)+1]){
	strcpy(cad_,cad.cad_);
}

Cadena::Cadena(const char* cad):cad_(new char[strlen(cad)+1]){
	strcpy(cad_,cad);
}

Cadena::~Cadena(){
	delete[] cad_;
}

Cadena& Cadena::operator =(const Cadena& cad){
	if(&cad!=this){
		delete[] cad_;
		cad_=new char[strlen(cad.cad_)+1];
		strcpy(cad_,cad.cad_);
	}
	return *this;
}

Cadena& Cadena::operator =(const char* cad){
	*this=Cadena(cad);
	return *this;
}

Cadena::operator const char *(){
	return cad_;
}

int Cadena::length(){
	return strlen(cad_);
}

const char* Cadena::substr(unsigned int i, unsigned int tam){
	if((i>=0)&&(i+tam<strlen(cad_))){
		char* str=new char[tam+1];
		for(unsigned int j=0;j<tam;j++){
			str[j]=cad_[j+i];
		}
		str[tam]='\0';
		return str;
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
}

Cadena& operator +=(Cadena& a, const Cadena& cad){
	char *c=new char[1 + strlen(a.cad_) + strlen(cad.cad_)];
	strcpy(c,a.cad_);
	strcat(c,cad.cad_);
	a=Cadena(c);
	return a;
}

Cadena& operator +=(Cadena& a, const char* cad){
	char *c=new char[1 + strlen(a.cad_) + strlen(cad)];
	strcpy(c,a.cad_);
	strcat(c,cad);
	a=Cadena(c);
	return a;
}

Cadena operator +(const Cadena& a, const Cadena& b){
	Cadena c(a);
	return c+=b;
}

bool operator <(const Cadena& a, const Cadena& b){
	/*bool ret_=false;
	int val_=strcmp(a.cad_,b.cad_);
	if(val_<0){
		val_=true;
	}
	return ret_;*/
	return (strcmp(a.cad_,b.cad_)<0)? true : false;
}

bool operator <=(const Cadena& a, const Cadena& b){
	return ((a<b)||strcmp(a.cad_,b.cad_)==0)? true : false;
}

bool operator >(const Cadena& a, const Cadena& b){
	return (strcmp(a.cad_,b.cad_)>0)? true : false;
}

bool operator >=(const Cadena& a, const Cadena& b){
	return ((a>b)||strcmp(a.cad_,b.cad_)==0)? true : false;
}

bool operator ==(const Cadena& a, const Cadena& b){
	return (strcmp(a.cad_,b.cad_)==0)? true : false;
}

bool operator !=(const Cadena& a, const Cadena& b){
	return (strcmp(a.cad_,b.cad_)!=0)? true : false;
}

char const Cadena::operator [](unsigned int i) const{
	return cad_[i];
}

char& Cadena::operator [](unsigned int i){
	return cad_[i];
}

char const Cadena::at(unsigned int i) const{
	if((i>=0)&&(i<strlen(cad_))){
		return cad_[i];
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
}

char& Cadena::at(unsigned int i){
	if((i>=0)&&(i<strlen(cad_))){
		return cad_[i];
	}
	else{
		throw std::out_of_range("OUT_OF_RANGE");
	}
}






