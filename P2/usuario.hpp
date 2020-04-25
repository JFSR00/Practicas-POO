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
/*El m�todo verifica recibe como par�metro una cadena de bajo nivel con una supuesta
contrase�a en claro y devuelve el valor booleano verdadero si se corresponde con la contrase�a
almacenada, o falso si no. Vea la secci�n 5.6 para saber c�mo cifrar y descifrar
la contrase�a.*/
