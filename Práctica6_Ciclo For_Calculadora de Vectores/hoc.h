/*
Nombre: Cruz Lopez Adrian
Practica 6
Opcion: Calculadora para vectores con ciclo for
Fecha: 01 diciembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

#include "vector_cal.h"
#include <string.h>

typedef struct Symbol { /* entrada en la tabla de símbolos */
char* name;
short   type;   /* VAR, BLTIN, UNDEF */
union {
double comp;	/* si es VAR */
Vector*  (*ptr)();       /* si es BLTIN */
Vector* vec;
} u;
struct Symbol   *next;  /* para ligarse a otro */ } Symbol;

Symbol* install(char* s, int t, Vector* vec);
Symbol* lookup(char* s);


typedef union Datum {   /* tipo de la pila del intérprete */
Vector*  val;
double num;
Symbol  *sym;
int eval; } Datum; 

extern Datum pop();

typedef int (*Inst)();  /* instrucción de maquina */ 

#define STOP    (Inst) 0

extern Inst prog[];
extern Inst *progp;
extern Inst *code();

extern	void eval();
extern	void add();
extern	void sub();  
extern	void producto_cruz(); 
extern	void producto_punto();
extern	void magnitud();
extern	void escalar();
extern	void assign(); 
extern	void varpush(); 
extern	void constpush(); 
extern	void print();
extern	void printd();
extern	void constpushd();
extern	void bltin();

//Agragados de la practica 5
//Condiciones y Ciclos
extern void mayor();
extern void menor();
extern void mayorIgual();
extern void menorIgual();
extern void igual();
extern void diferente();
extern void and();
extern void or();
extern void not();
extern void whilecode();
extern void ifcode();
extern void prexpr();
extern void forcode(); //Practica 6
