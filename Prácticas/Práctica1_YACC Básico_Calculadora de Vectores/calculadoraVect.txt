/*
Nombre: Cruz Lopez Adrian
Practica 1
Opcion: CALCULADORA PARA VECTORES
Grupo: 3CM15
*/

//Seccion de declaraciones
%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
    #include <ctype.h>
    #include "calculadoraVect.c"

    int yyerror(char *s);
    int yylex();
%}

%union{
    double val;
    Vector *vector;
}

//NUMBER ES EL UNICO TERMINAL
%token<val> NUMBER
%type<vector> exp
%type<vector> vector    
%type<val> num
     
//Definimos la jerarquia de operaciones
%left '+' '-' //Asocia por la izquierda
%left '*' //Asocia por la izquierda
%left 'x' '.' //Asocia por la izquierda (Mayor precedencia)

//Seccion de reglas gramaticales y sus respectivas acciones
//La gramática es la siguiente
%%
    inicio: /* NADA */
      		| inicio list;
     	    ;
    list: '\n'
     	 | exp '\n'  {imprimeVector($1);}
     	 | num '\n'  {printf("%lf\n", $1);}
     	 ;
    exp: vector
      	| exp '+' exp     {$$ = suma($1, $3);} //Caso SUMA
     	| exp '-' exp     {$$ = resta($1, $3);} //Caso RESTA
      	| exp '*' NUMBER  {$$ = escalarporVector($3, $1);} //Caso MULT por ESCALAR 1
      	| NUMBER '*' exp  {$$ = escalarporVector($1, $3);} //Caso MULT por ESCALAR 2
      	| exp 'x' exp     {$$ = productoCruz($1, $3);} //Caso PROD CRUZ
    	;
    num: NUMBER
      	 | vector '.' vector {$$ = productoPunto($1, $3);} //Caso PROD PUNTO
         | '|' vector '|' {$$ = magnitud($2);} //Caso MAGNITUD
            ;
    vector: '[' NUMBER NUMBER NUMBER ']' {Vector *v = crearVector(3);
                                            v -> vec[0] = $2;
                                            v -> vec[1] = $3;
                                            v -> vec[2] = $4;
                                            $$ = v;}
      		;
%%

//Codigo de soporte
void main(){
  	yyparse();
}

int yylex (){
  	int c;
  	while ((c = getchar ()) == ' ' || c == '\t')
  		;//Enunciado nulo, ignoramos los espacios en blanco
 	if (c == EOF) //Si se llega al fin de archivo regresamos 0, indicando que ya no hay tokens
    		return 0;
  	if(isdigit(c)){ //Se encarga de los numeros
    	ungetc(c, stdin); //Devuelve el caracter al buffer
      	scanf("%lf", &yylval.val);//lexema
      	return NUMBER;
  	}
  	return c;
}

int yyerror(char *s){
  	printf("%s\n", s);
  	return 0;
}
