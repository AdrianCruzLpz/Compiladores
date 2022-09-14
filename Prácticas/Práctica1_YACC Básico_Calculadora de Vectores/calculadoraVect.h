/*
Nombre: Cruz Lopez Adrian
Practica 1
Opcion: CALCULADORA PARA VECTORES
Grupo: 3CM15
*/
struct vector {
	char name;
	int n;
	double *vec;
};

typedef struct vector Vector;
Vector *crearVector(int n);
void imprimeVector(Vector *a);
Vector *copiaVector(Vector *a);
Vector *suma(Vector *a, Vector *b);
Vector *resta(Vector *a, Vector *b);
Vector *escalarporVector(double c, Vector *v);
Vector *productoCruz(Vector *a, Vector *b);
double productoPunto(Vector *a, Vector *b);
double magnitud(Vector *a);

