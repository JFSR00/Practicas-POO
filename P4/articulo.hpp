/* Juan Francisco Santos Relinque */

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <unordered_set>
#include <ostream>

//--------------------| Clase Autor |--------------------
class Autor{
public:
	Autor(Cadena, Cadena, Cadena) noexcept;

	const Cadena& nombre() const;
	const Cadena& apellidos() const;
	const Cadena& direccion() const;

private:
	const Cadena nom_, apel_, dir_;
};

inline const Cadena& Autor::nombre() const{return nom_;}
inline const Cadena& Autor::apellidos() const{return apel_;}
inline const Cadena& Autor::direccion() const{return dir_;}

//--------------------| Clase Articulo |--------------------
class Articulo{
public:
	typedef std::unordered_set<Autor*> Autores;

	// Constructores y destructor
	Articulo(Autores&, int, Cadena, Fecha, double);
	Articulo(Autores&, Cadena, Cadena, Fecha, double);
	virtual ~Articulo() = default;

	// Declaración de métodos consultores y modificadores
	const Autores& autores() const;
	int referencia() const;
	Cadena titulo() const;
	Fecha f_publi() const;
	double precio() const;
	double& precio();

	virtual void impresion_especifica(std::ostream&) = 0;

	class Autores_vacios{};
private:
	// Atributos de la clase
	const Autores aut_;
	const int ref_;
	const Cadena tit_;
	const Fecha f_publi_;
	double prec_;
};

// Métodos inline
inline const Articulo::Autores& Articulo::autores() const{return aut_;}
inline int Articulo::referencia() const{return ref_;}
inline Cadena Articulo::titulo() const{return tit_;}
inline Fecha Articulo::f_publi() const{return f_publi_;}
inline double Articulo::precio() const{return prec_;}
inline double& Articulo::precio(){return prec_;}

// Sobrecarga de operador <<
std::ostream& operator <<(std::ostream&, Articulo&);

//--------------------| Clase LibroDigital |--------------------
class LibroDigital : public Articulo{
public:
	LibroDigital(Autores, int, Cadena, Fecha, double, Fecha);
	LibroDigital(Autores, Cadena, Cadena, Fecha, double, Fecha);
	~LibroDigital() = default;

	Fecha f_expir() const;

	void impresion_especifica(std::ostream&);

private:
	const Fecha expira_;
};

inline Fecha LibroDigital::f_expir() const{return expira_;}

//--------------------| Clase ArticuloAlmacenable |--------------------
class ArticuloAlmacenable : public Articulo{
public:
	ArticuloAlmacenable(Autores, int, Cadena, Fecha, double, int =0);
	ArticuloAlmacenable(Autores, Cadena, Cadena, Fecha, double, int =0);
	virtual ~ArticuloAlmacenable() = default;

	int stock() const;
	int& stock();

private:
	int stock_;
};

inline int ArticuloAlmacenable::stock() const{return stock_;}
inline int& ArticuloAlmacenable::stock(){return stock_;}

//--------------------| Clase Libro |--------------------
class Libro : public ArticuloAlmacenable{
public:
	Libro(Autores, int, Cadena, Fecha, double, int, int =0);
	Libro(Autores, Cadena, Cadena, Fecha, double, int, int =0);
	~Libro() = default;

	int n_pag() const;

	void impresion_especifica(std::ostream&);

private:
	const int pgs_;
};

inline int Libro::n_pag() const{return pgs_;}

//--------------------| Clase Cederron |--------------------
class Cederron : public ArticuloAlmacenable{
public:
	Cederron(Autores, int, Cadena, Fecha, double, int, int =0);
	Cederron(Autores, Cadena, Cadena, Fecha, double, int, int =0);
	~Cederron() = default;

	int tam() const;

	void impresion_especifica(std::ostream&);

private:
	const int tam_;
};

inline int Cederron::tam() const{return tam_;}

#endif
