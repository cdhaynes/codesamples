package oop.chaynes.hw7.three;

import javax.swing.*;
import oop.chaynes.hw7.geometry.Point;
import oop.chaynes.hw7.one.DrawShape;
import java.awt.*;
import java.util.Random;
/**
 * Sets Sierpinski Logic
 *
 *
 * @author Casey Haynes
 * @class Sierpinski.java
 * @version HW7, #3
 * @bugs none
 */
public class Sierpinski extends JPanel {
    public Sierpinski() {
        setPreferredSize(new Dimension(500, 500));
        setBackground(Color.BLACK);
    }

    public Color triangleColor(Point R, Point G, Point B, Point x) {
        int diffX;
        int diffY;
        int hypotenuseRG;
        int hypotenuseGB;
        int hypotenuseBR;
        /* dist R - G */
        diffX = (int) Math.round(Math.abs(G.getX() - R.getX()));
        diffY = (int) Math.round(Math.abs(G.getY() - R.getY()));
        hypotenuseRG = (int) Math.round(Math.sqrt(Math.pow(diffX, 2) + Math.pow(diffY, 2)));

        /* dist G - B */
        diffX = (int) Math.round(Math.abs(B.getX() - G.getX()));
        diffY = (int) Math.round(Math.abs(B.getY() - G.getY()));
        hypotenuseGB = (int) Math.round(Math.sqrt(Math.pow(diffX, 2) + Math.pow(diffY, 2)));

        /* dist B - R */
        diffX = (int) Math.round(Math.abs(R.getX() - B.getX()));
        diffY = (int) Math.round(Math.abs(R.getY() - B.getY()));
        hypotenuseBR = (int) Math.round(Math.sqrt(Math.pow(diffX, 2) + Math.pow(diffY, 2)));

        /* Which one is the longest? */
        int L;
        if ((hypotenuseRG > hypotenuseGB) && (hypotenuseRG > hypotenuseBR)) {
            L = hypotenuseRG;
        } else if ((hypotenuseGB > hypotenuseRG) && (hypotenuseGB > hypotenuseBR)) {
            L = hypotenuseGB;
        } else {
            L = hypotenuseBR;
        }

        int r_dist = (int) Math.floor(255 * ((L - (x.distance(R) / 2)) / L));
        int g_dist = (int) Math.floor(255 * ((L - (x.distance(G) / 2)) / L));
        int b_dist = (int) Math.floor(255 * ((L - (x.distance(B) / 2)) / L));


        Color res = new Color(r_dist, g_dist, b_dist);
        return res;
    }

    public void paintComponent(Graphics gfx) {
        Graphics2D gfx2 = (Graphics2D) gfx;
        Point R = new Point(250, 77);
        Point G = new Point(50, 423);
        Point B = new Point(450, 423);
        Point RGB[] = {R, G, B};

        Point x = new Point();
        x.setX(RGB[0].getX());
        x.setY(RGB[0].getY());
        for (int i = 0; i < 50001; i++) {
            Point target = RGB[new Random().nextInt(3)];
            midpoint(x, target, x);
            DrawShape.drawPoint(gfx2, x, triangleColor(R, G, B, x));
        }
    }

    public void midpoint(Point x, Point Color, Point intake) {
       // Point res = new Point(); /* not sure if initializing new point will work or if I need to take one in */
        int diffX = (int) (Color.getX() + x.getX());
        int diffY = (int) (Color.getY() + x.getY());
        intake.setX(diffX / 2);
        intake.setY(diffY / 2);
    }
}
