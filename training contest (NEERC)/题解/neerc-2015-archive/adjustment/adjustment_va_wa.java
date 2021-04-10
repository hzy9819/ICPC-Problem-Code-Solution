import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.HashSet;

/**
 * Created by Aksenov239 on 11.11.2015.
 */
public class adjustment_va_wa {
    public static void main(String[] args) {
        new adjustment_va_wa().run();
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

        long subr = 0;
        int nr = 0;
        long subc = 0;
        int nc = 0;

        for (int i = 0; i < q; i++) {
            long total = 1L * n * (n + 1) / 2;
            if (nextToken().equals("R")) {
                total -= subc;
                int r = nextInt();
//                hr.add(r);
                total += 1L * (n - nc) * r;
                subr += r;
                nr++;
            } else {
                total -= subr;
                int c = nextInt();
                total += 1L * (n - nr) * c;
                subc += c;
                nc++;
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
