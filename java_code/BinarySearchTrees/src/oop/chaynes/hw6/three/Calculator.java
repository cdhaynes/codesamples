package oop.chaynes.hw6.three;
/**
 * Translates RPN to standard infix calculator
 *
 *
 * @author Casey Haynes
 * @class Calculator.java
 * @version HW6, #3
 * @bugs Rejects any input with parentheses.
 */
import oop.chaynes.hw6.two.Operator;
import oop.chaynes.hw6.two.RPN;
import oop.chaynes.hw6.two.Token;

import java.util.*;

import static oop.chaynes.hw6.two.RPN.eval;

public class Calculator {
    public static ArrayList<Token> toRPN(ArrayList<Token> inlist) {
        ArrayList<Token> outlist = new ArrayList<>();
        Stack<Operator> opStack = new Stack<>();

        for (Token e : inlist) {
            if (!e.isOperator()) {
                outlist.add(e);
            } else if (e.isOperator() && !e.getOperator().equals(Operator.LPAREN) && !e.getOperator().equals(Operator.RPAREN)) {
                Operator top_of_opStack;
                try {
                    top_of_opStack = opStack.peek();
                } catch (EmptyStackException expp){
                    top_of_opStack = Operator.ADD;
                }
                    while ((!top_of_opStack.equals(Operator.LPAREN) && (top_of_opStack.getPrecedence() > e.getOperator().getPrecedence()) || (top_of_opStack.equals(Operator.EXPONENT) && e.getOperator().equals(Operator.EXPONENT)))) {
                        Operator popped = opStack.pop();
                        Token out = new Token(popped);
                        outlist.add(out);
                    }
                opStack.push(e.getOperator());

            } else if (e.getOperator().equals(Operator.LPAREN)) {
                opStack.push(e.getOperator());
            } else if (e.getOperator().equals(Operator.RPAREN)) {
                Operator top_of_opStack;
                try {
                    top_of_opStack = opStack.peek();
                } catch (EmptyStackException exe) {
                    top_of_opStack = Operator.ADD;
                }
                    while (!top_of_opStack.equals(Operator.LPAREN)) {
                        Operator popped = opStack.pop();
                        Token out = new Token(popped);
                        outlist.add(out);
                    }
                    if (top_of_opStack.equals(Operator.LPAREN)) {
                        Operator trash_lparen = opStack.pop();
                    } else if (top_of_opStack.equals(null) || !top_of_opStack.equals(Operator.LPAREN)) {
                        throw new ArithmeticException("Mismatched Parentheses");
                    }


            }
        }
        Operator top_of_stack = null;
        try {
            top_of_stack = opStack.peek();
        } catch (EmptyStackException e) {
            top_of_stack = Operator.ADD;
        }
            while (!opStack.isEmpty()) {
                Operator tmp = opStack.pop();
                Token temp = new Token(tmp);
                outlist.add(temp);
            }



        return outlist;
    }

    public static void main(String[] args) {
        Scanner in  = new Scanner(System.in);
        while (true) {
            System.out.print("Expression> ");
            String commandline_raw;
            try {
                commandline_raw = in.nextLine();
            } catch (NoSuchElementException e) {
                break;
            }
            String[] commandline_processed = commandline_raw.split(" ");
            ArrayList<Token> token_list = new ArrayList<>();
            for (String e : commandline_processed) {
                Token instance = Token.parseToken(e);
                token_list.add(instance);
            }
            try {
                ArrayList<Token> poles = new ArrayList<>();
                poles = toRPN(token_list);

                double result = RPN.eval(poles);
                System.out.println(result);
            } catch (Exception e) {
                System.out.println("Invalid infix expression");
            }
        }
    }
    }

