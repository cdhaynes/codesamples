package Q_4;

/**
 * SpectrometerReading - child class of general, contains SpectrometerReading specific data
 */
public class SpectrometerReading extends GenericReading {

    private SpectrometerData spectrometerData;

    /**
     * Default Constructor
     */
    public SpectrometerReading() {
        spectrometerData = new SpectrometerData(); /* Hypothetical SpectrometerData Class has default constructor */
        setCenter(new LatLon());
        setWidth(0);
        setHeight(0);
        setTimeTaken(new Time());
    }

    public SpectrometerData getSpectrometerData() {
        return spectrometerData;
    }

    public void setSpectrometerData(SpectrometerData spectrometerData) {
        this.spectrometerData = spectrometerData;
    }
}
