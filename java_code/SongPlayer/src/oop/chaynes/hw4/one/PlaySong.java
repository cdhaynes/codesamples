package oop.chaynes.hw4.one;
import oop.projects.tone.Tone;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.io.File;
import java.util.Scanner;

/**
 * Implements an array list of notes and plays a song from song.txt
 *
 *
 * @author Casey Haynes
 * @class PlaySong.java
 * @version HW4, #1
 * @bugs none
 */
public class PlaySong {
    public static void playSong(ArrayList<Note> notes, int tempo) {
        double freq;
        double duration;

        for (Note i : notes) {
            freq = i.getFrequency();
            duration = i.getLength().getDuration(tempo);
            Tone.playTone(freq, duration);
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        ArrayList<Note> staff = new ArrayList<Note>();
        File file = new File("song.txt");
        Scanner in = new Scanner(file);

        while (in.hasNextLine()) {
            String spn = in.nextLine().split(" ")[0];
            String length = in.nextLine().split(" ")[1];
            System.out.println(spn);
            System.out.println(length);
            int i = 0;
            while (Beat.values()[i] != null) {
                if (length.equals(Beat.values()[i].toString())) {
                    Note note = new Note(spn, Beat.values()[i]);
                    staff.add(note);
                    System.out.println(note.getNote());
                }
                i++;
                if (i > 7) {
                    break;
                }
            }
        }

        playSong(staff, 120);

    }
}
