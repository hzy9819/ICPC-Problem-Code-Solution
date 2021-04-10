import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.util.stream.Collectors;

/**
 * NEERC'2015 Test generator for problem G: Generators.
 *
 * @author Roman Elizarov
 */
public class Tests {
    static final String TEST_NAME_FORMAT = "%03d";
    static final File LST_FILE = new File("tests/tests.lst");
    static final Random RND = new Random(1);
    public static final int MAX_ABC = 1000;
    public static final int MAX_N = 10_000;
    public static final int MAX_K = 1_000_000_000;
    static int nTests = 0;

    static PrintWriter openTestFile(String desc) throws IOException {
        new File("tests").mkdir();
        PrintWriter out = new PrintWriter(String.format("tests/" + TEST_NAME_FORMAT, ++nTests));
        try (PrintWriter out1 = new PrintWriter(new FileWriter(LST_FILE, true))) {
            out1.printf(TEST_NAME_FORMAT + " %s%n", nTests, desc);
        }
        System.out.printf("Writing test " + TEST_NAME_FORMAT + ": %s%n", nTests, desc);
        return out;
    }

    private static void write(String desc, int n, int k, int... p) throws IOException {
        assert p.length % 4 == 0;
        int m = p.length / 4;
        try (PrintWriter out = openTestFile(desc)) {
            out.println(n + " " + k);
            for (int j = 0; j < n; j++) {
                for (int i = 0; i < 4; i++) {
                    if (i > 0)
                        out.print(' ');
                    int idx = j % m;
                    out.print(p[4 * idx + i]);
                }
                out.println();
            }
        }
    }

    private static void writeRandom(String desc, int n, int k) throws IOException {
        int[] p = new int[4 * n];
        Random rnd = new Random(nTests + 1);
        for (int j = 0; j < n; j++) {
            int c = rnd.nextInt(MAX_ABC) + 1;
            p[4 * j + 0] = rnd.nextInt(c);
            p[4 * j + 1] = rnd.nextInt(MAX_ABC + 1);
            p[4 * j + 2] = rnd.nextInt(MAX_ABC + 1);
            p[4 * j + 3] = c;
        }
        write(desc, n, k, p);
    }

    private static void writeRandomFixC(String desc, int n, int k, int c) throws IOException {
        int[] p = new int[4 * n];
        Random rnd = new Random(nTests + 1);
        for (int j = 0; j < n; j++) {
            p[4 * j + 0] = rnd.nextInt(c);
            p[4 * j + 1] = rnd.nextInt(MAX_ABC + 1);
            p[4 * j + 2] = rnd.nextInt(MAX_ABC + 1);
            p[4 * j + 3] = c;
        }
        write(desc, n, k, p);
    }

    private static void writeRandomExcludeBigK(String desc, int n) throws IOException {
        int[] p = new int[4 * n];
        Random rnd = new Random(nTests + 1);
        int k = 0;
        for (int j = 0; j < n; j++) {
            int c = rnd.nextInt(MAX_ABC) + 1;
            p[4 * j + 0] = rnd.nextInt(c);
            p[4 * j + 1] = rnd.nextInt(MAX_ABC + 1);
            p[4 * j + 2] = rnd.nextInt(MAX_ABC + 1);
            p[4 * j + 3] = c;
            k += maxFromLCG(p[4 * j + 0], p[4 * j + 1], p[4 * j + 2], p[4 * j + 3]);
        }
        write(desc, n, k, p);
    }

    private static int maxFromLCG(int x, int a, int b, int c) {
        int max = 0;
        for (int i = 0; i <= c + 1; i++) {
            max = Math.max(max, x);
            x = (a * x + b) % c;
        }
        return max;

    }

    public static void main(String[] args) throws IOException {
        LST_FILE.delete();
        write("First sample", 2, 3,
                1, 1, 1, 6,
                2, 4, 0, 5
        );
        write("Second sample (all even)", 2, 2,
                0, 7, 2, 8,
                2, 5, 0, 6
        );
        write("First sample, but k=2", 2, 2,
                1, 1, 1, 6,
                2, 4, 0, 5
        );
        write("one LCG: (0)+, k=3", 1, 3,
                0, 5, 7, 7
        );
        write("one LCG: 7,(0)+, k=3", 1, 3,
                7, 0, 0, 8
        );
        write("one LCG: 21,(0)+, k=3", 1, 3,
                21, 0, 0, 22
        );
        write("one LCG: 3,2,(0)+, k=2", 1, 2,
                3, 2, 0, 4
        );
        write("one LCG: 3,2,(0)+, k=3", 1, 3,
                3, 2, 0, 4
        );
        write("one LCG: 5,(0,4,2)+, k=2", 1, 2,
                5, 4, 4, 6
        );
        write("one LCG: 5,(0,4,2)+, k=5", 1, 5,
                5, 4, 4, 6
        );
        write("one LCG: (3,0)+, k=3", 1, 3,
                3, 5, 3, 6
        );
        write("one LCG: (3,0)+, k=6", 1, 6,
                3, 5, 3, 6
        );
        write("two LCGs: (1,5,3)+; (5,1)+, k=2", 2, 2,
                1, 1, 4, 6,
                5, 2, 3, 6
        );
        write("two LCGs: (3,1)+; 11,(4,1)+, k=2", 2, 2,
                3, 4, 4, 5,
                11, 9, 10, 15
        );
        write("two LCGs: (3,1)+; 11,(4,1)+, k=7", 2, 7,
                3, 4, 4, 5,
                11, 9, 10, 15
        );
        write("three LCGs: (4,7,1)+; (7,10,1,4)+; 7,(1)+, k=3", 3, 3,
                4, 1, 3, 9,
                7, 5, 11, 12,
                7, 6, 4, 9
        );
        write("three LCGs: (4,7,1)+; (7,10,1,4)+; 7,(1)+, k=8", 3, 8,
                4, 1, 3, 9,
                7, 5, 11, 12,
                7, 6, 4, 9
        );
        write("four LCGs: (5,9)+; (17,1)+; 13,5,(17)+; (5,13)+, k=4", 4, 4,
                5, 14, 19, 20,
                17, 19, 18, 20,
                13, 12, 11, 18,
                5, 3, 14, 16
        );
        write("four LCGs: (5,9)+; (17,1)+; 13,5,(17)+; (5,13)+, k=7", 4, 7,
                5, 14, 19, 20,
                17, 19, 18, 20,
                13, 12, 11, 18,
                5, 3, 14, 16
        );
        write("four LCGs: 9,(1)+; (17,1)+; 13,5,(17)+; (5,13)+, k=8", 4, 8,
                9, 2, 15, 16,
                17, 19, 18, 20,
                13, 12, 11, 18,
                5, 3, 14, 16
        );
        write("10000 * <0 0 0 1>, k=1", MAX_N, 1,
                0, 0, 0, 1
        );
        write("10000 * <0 0 0 1>, k=10^9", MAX_N, MAX_K,
                0, 0, 0, 1
        );
        write("10000 * <999 1000 1000 1000>, k=10^9", MAX_N, MAX_K,
                MAX_ABC - 1, MAX_ABC, MAX_ABC, MAX_ABC
        );
        write("10000 * <999 1000 1000 1000>, k=10^7", MAX_N, 10_000_000,
                MAX_ABC - 1, MAX_ABC, MAX_ABC, MAX_ABC
        );
        for (int i = 1; i <= 10; i++) {
            writeRandom("Random with k=2", MAX_N, 2);
        }
        for (int i = 1; i <= 10; i++) {
            writeRandom("Random with k=3", MAX_N, 3);
        }
        for (int i = 1; i <= 5; i++) {
            writeRandomFixC("Random with c=997, k=2", MAX_N, 2, 997);
        }
        for (int i = 1; i <= 5; i++) {
            writeRandomFixC("Random with c=997, k=3", MAX_N, 3, 997);
        }
        for (int i = 1; i <= 5; i++) {
            writeRandomExcludeBigK("Random with big k==max sum", MAX_N);
        }
    }
}
