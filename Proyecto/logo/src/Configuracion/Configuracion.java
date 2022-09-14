/*
Cruz Lopez Adrian
Proyecto Final
Mini Logo
17 diciembre 2021
Grupo 3CM15
Compiladores
----------
Configuracion del objeto Linea, con operaciones
relacionadas con este; posicion, ángulos y color
*/
package Configuracion;
import java.awt.Color;
import java.util.ArrayList;

public class Configuracion{
    ArrayList<Linea> lineas;
    double x,y;
    int angulo;
    Color color;
    
    public Configuracion(){
        x = 0.0;
        y = 0.0;
        lineas = new ArrayList<>(); 
        color = Color.WHITE;
    }
    
    public void setPosicion(double x, double y){
        this.x = x;
        this.y = y;
    }
    
    public void agregarLinea(Linea linea){ 
        lineas.add(linea);
    }
    public void limpiar(){ 
        lineas.clear();
    }
    public ArrayList<Linea> getLineas(){ 
        return lineas;
    }

    public double getX(){ 
        return x; 
    }
    public double getY(){ 
        return y;
    }
   
    public int getAngulo(){ 
        return angulo; 
    }
    public void setAngulo(int angulo){ 
        this.angulo = angulo; 
    } 

    public Color getColor(){ 
        return color; 
    }
    public void setColor(Color color){ 
        this.color = color; 
    }

    @Override
    public String toString(){
        String valor = "";
        for(int i = 0; i < lineas.size(); i++){
           valor += lineas.get(i)+", "; 
        }     
        valor += "x:"+x+" y:"+y+" angulo: "+angulo;
        return valor;
    }
}