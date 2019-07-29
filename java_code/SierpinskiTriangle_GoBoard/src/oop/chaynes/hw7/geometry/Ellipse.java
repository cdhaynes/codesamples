package oop.chaynes.hw7.geometry;
/**
 * Extends Circle class to define Ellipse Object
 *
 *
 * @author Casey Haynes
 * @class Ellipse.java
 * @version HW7, geometry
 * @bugs none
 */
public class Ellipse extends Circle {
    private double minorRadius;

    public double getMinorRadius() {
        return this.minorRadius;
    }

    public void setMinorRadius(double minorRadius) {
        this.minorRadius = minorRadius;
    }

    public Ellipse() {
        super();
        this.minorRadius = super.getRadius();
    }

    public Ellipse(Point center, double radius, double minorRadius) {
        super(center, radius);
        this.minorRadius = minorRadius;
    }

    public double focalDistance() {
        double f = Math.sqrt(Math.abs(Math.pow(super.getRadius(), 2) - Math.pow(this.minorRadius, 2)));
        return f;
    }

    public double eccentricity() {
        double e = focalDistance()/Math.max(super.getRadius(), this.minorRadius);
        return e;
    }

    @Override
    public double area() {
        double a = Math.PI * super.getRadius() * this.minorRadius;
        return a;
    }

    @Override
    public double perimeter() {
        double p = Math.sqrt(2) * Math.PI * Math.sqrt(Math.pow(super.getRadius(), 2) + Math.pow(this.minorRadius, 2));
        return p;
    }

    @Override
    public boolean inBounds(Point a) {
        double h = super.getCenter().getX();
        double k = super.getCenter().getY();
        double x = a.getX();
        double y = a.getY();

        return ((Math.pow((x - h), 2) / Math.pow(super.getRadius(), 2)) + (Math.pow((y - k), 2) / Math.pow(this.minorRadius, 2)) <= 1);

    }
    @Override
    public Rectangle getBoundingBox() {
        double width = 2 * super.getRadius();
        double height = 2 * getMinorRadius();

        Rectangle ans = new Rectangle(width, height);

        return ans;
    }

}
