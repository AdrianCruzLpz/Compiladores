/*
Nombre: Cruz Lopez Adrian
Practica 2
Opcion: Uso de la carpeta grafibasi para dibujar círculos, lineas y rectángulos 
Fecha: 27 Octubre 2021
Grupo: 3CM15
Materia: Compiladores
*/

public class Tabla {
	Simbolo listaSimbolo;
	Tabla(){
		listaSimbolo=null;
	}

Simbolo install(String s, short t, double d){
		Simbolo simb=new Simbolo(s,t,d);
		simb.ponSig(listaSimbolo);
		listaSimbolo=simb;
		return simb;
	}

Simbolo lookup(String s){
	for(Simbolo sp=listaSimbolo; sp!=null; sp=sp.obtenSig())
		if((sp.obtenNombre()).equals(s))
			return sp;
	return null;
	}
}
