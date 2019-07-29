package interpreter;
/**
 * Abstract class for handling S expressions
 *
 *
 * @author Casey Haynes
 * @class Expression.java
 * @version 1.0
 * @bugs none
 */

import java.util.ArrayList;
import java.util.List;

public abstract class Expression extends MyTreeNode {
    private Object value; /* data of the object */
    private Class type; /* metadata which determines the object's particular type */
    private List<Expression> children = new ArrayList<>(); /*list of children */
    private Expression parent; /* parent node */

    /**
     * get Value
     * @return Object w value
     */
    public Object getValue() {
        return this.value;
    }

    /**
     * set Value
     * @param a Object to set Expression's value with
     */
    public void setValue(Object a) {
        this.value = a;
    }

    /**
     * get Type
     * @return a Class which the "type" attribute represents
     */
    public Class getType() {
        return this.type;
    }

    /**
     * set Type
     * @param a Class to set the type with
     */
    public void setType(Class a) {
        this.type = a;
    }

    /**
     * set Parent
     * @param parent Expression to set parent to
     */
    public void setParent (Expression parent) {
        this.parent = parent;
    }

    /**
     * add Child
     * @param child Expression to add as a child
     */
    public void addChild (Expression child) {
        child.setParent(this);
        this.children.add(child);
    }

    /**
     * get Parent
     * @return the Expression "parent"
     */
    public Expression getParent() {
        return this.parent;
    }

    /**
     * get ChildREN
     * @return a list of ALL children
     */
    public List<Expression> getChildren() {
        return children;
    }


    /**
     * evaluate, to be implemented in multiple classes
     */
    public abstract Object eval();



}

