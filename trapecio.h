#ifndef TRAPECIO_H
#define TRAPECIO_H

#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <cmath>

#include "Expression.h"
#include "util.h"

using std::string;
using std::vector;
using util::encontrarMaximo;

namespace integracion{
	
	/**
	* @brief Integracion mediante el metodo del trapecio.
	*/
	class trapecio{
	public:
		
		/**
		* @brief Crea una nueva instancia de trapecio.
		* @param str_fn Funcion a integrar.
		*/
		trapecio(string str_fn):f(str_fn){}
		
		
		void crear_tabla(vector<double> &x, 
						 vector<double> &y,
						 double a, 
						 double b, 
						 int n){
			//Reservar el espacio para la cantidad requerida de segmentos
			x.resize(n+1);
			y.resize(n+1);
			
			//Calcular el paso
			double h = (b - a)/(double)n;
			
			double xi=a;
			
			for(int i=0;i<=n;i++){
				x[i]=xi;
				y[i]=f(xi);
				xi+=h;
			}
		}
		
		/**
		* @brief Calcula el valor de la integral en el intervalo
		* @param a Limite inferior del intervalo
		* @param b Limite superior del intervalo
		* @param n Cantidad de segmentos
		* @return Valor aproximado de la integral
		*/
		double calcular(double a,
						double b,
						int n){
			
			if(n==0){
				return NAN;
			}
			
			//Intercambiar los limites si el limite inferior es mayor que el superior
			if(a>b){
				std::swap(a,b);
			}
			
			vector <double> x;
			vector <double> y;
			
			crear_tabla(x, y, a, b, n);
			
			return calcular(x,y);
		}
			
		/**
		* @brief Calcular la integral de una tabla de datos
		* @param x Valores de la variable independiente
		* @param y Valores de la variable independiente
		* @return Valor aproximado de la integral
		*/
		double calcular(vector<double> x,
						vector<double> y){
			size_t n = x.size()-1;
			if(n<=0){
				return NAN;
			}
			double sum = 0.0f;
			
			for(size_t i=1; i<n; i++){
				sum+=y[i];
			}
			
			double a = x[0];
			double b = x[n];
			
			double coef = y[0]+(2.0f*sum)+y[n];
			
			return (b-a)*(coef/(2.0f*n));
		}
		
		/**
		* @brief Calcula el error de aproximacion en un intervalo
		* @param a Limite inferior del intervalo
		* @param b Limite superior del intervalo
		* @param str_d2fn Texto de la segunda derivada de la funcion
		* @return Error de la aproximacion
		*/
		double calcularError(double a, double b, string str_d2fn){
			double df2E = encontrarMaximo(a, b, 0.001f, str_d2fn);
			
			return (pow(b - a,3.0f)/12.0f)*df2E;
		}
	private:
		Expression f; /*!< Evaluador de la funcion */
		
	};
};
#endif
