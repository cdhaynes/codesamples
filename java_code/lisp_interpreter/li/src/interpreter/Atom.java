package interpreter;
/**
 * Provides a structure for Atom objects
 *
 *
 * @author Casey Haynes
 * @class Atom.java
 * @version 1.0
 * @bugs Can't evaluate any recursed data in the driver class.
 */
public class Atom extends Expression {
    /**
     * Atom instantiator
     * @param op object to instatiate atom with
     */
    public Atom(Object op) {
        setValue(op);
    }

    /**
     * Evaluate an atom
     * @return Object with atom's value
     */
    @Override
    public Object eval() {
        return this.getValue();
    }

    /**
     * Return a string evaluation
     * @return String version of atom's value
     */
    @Override
    public String toString() {
        return (String) getValue();
    }

}
