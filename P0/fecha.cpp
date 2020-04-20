#include <ctime>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "fecha.hpp"

Fecha::Fecha(int d, int m, int a):d(d),m(m),a(a){f_hoy();verif_fecha();}

Fecha::Fecha(const Fecha &f):d(f.d),m(f.m),a(f.a){}

Fecha::Fecha(const char* str){
	verif_formato(str);

	char *aux=new char[strlen(str)];

	strcpy(aux,str);
	aux=strtok(aux,"/");
	d=atoi(aux);
	aux=strtok(NULL,"/");
	m=atoi(aux);
	aux=strtok(NULL,"/");
	a=atoi(aux);

	delete aux;

	f_hoy();
	verif_fecha();
}

Fecha::Invalida::Invalida(const char* str, int c):error_(new char[strlen(str)]),error_code(c){strcpy(error_,str);}

void Fecha::f_hoy(){
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

void const Fecha::verif_formato(const char* str) const{
	int i=0,j=0;
	while(str[i])
	{
		if(str[i]==' '){throw Fecha::Invalida(ERROR_FORMATO);}
		if(str[i]=='/'){j++;}
		i++;
	}
	if(j<2){throw Fecha::Invalida(ERROR_FORMATO);}
}

Fecha& operator ++(Fecha& f){
	bool bucle=true;
	f.d++;
	do{
		try{
			f.verif_fecha();
			bucle=false;
		}
		catch(Fecha::Invalida& e){
			switch(e.e_code())
			{
			case 1:
				f.d=1;
				f.m++;
				break;
			case 2:
				f.m=1;
				f.a++;
				break;
			case 3:
				f.a--;
				f.m=12;
				f.d=31;
				throw e;
				break;
			}
		}
	}while(bucle);
	return f;
}

Fecha& operator --(Fecha& f){return f-=1;}

Fecha& operator +=(Fecha& f, const int n){
	bool bucle=true;
	f.d+=n;
	do{
		try{
			f.verif_fecha();
			bucle=false;
		}
		catch(Fecha::Invalida& e){
			switch(e.e_code())
			{
			case 1:
				switch(f.m){
				case 1:
					f.d-=31;
					break;
				case 2:
					if(f.a % 4 == 0 && (f.a % 400 == 0 || f.a % 100 != 0)){f.d-=29;}
					else{f.d-=28;}
					break;
				case 3:
					f.d-=31;
					break;
				case 4:
					f.d-=30;
					break;
				case 5:
					f.d-=31;
					break;
				case 6:
					f.d-=30;
					break;
				case 7:
					f.d-=31;
					break;
				case 8:
					f.d-=31;
					break;
				case 9:
					f.d-=30;
					break;
				case 10:
					f.d-=31;
					break;
				case 11:
					f.d-=30;
					break;
				case 12:
					f.d-=31;
					break;
				default:
					break;
				}
				f.m++;
				break;
			case 2:
				f.m=1;
				f.a++;
				break;
			case 3:
				f.a--;
				f.m=12;
				f.d=(31+(f.d-n));
				throw e;
				break;
			}
		}
	}while(bucle);
	return f;
}

Fecha& operator -=(Fecha& f, const int n){
	bool bucle=true;
	f.d-=n;
	do{
		try{
			f.verif_fecha();
			bucle=false;
		}
		catch(Fecha::Invalida& e){
			switch(e.e_code())
			{
			case 1:
				f.m--;
				switch(f.m){
				case 1:
					f.d+=31;
					break;
				case 2:
					if(f.a % 4 == 0 && (f.a % 400 == 0 || f.a % 100 != 0)){f.d+=29;}
					else{f.d+=28;}
					break;
				case 3:
					f.d+=31;
					break;
				case 4:
					f.d+=30;
					break;
				case 5:
					f.d+=31;
					break;
				case 6:
					f.d+=30;
					break;
				case 7:
					f.d+=31;
					break;
				case 8:
					f.d+=31;
					break;
				case 9:
					f.d+=30;
					break;
				case 10:
					f.d+=31;
					break;
				case 11:
					f.d+=30;
					break;
				default:
					f.d+=31;
					break;
				}
				break;
			case 2:
				f.m=12;
				f.a--;
				break;
			case 3:
				f.a++;
				f.m=1;
				f.d=1;
				throw e;
				break;
			}
		}
	}while(bucle);
	return f;
}

Fecha operator ++(Fecha& f, const int){
	Fecha cp = f;
	++f;
	return cp;
}

Fecha operator --(Fecha& f, const int){
	Fecha cp = f;
	f-=1;
	return cp;
}

Fecha operator +(const Fecha& f, const int n){
	Fecha cp = f;
	return cp += n;
}

Fecha operator -(const Fecha& f, const int n){
	Fecha cp = f;
	return cp -= n;
}

Fecha::operator const char*(){
	char *s=new char[sizeof("miércoles 12 de septiembre de 2001")+1];
	sprintf(s,"%s %d de %s de %d",Fecha::dia_sem(),d,Fecha::nom_mes(),a);
	return s;
}

const char* Fecha::dia_sem() const{
	const int reg[]={0,3,3,6,1,4,6,2,5,0,3,5};
	const int bis[]={0,3,4,0,2,5,0,3,6,1,4,6};

	int dia=((((a-1)%7)+((((a-1)/4)-((3*(((a-1)/100)+1))/4))%7)+reg[m-1]+(d%7))-1)%7;

	if(a % 4 == 0 && (a % 400 == 0 || a % 100 != 0)){dia=((((a-1)%7)+((((a-1)/4)-((3*(((a-1)/100)+1))/4))%7)+bis[m-1]+(d%7))-1)%7;}

	switch(dia){
	case 0:
		return "lunes";
		break;
	case 1:
		return "martes";
		break;
	case 2:
		return "miercoles";
		break;
	case 3:
		return "jueves";
		break;
	case 4:
		return "viernes";
		break;
	case 5:
		return "sabado";
		break;
	case 6:
		return "domingo";
		break;
	default:
		return "ERROR";
		break;
	}
}

const char* Fecha::nom_mes() const{
	switch(m){
	case 1:
		return "enero";
		break;
	case 2:
		return "febrero";
		break;
	case 3:
		return "marzo";
		break;
	case 4:
		return "abril";
		break;
	case 5:
		return "mayo";
		break;
	case 6:
		return "junio";
		break;
	case 7:
		return "julio";
		break;
	case 8:
		return "agosto";
		break;
	case 9:
		return "septiembre";
		break;
	case 10:
		return "octubre";
		break;
	case 11:
		return "noviembre";
		break;
	case 12:
		return "diciembre";
		break;
	default:
		return "ERROR";
		break;
	}
}

bool operator <(const Fecha& a, const Fecha& b){
	if(a.a<b.a){return true;}
	else{
		if(a.m<b.m){return true;}
		else{
			if(a.d<b.d){return true;}
			else{return false;}
		}
	}
}

bool operator <=(const Fecha& a, const Fecha& b){
	if((a<b)||(a==b)){return true;}
	else{return false;}
}

bool operator >(const Fecha& a, const Fecha& b){
	if(a.a>b.a){return true;}
	else{
		if(a.m>b.m){return true;}
		else{
			if(a.d>b.d){return true;}
			else{return false;}
		}
	}
}

bool operator >=(const Fecha& a, const Fecha& b){
	if((a>b)||(a==b)){return true;}
	else{return false;}
}

bool operator ==(const Fecha& a, const Fecha& b){
	if((a.a==b.a)&&(a.m==b.m)&&(a.d==b.d)){return true;}
	else{return false;}
}

bool operator !=(const Fecha& a, const Fecha& b){
	if(a==b){return false;}
	else{return true;}
}



















