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

	// Sobrecarga de operadores de asignación
	Cadena& operator =(const Cadena&) noexcept;
	Cadena& operator =(const char*) noexcept;

	// Conversión implícita a cadena
	operator const char*() const noexcept;

	// Métodos de obtención de datos de la cadena
	//int length() noexcept;
	size_t length() const noexcept;
	Cadena substr(size_t, size_t) const;

	// Declaración de sobrecarga de operadores de concatenación
	friend Cadena& operator +=(Cadena&, const Cadena&) noexcept;
	friend Cadena& operator +=(Cadena&, const char*) noexcept;
	friend Cadena operator +(const Cadena&, const Cadena&) noexcept;

	// Sobrecarga de operador [] para obtención de caracter a partir de índice
	// y método "at" para realizar la misma operación pero compobando que el índice
	// señala un carácter dentro de la cadena
	char const operator [](unsigned int) const noexcept;
	char& operator [](unsigned int) noexcept;
	char const at(unsigned int) const;
	char& at(unsigned int);

	// Declaración de sobrecarga de operadores booleanos
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

// Sobrecarga de operadores de concatenación
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
