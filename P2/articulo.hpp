/* Juan Francisco Santos Relinque */

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <ostream>

class Articulo{
public:
	Articulo(int,Cadena,Fecha,double,int =0);

	int referencia();
	Cadena titulo();
	Fecha f_publi();
	double precio();
	int stock();

	friend std::ostream& operator <<(std::ostream&, Articulo&);

private:
	const int ref_;
	const Cadena tit_;
	const Fecha publi_;
	double prec_;
	int stock_;
};

inline int Articulo::referencia(){return ref_;}
inline Cadena Articulo::titulo(){return tit_;}
inline Fecha Articulo::f_publi(){return publi_;}
inline double Articulo::precio(){return prec_;}
inline int Articulo::stock(){return stock_;}

std::ostream& operator <<(std::ostream&, Articulo&);

#endif
