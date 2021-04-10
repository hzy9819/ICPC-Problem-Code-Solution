import java.io.*;

/**
 * Solution for NEERC'2015 Problem E: Easy Problemset.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class easy_re {
    private static final String INPUT = "easy.in";
    private static final String OUTPUT = "easy.out";

    public static final int MIN_N = 2;
    public static final int MAX_N = 10;
    public static final int MIN_K = 8;
    public static final int MAX_K = 14;
    public static final int MIN_P = 1;
    public static final int MAX_P = 10;
    public static final int HARD = 50;

    public static void main(String[] args) throws Exception {
        new easy_re().go();
    }

    void go() throws IOException {
        long time = System.currentTimeMillis();
        try (Scanner in = new Scanner(new File(INPUT))) {
            read(in);
        }
        solve();
        try (PrintWriter out = new PrintWriter(OUTPUT)) {
            write(out);
        }
        System.out.printf("Done in %d ms%n", System.currentTimeMillis() - time);
    }

    int n;
    int k;
    int[] p;
    int[][] e;

    void read(Scanner in) {
        n = in.nextInt();
        k = in.nextInt();
        in.nextLine();
        assert n >= MIN_N && n <= MAX_N;
        assert k >= MIN_K && k <= MAX_K;
        p = new int[n];
        e = new int[n][];
        for (int i = 0; i < n; i++) {
            p[i] = in.nextInt();
            assert p[i] >= MIN_P && p[i] <= MAX_P;
            e[i] = new int[p[i]];
            for (int j = 0; j < p[i]; j++) {
                e[i][j] = in.nextInt();
                assert e[i][j] >= 0 && e[i][j] < HARD;
            }
            in.nextLine();
        }
    }

    int total;

    void solve() {
        int proposed = 0;
    rounds:
        for (int round = 0;; round++) {
            boolean allDone = true;
            for (int i = 0; i < n; i++) {
                int cur;
                if (round < p[i]) {
                    allDone = false;
                    cur = e[i][round];
                } else {
                    cur = HARD;
                }
                if (cur >= total) {
                    total += cur;
                    proposed++;
                    if (proposed >= k)
                        break rounds;
                }
            }
            if (allDone)
                break;
        }
        total += (k - proposed) * HARD;
    }

    void write(PrintWriter out) {
        out.println(total);
    }

//----------------- just for validation ------------------

    /**
     * Strict scanner to verify 100% correspondence between input files and input file format specification.
     * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
     * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
     */
    public class Scanner implements Closeable {
        private final BufferedReader in;
        private String line = "";
        private int pos;
        private int lineNo;

        public Scanner(File source) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(source));
            nextLine();
        }

        public void close() {
            assert line == null : "Extra data at the end of file";
            try {
                in.close();
            } catch (IOException e) {
                throw new AssertionError("Failed to close with " + e);
            }
        }

        public void nextLine() {
            assert line != null : "EOF";
            assert pos == line.length() : "Extra characters on line " + lineNo;
            try {
                line = in.readLine();
            } catch (IOException e) {
                throw new AssertionError("Failed to read line with " + e);
            }
            pos = 0;
            lineNo++;
        }

        public String next() {
            assert line != null : "EOF";
            assert line.length() > 0 : "Empty line " + lineNo;
            if (pos == 0)
                assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
            else {
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
                pos++;
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) > ' ' : "Line " + lineNo + " has double whitespace";
            }
            StringBuilder sb = new StringBuilder();
            while (pos < line.length() && line.charAt(pos) > ' ')
                sb.append(line.charAt(pos++));
            return sb.toString();
        }

        public int nextInt() {
            String s = next();
            assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Integer.parseInt(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }
    }
}
