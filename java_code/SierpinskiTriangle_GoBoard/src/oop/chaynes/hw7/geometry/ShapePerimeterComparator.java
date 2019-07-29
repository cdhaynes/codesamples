package oop.chaynes.hw7.geometry;

import java.util.Comparator;

/**
 * Defines a comparator for the perimeter of two shapes.
 *
 *
 * @author Casey Haynes
 * @class ShapePerimeterComparator.java
 * @version HW7, geometry
 * @bugs none
 */
public class ShapePerimeterComparator implements Comparator<Shape> {

    public int compare(Shape a, Shape b) {
        if (a.perimeter() - b.perimeter() < 0) {
            return -1;
        } else if (a.perimeter() - b.perimeter() == 0) {
            return 0;
        } else {
            return 1;
        }
    }

}
