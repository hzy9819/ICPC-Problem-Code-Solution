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
public class landscape_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("landscape.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("landscape.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Landscape solver = new Landscape();
        solver.solve(1, in, out);
        out.close();
    }

    static class Landscape {
        static final long INF = (long) 3e18;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int w = in.nextInt();
            long n = in.nextLong();
            long[] h = new long[w];
            for (int i = 0; i < w; ++i) h[i] = in.nextLong();
            long[] hrev = new long[w];
            for (int i = 0; i < w; ++i) hrev[i] = h[w - 1 - i];
            long maxH = 0;
            for (long hh : h) maxH = Math.max(maxH, hh);
            long left = maxH;
            long right = maxH + ((w - 1) / 2) + 1;
            outer:
            while (right - left > 1) {
                long middle = (left + right) / 2;
                long[] needLeft = getNeed(h, middle);
                long[] needRight = getNeed(hrev, middle);
                for (int i = 0; i < w; ++i) {
                    if (needLeft[i] + needRight[w - 1 - i] - (middle - h[i]) <= n) {
                        left = middle;
                        continue outer;
                    }
                }
                right = middle;
            }
            out.println(left);
        }

        private long[] getNeed(long[] h, long middle) {
            long[] res = new long[h.length];
            long[] psum = new long[h.length + 1];
            for (int i = 0; i < h.length; ++i) psum[i + 1] = psum[i] + h[i];
            int[] stackPos = new int[h.length + 1];
            int sp = 0;
            for (int i = 0; i < h.length; ++i) {
                int left = -1;
                int right = sp;
                while (right - left > 1) {
                    int mid = (left + right) / 2;
                    if (middle - i <= h[stackPos[mid]] - stackPos[mid]) {
                        left = mid;
                    } else {
                        right = mid;
                    }
                }
                if (left >= 0) {
                    int cnt = i - stackPos[left];
                    res[i] = (middle + (middle - cnt + 1)) * cnt / 2;
                    res[i] -= psum[i + 1] - psum[stackPos[left] + 1];
                } else {
                    res[i] = INF;
                }
                while (sp > 0 && h[i] - i > h[stackPos[sp - 1]] - stackPos[sp - 1]) {
                    --sp;
                }
                stackPos[sp] = i;
                ++sp;
            }
            return res;
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

        public long nextLong() {
            return Long.parseLong(next());
        }

    }
}

