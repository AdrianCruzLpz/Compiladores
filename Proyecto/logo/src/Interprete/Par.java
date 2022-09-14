/*
Cruz Lopez Adrian
Proyecto Final
Mini Logo
17 diciembre 2021
Grupo 3CM15
Compiladores
----------
Manejo del par de valores para nombre y objeto
*/
package Interprete;
public class Par{
    private String nombre;
    private Object objeto;

    public Par(String nombre, Object objeto){
        this.nombre = nombre;
        this.objeto = objeto;
    }
    public String getNombre(){ 
        return nombre; 
    }
    public void setNombre(String nombre){ 
        this.nombre = nombre; 
    }
    public Object getObjeto(){ 
        return objeto; 
    }
    public void setObjeto(Object objeto){ 
        this.objeto = objeto;
    }      
}