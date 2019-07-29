package oop.chaynes.hw7.two;
import javax.swing.*;
import java.awt.*;
import java.util.TimeZone;
/**
 * Sets up ClockFrame
 *
 *
 * @author Casey Haynes
 * @class ClockFrame.java
 * @version HW7, #2
 * @bugs none
 */

public class ClockFrame extends JFrame {
    private static final int WIDTH = 400;
    private static final int HEIGHT = 465;

    public ClockFrame() {
        setSize(WIDTH, HEIGHT);
        ClockFace a = new ClockFace();
        this.add(a);
        pack();
        JLabel b = new JLabel(TimeZone.getDefault().getDisplayName(), SwingConstants.CENTER);
        b.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 24));
        this.add(b, BorderLayout.NORTH);
        pack();
    }

    public static void main(String[] args) {

        ClockFrame cf = new ClockFrame();
        cf.setSize(WIDTH, HEIGHT); /* Setting size in ClockFrame does not work for me */
        cf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        cf.setVisible(true);


    }
}