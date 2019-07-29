package Q_3;

/**
 * HistogramBin - Defines the HistogramBin object
 * @author Casey Haynes
 */
public class HistogramBin {
    private LatLon upperLeft;
    private LatLon lowerRight;
    private LatLon lowerLeft;
    private LatLon upperRight;
    public int count = 0;


    public void setUpperLeft(LatLon upperLeft) {
        this.upperLeft = upperLeft;
    }

    public LatLon getUpperLeft() {
        return upperLeft;
    }

    public void setLowerRight(LatLon lowerRight) {
        this.lowerRight = lowerRight;
    }

    public LatLon getLowerRight() {
        return lowerRight;
    }

    public void setLowerLeft(LatLon lowerLeft) {
        this.lowerLeft = lowerLeft;
    }

    public LatLon getLowerLeft() {
        return lowerLeft;
    }

    public void setUpperRight(LatLon upperRight) {
        this.upperRight = upperRight;
    }

    public LatLon getUpperRight() {
        return upperRight;
    }

    /**
     * Default Constructor - Make an empty bin
     */
    public HistogramBin() {
        this.upperLeft = new LatLon(0, 0);
        this.lowerRight = new LatLon(0, 0);
    }
}
