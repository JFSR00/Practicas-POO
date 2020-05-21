/* Juan Francisco Santos Relinque */

#ifndef FECHA_HPP
#define FECHA_HPP
#include <ostream>
#include <istream>

class Fecha {
public:
	class Invalida{
		char *error_;
	public:
		Invalida(const char*);
		const char* por_que() const;
	};

	// A�os m�ximo y m�nimo:
	static const int AnnoMaximo=2037, AnnoMinimo=1902;

	// Constructores
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
static const Fecha::Invalida ERROR_FORMATO{"Formato erroneo"};
static const Fecha::Invalida ERROR_DIA{"Dia erroneo"};
static const Fecha::Invalida ERROR_MES{"Mes erroneo"};
static const Fecha::Invalida ERROR_ANNO{"Anno erroneo"};

inline const char* Fecha::Invalida::por_que() const {return error_;}

// Sobrecarga de operadores booleanos
bool const operator <(const Fecha&, const Fecha&) noexcept;
bool const operator <=(const Fecha&, const Fecha&) noexcept;
bool const operator >(const Fecha&, const Fecha&) noexcept;
bool const operator >=(const Fecha&, const Fecha&) noexcept;
bool const operator ==(const Fecha&, const Fecha&) noexcept;
bool const operator !=(const Fecha&, const Fecha&) noexcept;

// Sobrecarga operadores de inserci�n y extracci�n
std::ostream& operator <<(std::ostream&, const Fecha&);
std::istream& operator >>(std::istream&, Fecha&);

#endif
