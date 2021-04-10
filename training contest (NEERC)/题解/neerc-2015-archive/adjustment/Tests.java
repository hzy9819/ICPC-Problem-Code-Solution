import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

/**
 * Created on 20.09.2015.
 */
public class Tests {
    int MAX_Q = 100000;
    int MAX_N = 1000000;

    Random rnd = new Random(239);

    public static void main(String[] args) throws FileNotFoundException {
        new Tests().gen();
    }

    int tests = 1;

    public void writeTest(int n, boolean[] type, int[] x) {
        try {
            PrintWriter out = new PrintWriter(String.format("tests/%02d", tests++));

            System.err.println("Writing test " + (tests - 1));

            out.println(n + " " + x.length);

            for (int i = 0; i < x.length; i++) {
                out.println((type[i] ? "R" : "C") + " " + x[i]);
            }

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public void genRandom(int n, int q, double p) {
        boolean[] type = new boolean[q];
        int[] x = new int[q];

        int[][] old = new int[2][q];
        int[] size = new int[2];

        for (int i = 0; i < q; i++) {
            int t = rnd.nextInt(2);
            type[i] = t == 1;
            if (rnd.nextDouble() < p && size[t] > 0) {
                x[i] = old[t][rnd.nextInt(size[t])];
            } else {
                x[i] = rnd.nextInt(n) + 1;
                old[t][size[t]++] = x[i];
            }
        }
        writeTest(n, type, x);
    }

    public void genMaximumRandom(int n, int q) {
        boolean[] type = new boolean[q];
        int[] x = new int[q];
        int[] s = new int[]{n, n};

        for (int i = 0; i < q; i++) {
            int t = rnd.nextInt(2);
            type[i] = t == 1;
            x[i] = s[t]--;
        }

        writeTest(n, type, x);
    }

    public void genMaximumOne(int n, int q, boolean t) {
        boolean[] type = new boolean[q];
        int[] x = new int[q];
        int s = n;
        for (int i = 0; i < q; i++) {
            type[i] = t;
            x[i] = s--;
        }
        writeTest(n, type, x);
    }

    public void gen() {
        writeTest(3, new boolean[]{true, false, true, true, false, false, true}, new int[]{2, 3, 2, 1, 2, 1, 3});

        writeTest(1, new boolean[]{true, false, true}, new int[]{1, 1, 1});

        for (int i = 0; i < 4; i++) {
            genRandom(rnd.nextInt(10) + 1, rnd.nextInt(19) + 1, rnd.nextDouble());
        }

        for (int i = 0; i <= 10; i++) {
            genRandom(MAX_N, MAX_Q, i * .1);
        }

        genMaximumOne(MAX_N, MAX_Q, false);
        genMaximumOne(MAX_N, MAX_Q, true);
        for (int i = 0; i < 2; i++)
            genMaximumRandom(MAX_N, MAX_Q);
    }
}
                       