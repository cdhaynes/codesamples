package Q_1;

/**
 * Time.java - Defines Time object and states in which it can be used
 * @author Casey Haynes
 */
public class Time {
    /* Assumptions:
       Time zones are restricted to UTC +/- 12
       If no timezone is listed in a reading, time zone defaults to UTC
       Class contains greenWich hour attribute so UTC time can be displayed regardless of time zone the satellite recorded
     */

    /**
     * Attributes
     */
    private int hour;
    private int minute;
    private int second;
    private String month;
    private int day;
    private int year;
    private String timeZone;
    private int greenwichHour;

    /**
     * Getters and Setters
     */
    public int getHour() {
        return hour;
    }

    public void setHour(int hour) {
        this.hour = hour;
    }

    public int getMinute() {
        return minute;
    }

    public void setMinute(int minute) {
        this.minute = minute;
    }

    public int getSecond() {
        return second;
    }

    public void setSecond(int second) {
        this.second = second;
    }

    public int getDay() {
        return day;
    }

    public void setDay(int day) {
        this.day = day;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public String getMonth() {
        return month;
    }

    public void setMonth(String month) {
        this.month = month;
    }

    public String getTimeZone() {
        return timeZone;
    }

    public void setTimeZone(String timeZone) {
        this.timeZone = timeZone;
    }

    public void setGreenwichHour(int greenwichHour) {
        this.greenwichHour = greenwichHour;
    }

    public int getGreenwichHour() {
        return greenwichHour;
    }

    /**
     * Default constructor
     * Sets Defualt time to the Epoch
     */
    public Time() {
        setGreenwichHour(0);
        setMinute(0);
        setSecond(0);
        setMonth("Jan");
        setDay(1);
        setYear(1970);
        setTimeZone("UTC");
    }

    /**
     * Second Constructor
     * @param time the Time in String format, listed one of two ways:
     *             "00:00:00 Jan 1 1970 UTC"
     *             "00:00:00 Jan 1 1970"
     */
    public Time(String time) {
        String[] components = time.split(" "); /* Initially Split String on spaces */
        String[] timeComponents = components[0].split(":"); /* Split the time component on colons */

        setHour(Integer.parseInt(timeComponents[0]));
        setMinute(Integer.parseInt(timeComponents[1]));
        setSecond(Integer.parseInt(timeComponents[2]));
        setMonth(components[1]);
        setDay(Integer.parseInt(components[2]));
        setYear(Integer.parseInt(components[3]));
        try {
            setTimeZone(components[4]);
        } catch (Exception e) {
            setTimeZone("UTC");
        }
        convertUTC(getTimeZone()); /* Set greenwichHour */
    }

    /**
     * Print timeZone specific time in UTC format
     */
    public void printUTC() {
        System.out.print(getGreenwichHour() + ":" + getMinute() + ":" + getSecond() + ":" + getMonth() + " " + getDay() + " " + getYear() + " " + "UTC");
    }

    /**
     * Convert time to UTC based on timeZone information with a Switch-on-string statement
     * @param timeZone timeZone, expressed as UTC +/- 12 in String Format
     */
    public void convertUTC(String timeZone) {
        switch (timeZone) {
            case "UTC+1":
                setGreenwichHour(getHour() - 1);
                break;
            case "UTC+2":
                setGreenwichHour(getHour() - 2);
                break;
            case "UTC+3":
                setGreenwichHour(getHour() - 3);
                break;
            case "UTC+4":
                setGreenwichHour(getHour() - 4);
                break;
            case "UTC+5":
                setGreenwichHour(getHour() - 5);
                break;
            case "UTC+6":
                setGreenwichHour(getHour() - 6);
                break;
            case "UTC+7":
                setGreenwichHour(getHour() - 7);
                break;
            case "UTC+8":
                setGreenwichHour(getHour() - 8);
                break;
            case "UTC+9":
                setGreenwichHour(getHour() - 9);
                break;
            case "UTC+10":
                setGreenwichHour(getHour() - 10);
                break;
            case "UTC+11":
                setGreenwichHour(getHour() - 11);
                break;
            case "UTC+12":
                setGreenwichHour(getHour() - 12);
                break;
            case "UTC-1":
                setGreenwichHour(getHour() + 1);
                break;
            case "UTC-2":
                setGreenwichHour(getHour() + 2);
                break;
            case "UTC-3":
                setGreenwichHour(getHour() + 3);
                break;
            case "UTC-4":
                setGreenwichHour(getHour() + 4);
                break;
            case "UTC-5":
                setGreenwichHour(getHour() + 5);
                break;
            case "UTC-6":
                setGreenwichHour(getHour() + 6);
                break;
            case "UTC-7":
                setGreenwichHour(getHour() + 7);
                break;
            case "UTC-8":
                setGreenwichHour(getHour() + 8);
                break;
            case "UTC-9":
                setGreenwichHour(getHour() + 9);
                break;
            case "UTC-10":
                setGreenwichHour(getHour() + 10);
                break;
            case "UTC-11":
                setGreenwichHour(getHour() + 11);
                break;
            case "UTC-12":
                setGreenwichHour(getHour() + 12);
                break;
            case "UTC":
                break;
            case "":
                break;

        }
    }

}
