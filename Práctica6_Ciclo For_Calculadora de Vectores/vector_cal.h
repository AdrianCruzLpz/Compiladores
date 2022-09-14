/*
Nombre: Cruz Lopez Adrian
Practica 6
Opcion: Calculadora para vectores con ciclo for
Fecha: 01 diciembre 2021
Grupo: 3CM15
Materia: Compiladores
*/

struct vector {
	char name;
	int n;
	double* vec;
};
typedef struct vector Vector;
Vector* creaVector(int n);
void imprimeVector(Vector* a);
void copiaVector(Vector* a, Vector* copy);
Vector* sumaVector(Vector* a, Vector* b);
Vector* restaVector(Vector* a, Vector* b);
Vector* escalarVector(double c, Vector* v);
Vector* productoCruz(Vector* a, Vector* b);
double productoPunto(Vector* a, Vector* b);
double vectorMagnitud(Vector* a);
