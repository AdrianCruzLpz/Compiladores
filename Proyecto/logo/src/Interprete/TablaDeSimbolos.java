/*
Cruz Lopez Adrian
Proyecto Final
Mini Logo
17 diciembre 2021
Grupo 3CM15
Compiladores
----------
Manejo de la Tabla de símbolos
*/
package Interprete;
import java.util.ArrayList;

public class TablaDeSimbolos{
    ArrayList<Par> simbolos;
 
    public TablaDeSimbolos(){
        simbolos = new ArrayList<>();
    }
    
    public Object encontrar(String nombre){
        for(int i = 0; i < simbolos.size(); i++)
            if(nombre.equals(simbolos.get(i).getNombre()))
                return simbolos.get(i).getObjeto();
        return null;
    }
    
    public boolean insertar(String nombre, Object objeto){
        Par par = new Par(nombre, objeto);
        for(int i = 0; i < simbolos.size(); i++)
            if(nombre.equals(simbolos.get(i).getNombre())){
                simbolos.get(i).setObjeto(objeto);
                return true;
            }
        simbolos.add(par);
        return false;
    }
    
    public void imprimir(){
        for(int i = 0; i < simbolos.size(); i++){
            System.out.println(simbolos.get(i).getNombre() + simbolos.get(i).getObjeto().toString());
        }
    }

}