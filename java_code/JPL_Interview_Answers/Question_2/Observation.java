package Q_2;

import java.util.List;

/**
 * Observation - Calculates Earth Coverage with SatellitePictures
 * @author Casey Haynes
 */
public class Observation {
    List<SatellitePicture> picturesTaken = null;

    private final int earthSurfaceArea = 510100000;

    public int getEarthSurfaceArea() {
        return earthSurfaceArea;
    }

    /**
     * CoverageAlgorithm - Calculate Earth Coverage
     * @return Earth Coverage as a decimal representation of a percentage
     */
    public int CoverageAlgorithm() {
        int imagedArea = 0;
        for (SatellitePicture image : picturesTaken) {
            imagedArea = imagedArea + (image.height * image.width);
        }
        int coverage = imagedArea / getEarthSurfaceArea();
        return coverage;
    }
}
