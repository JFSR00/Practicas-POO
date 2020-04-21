#include <ctime>
#include <ostream>
#include <istream>
#include <iostream>
#include <cstring>
#include "fecha.hpp"

Fecha::Fecha(int d, int m, int a):d(d),m(m),a(a){f_hoy();verif_fecha();}

//Fecha::Fecha(const Fecha &f):d(f.d),m(f.m),a(f.a){}

Fecha::Fecha(const char* str){

	if(sscanf(str, "%02d/%02d/%04d",&d,&m,&a) == 3){
		f_hoy();
		verif_fecha();
	}
	else{throw Fecha::Invalida(ERROR_FORMATO);}
}

Fecha::Invalida::Invalida(const char* str, int c):error_(new char[strlen(str)]),error_code(c){strcpy(error_,str);}

void Fecha::f_hoy() noexcept{
	time_t t=time(nullptr);
	tm *tiempo=localtime(&t);
	if(d==0)
		d=tiempo->tm_mday;
	if(m==0)
		m=tiempo->tm_mon+1;
	if(a==0)
		a=tiempo->tm_year+1900;
}

void const Fecha::verif_fecha() const{
	if(a<Fecha::AnnoMinimo || a>Fecha::AnnoMaximo){throw Fecha::Invalida(ERROR_ANNO);}
	if(m<1 || m>12){throw Fecha::Invalida(ERROR_MES);}
	if(d>0){
		switch(m){
			case 1:
				if(d>31){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 2:
				if(a % 4 == 0 && (a % 400 == 0 || a % 100 != 0)){if(d>29){throw Fecha::Invalida(ERROR_DIA);}}
				else{if(d>28){throw Fecha::Invalida(ERROR_DIA);}}
				break;
			case 3:
				if(d>31){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 4:
				if(d>30){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 5:
				if(d>31){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 6:
				if(d>30){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 7:
				if(d>31){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 8:
				if(d>31){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 9:
				if(d>30){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 10:
				if(d>31){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 11:
				if(d>30){throw Fecha::Invalida(ERROR_DIA);}
				break;
			case 12:
				if(d>31){throw Fecha::Invalida(ERROR_DIA);}
				break;
			default:
				break;
		}
	}else{throw Fecha::Invalida(ERROR_DIA);}
}

Fecha& Fecha::operator +=(const int n){
	time_t t;
	struct tm * tiempo;

	time (&t);
	tiempo = localtime (&t);
	tiempo->tm_year = a - 1900;
	tiempo->tm_mon = m - 1;
	tiempo->tm_mday = d + n;

	mktime (tiempo);

	d=tiempo->tm_mday;
	m=tiempo->tm_mon+1;
	a=tiempo->tm_year+1900;

	verif_fecha();

	return *this;
}

Fecha& Fecha::operator ++(){return *this+= 1;}

Fecha& Fecha::operator -=(const int n){return *this+= -n;}

Fecha& Fecha::operator --(){return *this+= -1;}

Fecha Fecha::operator ++(const int){
	Fecha cp = *this;
	*this+= 1;
	return cp;
}

Fecha Fecha::operator --(const int){
	Fecha cp = *this;
	*this+= -1;
	return cp;
}

Fecha Fecha::operator +(const int n) const{
	Fecha cp = *this;
	return cp += n;
}

Fecha Fecha::operator -(const int n) const{
	Fecha cp = *this;
	return cp += -n;
}

const char* Fecha::cadena() const noexcept{
	char *s=new char[sizeof("mi�rcoles 12 de septiembre de 2001")+1];
	const char* mes[]={"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};
	const char* dia[]={"domingo","lunes","martes","mi�rcoles","jueves","viernes","s�bado"};
	tm f{0};

	f.tm_mday = this->d;
	f.tm_mon = this->m - 1;
	f.tm_year = this->a - 1900;

	mktime(&f);

	sprintf(s,"%s %d de %s de %d", dia[f.tm_wday], f.tm_mday, mes[f.tm_mon], f.tm_year + 1900);

	return (const char*)s;
}

bool const operator <(const Fecha& a, const Fecha& b) noexcept{
	if(a.a<b.a){return true;}
	else{
		if(a.m<b.m){return true;}
		else{
			if(a.d<b.d){return true;}
			else{return false;}
		}
	}
}

bool const operator <=(const Fecha& a, const Fecha& b) noexcept{return ((a<b)||(a==b));}

bool const operator >(const Fecha& a, const Fecha& b) noexcept{return (b<a);}

bool const operator >=(const Fecha& a, const Fecha& b) noexcept{return ((b<a)||(a==b));}

bool const operator ==(const Fecha& a, const Fecha& b) noexcept{return ((a.a==b.a)&&(a.m==b.m)&&(a.d==b.d))? true : false;}

bool const operator !=(const Fecha& a, const Fecha& b) noexcept{return !(a==b);}

std::ostream& operator <<(std::ostream& os, const Fecha& f){
	os<<f.dia()<<"/"<<f.mes()<<"/"<<f.anno();
	return os;
}

std::istream& operator >>(std::istream& is, Fecha& f){
	char* str = new char[11];

	is.getline(str,11);
	try
	{
	f = Fecha(str);
	}catch(Fecha::Invalida& e){
		is.setstate(std::ios_base::failbit);
		throw e;
	}

	delete[] str;

	return is;

}