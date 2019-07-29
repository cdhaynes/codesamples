package oop.chaynes.hw7.geometry;
/**
 * Extends Rectangle class to define Parallelogram Object
 *
 *
 * @author Casey Haynes
 * @class Parallelogram.java
 * @version HW7, geometry
 * @bugs class inBounds not implemented
 */
public class Parallelogram extends Rectangle{
    private double skewAngle;

    public double getSkewAngle() {
        return this.skewAngle;
    }

    public Parallelogram() {
        super();
        this.skewAngle = Math.PI/2.0;
    }

    public Parallelogram(Point lowerLeft, Point upperRight, double skewAngle) {
        super(lowerLeft, upperRight);
        if (skewAngle < Math.atan2(upperRight.getY(), (upperRight.getX() - lowerLeft.getX()))) {
            skewAngle = Math.PI/2.0;
        } else if (skewAngle >= Math.PI) {
            skewAngle = Math.PI/2.0;
        }
        this.skewAngle = skewAngle;
    }
    @Override
    public Point getUpperLeft() {
        double x = super.getLowerLeft().getX();
        double y = super.getUpperRight().getY();

        x = x - Math.abs(super.getUpperLeft().getX()/Math.tan(skewAngle));

        Point a = new Point(x, y);
        return new Point(a);
    }
    @Override
    public Point getLowerRight() {
        double x = super.getUpperRight().getX();
        double y = super.getLowerLeft().getY();

        x = x - Math.abs(super.getLowerRight().getX()/Math.tan(skewAngle));

        Point a = new Point(x, y);
        return new Point(a);
    }
    @Override
    public double area() {
        double width = super.getLowerRight().getX() - super.getLowerLeft().getX();
        double height = super.getUpperLeft().getY() - super.getLowerLeft().getY();

        double area = width * height;

        return area;
    }
    @Override
    public double perimeter() {
        double width = super.getUpperRight().getX() - super.getLowerLeft().getX();
        double height = super.getUpperRight().getY() - super.getLowerLeft().getY();
        double skewLength = height / Math.sin(skewAngle);

        double perimeter = (2.0 * width) + (2.0 * skewLength);

        return perimeter;
    }
}
