package Q_4;

/**
 * SatellitePicture - child class of general, contains SatellitePicture specific data
 * @author Casey Haynes
 */
public class SatellitePicture extends GenericReading {

    private PictureData pictureData;

    /**
     * Default Constructor
     */
    public SatellitePicture() {
        pictureData = new PictureData();
        setCenter(new LatLon(0, 0));
        setWidth(0);
        setHeight(0);
        setTimeTaken(new Time());

    }

    public PictureData getPictureData() {
        return pictureData;
    }

    public void setPictureData(PictureData pictureData) {
        this.pictureData = pictureData;
    }
}
