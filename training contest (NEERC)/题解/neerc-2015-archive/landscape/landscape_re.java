import java.io.*;

/**
 * Solution for NEERC'2015 Problem L: Landscape Improved.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class landscape_re {
    private static final String INPUT = "landscape.in";
    private static final String OUTPUT = "landscape.out";
    public static final int MAX_W = 100_000;
    public static final long MAX_N = 1_000_000_000_000_000_000L;
    public static final int MAX_H = 1_000_000_000;
    public static final long NA = Long.MAX_VALUE;

    public static void main(String[] args) throws Exception {
        new landscape_re().go();
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
        System.out.printf("Done in %d ms with answer %d%n", System.currentTimeMillis() - time, a);
    }

    int w;
    long n;
    int[] h;

    void read(Scanner in) {
        w = in.nextInt();
        n = in.nextLong();
        in.nextLine();
        assert w >= 1 && w <= MAX_W;
        assert n >= 0 && n <= MAX_N;
        h = new int[w];
        for (int i = 0; i < w; i++) {
            h[i] = in.nextInt();
            in.nextLine();
            assert h[i] >= 1 && h[i] <= MAX_H;
        }
    }

    long a;
    long b;

    long[] cl;
    long[] cr;

    void solve() {
        cl = new long[w];
        cr = new long[w];
        for (int i = 0; i < w; i++) {
            a = Math.max(a, h[i]);
        }
        b = a + (long)Math.ceil(2 * Math.sqrt(n + 1)) + 1; // rough estimate for max
        while (a + 1 < b) {
            long m = (a + b) / 2;
            if (count(m) > n) {
                b = m;
            } else {
                a = m;
            }
        }
    }

    private long count(long m) {
        int j = 0;
        long sum = 0;
        for (int i = 0; i < w; i++) {
            while (j < w && m - (j - i) > h[j]) {
                sum += m - (j - i) - h[j];
                j++;
            }
            sum -= m - h[i];
            cr[i] = j < w ? sum : NA;
            sum += j - i - 1;
        }
        j = w - 1;
        sum = 0;
        for (int i = w - 1; i >= 0; i--) {
            while (j >= 0 && m - (i - j) > h[j]) {
                sum += m - (i - j) - h[j];
                j--;
            }
            sum -= m - h[i];
            cl[i] = j >= 0 ? sum : NA;
            sum += i - j - 1;
        }
        long min = NA;
        for (int i = 0; i < w; i++) {
            if (cl[i] == NA || cr[i] == NA)
                continue;
            min = Math.min(min, cl[i] + cr[i] + m - h[i]);
        }
        return min;
    }

    void write(PrintWriter out) {
        out.println(a);
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

        public long nextLong() {
            String s = next();
            assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Long.parseLong(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }
    }
}
