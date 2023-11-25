#include<iostream>
#include <string>
#include <iomanip>

#define _USE_MATH_DEFINES
#include "trapecio.h"
#include "util.h"
#include "simpson.h"
#include "romberg.h"
#include <cmath>

using std::cout;
using std::endl;
using std::string;
using std::setprecision;

using integracion::trapecio;
using integracion::simpson;
using integracion::romberg;
using integracion::resultado_romberg;
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
* @param x Variable independiente
* @param y Variable dependiente
*/
void integracion_simpson(string title,
						 string str_d4fn,
						 vector<double> &x,
						 vector<double> &y);

/**
* @brief Integracion usando el metodo de romberg
* @param title Titulo del caso
* @param str_fn Funcion a integrar
* @param a Limite inferior
* @param b Limite superior
* @param Numero de aproximaciones
*/
void integracion_romberg(string title,
						 string str_fn,
						 double a,
						 double b,
						 int k);

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
			integracion_simpson();
			break;
		case 2:
			integracion_romberg();
			break;
		case 3:
			derivar();
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

void integracion_trapecio(string title,
						  string str_fn,
						  string str_d2fn,
						  double a,
						  double b,
						  int n){
	
	cout << title << endl;
	
	//Crear una instancia de trapecio
	trapecio t(str_fn);
	
	vector<double> x;
	vector<double> y;
	
	t.crear_tabla(x,y,a,b,n);
	
	imprimir_tabla(x,y,"   x   ", "   y   ");
	
	//Calcular el valor de la integral
	double valor = t.calcular(x,y);
	double error = t.calcularError(a,b,str_d2fn);
	
	cout << "Valor de la integral entre "
		 << a
		 << " y "
		 << b
		 << " = "
		 << setprecision(8)
		 << valor << endl
		 << "Error de la aproximacion = "
		 << fabs(error) << endl;
	
}
	
void integracion_simpson(string title,
						 string str_d4fn,
						vector<double> &x,
						vector<double> &y) {
	cout << title << ":" << " por simpson." << endl;
	
	simpson s;
	
	imprimir_tabla(x, y, "X", "Y");
	
	//Calcular el valor de la integral
	double valor = s.calcular(x, y, str_d4fn);
	
	cout << "Integral ajustada: "
		<< valor << endl;
}

void integracion_romberg(string title,
						  string str_fn,
						  double a,
						  double b,
						  int k){
	
	cout << title << endl;
	
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
		<< setprecision(8) << res.error << endl;
	
}

