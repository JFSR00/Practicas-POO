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
Se construye a partir de una cadena de caracteres de bajo nivel que contendr� la contrase�a
�en claro�, sin cifrar. La contrase�a puede ser incorrecta por ser demasiado corta
(menos de 5 caracteres, como se ha dicho), o por haber ocurrido alg�n error al cifrarse.

En esos casos, el constructor elevar� la excepci�n Clave::Incorrecta. Esta clase almacenar�
como atributo la raz�n de la incorrecci�n, que ser� una enumeraci�n llamada
Clave::Razon con las constantes CORTA y ERROR_CRYPT. Su m�todo observador razon
devolver� dicho atributo.

El m�todo verifica recibe como par�metro una cadena de bajo nivel con una supuesta
contrase�a en claro y devuelve el valor booleano verdadero si se corresponde con la contrase�a
almacenada, o falso si no. Vea la secci�n 5.6 para saber c�mo cifrar y descifrar
la contrase�a.
*/
