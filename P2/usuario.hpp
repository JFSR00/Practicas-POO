/* Juan Francisco Santos Relinque */

#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "cadena.hpp"

class Clave{
public:
	Clave(Cadena);

	Cadena clave();
	bool verifica(Cadena);

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
/*
Se construye a partir de una cadena de caracteres de bajo nivel que contendrá la contraseña
«en claro», sin cifrar. La contraseña puede ser incorrecta por ser demasiado corta
(menos de 5 caracteres, como se ha dicho), o por haber ocurrido algún error al cifrarse.

En esos casos, el constructor elevará la excepción Clave::Incorrecta. Esta clase almacenará
como atributo la razón de la incorrección, que será una enumeración llamada
Clave::Razon con las constantes CORTA y ERROR_CRYPT. Su método observador razon
devolverá dicho atributo.

El método verifica recibe como parámetro una cadena de bajo nivel con una supuesta
contraseña en claro y devuelve el valor booleano verdadero si se corresponde con la contraseña
almacenada, o falso si no. Vea la sección 5.6 para saber cómo cifrar y descifrar
la contraseña.
*/
