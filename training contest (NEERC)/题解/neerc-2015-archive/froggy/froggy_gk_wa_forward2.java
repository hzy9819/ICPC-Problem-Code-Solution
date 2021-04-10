import java.io.File;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.NavigableSet;
import java.util.Scanner;
import java.util.TreeSet;

public class froggy_gk_wa_forward2 {
    static Scanner in;
    static PrintWriter out;

    class Edge implements Comparable<Edge> {
        final int side, v;
        final long l;

        Edge(int side, int v, long l) {
            this.side = side;
            this.v = v;
            this.l = l;
        }

        public int compareTo(Edge that) {
            if (this.l != that.l) {
                return Long.compare(this.l, that.l);
            } else if (this.side < that.side) {
                return Integer.compare(this.side, that.side);
            } else {
                return Integer.compare(this.v, that.v);
            }
        }
    }

    void run() {
        int w = in.nextInt();
        int n = in.nextInt();

        if (n == 0) {
            out.format("%.2f %.2f", w / 2.0, 0.0);
            out.println();
            return;
        }

        long[] x = new long[n];
        long[] y = new long[n];
        for (int i = 0; i < n; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
        }

        NavigableSet<Edge> edges = new TreeSet<Edge>();
        for (int i = 0; i < n; i++) {
            edges.add(new Edge(-1, i, x[i] * x[i]));
            edges.add(new Edge(1, i, (w - x[i]) * (w - x[i])));
        }

        int[] side = new int[n];
        double minX = Double.NaN, minY = Double.NaN;
        long minD = Long.MAX_VALUE;
        while (!edges.isEmpty()) {
            Edge e = edges.pollFirst();
            if (side[e.v] == e.side) {
                continue;
            }
            if (minD <= e.l * 4) {
                break;
            }
            assert side[e.v] == 0;
            side[e.v] = e.side;
            long dx = e.side == -1 ? w - x[e.v] : -x[e.v];
            if (minD > dx * dx) {
                minD = dx * dx;
                minX = x[e.v] + dx / 2.0;
                minY = y[e.v];
            }
            for (int j = 0; j < n; j++) {
                long d = (x[e.v] - x[j]) * (x[e.v] - x[j]) + (y[e.v] - y[j]) * (y[e.v] - y[j]);
                if (side[j] == 0) {
                    edges.add(new Edge(e.side, j, d));
                } else if (side[j] == -e.side && minD > d && (x[e.v] - x[j]) * side[e.v] >= 0) {
                    minD = d;
                    minX = (x[e.v] + x[j]) / 2.0;
                    minY = (y[e.v] + y[j]) / 2.0;
                }
            }
        }
        out.format("%.1f %.1f", minX, minY);
        out.println();
    }

    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.US);
        in = new Scanner(new File("froggy.in"));
        out = new PrintWriter("froggy.out");

        new froggy_gk_wa_forward2().run();

        in.close();
        out.close();
    }
}
