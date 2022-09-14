/*
Nombre: Cruz Lopez Adrian
Practica 7
Opcion: Calculadora para vectores con funciones y procedimientos
Fecha: 14 diciembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

#include <math.h> 
#include <errno.h>
#include "vector_cal.h"

extern  int    errno;
double  errcheck();

Vector* magnitudVector(Vector *c)
{
	Vector *v;
	v = creaVector(1);
	double x = c->vec[0] * c->vec[0];
	double y = c->vec[1] * c->vec[1];
	double z = c->vec[2] * c->vec[2];
	v->vec[0] = sqrt(x + y + z);
	return v;
}

double errcheck(double d, char* s)   /* comprobar resultado de llamada a biblioteca */ 
{
if (errno == EDOM) { 
errno = 0;
execerror(s, "argument out of domain"); 
} else if (errno == ERANGE) 
{ errno = 0;
execerror(s, "result out of range"); 
} 
return d;
}


