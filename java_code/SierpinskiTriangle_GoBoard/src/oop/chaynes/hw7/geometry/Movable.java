package oop.chaynes.hw7.geometry;
/**
 * Establishes the movable interface.
 *
 *
 * @author Casey Haynes
 * @class Movable.java
 * @version HW7, geometry
 * @bugs none
 */
public interface Movable {
    public void setPosition(double x, double y);
    public void setPolar(double rad, double theta);
    public void move(double dx, double dy);
    public void movePolar(double drad, double dtheta);
}
