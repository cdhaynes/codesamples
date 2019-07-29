package Q_4;

/**
 * InfraredReading - child class of generic, specifies IR specific data
 * @author Casey Haynes
 */
public class InfraredReading extends GenericReading {
    private InfraredData irdata;

    /**
     * Default Constructor
     */
    public InfraredReading() {
        irdata = new InfraredData(); /* Hypothetical InfraredData class has default constructor */
        setCenter(new LatLon(0, 0));
        setHeight(0);
        setWidth(0);
        setTimeTaken(new Time());
    }

    public InfraredData getIrdata() {
        return irdata;
    }

    public void setIrdata(InfraredData irdata) {
        this.irdata = irdata;
    }
}
