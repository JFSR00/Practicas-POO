#include "articulo.hpp"
#include <iomanip>
#include <iostream>

//--------------------| Clase Autor |--------------------
// Constructor de la clase Autor
Autor::Autor(Cadena n, Cadena a, Cadena d) noexcept : nom_(n), apel_(a), dir_(d){}

//--------------------| Clase Articulo |--------------------
// Constructor de la clase Articulo
Articulo::Articulo(Autores& a, Cadena r, Cadena t, Fecha f, double p): aut_(a), ref_(r), tit_(t), f_publi_(f), prec_(p){
	if(a.empty()){throw Autores_vacios();}
}

// Implementación de la sobrecarga del operador de inserción de flujo para objetos derivados de la case Articulo
std::ostream& operator <<(std::ostream& os, const Articulo& a){
	os<<"["<<a.referencia()<<"] \""<<a.titulo()<<"\"";
	for(auto aut : a.autores()){
		if(aut == *a.autores().begin()){
			os<<", de "<<aut->apellidos();
		}else{
			os<<", "<<aut->apellidos();
		}
	}
	os<<". "<<a.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<a.precio()<<" €\n\t";
	a.impresion_especifica(os);
	return os;
}

//--------------------| Clase LibroDigital |--------------------
// Constructor de la clase LibroDigital
LibroDigital::LibroDigital(Autores a, Cadena r, Cadena t, Fecha f, double p, Fecha exp): Articulo(a,r,t,f,p), f_expir_(exp){}

// Implementación del método de inserción de flujo declarado como puro en la clase Articulo, para la clase LibroDigital
void LibroDigital::impresion_especifica(std::ostream& os) const{
	os<<"A la venta hasta el "<<f_expir_<<".";
}

//--------------------| Clase ArticuloAlmacenable |--------------------
// Constructor de la clase ArticuloAlmacenable
ArticuloAlmacenable::ArticuloAlmacenable(Autores a, Cadena r, Cadena t, Fecha f, double p, int s): Articulo(a,r,t,f,p), stock_(s){}

//--------------------| Clase Libro |--------------------
// Constructor de la clase Libro
Libro::Libro(Autores a, Cadena r, Cadena t, Fecha f, double p, int pg, int s): ArticuloAlmacenable(a,r,t,f,p,s), n_pag_(pg){}

// Implementación del método de inserción de flujo declarado como puro en la clase Articulo, para la clase Libro
void Libro::impresion_especifica(std::ostream& os) const{
	os<<n_pag_<<" págs., "<<stock_<<" unidades.";
}

//--------------------| Clase Cederron |--------------------
// Constructor de la clase Cederron
Cederron::Cederron(Autores a, Cadena r, Cadena t, Fecha f, double p, int tam, int s): ArticuloAlmacenable(a,r,t,f,p,s), tam_(tam){}

// Implementación del método de inserción de flujo declarado como puro en la clase Articulo, para la clase Cederron
void Cederron::impresion_especifica(std::ostream& os) const{
	os<<tam_<<" MB, "<<stock_<<" unidades.";
}
