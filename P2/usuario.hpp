/* Juan Francisco Santos Relinque */

#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "cadena.hpp"

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

inline Clave::Razon Clave::Incorrecta::razon(){return err_;}

inline Cadena Clave::clave(){return key_;}

#endif
/*El método verifica recibe como parámetro una cadena de bajo nivel con una supuesta
contraseña en claro y devuelve el valor booleano verdadero si se corresponde con la contraseña
almacenada, o falso si no. Vea la sección 5.6 para saber cómo cifrar y descifrar
la contraseña.*/
