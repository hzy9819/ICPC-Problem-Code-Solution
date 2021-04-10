import java.io.File;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;
import java.util.Scanner;

public class landscape_gk_tl_n2logn {
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
        int max = Arrays.stream(h).max().getAsInt();
        int r = max;
        int l = (int) Math.min(Integer.MAX_VALUE / 2, max + n);
        while (r < l - 1) {
            int y = (l + r) / 2;
            if (check(n, h, y)) {
                r = y;
            } else {
                l = y;
            }
        }
        return r;
    }

    private boolean check(long n, int[] h, int y) {
        for (int x = 0; x < h.length; x++) {
            long required = y - h[x];
            boolean foundR = false;
            for (int i = 1; x + i < h.length; i++) {
                if (h[x + i] >= y - i) {
                    foundR = true;
                    break;
                } else {
                    required += y - i - h[x + i];
                }
            }
            boolean foundL = false;
            for (int i = 1; 0 <= x - i; i++) {
                if (h[x - i] >= y - i) {
                    foundL = true;
                    break;
                } else {
                    required += y - i - h[x - i];
                }
            }
            if (foundL && foundR && required <= n) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.US);
        in = new Scanner(new File("landscape.in"));
        out = new PrintWriter("landscape.out");

        new landscape_gk_tl_n2logn().run();

        in.close();
        out.close();
    }
}
