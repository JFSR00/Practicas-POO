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
	Numero(Cadena);

	operator const char*() const;

	friend bool operator <(Numero&, Numero&);

	typedef enum{LONGITUD, DIGITOS, NO_VALIDO} Razon;
	class Incorrecto{
		Razon err_;
	public:
		Incorrecto(Razon r):err_(r){};
		Razon razon();
	};

private:
	Cadena num_;

};

class Tarjeta{
public:
	typedef enum{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress} Tipo;

	Tarjeta(const Numero&, const Usuario&, const Fecha&);
	Tarjeta(const Tarjeta&) = delete;
	Tarjeta& operator =(const Tarjeta&) = delete;
	~Tarjeta();

	Numero numero() const;
	Usuario titular() const;
	Fecha caducidad() const;
	bool activa() const;
	Tipo tipo();

	bool activa(bool =true);
	void anula_titular();

	friend bool operator <(Tarjeta&, Tarjeta&);
	friend std::ostream& operator <<(std::ostream&, const Tarjeta&);

	class Caducada{
		Fecha err_;
	public:
		Caducada(Fecha f):err_(f){};
		Fecha cuando();
	};

	class Num_duplicado{
		Numero n_;
	public:
		Num_duplicado(Numero n):n_(n){};
		Numero que();
	};

	class Desactivada{};

private:
	const Numero tarj_;
	const Usuario* prop_;
	const Fecha cad_;
	bool act_;

	static std::set<Numero> numeros_;

};

// --------------| Inline clase Numero |--------------
inline Numero::operator const char*() const{return num_.c_str();}

inline bool operator <(Numero& a, Numero& b){return (a.num_<b.num_);}

// --------------| Inline clase Tarjeta |--------------
inline Tarjeta::Caducada::cuando(){return err_;}
inline Tarjeta::Num_duplicado::que(){return n_;}

inline Numero Tarjeta::numero() const{return tarj_;}
inline Usuario Tarjeta::titular() const{return prop_;}
inline Fecha Tarjeta::caducidad() const{return cad_;}
inline bool Tarjeta::activa() const{return act_;}

inline bool Tarjeta::activa(bool a){act_=a;return act_;}
inline void Tarjeta::anula_titular(){prop_=nullptr;act_=false;}

inline bool operator <(Tarjeta& a, Tarjeta& b){return (a.tarj_<b.tarj_);}

std::ostream& operator <<(std::ostream&, const Tarjeta&);

#endif
