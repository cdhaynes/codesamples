package oop.chaynes.hw4.one;

import java.util.Arrays;

import static oop.chaynes.hw4.one.Beat.*;
import static oop.chaynes.hw4.one.Pitch.*;

/**
 * Implements the Note constructors
 *
 *
 * @author Casey Haynes
 * @class Note.java
 * @version HW4, #1
 * @bugs none
 */

public class Note {
    private Pitch note;
    private int octave;
    private Beat length;
    private String spn; /*rarely used compared to the others */
    private int MIDI;
    private double frequency;

    public Pitch getNote() {
        return note;
    }

    public void setNote(Pitch note) {
        this.note = note;
    }

    public int getOctave() {
        return octave;
    }

    public void setOctave(int octave) {
        this.octave = octave;
    }

    public Beat getLength() {
        return length;
    }

    public void setLength(Beat length) {
        this.length = length;
    }

    public Note() {
        setNote(C);
        setOctave(4);
        setLength(QUARTER);
        setSPN("C4");

        int MIDI = 60;
        setMIDI(MIDI);

        int exp = (MIDI -69) / 12;
        double freq = 440.0 * Math.pow(2.0, exp);
        setFrequency(freq);

    }

    public Note(Pitch pitch, int octave, Beat length) {

        if (octave > 9 || octave < -1) {
            octave = 4;
        }
        if ((pitch.equals(GSHARP) || pitch.equals(A) || pitch.equals(ASHARP) || pitch.equals(B)) && octave > 8) {
            octave = 8;
        }

        setNote(pitch);
        setOctave(octave);
        setLength(length);

        int MIDI = 69 + pitch.getOffset() + 12 * (octave - 4);
        setMIDI(MIDI);

        double exp = (MIDI -69) / 12;
        double freq = 440.0 * Math.pow(2.0, exp);
        setFrequency(freq);

    }

    public Note(String spn, Beat length) {
        String note;
        int octave;
        setSPN(spn);
        if (spn.matches("(([CDFGA]#?|[EB])(-1|[0-8])|([CDF]#?|[EG])9)")) {
            if (spn.contains("-")) {
                note = spn.split("-")[0];
                octave = Integer.parseInt(("-" + spn.split("-")[1]));
            } else if (spn.contains("#")) {
                note = spn.split("#")[0] + "#";
                octave = Integer.parseInt(spn.split("#")[1]);
            } else {
                note = spn.substring(0, 1);
                octave = Integer.parseInt(spn.substring(1, 2));
            }

            if (note.equals("C")) {
                setNote(C);
            } else if (note.equals("C#")) {
                setNote(CSHARP);
            } else if (note.equals("D")) {
                setNote(D);
            } else if (note.equals("D#")) {
                setNote(DSHARP);
            } else if (note.equals("E")) {
                setNote(E);
            } else if (note.equals("F")) {
                setNote(F);
            } else if (note.equals("F#")) {
                setNote(FSHARP);
            } else if (note.equals("G")) {
                setNote(G);
            } else if (note.equals("G#")) {
                setNote(GSHARP);
            } else if (note.equals("A")) {
                setNote(A);
            } else if (note.equals("A#")) {
                setNote(ASHARP);
            } else if (note.equals("B")) {
                setNote(B);
            }


            if (octave > -2 && octave < 10) {
                setOctave(octave);
            } else {
                setOctave(4);
            }

            setLength(length);
            int MIDI = 69 + getNote().getOffset();
            setMIDI(MIDI);


            double exp = (getMIDI() - 69.0) / 12.0;
            double freq = 440.0 * Math.pow(2.0, exp);
            setFrequency(freq);
        }
    }

    public Note(int MIDI, Beat length) {
        if (MIDI < 0 || MIDI > 127) {
            setNote(C);
            setOctave(4);
            setLength(QUARTER);
        }

        int octave = Math.floorDiv(MIDI, 12) - 1;
        int value = MIDI % 12;

        setOctave(octave);
        setLength(length);
        setMIDI(MIDI);

        double exp = (MIDI - 69.0) / 12.0;
        double freq = 440.0 * Math.pow(2.0, exp);
        setFrequency(freq);


        if (value == 0) {
            setNote(C);
        } else if (value == 1) {
            setNote(CSHARP);
        } else if (value == 2) {
            setNote(D);
        } else if (value == 3) {
            setNote(DSHARP);
        } else if (value == 4) {
            setNote(E);
        } else if (value == 5) {
            setNote(F);
        } else if (value == 6) {
            setNote(FSHARP);
        } else if (value == 7) {
            setNote(G);
        } else if (value == 8) {
            setNote(GSHARP);
        } else if (value == 9) {
            setNote(A);
        } else if (value == 10) {
            setNote(ASHARP);
        } else if (value == 11) {
            setNote(B);
        } else {
            setNote(C);
        }
    }

    public Note(double freq, Beat length) {
        setFrequency(freq);
        double frac = freq / 440.0;
        double midi = 12.0 * (Math.log(frac) / Math.log(2.0)) + 69.0;
        int MIDI = (int) Math.round(midi);
        setMIDI(MIDI);


        if (MIDI < 0 || MIDI > 127) {
            setNote(C);
            setOctave(4);
            setLength(QUARTER);
        }

        int octave = Math.floorDiv(MIDI, 12) - 1;
        int value = MIDI % 12;

        setOctave(octave);
        setLength(length);

        if (value == 0) {
            setNote(C);
        } else if (value == 1) {
            setNote(CSHARP);
        } else if (value == 2) {
            setNote(D);
        } else if (value == 3) {
            setNote(DSHARP);
        } else if (value == 4) {
            setNote(E);
        } else if (value == 5) {
            setNote(F);
        } else if (value == 6) {
            setNote(FSHARP);
        } else if (value == 7) {
            setNote(G);
        } else if (value == 8) {
            setNote(GSHARP);
        } else if (value == 9) {
            setNote(A);
        } else if (value == 10) {
            setNote(ASHARP);
        } else if (value == 11) {
            setNote(B);
        } else {
            setNote(C);
        }
    }

    public String getSPN() {
        String note = this.getNote().toString();
        int octave = this.getOctave();

        return note + octave;
    }

    public void setSPN(String spn) {
        this.spn = spn;
    }

    public int getMIDI() {
        return this.MIDI;
    }

    public void setMIDI(int MIDI) {
        this.MIDI = MIDI;
    }

    public double getFrequency() {
        return this.frequency;
    }

    public void setFrequency(double frequency) {
        this.frequency = frequency;
    }
    @Override
    public String toString() {

        return this.getSPN() +" "+this.getLength();
    }


}
