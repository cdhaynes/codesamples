package oop.chaynes.hw6.one;
/**
 * Generates a citation list of library.txt with a binary tree
 *
 *
 * @author Casey Haynes
 * @class Library.java
 * @version HW6, #1
 * @bugs Doesn't do anything. No lambda functions written.
 */
import java.time.Year;
import java.util.*;
import java.io.*;

public class Library {
    public static void main (String[] args) {
       /* BinarySearchTree<> titles = new BinarySearchTree();
        BinarySearchTree<> years = new BinarySearchTree();
        BinarySearchTree<> authors = new BinarySearchTree(); */

        FileReader infile = null;
        try {
            infile = new FileReader("library.txt");
            Scanner input = new Scanner(infile);
            while (input.hasNextLine()) {
                String[] storage = input.nextLine().split(", ");
                String author = storage[0];
                String title = storage[1];
                int year = Integer.parseInt(storage[2]);
                String[] newlineStorage = input.nextLine().split("\n");
                String publisher = newlineStorage[0];
                Book elem = new Book(author, title, year, publisher);
                /*titles.add(elem);
                years.add(elem);
                authors.add(elem);*/
            }
        } catch (FileNotFoundException exc) {
            System.out.println("File not found");
        }
    }
}
