/*
Cruz Lopez Adrian
Proyecto Final
Mini Logo
17 diciembre 2021
Grupo 3CM15
Compiladores
----------
Manejo de la maquina de pila y sus operaciones
*/
package Interprete;
import java.awt.Color;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Stack;
import Configuracion.Configuracion;
import Configuracion.Linea;

public class MaquinaDePila{
    private int contadorDePrograma;
    private ArrayList  memoria;
    private Stack pila;
    private TablaDeSimbolos tabla;
    private boolean stop = false;
    private boolean returning = false;
    private Stack<Marco> pilaDeMarcos;
    private Configuracion configuracionActual;
    
    public MaquinaDePila(TablaDeSimbolos tabla){
        configuracionActual = new Configuracion();
        contadorDePrograma = 0;
        memoria = new ArrayList<Method>();
        pila = new Stack();
        this.tabla = tabla;
        pilaDeMarcos = new Stack();
    }
    
    public int numeroDeElementos(){
        return memoria.size() + 1;
    }
    
    //Funciones que se ingresan a la máquina de pila
    public int agregarOperacion(String nombre){
        int posicion = memoria.size();
        try{
            memoria.add(this.getClass().getDeclaredMethod(nombre, null));
            return posicion;
        }
        catch(Exception e ){
            System.out.println("Error al agregar " + nombre + ". ");
        }
        return -1;
    }
    
    public int agregar(Object objeto){
        int posicion = memoria.size();
        memoria.add(objeto);
        return posicion;
    }
    
    public void agregar(Object objeto, int posicion){
        memoria.remove(posicion);
        memoria.add(posicion, objeto);
    }
    
    public int agregarOperacionEn(String nombre, int posicion){
        try{
            memoria.add(posicion, this.getClass().getDeclaredMethod(nombre, null));
        }
        catch(Exception e ){
            System.out.println("Error al agregar " + nombre + ". ");
        }
        return posicion;
    }
    
    //Funciones para el manejo en la pila con operaciones
    private void SUM(){
        Object matriz2 = pila.pop();
        Object matriz1 = pila.pop();
        pila.push((double)matriz1 + (double)matriz2);
    }
    private void RES(){
        Object matriz2 = pila.pop();
        Object matriz1 = pila.pop();
        pila.push((double)matriz1 - (double)matriz2);
    }
    private void MUL(){
        Object matriz2 = pila.pop();
        Object matriz1 = pila.pop();
        pila.push((double)matriz1 * (double)matriz2);
    }
    private void negativo(){
        Object matriz1 = pila.pop();
        System.out.println(matriz1);
        pila.push(-(double)matriz1);
    }
    private void constPush(){
        pila.push(memoria.get(++contadorDePrograma));
    }
    private void varPush(){
        pila.push(memoria.get(++contadorDePrograma));
    }
    private void varPush_Eval(){
        pila.push(tabla.encontrar((String)memoria.get(++contadorDePrograma)));
    }
    private void asignar(){
        String variable = (String)pila.pop();
        Object objeto = pila.pop();
        tabla.insertar(variable, objeto);
    }
    private void EQ(){
        Object A = pila.pop();
        Object B = pila.pop();
        pila.push((boolean)((double)A==(double)B));
    }
    private void NE(){
        Object A = pila.pop();
        Object B = pila.pop();
        pila.push((double)A!=(double)B);
    }
    private void LE(){
        double a,b;
        Object B = pila.pop();
        Object A = pila.pop();
        a = (double)A;
	b = (double)B;
        pila.push(a < b);
    }
    private void GR(){
        double a,b;
        Object B = pila.pop();
        Object A = pila.pop();
        a = (double)A;
        b = (double)B;
        pila.push(a > b);
    }
    private void LQ(){
        double a,b;
        Object B = pila.pop();
        Object A = pila.pop();
	a = (double)A;
	b = (double)B;
        pila.push(a <= b);
    }
    private void GE(){
        double a,b;
        Object B = pila.pop();
        Object A = pila.pop();
	a = (double)A;
	b = (double)B;
        pila.push(a >= b);
    }
    private void NOT(){
        pila.push(! (boolean)pila.pop());
    }
    private void AND(){
        pila.push((boolean)pila.pop() && (boolean)pila.pop());
    }
    private void OR(){
        pila.push((boolean)pila.pop() || (boolean)pila.pop());
    }
    private void stop(){
        stop = true;
    }
    private void _return(){
        returning = true;
    }
    private void nop(){ 
       
    }
    private void WHILE(){
        int condicion = contadorDePrograma;
        boolean continua = true;
        while(continua && !returning){
            ejecutar(condicion + 3);           
            if((boolean)pila.pop()){
                ejecutar((int)memoria.get(condicion+1));
            }
            else{
                contadorDePrograma = (int)memoria.get(condicion+2); 
                continua = false;
            }
        }     
    }
    private void IF_ELSE(){
        int condicion = contadorDePrograma;
        ejecutar(condicion + 4);
        boolean resultado = true;
        try{
            resultado = (boolean)pila.pop();
        }
        catch(Exception e ){
        }
        if(resultado){
            ejecutar((int)memoria.get(condicion+1));
        }
        else{
            ejecutar((int)memoria.get(condicion+2));
        }
        contadorDePrograma = (int)memoria.get(condicion+3) - 1;
    }
    private void FOR(){
        int condicion = contadorDePrograma;
        ejecutar(condicion + 5);
        boolean continua = true;
        while(continua && !returning){
            ejecutar((int)memoria.get(condicion+1));        
            if((boolean)pila.pop()){
                ejecutar((int)memoria.get(condicion+3));
                ejecutar((int)memoria.get(condicion+2));
            }
            else{
                contadorDePrograma = (int)memoria.get(condicion+4); 
                continua = false;
            }
        } 
    }
    private void declaracion(){
        tabla.insertar((String)memoria.get(++contadorDePrograma), ++contadorDePrograma);
        int invocados = 0;
        while(memoria.get(contadorDePrograma) != null || invocados != 0){
            if( memoria.get(contadorDePrograma) instanceof Method)
                if(((Method)memoria.get(contadorDePrograma)).getName().equals("invocar"))
                    invocados++;
            if( memoria.get(contadorDePrograma) instanceof Funcion)
                invocados++;
            if(memoria.get(contadorDePrograma) == null)
                invocados--;
            contadorDePrograma++;
        }
    }
    private void invocar(){   
        Marco marco = new Marco();
        String nombre = (String)memoria.get(++contadorDePrograma);
        marco.setNombre(nombre);
        contadorDePrograma++;
        while(memoria.get(contadorDePrograma) != null){
            if(memoria.get(contadorDePrograma) instanceof String){
                if(((String)(memoria.get(contadorDePrograma))).equals("Limite")){
                    Object parametro = pila.pop();
                    marco.agregarParametro(parametro);
                    contadorDePrograma++;
                }
            }
            else{ 
                ejecutarInstruccion(contadorDePrograma);
            }
        }
        marco.setRetorno(contadorDePrograma);
        pilaDeMarcos.add(marco);
        ejecutarFuncion((int)tabla.encontrar(nombre));
    }
    private void push_parametro(){
        pila.push(pilaDeMarcos.lastElement().getParametro((int)memoria.get(++contadorDePrograma)-1));
    }
    //METODOS PARA LA EJECUCION
    public void imprimirMemoria(){
        for(int i = 0; i < memoria.size(); i++)
            System.out.println("" + i + ": " +memoria.get(i));
    }
    public void ejecutar(){
        stop = false;
        while(contadorDePrograma < memoria.size())
            ejecutarInstruccion(contadorDePrograma);
    }
    public boolean ejecutarSiguiente(){
        if(contadorDePrograma < memoria.size()){
            ejecutarInstruccion(contadorDePrograma);
            return true;
        }
        return false;
    }
    public void ejecutar(int indice){    
        contadorDePrograma = indice;
        while(!stop && !returning){
            ejecutarInstruccion(contadorDePrograma);
        }
        stop = false;
    }
    public void ejecutarFuncion(int indice){
        contadorDePrograma = indice;
        while(!returning && memoria.get(contadorDePrograma) != null){
            ejecutarInstruccion(contadorDePrograma);
        }
        returning = false;
        contadorDePrograma = pilaDeMarcos.lastElement().getRetorno();
        pilaDeMarcos.removeElement(pilaDeMarcos.lastElement());
    }
    public void ejecutarInstruccion(int indice){
        try{         
            Object objetoLeido = memoria.get(indice);
            if(objetoLeido instanceof Method){
                Method metodo = (Method)objetoLeido;
                metodo.invoke(this, null);
            }
            if(objetoLeido instanceof Funcion){
                ArrayList parametros = new ArrayList();
                Funcion funcion = (Funcion)objetoLeido;
                contadorDePrograma++;
                while(memoria.get(contadorDePrograma) != null){
                    if(memoria.get(contadorDePrograma) instanceof String){
                        if(((String)(memoria.get(contadorDePrograma))).equals("Limite")){
                            Object parametro = pila.pop();
                            parametros.add(parametro);
                            contadorDePrograma++;
                        }
                    }
                    else{ 
                        ejecutarInstruccion(contadorDePrograma);
                    }
                }
                funcion.ejecutar(configuracionActual, parametros);
            }
            contadorDePrograma++;
        }catch(Exception e){}
    }
    public Configuracion getConfiguracion(){
        return configuracionActual;
    }
    public static class Girar implements Funcion{
        @Override
        public void ejecutar(Object A, ArrayList parametros) {
            Configuracion configuracion = (Configuracion)A;
            int angulo = (configuracion.getAngulo() + (int)(double)parametros.get(0))%360;
            configuracion.setAngulo(angulo);
        }
    }
    public static class Avanzar implements Funcion{
        @Override
        public void ejecutar(Object A, ArrayList parametros) {
            Configuracion configuracion = (Configuracion)A;
            int angulo = configuracion.getAngulo();
            double x0 = configuracion.getX();
            double y0 = configuracion.getY();
            double x1 = x0 + Math.cos(Math.toRadians(angulo))*(double)parametros.get(0);
            double y1 = y0 + Math.sin(Math.toRadians(angulo))*(double)parametros.get(0);
            configuracion.setPosicion(x1, y1);
            configuracion.agregarLinea(new Linea((int)x0,(int)y0,(int)x1,(int)y1, configuracion.getColor()));
        }
    }
    public static class CambiarColor implements Funcion{
        @Override
        public void ejecutar(Object A, ArrayList parametros) {
            Configuracion configuracion = (Configuracion)A;
            configuracion.setColor(new Color((int)(double)parametros.get(0)%256, (int)(double)parametros.get(1)%256, (int)(double)parametros.get(2)%256));
        }
    }
}