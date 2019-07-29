package oop.chaynes.hw7.geometry;

/**
 * Defines the Rectangle object and some methods that manipulate Rectangle objects.
 *
 *
 * @author Casey Haynes
 * @class Rectangle.java
 * @version HW7, geometry
 * @bugs none
 */
public class Rectangle extends Shape{
    private Point lowerLeft;
    private Point upperRight;

    //constructors
    public Rectangle() {
        Point l = new Point(0.0,0.0);
        Point r = new Point(1.0, 1.0);
        this.lowerLeft = new Point(l);
        this.upperRight = new Point(r);

    }

    public Rectangle(double width, double height) {
        Point l = new Point(0.0,0.0);
        Point r = new Point(width, height);
        this.lowerLeft = new Point(l);
        this.upperRight = new Point(r);
    }

    public Rectangle(Point lowerLeft, Point upperRight) {
        double x1 = lowerLeft.getX();
        double y1 = lowerLeft.getY();
        double x2 = upperRight.getX();
        double y2 = upperRight.getY();

        if (x1 > x2) {
            double tmp = x1;
            x1 = x2;
            x2 = tmp;
        }

        if (y1 > y2) {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
        }

        Point l= new Point(x1, y1);
        Point r = new Point(x2, y2);
        this.lowerLeft = new Point(l);
        this.upperRight = new Point(r);
    }

    @Override
    public Rectangle clone() throws CloneNotSupportedException {
        Rectangle copy = (Rectangle) super.clone();
        copy.lowerLeft = getLowerLeft(); /* Check for deep copy */
        copy.upperRight = getUpperRight();
        return copy;
    }

    //begin getters and setters
    public Point getLowerLeft() {
        return new Point(lowerLeft);
    }

    public Point getUpperRight() {
        return new Point(upperRight);
    }

    public Point getLowerRight() {
        double x = upperRight.getX();
        double y = lowerLeft.getY();

        Point a = new Point(x, y);
        return new Point(a);
    }

    public Point getUpperLeft() {
        double x = lowerLeft.getX();
        double y = upperRight.getY();

        Point a = new Point(x, y);
        return new Point(a);
    }

    @Override
    public void setPosition(double x, double y) {
        this.lowerLeft.setX(x);
        this.lowerLeft.setY(y);
    }

    @Override
    public void setPolar(double rad, double theta) {
        this.lowerLeft.setRadius(rad);
        this.lowerLeft.setAngle(theta);
    }

    @Override
    public void move(double dx, double dy) {
        double x = this.lowerLeft.getX() + dx;
        double y = this.lowerLeft.getY() + dy;
        this.lowerLeft.setX(x);
        this.lowerLeft.setY(y);
        x = this.upperRight.getX() + dx;
        y = this.upperRight.getY() + dy;
        this.upperRight.setX(x);
        this.upperRight.setY(y);
    }

    @Override
    public void movePolar(double drad, double dtheta) {
        double rad = this.lowerLeft.getRadius() + drad;
        double theta = this.lowerLeft.getAngle() + dtheta;
        this.lowerLeft.setAngle(theta);
        this.lowerLeft.setRadius(rad);
        rad = this.upperRight.getRadius() + drad;
        theta = this.upperRight.getAngle() + dtheta;
        this.upperRight.setRadius(rad);
        this.upperRight.setAngle(theta);
    }

    //end getters and setters

    public double area() {
        double width = upperRight.getX() - lowerLeft.getX();
        double height = upperRight.getY() - lowerLeft.getY();
        double area = width * height;

        return area;
    }

    public double perimeter() {
        double width = upperRight.getX() - lowerLeft.getX();
        double height = upperRight.getY() - lowerLeft.getY();
        double perimeter = 2.0 * width + 2.0 * height;

        return perimeter;
    }

    public boolean inBounds(Point a) {
        double x = a.getX();
        double y = a.getY();
        double llx = lowerLeft.getX();
        double urx = upperRight.getX();
        double lly = lowerLeft.getY();
        double ury = upperRight.getY();

        return ((llx < x || urx > x || urx == x || llx == x) && (lly < y || ury > y || lly == y || ury == y)); //just says "is this on the line?"

    }



}

