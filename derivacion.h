#ifndef DERIVACION_H
#define DERIVACION_H

#include <string>
#include "Expression.h"
#include "util.h"

using std::string;
using std::cout;
using std::endl;
using util::imprimir_tabla;

namespace derivacion{
	class derivada{
	public:
		derivada(string p_str_fn):f(p_str_fn){}
		
		
		/** 
		* @brief Calcula la primera derivada en xi
		* @param xi Valor en el que se evalua la primera derivada
		* @param paso Incremento de xi
		* @param diferencias Variable entre 1 y 2 dependiendo de las diferencias que se deseen usar para el calculo
		* @param direccion Variable entre -1 y 1 dependiendo de la direccion en la que se desee calcular la derivada
		* @return Derivada de la funcion evaluada en xi
		*/
		double primera(double xi, 
					   double paso,
					   int diferencias,
					   int direccion){
			
			if(diferencias<=0 || diferencias>2){
				return NAN;
			}
			//Direccion == -1 Atras
			//Direccion == 0 Centro
			//Direccion == 1 Adelante
			//Primera derivada
			//Una diferencia:
			if(diferencias==1){
				//-hacia adelante
				if(direccion == 1){ 
					double yi = f(xi);
					double yip1 = f(xi + paso);
					
					//Imprimir la tabla
					vector<double> x{xi,xi+paso};
					vector<double> y{yi,yip1};
					
					imprimir_tabla(x,y," X ", " Y ");
					
					return (yip1 - yi)/paso;
				}//-hacia atras
				else if(direccion == -1){ 
					double yi = f(xi);
					double yim1 = f(xi - paso);
					
					//Imprimir la tabla
					vector<double> x{xi-paso,xi};
					vector<double> y{yim1,yi};
					
					imprimir_tabla(x,y," X ", " Y ");
					
					return (yi - yim1)/paso;
				}//-central
				else if(direccion == 0){ 
					double yip1 = f(xi + paso);
					double yim1 = f(xi - paso);
					
					//Imprimir la tabla
					vector<double> x{xi-paso,xi+paso};
					vector<double> y{yim1,yip1};
					
					imprimir_tabla(x,y," X ", " Y ");
					
					return (yip1 - yim1)/(2.0f*paso);
				}
			} //Dos diferencias:
			else if(diferencias==2){
				//-hacia adelante
				if(direccion == 1){
					double yi = f(xi);
					double yip1 = f(xi + paso);
					double yip2 = f(xi + (2.0f*paso));
					
					//Imprimir la tabla
					vector<double> x{xi,xi+paso,xi+(2.0f*paso)};
					vector<double> y{yi,yip1,yip2};
					
					imprimir_tabla(x,y," X ", " Y ");
					
					return (4.0f*yip1 - 3.0f*yi - yip2)/(2.0f*paso);
				}//-hacia atras
				else if(direccion == -1){
					double yi = f(xi);
					double yim1 = f(xi - paso);
					double yim2 = f(xi - (2.0f*paso));
					
					//Imprimir la tabla
					vector<double> x{xi-(2.0f*paso),xi-paso,xi};
					vector<double> y{yim2,yim1,yi};
					
					imprimir_tabla(x,y," X ", " Y ");
					
					return (3.0f*yi - 4.0f*yim1 + yim2)/(2.0f*paso);
				}//-central
				else if(direccion == 0){
					double yim1 = f(xi - paso);
					double yim2 = f(xi - (2.0f*paso));
					double yip1 = f(xi + paso);
					double yip2 = f(xi + (2.0f*paso));
					
					//Imprimir la tabla
					vector<double> x{xi-(2.0f*paso),xi-paso,xi+paso,xi+(2.0f*paso)};
					vector<double> y{yim2,yim1,yip1,yip2};
					
					imprimir_tabla(x,y," X ", " Y ");
					
					return (8.0f*yip1 - yip2 - 8.0f*yim1 + yim2)/(12.0f*paso);
				}
			}
		}
	private:
		Expression f;
	};
};

#endif
