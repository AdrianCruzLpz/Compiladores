/*
Nombre: Cruz Lopez Adrian
Practica 2
Opcion: Uso de la carpeta grafibasi para dibujar círculos, lineas y rectángulos 
Fecha: 27 Octubre 2021
Grupo: 3CM15
Materia: Compiladores
*/

import java.awt.*;

public class Circulo implements Dibujable {
	private int x=0;
	private int y=0;
	private int r=0;

	public Circulo(int x, int y, int r)
	{
		this.x=x;
		this.y=y;
		this.r=r;
	}

	public void dibuja(Graphics g){
		g.drawOval(x,y,r,r);
	}
}


