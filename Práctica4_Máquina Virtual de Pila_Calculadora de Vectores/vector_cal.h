/*
Nombre: Cruz Lopez Adrian
Practica 4
Opcion: Calculadora para vectores
Fecha: 05 noviembre 2021
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
Vector* copiaVector(Vector* a);
Vector* sumaVector(Vector* a, Vector* b);
Vector* restaVector(Vector* a, Vector* b);
Vector* escalarVector(double c, Vector* v);
Vector* productoCruz(Vector* a, Vector* b);
double productoPunto(Vector* a, Vector* b);
double vectorMagnitud(Vector* a);
