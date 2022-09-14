/*
Nombre: Cruz Lopez Adrian
Practica 2
Opcion: Uso de la carpeta grafibasi para dibujar círculos, lineas y rectángulos 
Fecha: 27 Octubre 2021
Grupo: 3CM15
Materia: Compiladores
*/

class Simbolo {
	String nombre;
	public short tipo;
	double val;
	public String metodo;
	int defn;
	Simbolo sig;

	Simbolo(String s, short t, double d)
	{
		nombre=s;
		tipo=t;
		val=d;
	}
        public Simbolo obtenSig()
        {
		return sig;
	}
        public void ponSig(Simbolo s)
	{
		sig=s;
	}
        public String obtenNombre()
	{
		return nombre;
	}
}
