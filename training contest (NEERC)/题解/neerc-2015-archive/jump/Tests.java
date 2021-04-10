import java.io.*;
import java.util.*;

public class Tests {
    private static final int MAX_N = 1000;
    private static final int N_INCREMENT = 500;
    private static int testNumber = 0;

    private static final String path = "tests/";

    static Random rnd = new Random(2373);

    static void writeTest(String test) throws IOException {
        try (PrintWriter out = new PrintWriter(String.format("%s%03d", path, ++testNumber))) {
            int n = test.length();
            out.println(n);
            out.println(test);
            out.println(n + N_INCREMENT);
            out.println(n);
        }
    }

    static String randomString(int n, double prob) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; ++i) {
            sb.append(rnd.nextDouble() < prob ? "1" : "0");
        }
        return sb.toString();
    }

    static void writeTestGroup(int n) throws IOException {
        writeTest(randomString(n, 0));
        writeTest(randomString(n, 1));
        writeTest(randomString(n, 0.5));
        writeTest(randomString(n, 1.0 / 3.0));
        writeTest(randomString(n, 2.0 / 3.0));
    }

    static void rmrf(File file) {
        if (file.isDirectory()) {
            File[] children = file.listFiles();
            if (children != null) {
                for (File f : children) {
                    rmrf(f);
                }
            }
        }
        file.delete();
    }

    public static void main(String[] args) throws IOException {
        File root = new File(path);
        rmrf(root);
        root.mkdir();

        int[] tests = new int[25];
        tests[0] = 2;
        tests[1] = 2;
        tests[2] = tests[3] = tests[4] = MAX_N & ~1;
        for (int i = 0; i < 10; ++i) {
            tests[i + 5] = (rnd.nextInt(MAX_N / 20) + 2) & ~1;
        }
        for (int i = 0; i < 10; ++i) {
            tests[i + 15] = (rnd.nextInt(MAX_N) + 2) & ~1;
        }
        Arrays.sort(tests);
        for (int i : tests) {
            writeTestGroup(i);
        }
    }
}
