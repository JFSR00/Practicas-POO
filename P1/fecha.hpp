/* Juan Francisco Santos Relinque */

#ifndef FECHA_HPP
#define FECHA_HPP
#include <ostream>
#include <istream>
#include <iostream>

class Fecha {
public:
	class Invalida{
		char *error_;
		int error_code;
	public:
		Invalida(const char*, int);
		const char* por_que() const {return error_;};
		int const e_code() const {return error_code;};
	};

	// A�os m�ximo y m�nimo:
	static const int AnnoMaximo=2037, AnnoMinimo=1902;

	// Constructores y destructor
	explicit Fecha(int d=0, int m=0, int a=0);
	Fecha(const char*);

	// M�todos de obtenci�n de datos
	int const dia() const noexcept {return d;};
	int const mes() const noexcept {return m;};
	int const anno() const noexcept {return a;};

	// Sobrecarga de operadores
	Fecha& operator +=(const int);
	Fecha& operator -=(const int);
	Fecha& operator ++();
	Fecha& operator --();
	Fecha operator ++(const int);
	Fecha operator --(const int);
	Fecha operator +(const int) const;
	Fecha operator -(const int) const;

	// Declaraci�n de sobrecarga de operadores booleanos
	friend bool const operator <(const Fecha&, const Fecha&) noexcept;
	friend bool const operator <=(const Fecha&, const Fecha&) noexcept;
	friend bool const operator >(const Fecha&, const Fecha&) noexcept;
	friend bool const operator >=(const Fecha&, const Fecha&) noexcept;
	friend bool const operator ==(const Fecha&, const Fecha&) noexcept;
	friend bool const operator !=(const Fecha&, const Fecha&) noexcept;

	// Conversi�n a cadena
	const char* cadena() const noexcept;

private:
	int d, m, a;

	// M�todos para la validaci�n de la fecha y la construcci�n de la fecha del d�a actual
	void f_hoy() noexcept;
	void const verif_fecha() const;

};

// Mensajes de error:
static const Fecha::Invalida ERROR_FORMATO{"Formato erroneo",0};
static const Fecha::Invalida ERROR_DIA{"Dia erroneo",1};
static const Fecha::Invalida ERROR_MES{"Mes erroneo",2};
static const Fecha::Invalida ERROR_ANNO{"A�o erroneo",3};

// Sobrecarga de operadores booleanos
bool const operator <(const Fecha&, const Fecha&) noexcept;
bool const operator <=(const Fecha&, const Fecha&) noexcept;
bool const operator >(const Fecha&, const Fecha&) noexcept;
bool const operator >=(const Fecha&, const Fecha&) noexcept;
bool const operator ==(const Fecha&, const Fecha&) noexcept;
bool const operator !=(const Fecha&, const Fecha&) noexcept;

std::ostream& operator <<(std::ostream&, const Fecha&);
std::istream& operator >>(std::istream&, Fecha&);
#endif
