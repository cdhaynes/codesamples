package oop.chaynes.hw6.one;

/**
 * Provides a framework for the citation machine (Author component)
 *
 *
 * @author Casey Haynes
 * @class Author.java
 * @version HW6, #1
 * @bugs none! :D
 */
public class Author implements Comparable<Author>{
    private String lastName;
    private String firstName;
    private String middleInitial;

    //constructors
    public Author(String first, String middle, String last) {
        String[] names = {first, middle, last};
        this.firstName = names[0];
        if (names.length == 2) {
            this.lastName = names[1];
            middle = "";
        } else {
            this.middleInitial = names[1].charAt(0) + ".";
            this.lastName = names[2];
        }
    }

    public Author(String full) {
        String[] names = full.split(" ");//
        this.firstName = names[0];
        if (names.length == 2) {
            this.lastName = names[1];
            this.middleInitial = "";
        } else {
            this.middleInitial = names[1].charAt(0) + ".";
            this.lastName = names[2];
        }
    }
    //end
    //getters
    public String getLastName() {
        return this.lastName;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public String getMiddleInitial() {
        return this.middleInitial;
    }
    //end

    public String getCitation() {
        return getLastName() + ", " + getFirstName().charAt(0) + ". " + getMiddleInitial();
    }

    @Override
    public int compareTo(Author a) {
        int result = this.lastName.compareTo(a.lastName);
        if (result < 0) {
            return -1;
        } else if (result == 0) {
            result = this.firstName.compareTo(a.getFirstName());
            if (result < 0) {
                return -1;
            } else if (result == 0) {
                return this.middleInitial.compareTo(a.getMiddleInitial());
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    }

    public static Author[] splitAuthors(String fields) {
        String[] names; /* Split on commas */
        if (fields.contains(", ")) {
            names = fields.split(", ");
            int i = 0;
            while (!names[i].equals("")) { /* While something exists in the string */
               names[i] = names[i].replaceFirst("and ", ""); /* replace any ands with "" */
                i++;
                if (i == names.length) { /* Avoid accessing out of bounds area */
                    break;
                }
            }
        } else {
            names = fields.split(" and ");
        }
        Author[] authors = new Author[names.length];
        int i = 0;
                /*!(names[i].equals(""))*/
        for (String e : names) { /*Similar scheme to above */
            authors[i] = new Author(names[i]);
            i++;
        }

        return authors;
    }
}
