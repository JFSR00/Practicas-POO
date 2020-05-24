#include "articulo.hpp"
#include <iomanip>
#include <cstdlib>
#include <iostream>

//--------------------| Clase Autor |--------------------

Autor::Autor(Cadena n, Cadena a, Cadena d) noexcept : nom_(n), apel_(a), dir_(d){}


//--------------------| Clase Articulo |--------------------

Articulo::Articulo(Autores& a, int r, Cadena t, Fecha f, double p): aut_(a), ref_(r), tit_(t), f_publi_(f), prec_(p){
	if(a.empty()){throw Autores_vacios();}
}

Articulo::Articulo(Autores& a, Cadena r, Cadena t, Fecha f, double p): aut_(a), ref_(atoi(r.c_str())), tit_(t), f_publi_(f), prec_(p){
	if(a.empty()){throw Autores_vacios();}
}

std::ostream& operator <<(std::ostream& os, Articulo& a){
	os<<"["<<a.referencia()<<"] \""<<a.titulo()<<"\"";
	for(auto aut : a.autores()){
		os<<", "<<aut->apellidos();
	}
	os<<". "<<a.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<a.precio()<<" €";
	a.impresion_especifica(os);
	return os;
}

//--------------------| Clase LibroDigital |--------------------

LibroDigital::LibroDigital(Autores a, int r, Cadena t, Fecha f, double p, Fecha exp): Articulo(a,r,t,f,p), expira_(exp){}

LibroDigital::LibroDigital(Autores a, Cadena r, Cadena t, Fecha f, double p, Fecha exp): Articulo(a,r,t,f,p), expira_(exp){}

void LibroDigital::impresion_especifica(std::ostream& os){
	os<<"\n\tA la venta hasta el "<<expira_<<".";
}

//--------------------| Clase ArticuloAlmacenable |--------------------

ArticuloAlmacenable::ArticuloAlmacenable(Autores a, int r, Cadena t, Fecha f, double p, int s): Articulo(a,r,t,f,p), stock_(s){}

ArticuloAlmacenable::ArticuloAlmacenable(Autores a, Cadena r, Cadena t, Fecha f, double p, int s): Articulo(a,r,t,f,p), stock_(s){}

//--------------------| Clase Libro |--------------------
Libro::Libro(Autores a, int r, Cadena t, Fecha f, double p, int pg, int s): ArticuloAlmacenable(a,r,t,f,p,s), pgs_(pg){}

Libro::Libro(Autores a, Cadena r, Cadena t, Fecha f, double p, int pg, int s): ArticuloAlmacenable(a,r,t,f,p,s), pgs_(pg){}

void Libro::impresion_especifica(std::ostream& os){
	os<<"\n\t"<<pgs_<<" págs., "<<this->stock()<<" unidades.";
}

//--------------------| Clase Libro |--------------------
Cederron::Cederron(Autores a, int r, Cadena t, Fecha f, double p, int tam, int s): ArticuloAlmacenable(a,r,t,f,p,s), tam_(tam){}

Cederron::Cederron(Autores a, Cadena r, Cadena t, Fecha f, double p, int tam, int s): ArticuloAlmacenable(a,r,t,f,p,s), tam_(tam){}

void Cederron::impresion_especifica(std::ostream& os){
	os<<"\n\t"<<tam_<<" MB, "<<this->stock()<<" unidades.";
}
