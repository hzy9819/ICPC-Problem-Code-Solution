import java.io.*;

/**
 * Solution for NEERC'2015 Problem G: Generators.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class generators_re {
    private static final String INPUT = "generators.in";
    private static final String OUTPUT = "generators.out";

    public static final int MAX_N = 10_000;
    public static final int MAX_K = 1_000_000_000;
    public static final int MAX_ABC = 1_000;

    public static void main(String[] args) throws Exception {
        new generators_re().go();
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
    LCG[] g;

    void read(Scanner in) {
        n = in.nextInt();
        k = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= MAX_N;
        assert k >= 1 && k <= MAX_K;
        g = new LCG[n];
        for (int j = 0; j < n; j++) {
            g[j] = new LCG(j, in);
        }
    }

    X[] best;
    int bestSum;

    void solve() {
        best = new X[n];
        int minDelta = Integer.MAX_VALUE;
        X minDeltaX = null;
        for (int j = 0; j < n; j++) {
            LCG g = this.g[j];
            X b1 = new X(g);
            X cur = new X(g);
            for (int i = 1; i <= g.c; i++) {
                cur.step();
                if (cur.x > b1.x) {
                    b1.assign(cur);
                }
            }
            best[j] = b1;
            bestSum += b1.x;
            X b2 = new X(g);
            b2.x = -1;
            b2.i = -1;
            cur = new X(g);
            for (int i = 0; i <= g.c; i++) {
                if ((b1.x - cur.x) % k != 0 && cur.x > b2.x) {
                    b2.assign(cur);
                }
                cur.step();
            }
            if (b2.x >= 0) {
                int delta = b1.x - b2.x;
                if (delta < minDelta) {
                    minDelta = delta;
                    minDeltaX = b2;
                }
            }
        }
        if (bestSum % k == 0 && minDeltaX != null) {
            int j = minDeltaX.g.j;
            bestSum = bestSum - best[j].x + minDeltaX.x;
            best[j] = minDeltaX;
        }
    }

    void write(PrintWriter out) {
        if (bestSum % k == 0) {
            out.println(-1);
            return;
        }
        out.println(bestSum);
        for (int j = 0; j < n; j++) {
            if (j > 0)
                out.print(' ');
            out.print(best[j].i);
        }
        out.println();
    }

    static class LCG {
        final int j;
        final int x0;
        final int a;
        final int b;
        final int c;

        public LCG(int j, Scanner in) {
            this.j = j;
            x0 = in.nextInt();
            a = in.nextInt();
            b = in.nextInt();
            c = in.nextInt();
            in.nextLine();
            assert a >= 0 && a <= MAX_ABC;
            assert b >= 0 && b <= MAX_ABC;
            assert x0 >= 0 && x0 < c && c <= MAX_ABC;
        }
    }

    static class X {
        private final LCG g;
        int x;
        int i;

        public X(LCG g) {
            this.g = g;
            x = g.x0;
        }

        void step() {
            x = (g.a * x + g.b) % g.c;
            i++;
        }

        void assign(X cur) {
            x = cur.x;
            i = cur.i;
        }
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
