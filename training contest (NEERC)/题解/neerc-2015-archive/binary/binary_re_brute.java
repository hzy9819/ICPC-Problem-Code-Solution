import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2015 Problem B: Binary vs. Decimal
 * This is a brute-force solution.
 *
 * @author Roman Elizarov
 */
public class binary_re_brute {
    private static final String INPUT = "binary.in";
    private static final String OUTPUT = "binary.out";

    public static void main(String[] args) throws Exception {
        new binary_re_brute().go();
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

    void read(Scanner in) {
        n = in.nextInt();
    }

    long answer;

    void solve() {
        long[] p = new long[19];
        p[0] = 1;
        for (int i = 1; i < 19; i++) {
            p[i] = p[i - 1] * 10;
        }
        int k = 0;
        for (int i = 1;; i++) {
            long cur = 0;
            int len = 32 - Integer.numberOfLeadingZeros(i);
            for (int j = 0; j < len; j++) {
                if ((i & (1 << j)) != 0) {
                    cur += p[j];
                }
            }
            if ((cur & ((1 << len) - 1)) == i) {
                k++;
                if (k == n) {
                    answer = cur;
                    return;
                }
            }
        }

    }

    void write(PrintWriter out) {
        out.println(answer);
    }
}
