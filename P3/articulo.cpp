#include "articulo.hpp"
#include <iomanip>
#include <cstdlib>
#include <iostream>

Articulo::Articulo(int r, Cadena t, Fecha f, double p, int s): ref_(r), tit_(t), f_publi_(f), prec_(p), stock_(s){}

Articulo::Articulo(Cadena r, Cadena t, Fecha f, double p, int s): ref_(atoi(r.c_str())), tit_(t), f_publi_(f), prec_(p), stock_(s){}

std::ostream& operator <<(std::ostream& os, Articulo& a){
	//os<<"["<<a.ref_<<"] \""<<a.tit_<<"\", "<<a.f_publi_.anno()<<". "<<std::fixed<<std::setprecision(2)<<a.prec_<<" €";
	os<<"["<<a.referencia()<<"] \""<<a.titulo()<<"\", "<<a.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<a.precio()<<" €";
	return os;
}
