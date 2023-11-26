#ifndef SIMPSONTERCIO_H
#define SIMPSONTERCIO_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Expression.h"
#include "util.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

using util::crear_tabla;
using util::imprimir_tabla;

namespace integracion{
	/**
	* @brief Integracion mediante el metodo de Simpson 1 tercio
	*/
	class simpson13{
	public:
		/**
		* @brief Constructor de la clase
		* @param p_fn Funcion a integrar
		*/
		explicit simpson13(string p_fn):str_fn(p_fn){}
		
		/**
		* @brief Calcula la integral en el intervalo dado por el metodo de simpson 1/3
		* @param a Limite inferior
		* @param b Limite superior
		* @param n Cantidad de segmentos
		* @param str_d4fn Texto de la cuarta derivada de la funcion
		* @return Integral aproximada
		*/
		double calcular(double a, double b, int n, string str_d4fn){
			if (n == 0 || n % 2 != 0) return NAN;
			if(a > b) std::swap(a , b);
			
			vector<double> x;
			vector<double> y;
			
			crear_tabla(x, y, a, b, n, str_fn);
			imprimir_tabla(x,y," X ", " F(x) ");
			
			return calcular(x, y, str_d4fn);
		}
		
		/**
		* @brief Calcula la integral con la tabla dada por el metodo de simpson 1/3
		* @param x Referencia a la variable independiente
		* @param y Referencia a la variable dependiente
		* @param str_d4fn Texto de la cuarta derivada de la funcion
		* @return Integral aproximada
		*/
		static double calcular(vector<double> &x,
							   vector<double> &y, 
							   string str_d4fn){
			size_t n = x.size() - 1;
			if(n <= 0 || n % 2 != 0) return NAN;
			
			double
				sum_pares = 0.0f,
				sum_impares = 0.0f,
				h = (x[n] - x[0]) / n,
				resultado = 0.0f;
			
			for(size_t i = 1; i < n; i++){
				if(i % 2 == 0){
					sum_pares += fabs(y[i]);
				} else {
					sum_impares += fabs(y[i]);
				}
			}
			
			double df4E = encontrarMaximo(x[0], x[n],((x[n]-x[0])/(double)n), str_d4fn);
			
			cout << "d4: " << df4E << endl;
			
			double error13 = (-(pow((x[n] - x[0])/2.0f,5.0f)/90.0f))*df4E;
			
			resultado = (h / 3.0f) * (fabs(y[0]) + 4.0f * sum_impares + 2.0f * sum_pares + fabs(y[n]));
			
			cout << "Resultado sin ajustar: " << resultado << endl;
			
			cout << "Error de la aproximacion: " << error13 << endl;
			
			//Resultado ajustado
			resultado = resultado + error13;
			
			return resultado;
		}
			
	private:
		string str_fn;
	};
}

#endif
