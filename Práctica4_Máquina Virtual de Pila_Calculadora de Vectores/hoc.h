/*
Nombre: Cruz Lopez Adrian
Practica 4
Opcion: Calculadora para vectores
Fecha: 05 noviembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

#include "vector_cal.h"
#include <string.h>
typedef struct Symbol {  /* Entrada de la tabla de s�mbolos */
	char* name;
	short type;            /* VAR, BLTIN, UNDEF */
	union {
		double comp;	       /* si es VAR */
		double  (*ptr)();    /* si es BLTIN */
		Vector* vec;
	} u;
	struct Symbol* next;   /* para ligarse a otro */ 
} Symbol;

Symbol* install(char* s, int t, Vector* vec);
Symbol* lookup(char* s);

typedef union Datum{     /*Tipo de la pila del interprete*/
  Vector* val;
  double num;
  Symbol* sym;
}Datum;

extern Datum pop();
typedef int (*Inst)();   /*Instruccion de maquina:*/

#define STOP (Inst) 0
extern Inst prog[];
extern void assign();
extern void varpush();
extern void constpush();
extern void print();
extern void printd();
extern void constpushd();
extern void eval();
extern void add();
extern void sub();
extern void producto_cruz();
extern void producto_punto(); 
extern void magnitud();
extern void escalar();
