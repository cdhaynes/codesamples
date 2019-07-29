package oop.chaynes.hw6.two;
import java.util.*;
/**
 * Implements details of Token objects
 *
 *
 * @author Casey Haynes
 * @class Token.java
 * @version HW6, #3
 * @bugs none
 */

public class Token {
    private Double number;
    private Operator operator;

    public Double getNumber() {
        return number;
    }

    public Operator getOperator() {
        return operator;
    }

    public Token(double a) {
        number = a;
        operator = null;
    }

    public Token(Operator a) {
        operator = a;
        number = null;
    }

    public boolean isOperator() {
        boolean result;
        if (operator != null) {
            result = true;
        } else {
            result = false;
        }

        return result;
    }

    public static Token parseToken(String a) {
        Token result;
        switch (a) {
            case "(":
               result = new Token(Operator.LPAREN);
               break;
            case ")":
                result = new Token(Operator.RPAREN);
                break;
            case "^":
                result = new Token(Operator.EXPONENT);
                break;
            case "*":
                result = new Token(Operator.MULTIPLY);
                break;
            case "/":
                result = new Token(Operator.DIVIDE);
                break;
            case "%":
                result = new Token(Operator.MODULO);
                break;
            case "+":
                result = new Token(Operator.ADD);
                break;
            case "-":
                result = new Token(Operator.SUBTRACT);
                break;
            default:
                try {
                    result = new Token(Double.parseDouble(a));
                } catch (NumberFormatException e) {
                    result = null;
                }
        }

        return result;
    }
}
