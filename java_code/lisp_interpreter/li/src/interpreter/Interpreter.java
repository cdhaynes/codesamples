package interpreter;
/**
 * Driver class. Decides what to do with input and prints result to an output file
 *
 *
 * @author Casey Haynes
 * @class Interpreter.java
 * @version 1.0
 * @bugs Tree implementations don't work recursively. I believe it's something to do with the level of encapsulation employed. I lost it somewhere along the way.
 */
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

public class Interpreter {
    /**
     * Determines if a LISP expression is valid based on the number of parentheses therein.
     * @param input the String to check
     * @return true if it's a valid exp, false if not.
     */
    public static boolean paren_parser(String input) {
        Stack<Integer> parentheses = new Stack<>();
        int i = 0;
        while (i < input.length()) {
            if (input.charAt(i) == '(') {
                parentheses.push(1);
            }
            if (input.charAt(i) == ')') {
                try {
                    parentheses.pop();
                } catch (EmptyStackException e) {
                    System.out.println("Invalid LISP input\n");
                    return false;
                }
            }
            i++;
        }
        if (!parentheses.isEmpty()) {
            System.out.println("Invalid LISP input\n");
            return false;
        }

        return true;
    }

    /**
     * Add spaces to the input in order to get elements of LISP expression into an ArrayList
     * @param input String to add spaces to
     * @return The same string with spaces added
     */
    public static String space_parser(String input) {
        input = input.replaceAll("\\(", " ( ");
        input = input.replaceAll("\\)", " ) ");

        input = input.trim().replaceAll(" +", " ");
        return input;
    }

    /**
     * The tokenizer method decides what to do with an expression based on the beginning element. The decision is carried out
     * via switch statement, and works for car, cdr, arith ops, etc. **Note, some requirements of the project were attempted but not
     * fully implemented.
     * An expression will be parsed by the tokenizer, and if Tokenizer hits a nested parenthesis, Tokenizer will call recursively
     * and create a subtree of the current tree.
     * Expressions are parsed via a parse tree structure. Theoretically then, the implementation could use different eval() methods to
     * evaluate expressions based on what data type they were. However, I employed too much encapsulation and I cannot get the data back out
     * of the tree. *****THE TREE BUILDS PROPERLY THOUGH****** I simply did not have the time to figure this issue out within the
     * temporal confines of the assignment, and as such, many implementational details are broken.
     *
     * @param input The String to Tokenize on (with spaces added)
     * @return A new tree with all expression data.
     */
    public static MyTreeNode<Expression> Tokenizer(String input) {
        if (!paren_parser(input)) {
            return null;
        }
        input = space_parser(input); /*add spaces*/
        /* Build the tree */
        String[] expressions = input.split(" ");

        MyTreeNode<Expression> tree = new MyTreeNode(); /* Tree to load data into */

        if (numTest(expressions[1])) {
            tree.setData(new Atom(expressions[1]));
        } else {
            if (expressions[1].equals("quit")) {
                try {

                } catch (NullPointerException e) {
                    System.out.println("Bye.");
                }
            }
            switch (expressions[1]) {
                case "+": /* prefix addition */
                    tree.setData(new ArithmeticOp(expressions[1]));
                    break;
                case "-": /* prefix subtraction */
                    tree.setData(new ArithmeticOp(expressions[1]));
                    break;
                case "*": /*prefix multiplication */
                    tree.setData(new ArithmeticOp(expressions[1]));
                    break;
                case "/": /* prefix division */
                    tree.setData(new ArithmeticOp(expressions[1]));
                    break;
                case "(": /*if there's a nested statement */
                    String accordion = "";
                    int parentheses = 1;
                    int first_run_test = 0;
                    int i = 1;
                    while (true) {
                        if (first_run_test == 0) {
                            parentheses = 0;
                            first_run_test = 1;
                        }

                        if (expressions[i].contains("(")) {
                            parentheses++;
                        } else if (expressions[i].contains(")")) {
                            parentheses--;
                        }

                        accordion = accordion.concat(expressions[i] + " ");

                        if (parentheses == 0) {
                            break;
                        }
                        i++;
                    }

                    tree.setData(new Atom(accordion));
                    break;
                case "car": /* car function */
                    if (expressions[2].equals("'")) {
                        tree.setData(new Atom(expressions[4]));
                        return tree;
                    } else {
                        accordion = "";
                        parentheses = 1;
                        first_run_test = 0;
                        i = 1;
                        while (true) {
                            if (first_run_test == 0) {
                                parentheses = 0;
                                first_run_test = 1;
                                i = 2;
                            }

                            if (expressions[i].contains("(")) {
                                parentheses++;
                            } else if (expressions[i].contains(")")) {
                                parentheses--;
                            }

                            accordion = accordion.concat(expressions[i] + " ");

                            if (parentheses == 0) {
                                break;
                            }
                            i++;
                        }
                        Tokenizer(accordion);
                    }
                    break;
                case "cdr": /* cdr function */
                    if (expressions[2].equals("'")) {
                        String ret = "";
                        for (int index = 5; index < expressions.length; index++) { /* build the string of remaining elements in expressions */
                            if (expressions[index].equals("(") || expressions[index].equals(")")) {
                                break;
                            }
                            ret = ret.concat(expressions[index] + " ");
                        }
                        tree.setData(new Atom(ret));
                        return tree;
                    } else {
                        accordion = ""; /* string to concatenate all array elements into */
                        parentheses = 1; /* fake stack implementation of parenthetical counter */
                        first_run_test = 0; /* if it's the first run of the loop, behavior will be different */
                        i = 1;
                        while (true) {
                            if (first_run_test == 0) {
                                parentheses = 0;
                                first_run_test = 1;
                            }

                            if (expressions[i].contains("(")) {
                                parentheses++;
                            } else if (expressions[i].contains(")")) {
                                parentheses--;
                            }

                            accordion = accordion.concat(expressions[i] + " ");

                            if (parentheses == 0) {
                                break;
                            }
                            i++;
                        }
                        Tokenizer(accordion); /* recurse */
                    }
                    break;
                case "cons": /* cons function */
                    String eval = "(";

                    int index = 3;
                    while (expressions[index] != null) {
                        if (expressions[index].equals("(") || expressions[index].equals(")")) {
                            index++;
                            continue;
                        }
                        eval = eval.concat(expressions[index] + " ");
                        index++;
                    }

                    eval = eval.concat(")");
                    tree.setData(new Atom(eval));
                    break;

                case "sqrt": /* sqrt function */
                    accordion = "";
                    parentheses = 1;
                    first_run_test = 0;
                    i = 1;
                    while (true) {
                        if (first_run_test == 0) {
                            parentheses = 0;
                            first_run_test = 1;
                            i = 2;
                        }

                        if (expressions[i].contains("(")) {
                            parentheses++;
                        } else if (expressions[i].contains(")")) {
                            parentheses--;
                        }

                        accordion = accordion.concat(expressions[i] + " ");

                        if (parentheses == 0) {
                            break;
                        }
                        i++;
                    }

                    Tokenizer(accordion);
                    Double ans = Math.sqrt(Double.parseDouble(accordion));
                    tree.setData(new Atom(ans));
                    break;

                case "exp": /* exp function */
                    accordion = "";
                    parentheses = 1;
                    first_run_test = 0;
                    i = 1;
                    while (true) {
                        if (first_run_test == 0) {
                            parentheses = 0;
                            first_run_test = 1;
                            i = 2;
                        }

                        if (expressions[i].contains("(")) {
                            parentheses++;
                        } else if (expressions[i].contains(")")) {
                            parentheses--;
                        }

                        accordion = accordion.concat(expressions[i] + " ");

                        if (parentheses == 0) {
                            break;
                        }
                        i++;
                    }

                    Tokenizer(accordion);
                    ans = Math.pow(Double.parseDouble(accordion), Double.parseDouble(expressions[3]));
                    tree.setData(new Atom(ans));
                    break;
                case ">": /* logical comparisons (not fully implemented) */
                case "<":
                case "=":
                case "!=":
                case "and":
                case "or":
                case "not":
                    tree.setData(new Atom(expressions));
                    break;


            }
        }

        for (int i = 2; i < expressions.length; i++) {
            if (expressions[i].contains("(")) {
                String accordion = "";
                int parentheses = 1;
                int first_run_test = 0;

                while (parentheses != 0) {
                    if (first_run_test == 0) {
                        parentheses = 0;
                        first_run_test = 1;
                    }

                    if (expressions[i].contains("(")) {
                        parentheses++;
                    } else if (expressions[i].contains(")")) {
                        parentheses--;
                    }

                    accordion = accordion.concat(expressions[i] + " ");

                    if (parentheses == 0) {
                        break;
                    }
                    i++;
                }
                Expression t = Tokenizer(accordion).getData();
                tree.getData().addChild(t); /*Recurse */
            }

            if (i < expressions.length && !expressions[i].contains("(") && !expressions[i].contains(")") && !expressions[i].contains(" ")) {
                if (numTest(expressions[i])) {
                    tree.getData().addChild(new Atom(expressions[i]));
                } else {

                    switch (expressions[i]) { /* Run through the same arithmetic comparisons for the rest of the expressions array */
                        case "+":
                            tree.getData().addChild(new ArithmeticOp(expressions[i]));
                            break;
                        case "-":
                            tree.getData().addChild(new ArithmeticOp(expressions[i]));
                            break;
                        case "*":
                            tree.getData().addChild(new ArithmeticOp(expressions[i]));
                            break;
                        case "/":
                            tree.getData().addChild(new ArithmeticOp(expressions[i]));
                            break;
                        default:
                            System.out.println("Invalid input: " + expressions[i]);
                            break;
                    }
                }
            }
        }

        return tree;

    }


    /**
     * Driver method for the driver class
     * @param args standard, makes main run.
     */
    public static void main (String[] args) {
        Scanner in = new Scanner(System.in);
        while (true) {
            System.out.println("Hello! Enter a LISP expression: ");
            String input = in.nextLine();
            paren_parser(input);
            //System.out.println(input);
            //input = space_parser(input);
            //System.out.println(input);
            MyTreeNode<Expression> tree = null;
            tree = Tokenizer(input);

            String data = (tree.getData().eval().toString());
            try {
                PrintWriter outfile = new PrintWriter("out.txt");
                outfile.println(data);
            } catch (FileNotFoundException e) {

            }
            System.out.println(data);




        }

    }

    /**
     * Simple test to determine whether or not a string is a number
     * @param input String to test
     * @return true or false
     */
    public static boolean numTest(String input) {
        try {
            Integer.parseInt(input);
            return true;
        } catch (NumberFormatException ex) {
            return false;
        }
    }

}
