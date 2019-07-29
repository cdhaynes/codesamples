package oop.chaynes.hw6.two;
/**
 * Reverse Polish Notation Calculator
 *
 *
 * @author Casey Haynes
 * @class RPN.java
 * @version HW6, #2
 * @bugs none
 */
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.Stack;

public class RPN {
    public static double eval(ArrayList<Token> inList) {
        Stack<Double> doubleStack = new Stack<Double>();
        for (Token i : inList) {
            if (!i.isOperator()) {
                doubleStack.push(i.getNumber());
            } else {
                Double b = doubleStack.pop();
                Double a = doubleStack.pop();
                doubleStack.push(i.getOperator().eval(a,b));
            }
        }
        int stackSize = doubleStack.size();
        if (stackSize != 1) {
            throw new ArithmeticException("Invalid RPN Expression!");
        } else {
            return doubleStack.pop();
        }

    }

    public static void main(String[] args) {
        Scanner in  = new Scanner(System.in);
        while (true) {
            System.out.print("RPN Expression> ");
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
                double result = eval(token_list);
                System.out.println(result);
            } catch (Exception e) {
                System.out.println("Invalid RPN expression");
            }
        }
    }
}
