/* Juan Francisco Santos Relinque */

#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <set>
#include <ostream>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

// Declaración adelantada de la clase Usuario
class Usuario;

// ---------------| Clase Numero |---------------
class Numero{
public:
	// Constructor
	Numero(const Cadena&);

	// Operador de conversión a const char
	operator const char*() const;

	// Declaración de la sobrecarga del operador menor que para la comparación de objetos Numero
	friend bool operator <(const Numero&, const Numero&);

	// Definición de razones de error en la construcción de un obejto Numero
	typedef enum{LONGITUD, DIGITOS, NO_VALIDO} Razon;
	// Clase de error de la clase Numero
	class Incorrecto{
		Razon err_;
	public:
		Incorrecto(Razon r):err_(r){};
		Razon razon() const;
	};

private:
	// Atributo de la clase Numero
	Cadena num_;	// Contiene el número representado por un objeto de esta clase

};

// ---------------| Clase Tarjeta |---------------
class Tarjeta{
public:
	// Definición de tipos de tarjetas
	typedef enum{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress} Tipo;

	// Constructor esxplícito de Tarjeta y destructor por defecto
	Tarjeta(const Numero&, Usuario&, const Fecha&);
	Tarjeta(const Tarjeta&) = delete;				// Suprimimos el constructor de copia
	Tarjeta& operator =(const Tarjeta&) = delete;	// Suprimimos el operador de asignación
	~Tarjeta();

	// Métodos observadores de la clase Tarjeta
	const Numero& numero() const;
	const Usuario* titular() const;
	const Fecha& caducidad() const;
	const bool activa() const;

	const Tipo tipo() const;

	// Métodos modificadores de la clase Tarjeta
	bool activa(bool =true);
	void anula_titular();

	// Declaración de la sobrecarga del operador menor que para la comparación de objetos Tarjeta
	friend bool operator <(const Tarjeta&, const Tarjeta&);

	// Declaración de la sobrecarga del operador de inserción de flujo para la inserción de los datos de una
	// tarjeta o para insertar su tipo
	friend std::ostream& operator <<(std::ostream&, const Tarjeta::Tipo&);
	friend std::ostream& operator <<(std::ostream&, const Tarjeta&);

	// Clases de error de la clase Tarjeta
	// Clase Caducada usada en caso de que la tarjeta esté caducada
	class Caducada{
		Fecha err_;
	public:
		Caducada(Fecha f):err_(f){};
		Fecha cuando() const;
	};

	// Clase Num_duplicado usada en caso de que exista otra tarjeta con el mismo número
	class Num_duplicado{
		Numero n_;
	public:
		Num_duplicado(Numero n):n_(n){};
		Numero que() const;
	};

	// Clase Descactivada usada en caso de que la tarjeta no esté activa
	class Desactivada{};

private:
	// Atributos de la clase Tarjeta
	Numero tarj_;		// Contiene el número de la tarjeta en custión
	Usuario* prop_;		// Referencia al Usuario propietario de una tarjeta
	Fecha cad_;			// Fecha de caducidad de una tarjeta
	bool act_;			// Estado de activación de una tarjeta

	static std::set<Numero> numeros_;	// Variable estática contenedora de los números de todas las tarjetas
										// existentes, para poder controlar que no hayan duplicidades
};

// Inline de los métodos de la clase Numero
inline Numero::operator const char*() const{return num_.c_str();}
inline Numero::Razon Numero::Incorrecto::razon() const{return err_;}
inline bool operator <(const Numero& a, const Numero& b){return (a.num_<b.num_);}

// Inline de los métodos de la clase Tarjeta
inline Fecha Tarjeta::Caducada::cuando() const{return err_;}
inline Numero Tarjeta::Num_duplicado::que() const{return n_;}

inline const Numero& Tarjeta::numero() const{return tarj_;}
inline const Usuario* Tarjeta::titular() const{return prop_;}
inline const Fecha& Tarjeta::caducidad() const{return cad_;}
inline const bool Tarjeta::activa() const{return act_;}

inline bool Tarjeta::activa(bool a){act_=a;return act_;}
inline void Tarjeta::anula_titular(){prop_=nullptr;act_=false;}

inline bool operator <(const Tarjeta& a, const Tarjeta& b){return (a.tarj_<b.tarj_);}

// Sobrecarga del operador de inserción de flujo para Tarjeta y Tarjeta::Tipo
std::ostream& operator <<(std::ostream&, const Tarjeta::Tipo&);
std::ostream& operator <<(std::ostream&, const Tarjeta&);

#endif
