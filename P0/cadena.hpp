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

	// Sobrecarga de operadores de asignación
	Cadena& operator =(const Cadena&);
	Cadena& operator =(const char*);

	// Conversión implícita a cadena
	operator const char*();

	// Métodos de obtención de datos de la cadena
	int length();
	const char* substr(unsigned int, unsigned int);

	// Declaración de sobrecarga de operadores de concatenación
	friend Cadena& operator +=(Cadena&, const Cadena&);
	friend Cadena& operator +=(Cadena&, const char*);
	friend Cadena operator +(const Cadena&, const Cadena&);

	// Sobrecarga de operador [] para obtención de caracter a partir de índice
	// y método "at" para realizar la misma operación pero compobando que el índice
	// señala un carácter dentro de la cadena
	char const operator [](unsigned int) const;
	char& operator [](unsigned int);
	char const at(unsigned int) const;
	char& at(unsigned int);

	// Declaración de sobrecarga de operadores booleanos
	friend bool operator <(const Cadena&, const Cadena&);
	friend bool operator <=(const Cadena&, const Cadena&);
	friend bool operator >(const Cadena&, const Cadena&);
	friend bool operator >=(const Cadena&, const Cadena&);
	friend bool operator ==(const Cadena&, const Cadena&);
	friend bool operator !=(const Cadena&, const Cadena&);

private:
	char* cad_;
};

// Sobrecarga de operadores de concatenación
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
