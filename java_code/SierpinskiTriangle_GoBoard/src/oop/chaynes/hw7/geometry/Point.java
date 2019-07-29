package oop.chaynes.hw7.geometry;

/**
 * Defines the Point object and some methods that manipulate point objects.
 *
 *
 * @author Casey Haynes
 * @class Point.java
 * @version HW7, geometry
 * @bugs none
 */
public class Point implements Movable, Cloneable {
    private double x;
    private double y;
    private double radius;
    private double angle;

    public Point() {
        this.x = 0.0;
        this.y = 0.0;
        this.radius = Math.sqrt(Math.pow(x, 2.0) + Math.pow(x, 2.0));
        this.angle = Math.atan2(y, x);
    }

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
        this.radius = Math.sqrt(Math.pow(x, 2.0) + Math.pow(x, 2.0));
        this.angle = Math.atan2(y, x);
    }

    public Point(Point in) {
        this.x = in.x;
        this.y = in.y;
        this.radius = in.radius;
        this.angle = in.angle;
    }

    @Override
    public Point clone() throws CloneNotSupportedException {
        return this.clone();
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public double getAngle() {
        return angle;
    }

    public void setAngle(double angle) {
        this.angle = angle;
    }

    @Override
    public void setPosition(double x, double y) {
        setX(x);
        setY(y);
    }

    @Override
    public void setPolar(double rad, double theta) {
        setRadius(rad);
        setAngle(theta);
    }

    @Override
    public void move(double dx, double dy) {
        double x = getX() + dx;
        double y = getY() + dy;
        setX(x);
        setY(y);
    }

    @Override
    public void movePolar(double drad, double dtheta) {
        double rad = getRadius() + drad;
        double theta = getAngle() + dtheta;
        setRadius(rad);
        setAngle(theta);
    }

    public double distance(Point a) {
        double xDist = Math.abs(a.x - getX());
        double yDist = Math.abs(a.y - getY());
        double ans = Math.sqrt(xDist * xDist + yDist * yDist);

        return ans;
    }

    public double distanceFromOrigin() {
        double xDist = Math.abs(getX());
        double yDist = Math.abs(getY());
        double ans = Math.sqrt(xDist * xDist + yDist * yDist);

        return ans;
    }

    public int compareTo(Point a) {
        double xDist = a.x - getX();
        double yDist = a.y - getY();

        if (xDist > 0.0 && yDist > 0.0) {
            return -1;
        } else if (xDist == 0.0 && yDist == 0.0) {
            return 0;
        } else {
            return 1;
        }
    }

    public String toString() {
        String s = "(" + getX() + ", " + getY() + ")\n";
        return s;
    }
}

