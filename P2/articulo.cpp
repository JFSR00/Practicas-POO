#include "articulo.hpp"
#include <iomanip>
#include <iostream>
#include <locale>

Articulo::Articulo(int r, Cadena t, Fecha f, double p, int s): ref_(r), tit_(t), f_publi_(f), prec_(p), stock_(s){}

std::ostream& operator <<(std::ostream& os, Articulo& a){
	os<<"["<<a.ref_<<"] \""<<a.tit_<<"\", "<<a.f_publi_.anno()<<". "<<std::fixed<<std::setprecision(2)<<a.prec_<<" �";
	return os;
}
