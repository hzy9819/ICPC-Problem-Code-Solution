import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * Created by Aksenov239 on 23.11.2015.
 */
public class generators_va {
    public static void main(String[] args) {
        new generators_va().run();
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public void solve() throws IOException {
        int n = nextInt();
        int k = nextInt();

        int total = 0;
        int minus = Integer.MAX_VALUE;
        int mid = -1;
        int mx = 0;
        int[] ans = new int[n];
        for (int i = 0; i < n; i++) {
            int x = nextInt();
            int a = nextInt();
            int b = nextInt();
            int c = nextInt();
            int[] has = new int[c];
            int max = x;
            Arrays.fill(has, -1);
            if (x < c) {
                has[x] = 0;
            }
            for (int j = 0; j < c; j++) {
                x = (a * x + b) % c;
                has[x] = j + 1;
            }

            ans[i] = 0;
            for (int j = c - 1; j >= 0; j--) {
                if (has[j] == -1) {
                    continue;
                }
                if (max < j) {
                    max = j;
                    ans[i] = has[j];
                }
                if ((max - j) % k != 0) {
                    if (minus > max - j) {
                        minus = max - j;
                        mid = i;
                        mx = has[j];
                    }
                }
            }
            total += max;
        }

        if (total % k == 0 && minus != Integer.MAX_VALUE) {
            total -= minus;
            ans[mid] = mx;
        }

        out.println(total % k == 0 ? -1 : total);
        if (total % k != 0) {
            for (int i = 0; i < n; i++) {
                out.print(ans[i] + " ");
            }
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("generators.in"));
            out = new PrintWriter("generators.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
