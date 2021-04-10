import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Random;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class jump_mp {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Jump solver = new Jump();
        solver.solve(1, in, out);
        out.close();
    }

    static class Jump {
        public int print(int[] a, InputReader in, PrintWriter out) {
            for (int i = 0; i < a.length; ++i)
                out.print(a[i]);
            out.println();
            out.flush();
            return in.nextInt();
        }

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int[] a = new int[n], b = new int[n];
            boolean[] notGuessed = new boolean[n];
            Random rnd = new Random(111);
            while (true) {
                for (int i = 0; i < n; ++i)
                    a[i] = rnd.nextInt(2);
                int cnt = print(a, in, out);
                if (cnt == n) {
                    return;
                }
                if (cnt == n / 2) {
                    break;
                }
            }
            for (int i = 1; i < n; ++i) {
                a[0] ^= 1;
                a[i] ^= 1;
                int cnt = print(a, in, out);
                if (cnt == n) {
                    return;
                }
                if (cnt == n / 2) {
                    notGuessed[i] = true;
                }
                a[0] ^= 1;
                a[i] ^= 1;
            }
            for (int i = 0; i < n; ++i) {
                b[i] = (notGuessed[i] ? (a[i] ^ 1) : a[i]);
            }
            if (print(b, in, out) != n) {
                for (int i = 0; i < n; ++i)
                    b[i] ^= 1;
                print(b, in, out);
            }
        }

    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }
}

