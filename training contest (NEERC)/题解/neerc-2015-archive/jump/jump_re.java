import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2015 Problem J: Jump.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class jump_re {
    public static final long SEED = 20152411;
    public static final int MAX_N = 1000;
    public static final boolean DEBUG_LOG = false;

    public static void main(String[] args) throws Exception {
        new jump_re().go();
    }

    PrintWriter log;

    private void log(String x) throws IOException {
        if (log == null)
            log = new PrintWriter(new FileWriter("jump.log"), true);
        log.println(x);
    }

    void go() throws IOException {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out, true);
        interact(in, out);
    }

    int n;

    private void interact(Scanner in, PrintWriter out) throws IOException {
        if (DEBUG_LOG)
            log("-- Started --");
        n = in.nextInt();
        if (DEBUG_LOG)
            log("<< " + n);
        assert n >= 2 && n <= MAX_N && n % 2 == 0;
        boolean[] q = new boolean[n];
        Random rnd = new Random(SEED);
        while (true) {
            for (int i = 0; i < n; i++) {
                q[i] = rnd.nextBoolean();
            }
            int jump = query(in, out, q);
            if (jump == n)
                return;
            if (jump == n / 2)
                break;
        }
        boolean[] s = new boolean[n];
        s[0] = q[0]; // assume q[0] is correct bit
        flip(q, 0); // flip it
        for (int i = 1; i < n; i++) {
            flip(q, i);
            int jump = query(in, out, q);
            flip(q, i);
            if (jump == n)
                return;
            s[i] = q[i] ^ (jump == n / 2);
        }
        if (query(in, out, s) == n)
            return;
        // flip all -- assume q[0] was not correct
        for (int i = 0; i < n; i++) {
            flip(s, i);
        }
        if (query(in, out, s) == n)
            return;
        if (DEBUG_LOG)
            log("Fail");
        throw new AssertionError("Fail");
    }

    private void flip(boolean[] q, int i) {
        q[i] = !q[i];
    }

    private int query(Scanner in, PrintWriter out, boolean[] q) throws IOException {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            sb.append(q[i] ? '1' : '0');
        }
        out.println(sb);
        if (DEBUG_LOG)
            log(">> " + sb);
        in.nextLine();
        int jump = in.nextInt();
        if (DEBUG_LOG)
            log("<< " + jump);
        assert jump == 0 || jump == n / 2 || jump == n;
        return jump;
    }


//----------------- just for validation ------------------

    /**
     * Strict scanner to verify 100% correspondence between input files and input file format specification.
     * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
     * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
     */
    public class Scanner {
        private final BufferedReader in;
        private String line = "";
        private int pos;
        private int lineNo;

        public Scanner(InputStream in) throws FileNotFoundException {
            this.in = new BufferedReader(new InputStreamReader(in));
            nextLine();
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
