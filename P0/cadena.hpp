/* Juan Francisco Santos Relinque */

#ifndef CADENA_HPP_
#define CADENA_HPP_
#include<iostream>

class Cadena{
public:
	// Constructores y destructor
	explicit Cadena(int tam=0, char c=' ');
	Cadena(const Cadena&);
	Cadena(const char*);
	~Cadena() noexcept;

	// Sobrecarga de operadores de asignaci�n
	Cadena& operator =(const Cadena&) noexcept;
	Cadena& operator =(const char*) noexcept;

	// Conversi�n impl�cita a cadena
	operator const char*() const noexcept;

	// M�todos de obtenci�n de datos de la cadena
	//int length() noexcept;
	size_t length() const noexcept;
	Cadena substr(size_t, size_t) const;

	// Declaraci�n de sobrecarga de operadores de concatenaci�n
	friend Cadena& operator +=(Cadena&, const Cadena&) noexcept;
	friend Cadena& operator +=(Cadena&, const char*) noexcept;
	friend Cadena operator +(const Cadena&, const Cadena&) noexcept;

	// Sobrecarga de operador [] para obtenci�n de caracter a partir de �ndice
	// y m�todo "at" para realizar la misma operaci�n pero compobando que el �ndice
	// se�ala un car�cter dentro de la cadena
	char const operator [](unsigned int) const noexcept;
	char& operator [](unsigned int) noexcept;
	char const at(unsigned int) const;
	char& at(unsigned int);

	// Declaraci�n de sobrecarga de operadores booleanos
	friend bool operator <(const Cadena&, const Cadena&) noexcept;
	friend bool operator <=(const Cadena&, const Cadena&) noexcept;
	friend bool operator >(const Cadena&, const Cadena&) noexcept;
	friend bool operator >=(const Cadena&, const Cadena&) noexcept;
	friend bool operator ==(const Cadena&, const Cadena&) noexcept;
	friend bool operator !=(const Cadena&, const Cadena&) noexcept;

private:
	char* cad_;
	size_t tam_;
};

inline size_t Cadena::length() const noexcept{return tam_;}

inline char const Cadena::operator [](unsigned int i) const noexcept{return cad_[i];}

inline char& Cadena::operator [](unsigned int i) noexcept{return cad_[i];}

// Sobrecarga de operadores de concatenaci�n
Cadena& operator +=(Cadena&, const Cadena&) noexcept;
Cadena& operator +=(Cadena&, const char*) noexcept;
Cadena operator +(const Cadena&, const Cadena&) noexcept;

// Sobrecarga de operadores booleanos
bool operator <(const Cadena&, const Cadena&) noexcept;
bool operator <=(const Cadena&, const Cadena&) noexcept;
bool operator >(const Cadena&, const Cadena&) noexcept;
bool operator >=(const Cadena&, const Cadena&) noexcept;
bool operator ==(const Cadena&, const Cadena&) noexcept;
bool operator !=(const Cadena&, const Cadena&) noexcept;

#endif /* CADENA_HPP_ */
