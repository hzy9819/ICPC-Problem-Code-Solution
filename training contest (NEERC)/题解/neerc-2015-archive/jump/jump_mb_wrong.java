import java.io.*;
import java.util.*;

public class jump_mb_wrong {
    static int query(boolean[] current, BufferedReader in, PrintWriter out) throws IOException {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < current.length; ++i) {
            sb.append(current[i] ? "0" : "1");
        }
        out.println(sb.toString());
        out.flush();
        int rv = Integer.parseInt(in.readLine());
        return rv;
    }

    public static void main(String[] args) throws IOException {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
             PrintWriter out = new PrintWriter(System.out)) {
            int n = Integer.parseInt(in.readLine());
            Random random = new Random();
            boolean[] current = new boolean[n];
            for (int t = 0; ; ++t) {
                for (int i = 0; i < n; ++i) {
                    current[i] = i < t;
                }
                int f = query(current, in, out);
                if (f == n) {
                    return;
                }
                if (f == n / 2) {
                    break;
                }
            }
            boolean[] guess = current.clone();
            current[0] ^= true;
            for (int i = 1; i < n; ++i) {
                current[i] ^= true;
                int f = query(current, in, out);
                if (f == n) {
                    return;
                }
                guess[i] ^= f == n / 2;
                current[i] ^= true;
            }
            if (query(guess, in, out) == n) {
                return;
            }
            for (int i = 0; i < n; ++i) {
                guess[i] ^= true;
            }
            if (query(guess, in, out) == n) {
                return;
            }
            throw new AssertionError("Should not be there");
        }
    }
}
