#ifndef ROMBERG_H
#define ROMBERG_H

#include <iostream>
#include <string>
#include "trapecio.h"

using integracion::trapecio;
using std::string;
using std::cout;
using std::endl;

namespace integracion{
	
	/**
	* @brief Resultado de integracion
	*/
	struct resultado_romberg{
		double valor = NAN; /*!< Valor de la integral*/
		double error = NAN; /*!< Error de aproximacion*/
	};
	
	/**
	* @brief Integracion mediante el metodo de romberg
	*/
	class romberg{
	public:
		
		/**
		* @brief Crea una nueva instancia de romberg
		* @param p_str_fn Texto de la funcion a integrar
		*/
		romberg(string p_str_fn):str_fn(p_str_fn){}
		
		
		/**
		* @brief Calcula la integral en el intervalo dado
		* @param a Limite inferior
		* @param b Limite superior
		* @param k Numero de aproximaciones
		* @return Valor de la integral aproximada
		*/
		resultado_romberg calcular(double a, double b, int k){
			
			int i,j;
			resultado_romberg res;
			
			vector<vector<double>> m(k);
			
			if(k<=1){
				return res;
			}
			
			int n=1;
			for(i=0;i<k;i++){
				m[i].resize(k-i);
				//Calcular el valor de la primera columna
				trapecio t(str_fn);
				m[i][0] = t.calcular(a,b,n);
				//cout << n << " segmentos = " << m[i][0] << endl;
				n*=2;
			}
			
			double pot = 4.0f;
			for(j=1;j<k;j++){
				for(i=0;i<k-j;i++){
					m[i][j]=((pot/(pot-1.0f))*m[i+1][j-1])-((1/(pot-1.0f))*m[i][j-1]);
				}
				pot*=4.0f;
			}
			
			res.valor = m[0][k-1];
			res.error = fabs((m[0][k-1] - m[0][k-2])/m[0][k-1]
							 )*100.0f;
			return res;
		}
		
	private:
		string str_fn; /*!< Texto de la funcion */
	};
};

#endif
