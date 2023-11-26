#include<iostream>
#include <string>
#include <iomanip>

#define _USE_MATH_DEFINES
#include "trapecio.h"
#include "util.h"
#include "simpson.h"
#include "romberg.h"
#include "derivacion.h"
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setprecision;

using integracion::trapecio;
using integracion::simpson;
using integracion::romberg;
using integracion::resultado_romberg;
using derivacion::derivada;
using util::imprimir_tabla;
/**
* @brief Integracion usando el metodo del trapecio
* @param title Titulo del caso
* @param str_fn Funcion a integrar
* @param a Limite inferior
* @param b Limite superior
* @param Cantidad de segmentos
*/
void integracion_trapecio(string title,
					  string str_fn,
					  string str_d2fn,
					  double a,
					  double b,
					  int n);

/**
* @brief Integracion usando el metodo de simpson
* @param title Titulo del caso
* @param str_fn Texto de la funcion
* @param str_d4fn Texto de la cuarta derivada de la funcion
* @param a Limite inferior
* @param b Limite superior
* @param n Cantidad de segmentos
*/
void integracion_simpson(string title,
						 string str_fn,
						 string str_d4fn,
						 double a,
						 double b,
						 int n);

/**
* @brief Integracion usando el metodo de romberg
* @param title Titulo del caso
* @param str_fn Funcion a integrar
* @param a Limite inferior
* @param b Limite superior
* @param k Numero de aproximaciones
*/
void integracion_romberg(string title,
						 string str_fn,
						 double a,
						 double b,
						 int k);

/** 
* @brief Derivacion numerica para primeras derivadas
* @param title Titulo del caso
* @param str_fn Texto de la funcion
* @param str_fn Texto de la primera derivada de la funcion
* @param xi Valor en el que se evalua la primera derivada de la funcion
* @param paso Incremento de xi
* @param diferencias Variable entre 1 y 2 dependiendo de las diferencias que se deseen usar para el calculo
* @param direccion Variable entre -1 y 1 dependiendo de la direccion en la que se desee calcular la derivada
*/
void primera_derivada(string title,
					  string str_fn,
					  string str_dfn,
					  double xi,
					  double paso,
					  int direccion);

int main (int argc, char *argv[]) {
	
	// Menu principal para pedir que caso usar
	int opcion;
	
	do{
		cout << "\n========================================" << endl;
		cout << "Integracion Numerica" << endl;
		cout << "========================================" << endl;
		cout << "1. Metodo de Simpson 1/3" << endl;
		cout << "2. Metodo de Romberg" << endl;
		cout << "========================================" << endl;
		cout << "Diferenciacion Numerica" << endl;
		cout << "========================================" << endl;
		cout << "3. Primera derivada" << endl;
		cout << "0. Salir" << endl;
		cout << "========================================" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opcion;
		
		switch(opcion){
		case 1:
			integracion_simpson("Integracion numerica de sen(x) + sen(2.5*x)^3 ",
								"sin(x) + (sin(2.5*x))^3",
								"sin(x) + 7.5*((~312.5*((cos(2.5*x))^2)*sin(2.5*x)) + (109.375*((sin(2.5*x))^3)))",
								0,
								1.82584,
								32);
			break;
		case 2:
			integracion_romberg("Integracion numerica de sen(x) + sen(2.5*x)^3 ",
								"sin(x) + (sin(2.5*x))^3",
								0,
								1.82584,
								4);
			break;
		case 3:
			primera_derivada("Derivacion numerica de ln(x)*cos(x) ",
							 "ln(x)*cos(x)",
							 "(cos(x)/x)-(sin(x)*ln(x))",
							 6.35f,
							 0.1,
							 0);
			break;
		case 0:
			cout << "Saliendo..." << endl;
			break;
		default:
			cout << "Opcion invalida" << endl;
			break;
		}
	} while(opcion != 0);
	
	return 0;
}
	
void integracion_simpson(string title,
						 string str_fn,
						 string str_d4fn,
						 double a,
						 double b,
						 int n) {
	cout << title << ":" << " por simpson 1/3." << endl;
	
	simpson13 s(str_fn);
	
	//Calcular el valor de la integral
	double valor = s.calcular(a,b,n, str_d4fn);
	
	cout << "Integral ajustada: "
		<< valor << endl;
}

void integracion_romberg(string title,
						  string str_fn,
						  double a,
						  double b,
						  int k){
	
	cout << title << " por metodo de romberg" << endl;
	
	//Crear una instancia de romberg
	romberg r(str_fn);
	
	//Calcular el valor de la integral
	resultado_romberg res = r.calcular(a,b,k);
	
	cout << "Valor de la integral entre "
		<< a
		<< " y "
		<< b
		<< " con "
		<< k
		<< " aproximaciones es = "
		<< setprecision(8)
		<< res.valor << endl
		<< "El error de aproximacion es = "
		<< setprecision(8) << res.error << "%" << endl;
	
}
void primera_derivada(string title,
					  string str_fn,
					  string str_dfn,
					  double xi,
					  double paso,
					  int direccion){
	cout << title << endl;
	
	derivada dx(str_fn);
	
	//Calcular la primera derivada con primera diferencia central
	cout << "Tabla para la primera derivada con primera diferencia central" << endl;
	double dx1dc = dx.primera(xi,paso,1,0);
	
	cout << "La primera derivada con 1 diferencia central es: " << setprecision(5) << dx1dc << endl;
	//Calcular la primera derivada con segunda diferencia central
	cout << "Tabla para la primera derivada con segundas diferencias central" << endl;
	double dx2dc = dx.primera(xi,paso,2,0);
	
	cout << "La primera derivada con 2 diferencias central es: " << setprecision(5) << dx2dc << endl;
}

