package oop.chaynes.hw7.geometry;
/**
 * Abstract class for shapes
 *
 *
 * @author Casey Haynes
 * @class Shape.java
 * @version HW7, geometry
 * @bugs class inBounds not implemented in the subclass
 */
abstract class Shape implements Movable, Cloneable {
    public abstract double area();
    public abstract double perimeter();
    public abstract boolean inBounds(Point pt);
}
