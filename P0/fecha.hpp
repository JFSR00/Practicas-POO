/* Juan Francisco Santos Relinque */

#ifndef FECHA_HPP
#define FECHA_HPP

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

	// Declaraci�n de sobrecarga de operadores
	friend Fecha& operator ++(Fecha&);
	friend Fecha& operator --(Fecha&);
	friend Fecha& operator +=(Fecha&, const int);
	friend Fecha& operator -=(Fecha&, const int);
	friend Fecha operator ++(Fecha&, const int);
	friend Fecha operator --(Fecha&, const int);
	friend Fecha operator +(const Fecha&, const int);
	friend Fecha operator -(const Fecha&, const int);

	// Declaraci�n de sobrecarga de operadores booleanos
	friend bool const operator <(const Fecha&, const Fecha&) noexcept;
	friend bool const operator <=(const Fecha&, const Fecha&) noexcept;
	friend bool const operator >(const Fecha&, const Fecha&) noexcept;
	friend bool const operator >=(const Fecha&, const Fecha&) noexcept;
	friend bool const operator ==(const Fecha&, const Fecha&) noexcept;
	friend bool const operator !=(const Fecha&, const Fecha&) noexcept;

	// Conversi�n impl�cita a cadena
	operator const char*() const noexcept;

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
static const Fecha::Invalida ERROR_ANNO{"Anno erroneo",3};

// Sobrecarga de operadores
Fecha& operator ++(Fecha&);
Fecha& operator --(Fecha&);
Fecha& operator +=(Fecha&, const int);
Fecha& operator -=(Fecha&, const int);
Fecha operator ++(Fecha&, const int);
Fecha operator --(Fecha&, const int);
Fecha operator +(const Fecha&, const int);
Fecha operator -(const Fecha&, const int);

// Sobrecarga de operadores booleanos
bool const operator <(const Fecha&, const Fecha&) noexcept;
bool const operator <=(const Fecha&, const Fecha&) noexcept;
bool const operator >(const Fecha&, const Fecha&) noexcept;
bool const operator >=(const Fecha&, const Fecha&) noexcept;
bool const operator ==(const Fecha&, const Fecha&) noexcept;
bool const operator !=(const Fecha&, const Fecha&) noexcept;



#endif
