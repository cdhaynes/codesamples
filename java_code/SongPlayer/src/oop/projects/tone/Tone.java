package oop.projects.tone;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.SourceDataLine;

/**
 * @author Scott Chadde and Jesse Maes
 */
public class Tone {
    private static final float sampleRate = 32 * 1024;

    /**
     * Convert the given frequency and duration into a raw byte array to send to an audio data line
     *
     * @param frequency The frequency of the sound to convert, in Hertz
     * @param seconds The duration of the sound, in seconds
     *
     * @return An array of bytes containing raw data to send to the
     */
    private static byte[] soundBytes(double frequency, double seconds) {
        //how many samples will the note hold
        byte[] note = new byte[(int)(seconds * sampleRate)];

        //sample_rate / frequency determines the number of samples
        double numberOfSamples = sampleRate / frequency;
        double sampleAngle = 2 * Math.PI / numberOfSamples;

        for (int i = 0; i < note.length; i++) {
            //determine the value of the sine wave at sample points
            double sampleAt = i * sampleAngle;

            //multiply by 127 to transform sine value to a byte value
            note[i] = (byte)(127 * Math.sin(sampleAt));
        }

        return note;
    }

    /**
     * Sends an audio tone to the speakers
     *
     * @param frequency The frequency of the sound to play, in Hertz
     * @param seconds The duration of the sound, in seconds
     */
    public static void playTone(double frequency, double seconds) {
        // sampleSizeInBits = 8, channels = 1, signed = true, bigEndian = true
        AudioFormat format = new AudioFormat(sampleRate, 8, 1, true, true);

        try {
            SourceDataLine line = AudioSystem.getSourceDataLine(format);
            DataLine.Info info = new DataLine.Info(SourceDataLine.class, format);

            if (!AudioSystem.isLineSupported(info)) {
                System.out.println(info);
                return;
            }

            // get data to send to speakers
            byte[] note = soundBytes(frequency, seconds);

            // Obtain and open the line.
            line = (SourceDataLine) AudioSystem.getLine(info);
            line.open(format);

            // play the note
            line.start();
            line.write(note, 0, note.length);

            // wait to finish then close the line
            line.drain();
            line.close();
        } catch (LineUnavailableException e) {
            e.printStackTrace();
        }
    }

    /**
     * Plays a MIDI tune from 'Scarborough Fair' by Simon and Garfunkel
     *
     * @param args Command line arguments (not used)
     */
    public static void main(String[] args) {
        double[] tune = {
                329.6275569128699, 391.99543598174927, 440.0, 391.99543598174927, 329.6275569128699,
                369.9944227116344, 293.6647679174076, 329.6275569128699
        };

        double[] beats = {
                0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 2.0
        };

        for (int i = 0; i < tune.length; i++) {
            playTone(tune[i], beats[i]);
        }
    }
}
