/* Juan Francisco Santos Relinque */

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <set>
#include <ostream>

//--------------------| Clase Autor |--------------------
class Autor{
public:
	// Constructor de la clase Autor
	Autor(Cadena, Cadena, Cadena) noexcept;

	// Métodos observadores del a clase Autor
	const Cadena& nombre() const noexcept;
	const Cadena& apellidos() const noexcept;
	const Cadena& direccion() const noexcept;

private:
	// Atributos de la clase Autor
	const Cadena nom_, apel_, dir_;	// Nombre, apellidos y dirección del autor al que representa un objeto Autor
};

// Inline de los métodos observadores de la clase Autor
inline const Cadena& Autor::nombre() const noexcept{return nom_;}
inline const Cadena& Autor::apellidos() const noexcept{return apel_;}
inline const Cadena& Autor::direccion() const noexcept{return dir_;}

//--------------------| Clase Articulo |--------------------
// Esta es una clase abstracta, dado que posee un método virtual puro
class Articulo{
public:
	// Definición del tipo conjunto (std::set) de autores
	typedef std::set<Autor*> Autores;

	// Constructor y destructor de la clase Articulo
	Articulo(Autores&, Cadena, Cadena, Fecha, double);
	virtual ~Articulo() = default;

	// Declaración de métodos observadores y modificadores
	const Autores& autores() const;
	Cadena referencia() const;
	Cadena titulo() const;
	Fecha f_publi() const;
	double precio() const;
	double& precio();

	// Método virtual puro para inserción en un flujo de salida los datos referentes al objeto que implemente dicho método
	virtual void impresion_especifica(std::ostream&) const = 0;

	// Clase de error de clase Articulo
	class Autores_vacios{};
private:
	// Atributos de la clase
	const Autores aut_;			// Conjunto de autores de un artículo
	const Cadena ref_, tit_;	// Referencia y título de un artículo
	const Fecha f_publi_;		// Fecha de publicación de un artículo
	double prec_;				// Precio de un artículo
};

// Inline de los métodos observadores de la clase Articulo
inline const Articulo::Autores& Articulo::autores() const{return aut_;}
inline Cadena Articulo::referencia() const{return ref_;}
inline Cadena Articulo::titulo() const{return tit_;}
inline Fecha Articulo::f_publi() const{return f_publi_;}
inline double Articulo::precio() const{return prec_;}
inline double& Articulo::precio(){return prec_;}

// Sobrecarga de operador de inserción de flujo para un objeto derivado de la clase Artículo
std::ostream& operator <<(std::ostream&, const Articulo&);

//--------------------| Clase LibroDigital |--------------------
// Clase derivada de la clase Articulo
class LibroDigital : public Articulo{
public:
	// Constructor y destructor de la clase LibroDigital
	LibroDigital(Autores, Cadena, Cadena, Fecha, double, Fecha);
	~LibroDigital() = default;

	// Método observador de la clase
	Fecha f_expir() const;

	// Declaración del método de inserción de flujo declarado como puro en la clase Articulo
	void impresion_especifica(std::ostream&) const;

private:
	// Atributo de la clase LibroDigital
	const Fecha f_expir_;	// Fecha de expiración de venta de un artículo de este tipo
};

// Inline del método observador de la clase LibroDigital
inline Fecha LibroDigital::f_expir() const{return f_expir_;}

//--------------------| Clase ArticuloAlmacenable |--------------------
// Clase derivada de la clase Articulo
// Es una clase abstracta dado que no implementa el método virtual puro impresion_especifica(std::ostream&)
class ArticuloAlmacenable : public Articulo{
public:
	// Constructor y destructor de la clase ArticuloAlmacenable
	ArticuloAlmacenable(Autores, Cadena, Cadena, Fecha, double, int =0);
	virtual ~ArticuloAlmacenable() = default;

	// Métodos observador y modificador de la clase ArticuloAlmacenable
	int stock() const;
	int& stock();

protected:
	// Atributo de la clase ArticuloAlmacenable
	int stock_;	// Almacena la cantidad de artículos almacenables disponibles para vender
};

// Inline de los métodos observador y modificador de la clase ArtiuloAlmacenable
inline int ArticuloAlmacenable::stock() const{return stock_;}
inline int& ArticuloAlmacenable::stock(){return stock_;}

//--------------------| Clase Libro |--------------------
// Clase derivada de la clase ArticuloAlmacenable
class Libro : public ArticuloAlmacenable{
public:
	// Constructor y destructor de la clase Libro
	Libro(Autores, Cadena, Cadena, Fecha, double, int, int =0);
	~Libro() = default;

	// Método observador de la clase Libro
	int n_pag() const;

	// Declaración del método de inserción de flujo declarado como puro en la clase Articulo
	void impresion_especifica(std::ostream&) const;

private:
	// Atributo de la clase Libro
	const int n_pag_;	// Contiene el número de páginas de un libro
};

// Inline del método observador de la clase Libro
inline int Libro::n_pag() const{return n_pag_;}

//--------------------| Clase Cederron |--------------------
// Clase derivada de la clase ArticuloAlmacenable
class Cederron : public ArticuloAlmacenable{
public:
	// Constructor y destructor de la clase Cederron
	Cederron(Autores, Cadena, Cadena, Fecha, double, int, int =0);
	~Cederron() = default;

	// Método observador de la clase Cederron
	int tam() const;

	// Declaración del método de inserción de flujo declarado como puro en la clase Articulo
	void impresion_especifica(std::ostream&) const;

private:
	// Atributo de la clase Cederron
	const int tam_;	// Contiene el tamaño de un cederron
};

// Inline del método observador de la clase Cederron
inline int Cederron::tam() const{return tam_;}

#endif
