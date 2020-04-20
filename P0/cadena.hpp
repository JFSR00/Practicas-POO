/* Juan Francisco Santos Relinque */

#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{
public:
	// Constructores y destructor
	Cadena(int tam=0, char c=' ');
	Cadena(const Cadena&);
	Cadena(const char*);
	~Cadena();

	// Sobrecarga de operadores de asignaci�n
	Cadena& operator =(const Cadena&);
	Cadena& operator =(const char*);

	// Conversi�n impl�cita a cadena
	operator const char*();

	// M�todos de obtenci�n de datos de la cadena
	int length();
	const char* substr(unsigned int, unsigned int);

	// Declaraci�n de sobrecarga de operadores de concatenaci�n
	friend Cadena& operator +=(Cadena&, const Cadena&);
	friend Cadena& operator +=(Cadena&, const char*);
	friend Cadena operator +(const Cadena&, const Cadena&);

	// Sobrecarga de operador [] para obtenci�n de caracter a partir de �ndice
	// y m�todo "at" para realizar la misma operaci�n pero compobando que el �ndice
	// se�ala un car�cter dentro de la cadena
	char const operator [](unsigned int) const;
	char& operator [](unsigned int);
	char const at(unsigned int) const;
	char& at(unsigned int);

	// Declaraci�n de sobrecarga de operadores booleanos
	friend bool operator <(const Cadena&, const Cadena&);
	friend bool operator <=(const Cadena&, const Cadena&);
	friend bool operator >(const Cadena&, const Cadena&);
	friend bool operator >=(const Cadena&, const Cadena&);
	friend bool operator ==(const Cadena&, const Cadena&);
	friend bool operator !=(const Cadena&, const Cadena&);

private:
	char* cad_;
};

// Sobrecarga de operadores de concatenaci�n
Cadena& operator +=(Cadena&, const Cadena&);
Cadena& operator +=(Cadena&, const char*);
Cadena operator +(const Cadena&, const Cadena&);

// Sobrecarga de operadores booleanos
bool operator <(const Cadena&, const Cadena&);
bool operator <=(const Cadena&, const Cadena&);
bool operator >(const Cadena&, const Cadena&);
bool operator >=(const Cadena&, const Cadena&);
bool operator ==(const Cadena&, const Cadena&);
bool operator !=(const Cadena&, const Cadena&);

#endif /* CADENA_HPP_ */
