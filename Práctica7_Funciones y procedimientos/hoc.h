/*
Nombre: Cruz Lopez Adrian
Practica 7
Opcion: Calculadora para vectores con funciones y procedimientos
Fecha: 14 diciembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

//typedef void (*Inst)(void);
typedef int (*Inst)();

typedef struct Symbol { /* entrada de la tabla de simbolos */
	char   *name;
	short   type;   /* VAR, BLTIN, UNDEF */
	union {
		Vector * val;	       /* si es VAR */
		Vector*  (*ptr)();      /* si es BLTIN */
		int 	(*defn)();     /* FUNCION, PROCEDIMIENTO*/
		char 	*str;	      /* CADENA*/
	} u;
	struct Symbol   *next;  /* para ligarse a otro */ 
} Symbol;

typedef union Datum { /*tipo de la pila del interprete*/
	Vector *val;
	double numero;
	Symbol *sym;
}Datum;

extern Datum pop();
#define STOP  (Inst) 0

extern Inst *progp,prog[],*code(),*progbase;
extern void eval(), add(), sub(), punto(), mul(), cruz();
extern void assign(), bltin(), varpush(), constpush(), print();	
extern void prexpr();
extern void gt(), lt(), eq(), ge(), le(), ne(), and(), or(), not();
extern void ifcode(), whilecode();

extern  void funcret(),procret(),call(), arg(), argassign(),varread(),prstr();

Vector* creaVector(int n);
void imprimeVector(Vector* a);
Vector* copiaVector(Vector* a);
Vector* sumaVector(Vector* a, Vector* b);
Vector* restaVector(Vector* a, Vector* b);
Vector* vectorEscalar(Vector* a, double escalar);
Vector* multiplicaVector(Vector *a, Vector *b);
Vector* productoCruz(Vector* a, Vector* b);

//Para buscar e instalar en la tabla de simbolos
Symbol *lookup(char *s);
Symbol *install(char *s,int t, Vector *d);



