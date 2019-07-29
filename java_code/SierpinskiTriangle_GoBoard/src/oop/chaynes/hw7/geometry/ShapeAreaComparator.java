package oop.chaynes.hw7.geometry;

import java.util.Comparator;

/**
 * Defines a comparator for the area of two shapes.
 *
 *
 * @author Casey Haynes
 * @class ShapeAreaComparator.java
 * @version HW7, geometry
 * @bugs none
 */
public class ShapeAreaComparator implements Comparator<Shape> {

    public int compare(Shape a, Shape b) {
        if (a.area() - b.area() < 0) {
            return -1;
        } else if (a.area() - b.area() == 0) {
            return 0;
        } else {
            return 1;
        }
    }

}