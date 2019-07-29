package oop.chaynes.hw6.one;
/**
 * Citation provides a starting point for other classes in the package (Author, Book)
 *
 *
 * @author Casey Haynes
 * @class Citation.java
 * @version HW6, #1
 * @bugs none
 */
public class Citation {
    protected Author[] author;
    protected String title;
    protected int year;

    public Citation(String authors, String title, int year) {
        this.author = Author.splitAuthors(authors);
        this.title = title;
        this.year = year;
    }

    public Author[] getAuthor() {
        return this.author;
    }

    public String getTitle() {
        return this.title;
    }

    public int getYear() {
        return this.year;
    }

    public String toString() {
        String firstName = "";
        String middleInitial = "";
        String lastName = "";

        for (Author auth : this.author) {
            firstName = auth.getFirstName();
            middleInitial = auth.getMiddleInitial();
            lastName = auth.getLastName();
        }

        return (lastName +" "+ firstName +" "+ middleInitial + ", " + this.getTitle() + "., " + this.year + "\n");
    }
}
