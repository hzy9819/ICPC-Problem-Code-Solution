import java.io.*;
import java.util.EnumMap;
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;

/**
 * Solution for NEERC'2015 Problem A: Adjustment Office
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class adjustment_re {
    private static final String INPUT = "adjustment.in";
    private static final String OUTPUT = "adjustment.out";

    public static final int MAX_N = 1_000_000;
    public static final int MAX_Q = 100_000;

    public static void main(String[] args) throws Exception {
        new adjustment_re().go();
    }

    void go() throws IOException {
        long time = System.currentTimeMillis();
        try (Scanner in = new Scanner(new File(INPUT))) {
            in.useLocale(Locale.US);
            read(in);
        }
        solve();
        try (PrintWriter out = new PrintWriter(OUTPUT)) {
            write(out);
        }
        System.out.printf("Done in %d ms%n", System.currentTimeMillis() - time);
    }

    int n;
    int q;
    Query[] qs;

    void read(Scanner in) {
        n = in.nextInt();
        q = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= MAX_N;
        assert q >= 1 && q <= MAX_Q;
        qs = new Query[q];
        for (int i = 0; i < q; i++) {
            qs[i] = new Query(in, n);
        }
    }

    long[] res;

    void solve() {
        EnumMap<Dir, DirInfo> dis = new EnumMap<>(Dir.class);
        for (Dir dir : Dir.values()) {
            dis.put(dir, new DirInfo(n));
        }
        res = new long[q];
        for (int i = 0; i < q; i++) {
            Query q = qs[i];
            DirInfo dd = dis.get(q.dir);
            if (!dd.rem.add(q.num))
                continue;
            dd.sum -= q.num;
            DirInfo df = dis.get(q.dir.flip());
            int k = n - df.rem.size();
            res[i] = (long)q.num * k + df.sum;
        }
    }

    void write(PrintWriter out) {
        for (int i = 0; i < q; i++) {
            out.println(res[i]);
        }
    }

    static class Query {
        Dir dir;
        int num;

        Query(Scanner in, int n) {
            dir = Dir.valueOf(in.next());
            num = in.nextInt();
            in.nextLine();
            assert num >= 1 && num <= n;
        }
    }

    static class DirInfo {
        final Set<Integer> rem = new HashSet<>();
        long sum;

        public DirInfo(int n) {
            sum = (1L + n) * n / 2;
        }
    }

    enum Dir {
        R, C;

        Dir flip() { return this == R ? C : R; }
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
        private boolean localeset;

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

        public double nextDouble() {
            assert localeset : "Locale must be set with useLocale(Locale.US)";
            String s = next();
            assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Double.parseDouble(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }

        public void useLocale(Locale locale) {
            assert locale == Locale.US;
            localeset = true;
        }
    }
}
