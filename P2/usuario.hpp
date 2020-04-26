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

class Clave{
public:
	Clave(const char*);

	Cadena clave();
	bool verifica(const char*);

	typedef enum{CORTA, ERROR_CRYPT} Razon;
	class Incorrecta{
		Razon err_;
	public:
		Incorrecta(Razon r):err_(r){};
		Razon razon();
	};

private:
	Cadena key_;

};

class Usuario{
public:
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned int> Articulos;

	Usuario(Cadena, Cadena, Cadena, Cadena, Clave);
	Usuario(const Usuario&) = delete;
	Usuario& operator =(const Usuario&) = delete;
	~Usuario();

	Cadena id() const;
	Cadena nombre() const;
	Cadena apellidos() const;
	Cadena direccion() const;
	const Tarjetas& tarjetas() const;
	const Articulos& compra() const;

	void es_titular_de(Tarjeta&);
	void no_es_titular_de(Tarjeta&);

	void compra(Articulo&, unsigned = 1);
	unsigned int n_articulos() const;

	friend std::ostream& operator <<(std::ostream&, const Usuario&);

	class Id_duplicado{
		const Cadena error_;
	public:
		Id_duplicado(Cadena& c):error_(c){};
		Cadena idd() const;
	};

private:
	const Cadena id_, nom_, apell_, dir_;
	Clave cont_;
	Tarjetas cards_;
	Articulos arts_;

	static std::unordered_set<Cadena> users_;
};

// --------------| Inline clase Clave |--------------
inline Clave::Razon Clave::Incorrecta::razon(){return err_;}

inline Cadena Clave::clave(){return key_;}

// --------------| Inline clase Usuario |--------------
inline Cadena Usuario::Id_duplicado::idd() const{return error_;}

inline Cadena Usuario::id() const{return id_;}
inline Cadena Usuario::nombre() const{return nom_;}
inline Cadena Usuario::apellidos() const{return apell_;}
inline Cadena Usuario::direccion() const{return dir_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const{return cards_;}
inline const Usuario::Articulos& Usuario::compra() const{return arts_;}

inline unsigned int Usuario::n_articulos() const{return arts_.size();}

// Sobrecarga de operadores de flujo
std::ostream& operator <<(std::ostream&, const Usuario&);
std::ostream& mostrar_carro(std::ostream&, const Usuario&);

#endif
