/*
Nombre: Resendiz Alfaro Gerardo Ulises
Practica numero 4
Opcion: CALCULADORA PARA VECTORES
Fecha: 26 de mayo del 2021
Grupo: 3CM15
Materia: Compiladores
*/

//Seccion de Declaraciones
%{
    #include "hoc.h"
    #include <math.h>
    #include <stdio.h>
    #define MSDOS //Definido para practica 4
    #define code2(c1, c2) code(c1); code(c2); //Definido para practica 4
    #define code3(c1, c2, c3) code(c1); code(c2); code(c3); //Definido para practica 4
	
    void yyerror(char* s);
    int yylex();
    void warning(char* s, char* t); //A�adimos la funci�n warning
    //Funciones a�adidas para el funcionamiento de la practica 4
    void fpecatch();
    void execerror(char*s, char* t);
    extern void init();
%}  

//Tipo de datos en la pila de YACC
%union{
    double comp;
    Vector* vec;
    Symbol* sym; //A�adido para la practica 3
    Inst* inst; //A�adida para la practica 4
} 

//Modificamos esta parte para la practica 4
%token<comp> NUMBER    
%type<vec> exp        
%type<sym> vect       
%type<sym> number     
%token<sym> VAR 
%token<sym> INDEF      
%type<vec> asgn
%type<comp> escalar
%token<sym> VECT 
%token<sym> NUMB      

//Definimos la jerarquia de operaciones
%right '=' //Asocia por la derecha y a�adida para la practica 3
%left '+' '-' //Asocia por la izquierda
%left '*' //Asocia por la izquierda
%left UNARYMINUS //Para valores negativos
%left 'x' '.' //Asocia por la izquierda (MAYOR precedenmcia)

//Seccion de reglas gramaticales y sus respectivas acciones
//La gram�tica es la siguiente
%%
	list: /*NADA*/ 
		| list '\n'
		| list asgn '\n'		{code2(pop, STOP); return 1;}
		| list exp '\n'			{code2(print, STOP); return 1;}
		| list escalar '\n'		{code2(printd, STOP); return 1;}
		| list error '\n'		{yyerror;}
		; 
	exp: vect				{code2(constpush, (Inst)$1);}
		| VAR				{code3(varpush, (Inst)$1, eval);}
		| asgn  
		| exp '+' exp		{code(add);} //Caso SUMA
		| exp '-' exp		{code(sub);} //Caso RESTA
		| NUMBER '*' exp	{code(escalar);} //Caso MULT por ESCALAR 1
		| exp '*' NUMBER	{code(escalar);} //Caso MULT por ESCALAR 2
		| exp 'x' exp		{code(producto_cruz);} //Caso PROD CRUZ
		;
	escalar: number			{code2(constpushd, (Inst)$1);}
			| exp '.' exp 	{code(producto_punto);} //Caso PROD PUNTO
			| '|' exp '|' 	{code(magnitud);} //Caso MAGNITUD
			;
	vect: '[' NUMBER NUMBER NUMBER ']'		{Vector* v = creaVector(3);
												v -> vec[0] = $2;
												v -> vec[1] = $3;
												v -> vec[2] = $4;
												$$ = install("", VECT, v);}
			;
	asgn: VAR '=' exp		{code3(varpush, (Inst)$1, assign);}
		;
	number: NUMBER		{$$ = installd("", NUMB, $1);}
			;
%%

//Codigo de Soporte
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

char* progname;
int lineno = 1;
jmp_buf begin;

void main(int argc, char * argv[]) {
    progname = argv[0];
    setjmp(begin);
    signal(SIGFPE, fpecatch);
    for(initcode(); yyparse (); initcode())
		execute(prog);
}

int yylex(){
	int c;
	while((c = getchar()) == ' '|| c == '\t')
	; //Enunciado nulo, ignoramos los espacios en blanco
	if(c == EOF) //Si se llega al fin de archivo regresamos 0, indicando que ya no hay tokens
		return 0;
	if(isdigit(c)){ //Se encarga de los numeros
		ungetc(c, stdin); //Devuelve el caracter al buffer
		scanf("%lf", &yylval.comp); //Lexema
		return NUMBER;
	}
	if(isalpha(c)){ //checar no jacs
		Symbol* s;
		char sbuf[200];
		char* p = sbuf;
		do{
			*p++ = c;
		}while((c = getchar()) != EOF && isalnum(c));
		ungetc(c, stdin);
		*p = '\0';
		if((s = lookup(sbuf)) == (Symbol* )NULL) //Busqueda
			s = install(sbuf, INDEF, NULL); //Lo instala
		yylval.sym = s;
		if(s -> type == INDEF) 
			return VAR;
		else 
			return s -> type;
	}
	if(c == '\n')
		lineno++;
	return c; 
}

void yyerror(char* s){
	warning(s, (char* )0);
}

void warning(char* s, char* t){
	fprintf(stderr, "%s: %s", progname, s);
	if(t)
		fprintf(stderr, "%s", t);
	fprintf(stderr, "\tCerca de la linea %d\n", lineno);
}

void execerror(char * s, char * t){
    warning(s, t);
    longjmp(begin, 0);
}

void fpecatch(){
    execerror("Excepcion de punto flotante", (char *)0);
}
