import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

/**
 * Solution for NEERC'2015 Problem B: Binary vs Decimal.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class binary_re {
    private static final String INPUT = "binary.in";
    private static final String OUTPUT = "binary.out";
    public static final int MAX_N = 10_000;

    public static void main(String[] args) throws Exception {
        new binary_re().go();
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

    void read(Scanner in) {
        n = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= MAX_N;
    }

    BigInteger sol;

    void solve() {
        List<BigInteger> cur = new ArrayList<>();
        List<BigInteger> next0 = new ArrayList<>();
        List<BigInteger> next1 = new ArrayList<>();
        cur.add(BigInteger.ZERO);
        BigInteger pow = BigInteger.ONE;
        int num = 0;
        for (int i = 0;; i++) {
            for (BigInteger s : cur) {
                if (!s.testBit(i)) {
                    next0.add(s);
                    BigInteger q = s.add(pow);
                    next1.add(q);
                    if (++num == n) {
                        sol = q;
                        return;
                    }
                }
            }
            cur.clear();
            cur.addAll(next0);
            cur.addAll(next1);
            next0.clear();
            next1.clear();
            pow = pow.multiply(BigInteger.TEN);
        }
    }

    void write(PrintWriter out) {
        out.println(sol);
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
