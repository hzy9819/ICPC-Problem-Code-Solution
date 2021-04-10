import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class binary_petr_wa {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("binary.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("binary.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Binary solver = new Binary();
        solver.solve(1, in, out);
        out.close();
    }

    static class Binary {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            outer:
            for (int u = 1; ; ++u) {
                int t = u;
                long p5 = 1;
                long num = 0;
                int pw = 0;
                while (t > 0) {
                    if (t % 2 != 0) {
                        --t;
                        num += p5;
                        if (num % 2 == 0) {
                            continue outer;
                        }
                    }
                    t /= 2;
                    num /= 2;
                    p5 *= 5;
                    ++pw;
                }
                --n;
                if (n == 0) {
                    out.println(Integer.toBinaryString(u));
                    return;
                }
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

