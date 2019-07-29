package oop.chaynes.hw7.four;
import javax.swing.*;
import java.awt.*;
/**
 * Sets up GoFrame (runs it)
 *
 *
 * @author Casey Haynes
 * @class GoFrame.java
 * @version HW7, #4
 * @bugs none
 */
public class GoFrame extends JFrame {
    private static final int WIDTH = 720;
    private static final int HEIGHT = 780;
    public GoFrame(GoBoard board) {
        setSize(WIDTH, HEIGHT);
        this.add(board);
        pack();
        setTitle("Go Board");
        JLabel black = new JLabel("Black: 23", SwingConstants.CENTER);
        JLabel white = new JLabel("White: 12.5", SwingConstants.CENTER);
        black.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 32));
        black.setForeground(Color.BLACK);
        white.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 32));
        white.setForeground(Color.WHITE);
        JPanel s_panel = new JPanel(new GridLayout(1, 2));

        s_panel.add(white, SwingConstants.CENTER);
        s_panel.add(black, SwingConstants.CENTER);
        s_panel.setBackground(Color.decode("#ffd294"));
        this.add(s_panel, BorderLayout.SOUTH);
        pack();

    }

    public static void main (String[] args) {
        GoBoard board = new GoBoard();
        GoFrame f = new GoFrame(board);
        f.setSize(WIDTH, HEIGHT); /* Setting size in ClockFrame does not work for me */
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);
    }
}
