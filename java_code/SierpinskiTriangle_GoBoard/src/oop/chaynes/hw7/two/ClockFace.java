package oop.chaynes.hw7.two;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.time.LocalTime;
/**
 * Sets up the ClockFace
 *
 *
 * @author Casey Haynes
 * @class ClockFace.java
 * @version HW7, #2
 * @bugs none
 */
public class ClockFace extends JComponent {
    private int hour;
    private int minute;
    private int second;

    public int getHour() {
        return this.hour;
    }

    public int getMinute() {
        return this.minute;
    }

    public int getSecond() {
        return this.second;
    }

    public void setHour(int hr) {
        this.hour = hr;
    }

    public void setMinute(int min) {
        this.minute = min;
    }

    public void setSecond(int sec) {
        this.second = sec;
    }

    public void ClockFace() {
        this.hour = (LocalTime.now().getHour());
        setMinute(LocalTime.now().getMinute());
        setSecond(LocalTime.now().getSecond());
        setPreferredSize(new Dimension(400, 400));
    }

    public void ClockFace(int hour, int min, int sec) {
        if (hour < 0 || hour > 23) {
            setHour(LocalTime.now().getHour());
        } else {
            setHour(hour);
        }

        if (min < 0 || min > 59) {
            setMinute(LocalTime.now().getMinute());
        } else {
            setMinute(min);
        }

        if (sec < 0 || sec > 59) {
            setSecond(LocalTime.now().getSecond());
        } else {
            setSecond(sec);
        }
        setPreferredSize(new Dimension(400, 400));
    }

    public void paintComponent(Graphics gfx) {
        try {
            BufferedImage bg = ImageIO.read(new File("clock.jpg"));
            gfx.drawImage(bg, 0, 0, null);
        } catch (IOException e) {
            System.out.println("File does not exist");
        }

        Graphics2D clockFace = (Graphics2D) gfx;
        double secTheta = (Math.PI / 30.0) * LocalTime.now().getSecond();
        double minTheta = (Math.PI / 30.0) * LocalTime.now().getMinute();
        double hrTheta = (Math.PI / 6.0) * (LocalTime.now().getHour() % 12) +   (Math.PI / 360) * getMinute();
        double secX = (200.0 + 190.0 * Math.sin(secTheta));
        double secY = (200.0 - 190.0 * Math.cos(secTheta));
        double minX = (200.0 + 160.0 * Math.sin(minTheta));
        double minY = (200.0 - 160.0 * Math.cos(minTheta));
        double hrX = (200.0 + 100.0 * Math.sin(hrTheta));
        double hrY = (200.0 - 100.0 * Math.cos(hrTheta));
        Color tmp = clockFace.getColor();
        clockFace.setColor(Color.RED);
        clockFace.setStroke(new BasicStroke(3));
        clockFace.draw(new Line2D.Double(200.0, 200.0, secX, secY));       //(200, 200, secX, secY);
        clockFace.setColor(tmp);
        clockFace.setStroke(new BasicStroke(5));
        clockFace.draw(new Line2D.Double(200.0, 200.0, minX, minY)); //(200, 200, minX, minY);
        clockFace.setStroke(new BasicStroke(7));
        clockFace.draw(new Line2D.Double(200.0, 200.0, hrX, hrY)) ;       //(200, 200, hrX, hrY);

    }
}
