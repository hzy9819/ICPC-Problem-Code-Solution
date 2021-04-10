import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.StringTokenizer;

/**
 * Created by Aksenov239 on 11.11.2015.
 */
public class adjustment_va_n2 {
    public static void main(String[] args) {
        new adjustment_va_n2().run();
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
        int q = nextInt();

        int[][] a = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = i + j + 2;
            }
        }

        for (int i = 0; i < q; i++) {
            long total = 0;
            if (nextToken().equals("R")) {
                int r = nextInt();
                for (int j = 0; j < n; j++) {
                    total += a[r - 1][j];
                    a[r - 1][j] = 0;
                }
            } else {
                int c = nextInt();
                for (int j = 0; j < n; j++) {
                    total += a[j][c - 1];
                    a[j][c - 1] = 0;
                }
            }

            out.println(total);
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("adjustment.in"));
            out = new PrintWriter("adjustment.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
