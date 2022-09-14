/*
Cruz Lopez Adrian
Proyecto Final
Mini Logo
17 diciembre 2021
Grupo 3CM15
Compiladores
----------
Interface que se implementará para ejecutar el
código de una instrucción
*/
package Interprete;
import java.util.ArrayList;
public interface Funcion{
    public abstract void ejecutar(Object A, ArrayList parametros);
    
}