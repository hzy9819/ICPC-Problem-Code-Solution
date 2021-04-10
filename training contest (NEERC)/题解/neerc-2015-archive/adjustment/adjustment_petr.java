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
public class adjustment_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("adjustment.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("adjustment.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskA solver = new TaskA();
        solver.solve(1, in, out);
        out.close();
    }

    static class TaskA {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int q = in.nextInt();
            long sumr = n * (long) (n + 1) / 2;
            long sumc = n * (long) (n + 1) / 2;
            int numr = n;
            int numc = n;
            boolean[] rs = new boolean[n];
            boolean[] cs = new boolean[n];
            for (int i = 0; i < q; ++i) {
                String s = in.next();
                int j = in.nextInt();
                --j;
                if (s.equals("R")) {
                    if (rs[j]) {
                        out.println(0);
                        continue;
                    }
                    rs[j] = true;
                    --numr;
                    sumr -= (j + 1);
                    out.println((j + 1) * (long) numc + sumc);
                } else if (s.equals("C")) {
                    if (cs[j]) {
                        out.println(0);
                        continue;
                    }
                    cs[j] = true;
                    --numc;
                    sumc -= (j + 1);
                    out.println((j + 1) * (long) numr + sumr);
                } else throw new RuntimeException();
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

