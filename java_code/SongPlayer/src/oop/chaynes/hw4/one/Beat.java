package oop.chaynes.hw4.one;
/**
 * Implements constructors for the Beat enumeration.
 *
 *
 * @author Casey Haynes
 * @class Beat.java
 * @version HW4, #1
 * @bugs none
 */
public enum Beat {
    WHOLE(4),
    THREEQUARTER(3),
    HALF(2),
    THREEEIGHTH(1.5),
    QUARTER(1),
    THREESIXTEENTH(0.75),
    EIGHTH(0.5),
    SIXTEENTH(0.25);

    private double beats;
    private int index;

    private Beat(double beats) {
        this.beats = beats;
    }

    public double getBeats() {
        return beats;
    }

    public double getDuration(int tempo) {
        double secondsToPlay = (60.0 * getBeats()) / tempo;
        return secondsToPlay;
    }

    public String toString() {
        if (getBeats() == 4) {
            return "(1)";
        } else if (getBeats() == 3) {
            return "(3/4)";
        } else if (getBeats() == 2) {
            return "(1/2)";
        } else if (getBeats() == 1.5) {
            return "(3/8)";
        } else if (getBeats() == 1) {
            return "(1/4)";
        } else if (getBeats() == 0.75) {
            return "(3/16)";
        } else if (getBeats() == 0.5) {
            return "(1/8)";
        } else if (getBeats() == 0.25) {
            return "(1/16)";
        } else {
            return null;
        }
    }
}
