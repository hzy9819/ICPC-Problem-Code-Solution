import java.io.OutputStream;
import java.util.Locale;
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
public class froggy_mp {
    public static void main(String[] args) {
        Locale.setDefault(Locale.US);
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("froggy.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("froggy.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Froggy solver = new Froggy();
        solver.solve(1, in, out);
        out.close();
    }

    static class Froggy {
        final int MAX_IT = 50;
        final double eps = 1e-8;
        int[] x;
        int[] y;
        double[] resultPair;
        double[][] d;
        int w;
        int n;
        boolean[] used_start;
        boolean[] used_finish;

        void dfs(int v, double q, boolean[] used) {
            if (used[v]) return;
            used[v] = true;
            for (int i = 0; i < n; ++i)
                if (d[v][i] < q + eps)
                    dfs(i, q, used);
        }

        boolean check(double q) {
            if (q > w - eps) {
                return true;
            }
            for (int i = 0; i < n; ++i) {
                used_start[i] = false;
                used_finish[i] = false;
            }
            for (int i = 0; i < n; ++i) {
                if (x[i] < q + eps) {
                    dfs(i, q, used_start);
                }
                if (x[i] > w - q - eps) {
                    dfs(i, q, used_finish);
                }
            }
            for (int i = 0; i < n; ++i)
                if (used_start[i] && used_finish[i])
                    return true;
            for (int i = 0; i < n; ++i)
                if (used_start[i])
                    for (int j = 0; j < n; ++j)
                        if (used_finish[j] && (d[i][j] < 2 * q + eps)) {
                            resultPair[0] = (x[i] + x[j]) / 2.0;
                            resultPair[1] = (y[i] + y[j]) / 2.0;
                            return true;
                        }
            for (int i = 0; i < n; ++i) {
                if (used_start[i] && (x[i] > w - 2 * q - eps)) {
                    resultPair[0] = (x[i] + w) / 2.0;
                    resultPair[1] = y[i];
                    return true;
                }
                if (used_finish[i] && (x[i] < 2 * q + eps)) {
                    resultPair[0] = (x[i] + 0) / 2.0;
                    resultPair[1] = y[i];
                    return true;
                }
            }
            return false;
        }

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            w = in.nextInt();
            n = in.nextInt();
            x = new int[n];
            y = new int[n];
            d = new double[n][n];
            used_start = new boolean[n];
            used_finish = new boolean[n];
            resultPair = new double[2];
            for (int i = 0; i < n; ++i) {
                x[i] = in.nextInt();
                y[i] = in.nextInt();
            }
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    d[i][j] = hypot(x[i] - x[j], y[i] - y[j]);
            double l = 0, r = w;
            for (int it = 0; it < MAX_IT; ++it) {
                double q = (l + r) / 2;
                if (check(q))
                    r = q;
                else
                    l = q;
            }
            check((l + r) / 2);
            out.printf("%.10f %.10f\n", resultPair[0], resultPair[1]);
        }

        private double hypot(double x, double y) {
            return Math.sqrt(x * x + y * y);
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

