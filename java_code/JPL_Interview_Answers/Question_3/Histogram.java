package Q_3;

/**
 * Histogram - defines the Histogram Data Structure
 * @author Casey Haynes
 */
public class Histogram {
    /* Bins of the histogram are deliminated by lines of latitude and longitude every 15 degrees from the equator and from the prime meridian, respectively.
       So, there are 144 bins in the histogram.
       I wanted to be able to use math to determine which bin in the histogram each reading occupied, instead of assigning an arbitrary indexing system.
       So, the Histogram is made of an array of HistogramBin objects, each of which contain coordinate data corresponding to their relative cartesian location
       on the mercator projection. The Histogram method "inBounds" determines whether or not the center coordinate of a reading is within the bounds of each bin's
       coordinate data. If it is, the reading goes in the correct bin.
     */
    public HistogramBin[] grid = new HistogramBin[144];

    /**
     * Default Constructor - Set up an array of 144 Histogram Bins
     */
    public Histogram() {
        for (int i = 0; i < 144; i++) {
            this.grid[i] = new HistogramBin();
            this.grid[i].setLowerRight(new LatLon(0, 0));
            this.grid[i].setUpperRight(new LatLon(0, 0));
            this.grid[i].setUpperLeft(new LatLon(0, 0));
            this.grid[i].setLowerLeft(new LatLon(0, 0));
        }
        int gridIndex = 0;
        for (int j = 90; j >= -75; j -= 15) {
            for (int i = -90; i <= 75; i += 15) {
                LatLon upperLeft = new LatLon(i, j);
                LatLon lowerLeft = new LatLon (i, j - 15);
                LatLon lowerRight = new LatLon(i + 15, j - 15);
                LatLon upperRight = new LatLon(i + 15, j);
                grid[gridIndex].setUpperLeft(upperLeft);
                grid[gridIndex].setLowerLeft(lowerLeft);
                grid[gridIndex].setUpperRight(upperRight);
                grid[gridIndex].setLowerRight(lowerRight);
                gridIndex++;

            }
        }
    }

    /**
     * inBounds - Check to see if the center of a reading is within the coordinate definition of a bin
     * @param coordinate center coordinate
     * @param cell Histogram Bin
     * @return T or F regarding inBounds status
     */
    public boolean inBounds(LatLon coordinate, HistogramBin cell) {
        double x = coordinate.getX();
        double y = coordinate.getY();
        double llx = cell.getLowerLeft().getX();
        double urx = cell.getUpperRight().getX();
        double lly = cell.getLowerLeft().getY();
        double ury = cell.getUpperRight().getY();

        return ((llx < x || urx > x || urx == x || llx == x) && (lly < y || ury > y || lly == y || ury == y)); //just says "is this on the line?"

    }

    /**
     * Algorithm - Takes an observation and creates a histogram of the times a latititude and longitude observation has been seen.
     * @param observation
     * @return the resultant Histogram
     */
    public Histogram Algorithm(Observation observation) {
        Histogram result = new Histogram();
        for (SatellitePicture image : observation.picturesTaken) {
            LatLon center = new LatLon();
            center.setX(image.center.getX());
            center.setY(image.center.getY());
            for (HistogramBin c : result.grid) {
                if (inBounds(center, c)) {
                    c.count++;
                }
            }
        }

        return result;
    }
}
