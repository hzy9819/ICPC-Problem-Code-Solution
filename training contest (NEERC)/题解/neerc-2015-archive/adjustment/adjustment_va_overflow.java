import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.HashSet;

/**
 * Created by Aksenov239 on 11.11.2015.
 */
public class adjustment_va_overflow {
    public static void main(String[] args) {
        new adjustment_va_overflow().run();
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

        int subr = 0;
        int nr = 0;
        int subc = 0;
        int nc = 0;

        HashSet<Integer> hr = new HashSet<Integer>();
        HashSet<Integer> hc = new HashSet<Integer>();

        for (int i = 0; i < q; i++) {
            int total = n * (n + 1) / 2;
            if (nextToken().equals("R")) {
                total -= subc;
                int r = nextInt();
                if (hr.contains(r)) {
                    out.println(0);
                    continue;
                }
                hr.add(r);
                total += (n - nc) * r;
                subr += r;
                nr++;
            } else {
                total -= subr;
                int c = nextInt();
                if (hc.contains(c)) {
                    out.println(0);
                    continue;
                }
                hc.add(c);
                total += (n - nr) * c;
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
