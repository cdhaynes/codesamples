package Q_4;

import java.util.List;

/**
 * Observation - Calculates Earth Coverage with multiple types of readings
 * @author Casey Haynes
 */
public class Observation {

    /* Example of Polymorphism applied to this case:
       Because the InfraredReading, SatellitePicture, and SpectrometerReading classes are all child classes of the Generic Reading class,
       the Java JIT Compiler only knows that each element in the readings list is a GenericReading, though the elements could be any one of the
       three types of objects listed above. As such, the elements in the readings list take on "many forms."
     */
    List<GenericReading> readings;

    private final int earthSurfaceArea = 510100000;

    public int getEarthSurfaceArea() {
        return earthSurfaceArea;
    }

    /**
     * CoverageAlgorithm - Calculates Earth Coverage
     * @return Earth Coverage as a decimal representation of a percentage
     */
    public int CoverageAlgorithm() {
        int imagedArea = 0;
        for (GenericReading image : readings) {
            imagedArea = imagedArea + (image.getHeight() * image.getWidth());
        }
        int coverage = imagedArea / getEarthSurfaceArea();
        return coverage;
    }
}
