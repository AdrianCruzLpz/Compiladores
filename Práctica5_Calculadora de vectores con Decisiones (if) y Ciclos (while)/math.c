/*
Nombre: Cruz Lopez Adrian
Practica 5
Opcion: Calculadora para vectores con decisiones y ciclos
Fecha: 01 diciembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

#include <math.h> 
#include <errno.h>

extern  int errno;
double  errcheck();

double Log(x)
double x;
{
return errcheck(log(x) , "log");
}


double Log10(x)
double x;
{
return  errcheck(log10(x), "log10");
}

double Sqrt(x)
double x; 
{
return errcheck(sqrt(x), "sqrt"); 
}

double Exp(x)
double x; 
{
return errcheck( exp(x) , "exp" ) ;
}

double Pow(x, y)
double x, y;
{
return errcheck(pow(x,y), "exponentiation");
}

double integer(double x)
{
return (double)(long)x;
}
double errcheck(double d, char *s)   /* comprobar resultado de llamada a biblioteca */ 
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


