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
public class generators_mp {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("generators.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("generators.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Generators solver = new Generators();
        solver.solve(1, in, out);
        out.close();
    }

    static class Generators {
        final int LIMIT = 1111;
        int[] x = new int[LIMIT];

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt(), k = in.nextInt(), sum = 0, lose = Integer.MAX_VALUE, losepos = -1;
            int[] mx = new int[n];
            int[] mxpos = new int[n];
            int[] smx = new int[n];
            int[] smxpos = new int[n];
            for (int i = 0; i < n; ++i) {
                int x0 = in.nextInt(), a = in.nextInt(), b = in.nextInt(), c = in.nextInt();
                x[0] = x0;
                for (int j = 0; j + 1 < LIMIT; ++j) {
                    x[j + 1] = (a * x[j] + b) % c;
                }
                mx[i] = x[0];
                mxpos[i] = 0;
                for (int j = 0; j < LIMIT; ++j) {
                    if (x[j] > mx[i]) {
                        mx[i] = x[j];
                        mxpos[i] = j;
                    }
                }
                smx[i] = -1;
                smxpos[i] = -1;
                for (int j = 0; j < LIMIT; ++j) {
                    if ((x[j] % k != mx[i] % k) && (x[j] > smx[i])) {
                        smx[i] = x[j];
                        smxpos[i] = j;
                    }
                }
                if ((smx[i] != -1) && (lose > mx[i] - smx[i])) {
                    lose = mx[i] - smx[i];
                    losepos = i;
                }
                sum += mx[i];
            }
            if ((sum % k == 0) && (lose == Integer.MAX_VALUE)) {
                out.println(-1);
            } else {
                if (sum % k != 0) {
                    lose = 0;
                    losepos = -1;
                }
                out.println(sum - lose);
                for (int i = 0; i < n; ++i) {
                    if (i == losepos) {
                        out.print(smxpos[i]);
                    } else {
                        out.print(mxpos[i]);
                    }
                    out.print(" ");
                }
                out.println();
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

