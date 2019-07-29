package oop.chaynes.hw6.one;
/**
 * Extends Citation to generate Book object
 *
 *
 * @author Casey Haynes
 * @class Book.java
 * @version HW6, #1
 * @bugs none
 */
public class Book extends Citation {
    protected String publisher;

    public String getPublisher() {
        return this.publisher;
    }

    public Book(String author, String title, int year, String publisher) {
        super(author, title, year);
        this.publisher = publisher;
    }

    public String toString() {
        return super.toString() + this.publisher;
    }




}
