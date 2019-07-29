package interpreter;

/**
 * Evaluates arithmetic expressions from a tree structure
 *
 *
 * @author Casey Haynes
 * @class ArithmeticOp.java
 * @version 1.0
 * @bugs none
 */
public class ArithmeticOp extends Expression {
    /**
     * Setter
     * @param op the operator to set default
     */
    public ArithmeticOp(Object op) {
        setValue(op);
    }

    /**
     * Default constructor
     * @return integer which is the result of the requisite calculation.
     */
    @Override
    public Object eval() {
        Integer result = 0;
        Expression child0 = this.getChildren().get(0);
        Expression child1 = this.getChildren().get(1);
        switch (this.getValue().toString()) {
            case "+":
                result = Integer.parseInt((String) child0.eval()) + Integer.parseInt((String) child1.eval());
                break;
            case "-":
                result = Integer.parseInt((String) child0.eval()) - Integer.parseInt((String) child1.eval());
                break;
            case "*":
                result = Integer.parseInt((String) child0.eval()) * Integer.parseInt((String) child1.eval());
                break;
            case "/":
                result = Integer.parseInt((String) child0.eval()) / Integer.parseInt((String) child1.eval());
                break;
            default:
                System.out.println("Not a valid operator");
                break;
        }
        return result;
    }

    /**
     * convert data to String
     * @return the resultant string
     */
    public String toString() {
        return (String) getValue();
    }

}
