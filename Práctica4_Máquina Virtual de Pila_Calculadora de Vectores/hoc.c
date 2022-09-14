/*
Nombre: Cruz Lopez Adrian
Practica 4
Opcion: Calculadora para vectores
Fecha: 05 noviembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

#include <string.h>
#include <stdlib.h>
#include "hoc.h" 
#include "y.tab.h"

static Symbol *symlist=0;    /*Lista ligada*/

Symbol *lookup(char *s){     /*Funcion para buscar a s*/
Symbol  *sp;
	for (sp = symlist; sp != (Symbol *)0; sp = sp->next) 
		if (strcmp(sp->name, s)== 0) 
			return sp;
	return 0;                /*En caso de no encontrarse*/ 
}

Symbol *install(char *s,int t, Vector *vec){ /*Mete un elemento a la tabla*/
	Symbol *sp;
	char *emalloc();
	sp = (Symbol *) emalloc(sizeof(Symbol));
	sp->name = emalloc(strlen(s)+ 1) ;
	strcpy(sp->name, s);
	sp->type = t;
	sp->u.vec = vec;
	sp->next = symlist;        /*Lo coloca al frente de la lista*/
	symlist = sp; 
    return sp; 
}

char  *emalloc(unsigned n){
	char *p;
	p = malloc(n); 
	return p; 
}

Symbol * installd(char * s, int t, double d){  /*Se instala 's'*/
    Symbol * sp;                                
    char * emalloc();
    sp = (Symbol *)emalloc(sizeof(Symbol));

    sp->name = emalloc( strlen(s) + 1); 
    strcpy( sp->name, s);
    sp->type = t;
    sp->u.comp = d;
    sp->next = symlist;        /*Se coloca al frente de la lista*/
    symlist = sp;

    return sp;
}
