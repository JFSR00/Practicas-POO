/* Juan Francisco Santos Relinque */

#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <ostream>
#include <istream>
#include <string>

class Cadena{
public:
	// Constructores y destructor
	explicit Cadena(unsigned long tam=0, char c=' ');
	Cadena(const Cadena&);
	Cadena(Cadena&&);
	Cadena(const char*);
	~Cadena() noexcept;

	// Sobrecarga de operadores de asignación
	Cadena& operator =(const Cadena&) noexcept;
	Cadena& operator =(Cadena&&) noexcept;
	Cadena& operator =(const char*) noexcept;

	// Conversión implícita a cadena
	const char* c_str() const noexcept;

	// Métodos de obtención de datos de la cadena
	unsigned length() const noexcept;
	Cadena substr(unsigned, unsigned) const;

	// Sobrecarga de operadores de concatenación
	Cadena& operator +=(const Cadena&) noexcept;
	Cadena& operator +=(const char*) noexcept;
	Cadena const operator +(const Cadena&) const noexcept;

	// Sobrecarga de operador [] para obtención de caracter a partir de índice
	// y método "at" para realizar la misma operación pero comprobando que el índice
	// señala un carácter dentro de la cadena
	char const operator [](unsigned) const noexcept;
	char& operator [](unsigned) noexcept;
	char const at(unsigned) const;
	char& at(unsigned);

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
	char* s_;
	unsigned tam_;
};

// Inlines
inline unsigned Cadena::length() const noexcept{return tam_;}
inline const char* Cadena::c_str() const noexcept{return s_;}
inline char const Cadena::operator [](unsigned i) const noexcept{return s_[i];}
inline char& Cadena::operator [](unsigned i) noexcept{return s_[i];}

// Inlines iteradores
inline Cadena::iterator Cadena::begin() noexcept{return s_;}
inline Cadena::iterator Cadena::end() noexcept{return s_+tam_;}
inline Cadena::const_iterator Cadena::begin() const noexcept{return s_;}
inline Cadena::const_iterator Cadena::cbegin() const noexcept{return s_;}
inline Cadena::const_iterator Cadena::end() const noexcept{return s_+tam_;}
inline Cadena::const_iterator Cadena::cend() const noexcept{return s_+tam_;}
inline Cadena::reverse_iterator Cadena::rbegin() noexcept{return reverse_iterator(end());}
inline Cadena::reverse_iterator Cadena::rend() noexcept{return reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::rbegin()const noexcept{return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::crbegin()const noexcept{return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::rend()const  noexcept{return const_reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::crend()const noexcept{return const_reverse_iterator(begin());}

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

// Función hash
namespace std{	// Estaremos dentro del espacio de nombres std
	template<>	// Es una especialización de una plantilla para Cadena
	struct hash<Cadena>{	// Es una clase con solo un operador publico
		size_t operator() (const Cadena& cad) const	// El operador función
		{
			hash<string> hs;				// Creamos un objeto hash de string
			const char* p = cad.c_str();	// Obtenemos la cadena de la Cadena
			string s(p);					// Creamos un string desde una cadena
			size_t res = hs(s);				// El hash del string. Como hs.operator()(s);
			return res;						// Devolvemos el hash del string
		}
	};
}

#endif
