/**
* @file
* @brief Biblioteca de utilidades
*/

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>

using std::vector;
using std::setw;
using std::setprecision;
using std::cout;
using std::endl;
using std::string;


namespace util{
	
	/**
	* @brief Repite una cadena de caracteres
	* @param s Cadena a repetir
	* @param n Cantidad de repeticiones
	* @return Concatenacion de s n veces
	*/
	string str_repeat(string s, int n){
		string ret = "";
		for(int i=0; i<n; i++){
			ret+=s;
		}
		return ret;
	}
		
	/**
	* @brief Imprime una tabla de datos
	* @param x Variable independiente
	* @param y Variable dependiente
	* @param x_label Etiqueta de la variable independiente
	* @param y_label Etiqueta de la variable dependiente
	*/
	void imprimir_tabla(vector<double> x, 
						vector<double> y,
						string x_label="",
						string y_label="")
	{
		if(x_label.length() == 0) {x_label="X";}
		if(y_label.length() == 0) {y_label="Y";}
		
		size_t x_width = x_label.length() + 8;
		size_t y_width = y_label.length() + 8;
		
		cout << setw(x_width)
			<< x_label
			<< setw(y_width)
			<< y_label
			<< endl
			<< str_repeat("=",(x_width+y_width+2))
			<< endl;
		
		for(size_t i=0; i< x.size(); i++){
			cout << setw(x_width)
				<< x[i]
				<< setw(y_width)
				<< y[i]
				<< endl;
		}
		cout<< str_repeat("=",(x_width+y_width+2))
			<< endl << endl;
	}
	
	/**
	* @brief Eliminacion de Gauss para una matriz de reales
	* @param m Matriz
	* @return Vector de coeficientes
	*/
	vector<double> gauss(vector<vector<double>> m) {
		int i, j, k;
		int n = m.size();
		vector<double> resultado(n);
		//pivoteo: Para cada fila i, buscar en la columna i el valor mayor
		//e intercambiar la fila i por la que contenga el valor mayor.
		for (i = 0; i < n - 1; i++) {
			for (j = i + 1; j < n; j++) {
				if (m[i][j] > m[i][i]) {
					std::swap(m[i], m[j]);
				}
			}
		}
		//Eliminacion gaussiana
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				double v = m[j][i] / m[i][i]; //Valor que anula el elemento en la columna
				//Hacer la operacion fila[j] = fila[j] - v * fila[i]
				for(k=0; k <= n; k++) {
					m[j][k] -= v * m[i][k];
				}
			}
		}
		//Despejar las variables
		for (i= n - 1; i >= 0; i--) {
			resultado[i] = m[i][n];
			//reemplazar las variables ya halladas
			for (j = i + 1; j < n; j++) {
				if (i != j) { //reeemplazar las variables, menos el coeficiente
					resultado[i] = resultado[i] - m[i][j] * resultado[j];
				}
			}
			resultado[i] = resultado[i] / m[i][i];
		}
		return resultado;
	}
	
	/**
	* @brief Construye una tabla de datos espaciados uniformemente
	* @param x Referencia al vector donde se almacenaran los valores de x
	* @param y Referencia al vector donde se almacenaran los valores de y
	* @param a Limite inferior
	* @param b Limite Superior
	* @param n Cantidad de Segmentos
	* @param f_str Texto de la funcion
	*/
	void crear_tabla(vector<double> &x,
					 vector<double> &y,
					 double a,
					 double b,
					 int n,
					 string f_str){
		Expression f(std::move(f_str));
		cout << "F(x)=" << f.str() << endl;
		x.resize(n + 1);
		y.resize(n + 1);
		
		//Calcular el paso
		double h = (b - a) / (double) n;
		double xi = a;
		
		for (int i = 0; i <= n; i++) {
			x[i] = xi;
			y[i] = f(xi);
			xi += h;
		}
	}
		
	/**
	* @brief Encuentra el valor maximo de una funcion en el rango dado
	* @param a Limite inferior del rango
	* @param b Limite superior del rango
	* @param paso Incremento
	* @param str_fn Texto de la funcion
	* @return Valor maximo de la funcion
	*/
	
	double encontrarMaximo(double a, double b, double paso, string str_fn){
		double valorMax=0.0f;
		Expression f(str_fn);
		double valor=f(a);
		// cout << "Valores maximos" << endl;
		for(double aux = a; aux<=b; aux+=paso){
			valor=f(aux);
			if(fabs(valorMax) < fabs(valor)){valorMax=valor;}
			
			// cout << "v: " << valor << "  vm:" << valorMax << endl;
		}
		return valorMax;
	}
};


#endif
