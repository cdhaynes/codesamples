package oop.projects.art;

import java.awt.EventQueue;
import java.time.LocalDateTime;
import javax.swing.JFrame;

/**
 * This subclass of JFrame automatically adds a HelloComponent (a smiley face
 * drawing) to the contents of the window
 */
public class HelloFrame extends JFrame {
    public HelloFrame() {
        // Parent constructor sets the window title
        super("Java Art");
        // Exit on close
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        add(new HelloComponent());
        pack();
    }

    public static void main(String[] args) {
        // Create a GUI window
        HelloFrame window = new HelloFrame();
        // Show the window - slightly fancier than `window.setVisible(true)`
        EventQueue.invokeLater(() -> window.setVisible(true));
    }
}
