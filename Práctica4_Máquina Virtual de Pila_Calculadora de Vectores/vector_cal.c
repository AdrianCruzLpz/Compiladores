/*
Nombre: Cruz Lopez Adrian
Practica 4
Opcion: Calculadora para vectores
Fecha: 05 noviembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector_cal.h"

/*Se crea el vector de 3 dimensiones
  recibe como parametro un entero n y retorna el vector*/
Vector* creaVector(int n){
   Vector* vec;
   vec=(Vector* )malloc(sizeof(Vector));
   vec->n = n;
   vec->vec = (double* )malloc(sizeof(double)*n);
   return vec;
}

/*Imprime en pantalla el vector y su contenido
  recibe como parametro un vector y no retorna nada*/
void imprimeVector(Vector* v){
   int i;
   printf("[ ");
   for(i=0; i< v->n; i++)
      printf("%.2lf ", v->vec[i]);
   printf("]\n");
}

/*Copia el contenido del vector y sirve de apoyo
  recibe como parametro y retorna el vector*/
Vector* copiaVector(Vector* v){
   int i;
   Vector* copy=creaVector(v->n);
   for(i = 0; i< v->n; i++)
      copy->vec[i]=v->vec[i];
   return copy;
}

/*Funcion que suma los vectores que recibe y 
  retorna el vector resultante*/
Vector* sumaVector(Vector* a, Vector* b){
    Vector* c;
    int i;
    c = creaVector(a->n);
    for(i=0; i< a->n;i++)
        c->vec[i]=a->vec[i]+b->vec[i];
    return c;
}

/*Funcion que resta los vectores que recibe y 
  retorna el vector resultante*/
Vector* restaVector(Vector* a, Vector* b){
    Vector* c;
    int i;
    c=creaVector(a->n);
    for(i=0; i< a->n;i++)
       c->vec[i]=a->vec[i]-b->vec[i];
    return c;
}

/*Funcion que multiplica un escalar por un vector y
  retorna el vector resultante, recibe como parametro el vector y un double*/
Vector* escalarVector(double c, Vector* v){
    //printf("%lf", c);
    Vector* r_vector = creaVector(v -> n);
    int i;
    for(i = 0; i < v -> n; i++){
    	//Multiplica el escalar por cada valor del vector
        r_vector -> vec[i] = c * v->vec[i];   
    }
  return r_vector;
}

/*Funcion que realiza el producto cruz de los vectores recibidos y
  retorna el vector resultante*/
Vector* productoCruz(Vector* a, Vector* b){
	Vector* r;
	r = creaVector(a -> n);
	//Si tiene 2 elementos
	if(a-> n == 2){
		r -> vec[0] = a -> vec[0] * b ->vec[1];
        r -> vec[1] -= a -> vec[1] * b -> vec[0]; 
	} 
    //Si tiene 3 elementos
    else if(a -> n == 3){
        r -> vec[0] = a -> vec[1] * b -> vec[2] 
            - a -> vec[2] * b -> vec[1];
            
        r -> vec[1] = a -> vec[2] * b -> vec[0]
            - a -> vec[0] * b -> vec[2];
        
        r -> vec[2] = a -> vec[0] * b -> vec[1] 
            - a->vec[1] * b -> vec[0];
    }
    return r;
}

/*Funcion que realiza el producto punto entre dos vectores
  su resultado es un solo valor, por lo cual se le asigna el tipo double*/
double productoPunto(Vector* a, Vector* b){
    double resultado = 0.0f;
    int i; 
    for(i = 0; i < a->n; i++){
        resultado += ( a -> vec[i] * b->vec[i] );
    }
    return resultado;
}


/*Funcion que calcula la magnitud de un vector
  su resultado es un solo valor, por lo que se le asigana el tipo double*/
double vectorMagnitud(Vector* a){
    double resultado = 0.0f;
    int i;
    for(i = 0; i < a->n; i++){
        resultado += ( a -> vec[i] * a -> vec[i] );
    }
    return sqrt(resultado);
}
