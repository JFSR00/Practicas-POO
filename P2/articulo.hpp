/* Juan Francisco Santos Relinque */

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <ostream>

class Articulo{
public:
	// Constructor
	Articulo(int,Cadena,Fecha,double,int =0);
	Articulo(Cadena,Cadena,Fecha,double,int =0);

	// Declaración de métodos consultores y modificadores
	int referencia() const;
	Cadena titulo() const;
	Fecha f_publi() const;
	double precio() const;
	double& precio();
	int stock() const;
	int& stock();

	// Declaración de sobrecarga de oerador <<
	friend std::ostream& operator <<(std::ostream&, Articulo&);

private:
	// Atributos de la clase
	const int ref_;
	const Cadena tit_;
	const Fecha f_publi_;
	double prec_;
	int stock_;
};

// Métodos inline
inline int Articulo::referencia() const{return ref_;}
inline Cadena Articulo::titulo() const{return tit_;}
inline Fecha Articulo::f_publi() const{return f_publi_;}
inline double Articulo::precio() const{return prec_;}
inline double& Articulo::precio(){return prec_;}
inline int Articulo::stock() const{return stock_;}
inline int& Articulo::stock(){return stock_;}

// Sobrecarga de oerador <<
std::ostream& operator <<(std::ostream&, Articulo&);

#endif
