import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;
import java.util.NavigableSet;
import java.util.TreeSet;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem F: Froggy Frog.
 *
 * @author Georgiy Korneev
 */
public class Check implements Checker {
    public static double EPS = 2e-3;
    public static final int MAX_C = 1000_000_000;

    class Edge implements Comparable<Edge> {
        final int v;
        final double l;
        final int len;

        Edge(int v, double l, int len) {
            this.v = v;
            this.l = l;
            this.len = len;
        }

        public int compareTo(Edge that) {
            if (this.l != that.l) {
                return Double.compare(this.l, that.l);
            } else {
                return Integer.compare(this.v, that.v);
            }
        }
    }

    int len;

    double read(double w, int n, double[] x, double[] y, InStream is, Outcome.Type type) {
        len = 0;
        x[n] = is.nextDouble();
        y[n] = is.nextDouble();
        if (!is.seekEoF())
            throw new Outcome(type, "Extra data in output file");

        if (x[n] < -EPS || w + EPS < x[n]) {
            throw new Outcome(WA, String.format(Locale.US, "x = %.3f outside of the river", x[n]));
        }
        if (y[n] < -MAX_C || MAX_C + EPS < y[n]) {
            throw new Outcome(WA, String.format(Locale.US, "y = %.3f outside of allowed range", y[n]));
        }
        
        NavigableSet<Edge> edges = new TreeSet<>();
        for (int i = 0; i <= n; i++) {
            edges.add(new Edge(i, x[i] * x[i], 1));
        }
        double minD = w * w / 4.0;
        double maxD = 0;
        boolean[] u = new boolean[n + 1];
        while (!edges.isEmpty()) {
            Edge e = edges.pollFirst();
            if (u[e.v]) {
                continue;
            }
            if (e.l >= minD) {
                break;
            }
            maxD = Math.max(maxD, e.l);
            if (minD >= (w - x[e.v]) * (w - x[e.v])) {
                minD = (w - x[e.v]) * (w - x[e.v]);
                len = e.len + 1;
            }
            minD = Math.min(minD, (w - x[e.v]) * (w - x[e.v]));

            if (minD <= maxD) {
                break;
            }
            u[e.v] = true;
            for (int j = 0; j <= n; j++) {
                double d = (x[e.v] - x[j]) * (x[e.v] - x[j]) + (y[e.v] - y[j]) * (y[e.v] - y[j]);
                if (!u[j]) {
                    edges.add(new Edge(j, d, e.len + 1));
                }
            }
        }
        return Math.sqrt(Math.max(minD, maxD));
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        double w = inf.nextInt();
        int n = inf.nextInt();
        double[] x = new double[n + 1];
        double[] y = new double[n + 1];
        for (int i = 0; i < n; i++) {
            x[i] = inf.nextInt();
            y[i] = inf.nextInt();
        }

        double ja = read(w, n, x, y, ans, FAIL);
        double pa = read(w, n, x, y, ouf, PE);

        if (Math.abs(ja - pa) <= EPS) {
            return new Outcome(OK, String.format(Locale.US, "%.3f, len = %d", ja, len));
        }
        Outcome.Type type = ja < pa ? WA : FAIL;
        return new Outcome(type, String.format(Locale.US, "Expected %.3f, found %.3f", ja, pa));
    }
}
