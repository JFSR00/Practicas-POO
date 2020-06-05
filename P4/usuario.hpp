/* Juan Francisco Santos Relinque */

#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

// Declaración anticipada de las clases Numero y Tarjeta
class Numero;
class Tarjeta;

// ---------------| Clase Clave |---------------
class Clave{
public:
	// Constructor
	Clave(const char*);

	// Métodos observadores de la clase Clave
	const Cadena clave() const;
	bool verifica(const char*) const;

	// Definición de tipos de errores que se pueden producir en la construcción de un objeto de esta clase
	typedef enum{CORTA, ERROR_CRYPT} Razon;
	// Clase de error de la clase Clave
	class Incorrecta{
		Razon err_;
	public:
		Incorrecta(const Razon r):err_(r){};
		Razon razon() const;
	};

private:
	// Atributo de la clase Clave
	Cadena key_;	// Contiene la clave representada por un objeto de esta clase

};

// ---------------| Clase Usuario |---------------
class Usuario{
public:
	// Definición de tipos de contenedores usados para las asociaciones de la clase Usuario con las clases Tarjeta y Articulo
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned int> Articulos;

	// Constructor y destructor de la clase Usuario
	Usuario(Cadena, Cadena, Cadena, Cadena, Clave);
	Usuario(const Usuario&) = delete;				// Eliminamos el constructor de copia
	Usuario& operator =(const Usuario&) = delete;	// Eliminamos el operador de asignación
	~Usuario();

	// Métodos observadores de la clase Usuario
	Cadena id() const;
	Cadena nombre() const;
	Cadena apellidos() const;
	Cadena direccion() const;
	const Tarjetas& tarjetas() const;
	const Articulos& compra() const;

	// Métodos para la asociación o desasociación de un usuario con una tarjeta
	void es_titular_de(Tarjeta&);
	void no_es_titular_de(Tarjeta&);

	// Métodos para asociar un usuario con un artículo y consultar el número total de artículos asociados
	void compra(Articulo&, unsigned = 1);
	unsigned int n_articulos() const;

	// Declaración de la sobrecarga del operador de inserción de flujo de la clase Usuario como friend
	friend std::ostream& operator <<(std::ostream&, const Usuario&);

	// Clase de error de la clase Usuario, usada en caso de que exista ya un usuario con el mismo número de identificación
	class Id_duplicado{
		const Cadena error_;
	public:
		Id_duplicado(Cadena& c):error_(c){};
		Cadena idd() const;
	};

private:
	// Atributos de la clase Usuario
	const Cadena id_, nom_, apell_, dir_;	// Datos del usuario, como nº identificación, nombre, apellidos y dirección
	Clave cont_;		// Contraseña de acceso del usuario
	Tarjetas cards_;	// Conjunto (std::map) de tarjetas asociadas al usuario en cuestión
	Articulos arts_;	// Conjunto (std::unordered_map) de artículos asociados a este usuario

	static std::unordered_set<Cadena> users_;	// Variable estática contenedora de todos usuarios existentes en el sistema
};

// Inline de los métodos observadores de la clase Clave y de su clase de error Clave::Incorrecta
inline Clave::Razon Clave::Incorrecta::razon() const{return err_;}
inline const Cadena Clave::clave() const {return key_;}

// Inline de los métodos observadores de la clase Usuario
inline Cadena Usuario::Id_duplicado::idd() const{return error_;}

inline Cadena Usuario::id() const{return id_;}
inline Cadena Usuario::nombre() const{return nom_;}
inline Cadena Usuario::apellidos() const{return apell_;}
inline Cadena Usuario::direccion() const{return dir_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const {return cards_;}
inline const Usuario::Articulos& Usuario::compra() const {return arts_;}

inline unsigned int Usuario::n_articulos() const{return arts_.size();}

// Sobrecarga del operador de inserción de flujo para la inserción de los datos de uno objeto Usuario
std::ostream& operator <<(std::ostream&, const Usuario&);
// Función para inserción de flujo de los datos del carro de artículos de un objeto Usuario
std::ostream& mostrar_carro(std::ostream&, const Usuario&);

#endif
