/*
 * articulo.cpp
 *
 *  Created on: 21 abr. 2020
 *      Author: Juan Francisco
 */

#include "articulo.hpp"
#include <iomanip>
#include <iostream>

Articulo::Articulo(int r, Cadena t, Fecha f, double p, int s): ref_(r), tit_(t), publi_(f), prec_(p), stock_(s){}

std::ostream& operator <<(std::ostream& os, Articulo& a){
	os<<"["<<a.ref_<<"] \""<<a.tit_<<"\", "<<a.publi_.anno()<<". "<<std::fixed<<std::setprecision(2)<<a.prec_<<" €";
	return os;
}

/*
 * El operador de inserción en un flujo de salida << imprimirá referencia, título, año de
 * publicación y precio con el formato: «referencia entre corchetes, espacio, título entre
 * comillas dobles, coma, espacio, año de publicación, punto, espacio, precio con 2 decimales,
 * espacio, símbolo del euro», como se muestra en el ejemplo:
 * [110] "Fundamentos de C++", 1998. 29,95 €

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main()
{
	double res,n,x;
	int pres;
	while(true)
	{
		res=0;
		cout<<"f(x)= ln(x), para x>0\n";
		cout<<"x= ";cin>>x;
		cout<<"n= ";cin>>n;
		if(n==0)
			return 0;
		for(double i=0;i<=n;i++)
		{
			res=res+((1/((2*i)+1))*(pow((((x*x)-1)/((x*x)+1)),((2*i)+1))));
		}
		cout<<"Precision: ";cin>>pres;
		if(pres>53)
		{
			pres=53;
		}
		cout<<"res= "<<fixed<<setprecision(pres)<<res<<endl<<endl;
	}
	return 0;
}
 *
 */
