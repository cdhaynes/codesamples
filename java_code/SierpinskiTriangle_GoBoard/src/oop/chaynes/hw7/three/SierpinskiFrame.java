package oop.chaynes.hw7.three;

import javax.swing.*;
import java.awt.*;
/**
 * Sets up Sierpinski Frame (drives the thing!)
 *
 *
 * @author Casey Haynes
 * @class SierpinskiFrame.java
 * @version HW7, #3
 * @bugs none
 */
public class SierpinskiFrame extends JFrame {
    public SierpinskiFrame() {
        setBackground(Color.BLACK);
        setSize(500, 500);
        Sierpinski t = new Sierpinski();
        this.add(t);
        pack();
        setTitle("Sierpinski Triangle --- 50,000 iterations");
        /*JLabel b = new JLabel("Sierpinski Triangle");
        b.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 24));
        this.add(b, BorderLayout.NORTH);
        pack();*/
    }

    public static void main (String[] args) {
        SierpinskiFrame tri = new SierpinskiFrame();
        tri.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        tri.setVisible(true);
    }
}
