package oop.chaynes.hw6.two;
/**
 * Implements details for Operators (Enum)
 *
 *
 * @author Casey Haynes
 * @class Operator.java
 * @version HW6, #2
 * @bugs none
 */
public enum Operator {
    LPAREN(3),
    RPAREN(3),
    EXPONENT(2),
    MULTIPLY(1),
    DIVIDE(1),
    MODULO(1),
    ADD(0),
    SUBTRACT(0);

    private int precedence;
    private Operator(int precedence) {
        this.precedence = precedence;
    }

    public int getPrecedence() {
        return this.precedence;
    }

    public double eval(double a, double b) {
        double ans = 0;
        switch (this) {
            case EXPONENT:
                ans = Math.pow(a,b);
                break;
            case MULTIPLY:
                ans = a * b;
                break;
            case DIVIDE:
                ans = a / b;
                break;
            case MODULO:
                ans = a % b;
                break;
            case ADD:
                ans = a + b;
                break;
            case SUBTRACT:
                ans = a - b;
                break;
            case LPAREN:
                ans = Double.NaN;
                break;
            case RPAREN:
                ans = Double.NaN;
                break;
        }
        return ans;
    }

    @Override
    public String toString() {
        switch(this) {
            case EXPONENT:
                System.out.print("^");
                break;
            case MULTIPLY:
                System.out.print("*");
                break;
            case DIVIDE:
                System.out.print("/");
                break;
            case MODULO:
                System.out.print("%");
                break;
            case ADD:
                System.out.print("+");
                break;
            case SUBTRACT:
                System.out.print("-");
                break;
            case LPAREN:
                System.out.print("(");
                break;
            case RPAREN:
                System.out.print(")");
                break;
        }

        return null;
    }
}
