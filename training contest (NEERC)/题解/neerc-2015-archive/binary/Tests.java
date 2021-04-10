import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;

public class Tests {
    static int MAXN = 10000;

    Random rnd = new Random(239);

    String folder;

    public static void main(String[] args) throws FileNotFoundException {
        new Tests().gen();
    }

    public int random(int l, int r) {
        if (r < l)
            return l;

        return l + rnd.nextInt(r - l + 1);
    }

    static int tests = 1;

    public void writeTest(int n) {
        try {
            PrintWriter out = new PrintWriter(String.format(folder + "%02d", tests++));

            System.err.println("Writing test " + (tests - 1));

            out.println(n);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void gen() {
        tests = 1;
        folder = "tests/";
        if (!new File(folder).exists())
            new File(folder).mkdir();

        writeTest(1);
        writeTest(2);
        writeTest(10);
        for (int i = 3; i <= 9; ++i) writeTest(i);
        for (int i = 2; i <= 10; ++i) writeTest(10 * i);
        for (int i = 2; i <= 10; ++i) writeTest(100 * i);
        for (int i = 2; i <= 10; ++i) writeTest(1000 * i);
        for (int i = 1; i <= 10; ++i) writeTest(random(1, MAXN));
    }
}
