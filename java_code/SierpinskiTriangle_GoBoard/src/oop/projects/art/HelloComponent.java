package oop.projects.art;

import java.awt.*;
import javax.swing.JComponent;

/**
 * JComponent is a generic container for window contents in Java. Creating a
 * custom subclass of JComponent is the canonical way to control the features
 * that are added to the JFrame window -- in this case, a 2D drawing!
 */
public class HelloComponent extends JComponent {
    public HelloComponent() {
        super();
        setPreferredSize(new Dimension(500, 500));
    }

    /**
     * Overrides JComponent.paintComponent() to draw a smiley face instead of an
     * empty container
     *
     * @param g The Graphics object to paint features onto
     */
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        // Graphics is an abstract class. The Graphics argument passed to
        // paintComponent() is actually a Graphics2D object
        Graphics2D canvas = (Graphics2D) g;

        // These are some features of the Graphics2D API that aren't available
        // in the Graphics class
        canvas.setStroke(new BasicStroke(2));
        canvas.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        // Draw a face...
        canvas.setColor(new Color(255, 192, 0));
        canvas.fillOval(150, 150, 200, 200);
        canvas.setColor(Color.BLACK);
        canvas.drawOval(150, 150, 200, 200);

        // with eyes...
        canvas.fillOval(200, 210, 20, 20);
        canvas.fillOval(280, 210, 20, 20);

        // and a mouth...
        canvas.drawArc(190, 240, 120, 80, 190, 160);

        // Add a greeting
        canvas.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 24));
        canvas.drawString("Hello World!", 180, 400);
    }
}
