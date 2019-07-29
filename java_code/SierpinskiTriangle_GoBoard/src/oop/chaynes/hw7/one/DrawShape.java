package oop.chaynes.hw7.one;
import oop.chaynes.hw7.geometry.*;
import oop.chaynes.hw7.geometry.Point;
import oop.chaynes.hw7.geometry.Rectangle;
import java.awt.*;
/**
 * Draws Shapes
 *
 *
 * @author Casey Haynes
 * @class DrawShape.java
 * @version HW7, #1
 * @bugs none
 */
public class DrawShape {
    public static void drawPoint(Graphics2D gfx, Point pt, Color hue) {
        Color orig = gfx.getColor();
        gfx.setColor(hue);
        gfx.drawOval((int) Math.round(pt.getX()), (int) Math.round(pt.getY()), 1, 1);
        gfx.setColor(orig);

    }

    public static void drawRectangle(Graphics2D gfx, Rectangle rect, Color hue) {
        Color orig = gfx.getColor();
        gfx.setColor(hue);
        gfx.drawRect((int) (rect.getLowerLeft().getX()), (int) (rect.getLowerLeft().getY()), (int) (rect.getUpperRight().getX() - rect.getLowerLeft().getX()), (int) (rect.getUpperRight().getY() - rect.getLowerLeft().getY()));
        gfx.setColor(orig);
    }

    public static void drawCircle(Graphics2D gfx, Circle circ, Color hue) {
        Color orig = gfx.getColor();
        gfx.setColor(hue);
        gfx.fillOval((int) (circ.getBoundingBox().getLowerLeft().getX()), (int) (circ.getBoundingBox().getLowerLeft().getY()),
                (int) ((2 * circ.getRadius())), (int) ((2 * circ.getRadius())));
        gfx.setColor(orig);
    }
}
