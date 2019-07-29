package Q_4;

/**
 * GenericReading - Parent Class to other types of reading, contains common attributes
 * @author Casey Haynes
 */
public class GenericReading {

    private Time timeTaken;
    private LatLon center;
    private int width;
    private int height;

    public Time getTimeTaken() {
        return timeTaken;
    }

    public void setTimeTaken(Time timeTaken) {
        this.timeTaken = timeTaken;
    }

    public LatLon getCenter() {
        return center;
    }

    public void setCenter(LatLon center) {
        this.center = center;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }
}
