package oop.chaynes.hw4.one;
/**
 * Implements constructors for the Pitch enumeration. "Pitch, get it right!"
 *
 *
 * @author Casey Haynes
 * @class Pitch.java
 * @version HW4, #1
 * @bugs none
 */
public enum Pitch {
    C(0, -9),
    CSHARP(1, -8),
    D(2, -7),
    DSHARP(3, -6),
    E(4, -5),
    F(5, -4),
    FSHARP(6, -3),
    G(7, -2),
    GSHARP(8, -1),
    A(9, 0),
    ASHARP(10, 1),
    B(11, 2);


    private int value;
    private int offset;

    private Pitch(int value, int offset) {
        this.value = value;
        this.offset = offset;
    }

    public int getOffset() {
        return offset;
    }

    public String toString() {
        switch (getOffset()) {
            case -9:
                return "C";
            case -8:
                return "C#";
            case -7:
                return "D";
            case -6:
                return "D#";
            case -5:
                return "E";
            case -4:
                return "F";
            case -3:
                return "F#";
            case -2:
                return "G";
            case -1:
                return "G#";
            case 0:
                return "A";
            case 1:
                return "A#";
            case 2:
                return "B";
            default:
                return null;
        }
    }
}
