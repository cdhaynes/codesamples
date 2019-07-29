package oop.chaynes.hw7.geometry;

/**
 * Defines the Circle object and some methods that manipulate Circle objects.
 *
 *
 * @author Casey Haynes
 * @class Circle.java
 * @version HW7, geometry
 * @bugs none
 */
public class Circle extends Shape{
    private Point center;
    private double radius;

    //constructors
    public Circle() {
        Point c = new Point(0.0, 0.0);
        this.center = new Point(c);
        this.radius = 1.0;
    }

    public Circle(Point a, double radius) {
        double x = a.getX();
        double y = a.getY();
        this.center = new Point(x, y);
        this.radius = Math.abs(radius);
    }

    @Override
    public Circle clone() throws CloneNotSupportedException {
        Circle copy = (Circle) super.clone();
        copy.center = (Point) copy.center.clone(); /* Check for deep copy */

        return copy;
    }
    //getters and setters
    public Point getCenter() {
        Point a = new Point(center);
        return a;
    }

    public void setCenter(Point x) {
        this.center = new Point(x);
    }

    public double getRadius() {
        return Math.abs(radius);
    }

    public void setRadius(double radius) {
        this.radius = Math.abs(radius);
    }

    @Override
    public void setPosition(double x, double y) {
        this.center.setX(x);
        this.center.setY(y);
    }

    @Override
    public void setPolar(double rad, double theta) {
        this.center.setRadius(rad);
        this.center.setAngle(theta);
    }

    @Override
    public void move(double dx, double dy) {
        double x = this.center.getX() + dx;
        double y = this.center.getY() + dy;
        this.center.setX(x);
        this.center.setY(y);
    }

    @Override
    public void movePolar(double drad, double dtheta) {
        double rad = this.center.getRadius() + drad;
        double theta = this.center.getAngle() + dtheta;
        this.center.setRadius(rad);
        this.center.setAngle(theta);
    }

    //end
    public double area() {
        double area = Math.PI * (getRadius() * getRadius());

        return area;
    }

    public double perimeter() {
        double circumference = 2 * Math.PI * getRadius();

        return circumference;
    }

    public boolean inBounds(Point a) {
        double x = a.getX();
        double y = a.getY();
        double cenX = getCenter().getX();
        double cenY = getCenter().getY();
        double rad = getRadius();
        //Pythagorean Theorem
        return (Math.pow(x - cenX, 2) + Math.pow(y - cenY, 2) <= Math.pow(rad, 2));

    }

    public Rectangle getBoundingBox() {
        Point cen = getCenter();
        double cx = cen.getX();
        double cy = cen.getY();
        double rad = getRadius();
        Point lowerLeft = new Point (cx - rad, cy - rad);
        Point upperRight = new Point (cx + rad, cy + rad);

        Rectangle ans = new Rectangle(lowerLeft, upperRight);

        return ans;
    }

}
