#ifndef DERIVACION_H
#define DERIVACION_H

#include <string>
#include "Expression.h"

using std::string;

namespace derivacion{
	class derivada{
	public:
		derivada(string p_str_fn):f(p_str_fn){}
		
		
		/** 
		* @brief Calcula la primera derivada en xi
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
					return (yip1 - yi)/paso;
				}//-hacia atras
				else if(direccion == -1){ 
					double yi = f(xi);
					double yim1 = f(xi - paso);
					return (yi - yim1)/paso;
				}//-central
				else if(direccion == 0){ 
					double yip1 = f(xi + paso);
					double yim1 = f(xi - paso);
					return (yip1 - yim1)/(2.0f*paso);
				}
			} //Dos diferencias:
			else if(diferencias==2){
				//-hacia adelante
				if(direccion == 1){
					double yi = f(xi);
					double yip1 = f(xi + paso);
					double yip2 = f(xi + (2.0f*paso));
					return (4.0f*yip1 - 3.0f*yi - yip2)/(2.0f*paso);
				}//-hacia atras
				else if(direccion == -1){
					double yi = f(xi);
					double yim1 = f(xi - paso);
					double yim2 = f(xi - (2.0f*paso));
					return (3.0f*yi - 4.0f*yim1 + yim2)/(2.0f*paso);
				}//-central
				else if(direccion == 0){
					double yim1 = f(xi - paso);
					double yim2 = f(xi - (2.0f*paso));
					double yip1 = f(xi + paso);
					double yip2 = f(xi + (2.0f*paso));
					return (8.0f*yip1 - yip2 - 8.0f*yim1 + yim2)/(12.0f*paso);
				}
			}
			
			
		}
	private:
		Expression f;
	};
};

#endif
