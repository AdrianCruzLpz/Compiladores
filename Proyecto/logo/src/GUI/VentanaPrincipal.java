/*
Cruz Lopez Adrian
Proyecto Final
Mini Logo
17 diciembre 2021
Grupo 3CM15
Compiladores
----------
Despliegue de la aplicacion principal
*/
package GUI;
import java.awt.Color;
import java.awt.Font;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import Interprete.Parser;

public class VentanaPrincipal extends JFrame{
    JLabel lbltitulo = new JLabel();
    JTextArea areaCodigo;
    JScrollPane scrollCodigo;
    PanelDibujo panelDibujo;
    JButton ejecutar;
    JButton salir;
    Parser parser;
    boolean modoDebug;
    
    public VentanaPrincipal(){
        super("Mini LOGO Proyecto Final Compiladores -- Cruz López Adrián -- 3CM15");
        modoDebug = false;
        parser = new Parser();
        parser.insertarInstrucciones();
        
        areaCodigo = new JTextArea(20,10);
        areaCodigo.setFont(new Font("Console", Font.PLAIN, 20));
        areaCodigo.setText("");
        areaCodigo.setLineWrap(true);
        areaCodigo.setWrapStyleWord(true);
        areaCodigo.setTabSize(4);
        
        scrollCodigo = new JScrollPane (areaCodigo);
        scrollCodigo.setBounds(10,10,400,550);
        add(scrollCodigo);
        panelDibujo = new PanelDibujo();
        panelDibujo.setBounds(scrollCodigo.getX()+scrollCodigo.getWidth()+10,10,Propiedades.PANEL_DE_DIBUJO_ANCHO,Propiedades.PANEL_DE_DIBUJO_LARGO-5);
        panelDibujo.setBackground(new Color(Color.black.getRGB()));
        add(panelDibujo);
        
        ejecutar = new JButton("Ejecutar Instrucciones");
        ejecutar.setBounds(45,565,165,40);
        
        salir = new JButton("Salir");
        salir.setBounds(255,565,115,40);
        
        ejecutar.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent ae){
                if(areaCodigo.getText().isEmpty())
                    JOptionPane.showMessageDialog(null,"Por favor, ingrese una instruccion");
                parser.limpiar();
                if(parser.compilar(areaCodigo.getText()))
                    panelDibujo.setConfiguracion(parser.ejecutar());
                else{
                    parser = new Parser();
                    parser.insertarInstrucciones();
                    panelDibujo.setConfiguracion(parser.getConfiguracion());
                }
                panelDibujo.repaint();
            }
        });
        
        salir.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent ae2) {
                System.exit(0);
            }
        });
        
        add(ejecutar);
        add(salir);
        setLayout(null);
        setBounds(10,10,10+scrollCodigo.getWidth()+panelDibujo.getWidth()+30,649);
        setVisible(true);
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
    }
}