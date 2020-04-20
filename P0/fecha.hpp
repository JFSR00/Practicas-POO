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
	Fecha(const Fecha&);
	explicit Fecha(const char*);
	~Fecha(){};

	// M�todos de obtenci�n de datos
	int const dia() const {return d;};
	int const mes() const {return m;};
	int const anno() const {return a;};

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
	friend bool operator <(const Fecha&, const Fecha&);
	friend bool operator <=(const Fecha&, const Fecha&);
	friend bool operator >(const Fecha&, const Fecha&);
	friend bool operator >=(const Fecha&, const Fecha&);
	friend bool operator ==(const Fecha&, const Fecha&);
	friend bool operator !=(const Fecha&, const Fecha&);

	// Conversi�n impl�cita a cadena
	operator const char*();

private:
	int d, m, a;

	// M�todos para la validaci�n de la fecha y la construcci�n de la fecha del d�a actual
	void f_hoy();
	void const verif_fecha() const;
	void const verif_formato(const char*) const;

	// M�todos para conversi�n de la fecha a cadena de caracteres
	const char* dia_sem() const;
	const char* nom_mes() const;

};

// Mensajes de error:
static const Fecha::Invalida ERROR_FORMATO{"Formato erroneo",0};
static const Fecha::Invalida ERROR_DIA{"Dia erroneo",1};
static const Fecha::Invalida ERROR_MES{"Mes erroneo",2};
static const Fecha::Invalida ERROR_ANNO{"A�o erroneo",3};

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
bool operator <(const Fecha&, const Fecha&);
bool operator <=(const Fecha&, const Fecha&);
bool operator >(const Fecha&, const Fecha&);
bool operator >=(const Fecha&, const Fecha&);
bool operator ==(const Fecha&, const Fecha&);
bool operator !=(const Fecha&, const Fecha&);



#endif
