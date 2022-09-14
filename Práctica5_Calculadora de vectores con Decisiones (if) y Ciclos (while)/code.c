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
#include<stdio.h>
#define NSTACK  256
static  Datum  stack[NSTACK];  /* la pila */
static  Datum   *stackp;       /* siguiente lugar libre en la pila */
#define NPROG   2000
Inst    prog[NPROG];    /* la máquina */
Inst    *progp;         /* siguiente lugar libre para la generación de código */
Inst    *pc;	/* contador de programa durante la ejecución */

void initcode()      /* inicialización para la generación de código */ {
   stackp = stack;
   progp = prog;
}

void push(d)	/*  meter d en la pila  */
	Datum d;
{
if (stackp >= &stack[NSTACK])
execerror("stack overflow", (char *) 0);
*stackp++ = d;
}

void pop1( ){     /* sacar y retornar de la pila el elemento del tope */
   if (stackp <= stack)
      execerror("stack underflow", (char *) 0);
   --stackp;
}

Datum pop( )     /* sacar y retornar de la pila el elemento del tope */
{
if (stackp <= stack)
execerror("stack underflow", (char *) 0);
return  *--stackp;
}


void constpush( )	/* meter una constante a la pila  */
{
Datum d;
d.val  =  ((Symbol  *)*pc++)->u.vec;
push(d);
}

void constpushd(){       
    Datum d;
    d.num = ((Symbol  *)*pc++)->u.comp;    
                                           
    push(d);
}

void varpush()	/* meter una variable a la pila   */
{
Datum d;
d.sym  =  (Symbol   *)(*pc++);
push(d);
}

/*Las siguientes funciones son agregadas
para la practica 5 y se encargan de
el caso de escribir las condiciones if y while*/
void whilecode() {
Datum d;
Inst  *savepc  = pc;	/*  cuerpo de la iteración  */
execute(savepc+2);     /*   condición   */ 
d  =  pop(); 
while   (d.val)   {
execute(*((Inst  **)(savepc)));     /*  cuerpo  */
execute(savepc+2);
d  = pop(); 
} 
pc  =  *((Inst  **)(savepc+1));     /*   siguiente proposición   */
}

void ifcode(){
   Datum d;
   Inst  *savepc  = pc;	/* parte then */
   execute(savepc+3);	/*  condición   */
   d  =  pop(); 
   if (d.val)
      execute(*((Inst   **)(savepc))); 
   else  if   (*((Inst  **)(savepc+1)))   /*  ¿parte else?   */
      execute(*(( Inst  **) (savepc+1)));
   pc  =  *((Inst  **)(savepc+2));	/*  siguiente proposición   */ 
}

void eval( )	/*  evaluar una variable en la pila   */
{
Datum  d;
d   =  pop();
if   (d.sym->type   ==   INDEF)
execerror("undefined variable",   
d.sym->name); 
d.val = d.sym->u.vec; push(d);
}

void add( )	/*   sumar los dos elementos superiores de la pila   */
{
Datum d1,   d2; 
d2  =  pop(); 
d1   =  pop(); 
d1.val  =  sumaVector(d1.val, d2.val); push(d1); 
}

void sub(){
Datum d1,  d2; 
d2  = pop(); 
d1  = pop(); 
d1.val  = restaVector(d1.val, d2.val); 
push(d1);
}

void escalar(){
Datum d1, d2;
d2 = pop(); 
d1 = pop(); 
d1.val = escalarVector(d1.num, d2.val); 
push(d1);
}

void producto_punto( ){
Datum d1, d2;
double d3;
d2 = pop();
d1 = pop(); 
d3 = productoPunto(d1.val, d2.val); 
push((Datum)d3);
}

void producto_cruz(){
Datum d1, d2; 
d2 = pop();
d1 = pop(); 
d1.val  =  productoCruz(d1.val, d2.val); 
push(d1);
}

void magnitud(){
Datum d1;
d1 = pop();
d1.num = vectorMagnitud(d1.val);
push(d1);
}

void assign( )        /* asignar el valor superior al siguientevalor */ 
{
Datum d1, d2;
d1 = pop();
d2 = pop();
if (d1.sym->type != VAR && d1.sym->type != INDEF) 
execerror("assignment to non-variable", d1.sym->name);
d1.sym->u.vec = d2.val;
d1.sym->type = VAR;
push(d2); 
} 

void print( ){  /* sacar el valor superior de la pila e imprimirlo */ 
 Datum d;
 d = pop();
 imprimeVector(d.val);
}

void printd(){       
    Datum d;
    d = pop();
    printf("%.2lf\n",d.num);
}

void bltin( )/*  evaluar un predefinido en el tope de la pila  */
{
Datum d;
d  =  pop();
d.val  =   (*(Vector * (*)() )(*pc++))(d.val);
push(d);
}

Inst *code(Inst f){ /*   instalar una instrucción u operando   */
   //puts("code1");
   Inst *oprogp = progp;
   if (progp >= &prog [ NPROG ])
     execerror("program too big", (char *) 0);
   *progp++ = f;
   return oprogp;
}

void execute(Inst *p){	/*   ejecución con la máquina   */
for  (pc  =  p;   *pc != STOP; ) 
	(*(*pc++))();
}

//Las siguientes funciones son de comparacion
void mayor(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.num = (int)( vectorMagnitud(d1.val) > vectorMagnitud(d2.val) );
    push(d1);
}

void menor(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.num = (int)( vectorMagnitud(d1.val) < vectorMagnitud(d2.val) );
    push(d1);
}

void mayorIgual(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.num = (int)( vectorMagnitud(d1.val) >= vectorMagnitud(d2.val) );
    push(d1);
}

void menorIgual(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.num = (int)( vectorMagnitud(d1.val) <= vectorMagnitud(d2.val) );
    push(d1);
}

void igual(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.num = (int)( vectorMagnitud(d1.val) == vectorMagnitud(d2.val) );
    push(d1);
}

void diferente(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.num = (int)( vectorMagnitud(d1.val) != vectorMagnitud(d2.val) );
    push(d1);
}

void and()
{
Datum d1,   d2;
d2   = pop();
d1   = pop();
d1.num = (int)( vectorMagnitud(d1.val) && vectorMagnitud(d2.val) );
push(d1);
}

void or()
{
Datum d1, d2;
d2 = pop();
d1 = pop();
d1.num = (int)( vectorMagnitud(d1.val) || vectorMagnitud(d2.val) );
push(d1);
}

void not( )
{
Datum d1;
d1 = pop();
d1.num = (int)( vectorMagnitud(d1.val) == (double)0.0);;
push(d1);
}

