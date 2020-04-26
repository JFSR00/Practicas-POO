/* Juan Francisco Santos Relinque */

#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "cadena.hpp"

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

};

// --------------| Inline clase Numero |--------------
inline Numero::operator const char*() const{return num_.c_str();}

inline bool operator <(Numero& a, Numero& b){return (a.num_<b.num_);}

#endif
