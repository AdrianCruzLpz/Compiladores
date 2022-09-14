/*
Nombre: Cruz Lopez Adrian
Practica 5
Opcion: Calculadora para vectores con decisiones y ciclos
Fecha: 01 diciembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

#include "hoc.h"
#include "y.tab.h"
#include <math.h>
//extern double   Log(), Log10(), Sqrt(), Exp( ) , integer ( ) ;

static struct { char   *name;	/* Palabras clave */
int    kval;
} keywords[] = {
"if",		IF,
"else" ,	ELSE,
"while",	WHILE,
"print",	PRINT,
0,      0,
};

int init( )  /* instalar constantes y predefinidos en la tabla */
{
int i;
Symbol *s;

for (i = 0; keywords[i].name; i++)
	install(keywords[i].name, keywords[i].kval, NULL);
/*for (i = 0; consts[i].name; i++)
	install(consts[i].name, VAR, consts[i].cval);
for (i = 0; builtins[i].name; i++) {
	s = install(builtins[i].name, BLTIN, 0.0);
	s->u.ptr = builtins[i].func;
}*/
}

