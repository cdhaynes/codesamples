package Q_3;

/**
 * LatLon.java - Defines LatLon object and states in which it can be used
 * @author Casey Haynes
 */
public class LatLon {
    private double x;
    private double y;

    public double getX() {
        return this.x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return this.y;
    }

    public void setY(double y) {
        this.y = y;
    }

     /* Assumption:
       Latitude and Longitude coordinates can be expressed in Degrees, Minutes, and Seconds, or
       as decimal degrees. So, the constructors for the LatLon class should be able to handle both
       cases.
     */

    /**
     * Default Constructor - sets x, y to (0, 0)
     */
    public LatLon() {
        setX(0.0);
        setY(0.0);
    }

    /**
     * Second Constructor - Takes X and Y and sets the coordinate pair
     * @param x
     * @param y
     */
    public LatLon(double x, double y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Third Constructor - takes in String, finds out what format the coordinates are listed in, and converts them to cartesian.
     * @param rawCoordinates coordinates listed in string format following one of three formats (Asterisk (*) indicates degrees):
     *                       10*30'27"N, 5*10'17"E
     *                       35.0844*N, 106.6504*W
     *                       35.0844*, -106.6504*
     */
    public LatLon(String rawCoordinates) {
        String coordinates[] = rawCoordinates.split(",");
        if (rawCoordinates.contains("'") || rawCoordinates.contains("\"")) {
            setX(convertDegMinSec(coordinates[0]));
            setY(convertDegMinSec(coordinates[1]));
        } else if (rawCoordinates.contains(".") && !rawCoordinates.contains("-")) {
            setX(convertDecDegrees(coordinates[0]));
            setY(convertDecDegrees(coordinates[1]));
        } else {
            setX(Double.parseDouble(coordinates[0]));
            setY(Double.parseDouble(coordinates[1]));
        }


    }

    /**
     * Converts Decimal Degree format to cartesian
     * @param coordinate Singular coordinate represented in Decimal Degrees in String Format
     * @return the coordinate in cartesian
     */
    public double convertDecDegrees(String coordinate) {
        double decimalDegrees = 0.0;
        String direction = null;
        decimalDegrees = Double.parseDouble(coordinate.split("\\*")[0]);

        if (coordinate.contains("N") && !coordinate.contains("S") && !coordinate.contains("W") && !coordinate.contains("E")) {
            direction = "N";
        } else if (!coordinate.contains("N") && coordinate.contains("S") && !coordinate.contains("W") && !coordinate.contains("E")) {
            direction = "S";
            decimalDegrees = -decimalDegrees;
        } else if (!coordinate.contains("N") && !coordinate.contains("S") && !coordinate.contains("W") && coordinate.contains("E")) {
            direction = "E";
        } else if (!coordinate.contains("N") && !coordinate.contains("S") && coordinate.contains("W") && !coordinate.contains("E")) {
            direction = "W";
            decimalDegrees = -decimalDegrees;
        } else {
            System.out.println("No correct direction listed");
        }

        return decimalDegrees;
    }

    /**
     * Converts Degrees, Minutes, Seconds format to cartesian
     * @param coordinate Single coordinate represented in DMS in String form
     * @return the coordinate in cartesian
     */
    public double convertDegMinSec(String coordinate) {
        /* I'm using "*" for the degrees symbol */
        double degrees = 0.0;
        double minutes = 0.0;
        double seconds = 0.0;
        String direction = null;

        String[] components = coordinate.split("\\*");
        degrees = Double.parseDouble(components[0]);

        if (coordinate.contains("'") && coordinate.contains("\"")) {
            components = components[1].split("'");
            minutes = Double.parseDouble(components[0]);
            components = components[1].split("\"");
            seconds = Double.parseDouble(components[0]);
            direction = components[1];
        } else {
            components = components[1].split("\"");
            seconds = Double.parseDouble(components[0]);
            direction = components[1];
        }

        double decimalDegrees = degrees + (minutes/60) + (seconds/3600);
        if (direction.equals("S") || direction.equals("W")) {
            decimalDegrees = -decimalDegrees;
        }

        return decimalDegrees;

    }
}
