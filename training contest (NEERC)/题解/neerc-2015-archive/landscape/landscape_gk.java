import java.io.*;
import java.util.Arrays;
import java.util.Locale;
import java.util.StringTokenizer;

public class landscape_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int w = in.nextInt();
        long n = in.nextLong();

        int[] h = new int[w];
        for (int i = 0; i < w; i++) {
            h[i] = in.nextInt();
        }

        out.println(solve(n, h));
    }

    int solve(long n, int[] h) {
        int[] rh = new int[h.length];
        for (int i = 0; i < h.length; i++) {
            rh[h.length - i - 1] = h[i];
        }

        long[] sums = new long[h.length];
        long sum = 0;
        for (int i = 0; i < sums.length; i++) {
            sum += h[i];
            sums[i] = sum;
        }

        int max = Arrays.stream(h).max().getAsInt();
        int r = max;
        int l = (int) Math.min(Integer.MAX_VALUE / 2, max + n);
        while (r < l - 1) {
            int y = (l + r) / 2;
            if (check(n, h, rh, y, sums)) {
                r = y;
            } else {
                l = y;
            }
        }
        return r;
    }

    private boolean check(long n, int[] h, int[] rh, int y, long[] sums) {
        int[] lefts = bounds(h, y);
        int[] rights = bounds(rh, y);
        for (int x = 0; x < h.length; x++) {
            int l = lefts[x];
            int r = h.length - 1 - rights[h.length - 1 - x];

            long dr = r - x - 1;
            long dl = x - 1 - l;
            long volL = dl * (2 * y - 1 - dl) / 2;
            long volR = dr * (2 * y - 1 - dr) / 2;

            if (l >= 0 && r < h.length && volR + volL + y - (sums[r - 1] - sums[l]) <= n) {
                return true;
            }
        }
        return false;
    }

    int[] bounds(int[] h, long y) {
        int[] bounds = new int[h.length];
        int[] queue = new int[h.length];
        int head = 0;
        int tail = 0;
        int bound = -1;
        for (int x = 0; x < h.length; x++) {
            while (tail >= head && h[queue[tail]] - queue[tail] <= h[x] - x) {
                tail--;
            }
            queue[++tail] = x;
            while (h[queue[head]] - queue[head] >= y - x) {
                bound = queue[head];
                head++;
            }
            bounds[x] = bound;
        }
        return bounds;
    }

    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.US);
        in = new Scanner(new File("landscape.in"));
        out = new PrintWriter("landscape.out");

        new landscape_gk().run();

        in.close();
        out.close();
    }

    static class Scanner {
        final BufferedReader reader;
        StringTokenizer tokenizer = new StringTokenizer("");

        public Scanner(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }

        public String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new AssertionError();
                }
            }
            return tokenizer.nextToken();
        }

        public void close() {
        }
    }
}
