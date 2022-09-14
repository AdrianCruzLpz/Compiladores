/*
Nombre: Cruz Lopez Adrian
Practica 2
Opcion: Uso de la carpeta grafibasi para dibujar círculos, lineas y rectángulos 
Fecha: 27 Octubre 2021
Grupo: 3CM15
Materia: Compiladores
*/

import java.awt.*;


public class Rectangulo implements Dibujable {
	private int x1=0;
	private int y1=0;
	private int x2=0;
	private int y2=0;

	public Rectangulo(int x1, int y1, int x2, int y2)
	{
		this.x1=x1;
                this.y1=y1;
		this.x2=x2;
		this.y2=y2;
	}
	public void dibuja(Graphics g)
	{
		g.drawRect(x1,y1,x2,y2);
	}
}
