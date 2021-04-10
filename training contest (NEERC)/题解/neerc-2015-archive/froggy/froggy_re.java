import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2015 Problem F: Froggy Ford.
 * This solution checks correctness of the input.
 * This solution has O(n^2) asymptotic time complexity.
 *
 * @author Roman Elizarov
 */
public class froggy_re {
    private static final String INPUT = "froggy.in";
    private static final String OUTPUT = "froggy.out";
    public static final int MAX_W = 1_000_000_000;
    public static final int MAX_N = 1000;
    public static final int MAX_ABS_Y = 1_000_000_000;

    public static void main(String[] args) throws Exception {
        new froggy_re().go();
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

    int w;
    int n;
    int[] x;
    int[] y;

    void read(Scanner in) {
        w = in.nextInt();
        n = in.nextInt();
        in.nextLine();
        assert w >= 1 && w <= MAX_W;
        assert n >= 0 && n <= MAX_N;
        x = new int[n + 2];
        y = new int[n + 2];
        for (int i = 1; i <= n; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
            in.nextLine();
            assert x[i] > 0 && x[i] < w;
            assert Math.abs(y[i]) <= MAX_ABS_Y;
        }
    }

    long[] dl;
    long[] dr;
    double xp;
    double yp;

    void solve() {
        x[0] = 0;
        x[n + 1] = w;
        dl = find(0);
        dr = find(n + 1);
        long best = Long.MAX_VALUE;
        for (int u = 0; u < n + 2; u++) {
            for (int v = 0; v < n + 2; v++) {
                long dn = Math.max(4 * Math.max(dl[u], dr[v]), sqrDist(u, v));
                if (dn < best) {
                    best = dn;
                    int xu = x[u];
                    int yu = u >= 1 && u <= n ? y[u] : y[v];
                    int xv = x[v];
                    int yv = v >= 1 && v <= n ? y[v] : y[u];
                    xp = ((double)xu + xv) / 2;
                    yp = ((double)yu + yv) / 2;
                }
            }
        }
    }

    private long[] find(int start) {
        long[] d = new long[n + 2];
        boolean[] f = new boolean[n + 2];
        Arrays.fill(d, Long.MAX_VALUE);
        d[start] = 0;
        for (int i = 0; i < n + 2; i++) {
            int u = -1;
            long best = Long.MAX_VALUE;
            for (int v = 0; v < n + 2; v++) {
                if (!f[v] && d[v] < best) {
                    best = d[v];
                    u = v;
                }
            }
            f[u] = true;
            for (int v = 0; v < n + 2; v++) {
                if (f[v])
                    continue;
                long nd = Math.max(d[u], sqrDist(u, v));
                if (nd < d[v])
                    d[v] = nd;
            }
        }
        return d;
    }

    private long sqrDist(int u, int v) {
        int xu = x[u];
        int yu = u >= 1 && u <= n ? y[u] : y[v];
        int xv = x[v];
        int yv = v >= 1 && v <= n ? y[v] : y[u];
        return sqr(xu - xv) + sqr(yu - yv);
    }

    private long sqr(int x) {
        return (long)x * x;
    }

    void write(PrintWriter out) {
        out.println(xp + " " + yp);
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
