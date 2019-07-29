package oop.chaynes.hw7.four;
import oop.chaynes.hw7.geometry.Circle;
import oop.chaynes.hw7.geometry.Rectangle;
import oop.chaynes.hw7.geometry.Point;
import oop.chaynes.hw7.one.DrawShape;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
/**
 * Sets up GoBoard
 *
 *
 * @author Casey Haynes
 * @class GoBoard.java
 * @version HW7, #4
 * @bugs none
 */

public class GoBoard extends JComponent {
    private Color stones[][];
    public GoBoard() {
        setPreferredSize(new Dimension(720, 720));
        this.stones = new Color[20][20];
    }

    public static GoBoard fromFile (String a) {
        GoBoard f = new GoBoard();
        FileReader infile = null;
        try {
            infile = new FileReader("stones.txt");
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        }
            Scanner input = new Scanner(infile);
            while (input.hasNextLine()) {
                System.out.println("TESTING");
                String args[] = input.nextLine().split(" ");
                System.out.println(args[0] + " " + args[1] + " " + args[2]);
                Color c = null;
                int col;
                Integer row;
                switch (args[0]) {
                    case "B":
                        c = Color.BLACK;
                        break;
                    case "W":
                        c = Color.WHITE;
                        break;
                    default:
                        System.out.print("Improper color in file");
                        break;
                }

                col = args[1].charAt(0) - 'A';
                if (args[1].charAt(0) > 'I') {
                    col--;
                }
                row = Integer.valueOf(args[2]);
                f.addStone(col, row, c);
            }

        return f;
    }

    public void addStone(int i, int j, Color c) {
        if ((i < 0 || i > 19) || (j < 0 || j > 19)) {
            /* Do nothing */
        } else {
            stones[i][j] = c;
        }
    }

    public void paintComponent(Graphics gfx) {
        Graphics2D gfx2 = (Graphics2D) gfx;
        try {
            BufferedImage bg = ImageIO.read(new File("bamboo.jpg"));
            gfx2.drawImage(bg, 0, 0, null);
        } catch (IOException e) {
            System.out.println("File does not exist");
        }

        Color tmp = gfx2.getColor();

        Point start = new Point(45, 45);
        Point end = new Point(80, 80);

        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 18; j++) {
                Point LL = new Point(i * 35 + 45, j * 35 + 45);
                Point UR = new Point((i+1) * 35 + 45, (j + 1) * 35 + 45);
                Rectangle rect = new Rectangle(LL, UR);
                DrawShape.drawRectangle(gfx2, rect, Color.BLACK);
            }
        }
        GoBoard tst = new GoBoard();
        tst = fromFile("");
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (tst.stones[i][j] != null) {
                    DrawShape.drawCircle(gfx2, new Circle(new Point(45 + i * 35, 15 + j * 35), 16), tst.stones[i][j]);
                }
            }
        }
        setVisible(true);
    }
}
