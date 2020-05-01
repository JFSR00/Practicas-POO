/* Juan Francisco Santos Relinque */

#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <set>
#include <ostream>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Usuario;

class Numero{
public:
	Numero(const Cadena&);

	operator const char*() const;

	friend bool operator <(const Numero&, const Numero&);

	typedef enum{LONGITUD, DIGITOS, NO_VALIDO} Razon;
	class Incorrecto{
		Razon err_;
	public:
		Incorrecto(Razon r):err_(r){};
		Razon razon() const;
	};

private:
	Cadena num_;

};

class Tarjeta{
public:
	typedef enum{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress} Tipo;

	Tarjeta(const Numero&, Usuario&, const Fecha&);
	Tarjeta(const Tarjeta&) = delete;
	Tarjeta& operator =(const Tarjeta&) = delete;
	~Tarjeta();

	const Numero& numero() const;
	const Usuario* titular() const;
	const Fecha& caducidad() const;
	const bool activa() const;

	const Tipo tipo() const;

	bool activa(bool =true);
	void anula_titular();

	friend bool operator <(const Tarjeta&, const Tarjeta&);
	friend std::ostream& operator <<(std::ostream&, const Tarjeta::Tipo&);
	friend std::ostream& operator <<(std::ostream&, const Tarjeta&);

	class Caducada{
		Fecha err_;
	public:
		Caducada(Fecha f):err_(f){};
		Fecha cuando() const;
	};

	class Num_duplicado{
		Numero n_;
	public:
		Num_duplicado(Numero n):n_(n){};
		Numero que() const;
	};

	class Desactivada{};

private:
	Numero tarj_;
	Usuario* prop_;
	Fecha cad_;
	bool act_;

	static std::set<Numero> numeros_;

};

// --------------| Inline clase Numero |--------------
inline Numero::operator const char*() const{return num_.c_str();}

inline Numero::Razon Numero::Incorrecto::razon() const{return err_;}

inline bool operator <(const Numero& a, const Numero& b){return (a.num_<b.num_);}

// --------------| Inline clase Tarjeta |--------------
inline Fecha Tarjeta::Caducada::cuando() const{return err_;}
inline Numero Tarjeta::Num_duplicado::que() const{return n_;}

inline const Numero& Tarjeta::numero() const{return tarj_;}
inline const Usuario* Tarjeta::titular() const{return prop_;}
inline const Fecha& Tarjeta::caducidad() const{return cad_;}
inline const bool Tarjeta::activa() const{return act_;}

inline bool Tarjeta::activa(bool a){act_=a;return act_;}
inline void Tarjeta::anula_titular(){prop_=nullptr;act_=false;}

inline bool operator <(const Tarjeta& a, const Tarjeta& b){return (a.tarj_<b.tarj_);}

std::ostream& operator <<(std::ostream&, const Tarjeta::Tipo&);
std::ostream& operator <<(std::ostream&, const Tarjeta&);

#endif
