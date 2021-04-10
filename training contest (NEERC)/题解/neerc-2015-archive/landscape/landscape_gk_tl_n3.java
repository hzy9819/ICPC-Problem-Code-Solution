import java.io.*;
import java.util.*;

public class landscape_gk_tl_n3 {
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
        int maxH = 0;
        for (int y = 1; maxH == y - 1; y++) {
            for (int x = 0; x < h.length; x++) {
                if (h[x] >= y) {
                    maxH = y;
                } else {
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
                        maxH = y;
                    }
                }
            }
        }
        return maxH;
    }

    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.US);
        in = new Scanner(new File("landscape.in"));
        out = new PrintWriter("landscape.out");

        new landscape_gk_tl_n3().run();

        in.close();
        out.close();
    }
}
