/* Juan Francisco Santos Relinque */

#ifndef CADENA_HPP_
#define CADENA_HPP_
#include<ostream>
#include<istream>
#include<iostream>

class Cadena{
public:
	// Constructores y destructor
	explicit Cadena(int tam=0, char c=' ');
	Cadena(const Cadena&);
	Cadena(Cadena&&);
	Cadena(const char*);
	~Cadena() noexcept;

	// Sobrecarga de operadores de asignación
	Cadena& operator =(const Cadena&) noexcept;
	Cadena& operator =(const char*) noexcept;

	// Conversión implícita a cadena
	const char* c_str() const noexcept;

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

	// Iteradores
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;
	reverse_iterator rbegin() noexcept;
	reverse_iterator rend() noexcept;
	const_reverse_iterator rbegin()const noexcept;
	const_reverse_iterator crbegin()const noexcept;
	const_reverse_iterator rend()const  noexcept;
	const_reverse_iterator crend()const noexcept;

private:
	char* cad_;
	size_t tam_;
};

// Inlines
inline size_t Cadena::length() const noexcept{return tam_;}
inline char const Cadena::operator [](unsigned int i) const noexcept{return cad_[i];}
inline char& Cadena::operator [](unsigned int i) noexcept{return cad_[i];}

// Inline iteradores
inline Cadena::iterator Cadena::begin() noexcept{return cad_;}
inline Cadena::iterator Cadena::end() noexcept{return cad_+tam_;}
inline Cadena::const_iterator Cadena::begin() const noexcept{return cad_;}
inline Cadena::const_iterator Cadena::cbegin() const noexcept{return cad_;}
inline Cadena::const_iterator Cadena::end() const noexcept{return cad_+tam_;}
inline Cadena::const_iterator Cadena::cend() const noexcept{return cad_+tam_;}
inline Cadena::reverse_iterator Cadena::rbegin() noexcept{return reverse_iterator(end());}
inline Cadena::reverse_iterator Cadena::rend() noexcept{return reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::rbegin()const noexcept{return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::crbegin()const noexcept{return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::rend()const  noexcept{return const_reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::crend()const noexcept{return const_reverse_iterator(begin());}

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

// Stream de entrada y salida
std::ostream& operator <<(std::ostream&, const Cadena&);
std::istream& operator >>(std::istream&, Cadena&);

#endif
