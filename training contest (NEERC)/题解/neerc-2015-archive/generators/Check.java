import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.*;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem G: Generators.
 *
 * @author Roman Elizarov
 */
public class Check implements Checker {
    private static final int MAX_T = 1_000_000_000;

    static class LCG {
        final int x0;
        final int a;
        final int b;
        final int c;

        final int[] x;
        final int cs;
        final int cl;

        public LCG(InStream in) {
            x0 = in.nextInt();
            a = in.nextInt();
            b = in.nextInt();
            c = in.nextInt();
            Map<Integer, Integer> seen = new HashMap<>();
            x = new int[c + 2];
            x[0] = x0;
            seen.put(x0, 0);
            int cs = -1;
            int cl = -1;
            for (int i = 1; i <= c + 1; i++) {
                x[i] = (x[i - 1] * a + b) % c;
                Integer prev = seen.put(x[i], i);
                if (prev != null) {
                    cs = prev;
                    cl = i - cs;
                    break;
                }
            }
            assert cs >= 0;
            this.cs = cs;
            this.cl = cl;
        }

        public int get(int i) {
            if (i < cs)
                return x[i];
            return x[(i - cs) % cl + cs];
        }
    }

    int n;
    int k;
    LCG[] g;

    private void readInput(InStream in) {
        n = in.nextInt();
        k = in.nextInt();
        g = new LCG[n];
        for (int j = 0; j < n; j++) {
            g[j] = new LCG(in);
        }
    }

    private long readOut(InStream ouf, Outcome.Type wa, Outcome.Type pe) {
        long s = ouf.nextLong();
        if (s < 0 && s != -1)
            throw new Outcome(pe, "Invalid number s=" + s);
        if (s >= 0) {
            int[] t = new int[n];
            long realSum = 0;
            for (int j = 0; j < n; j++) {
                t[j] = ouf.nextInt();
                if (t[j] < 0 || t[j] > MAX_T)
                    throw new Outcome(wa, String.format(Locale.US, "Invalid t[%d]=%d", j + 1, t[j]));
                realSum += g[j].get(t[j]);
            }
            if (realSum != s)
                throw new Outcome(wa, String.format(Locale.US, "Real sum %d != reported sum %d", realSum, s));
            if (s % k == 0)
                throw new Outcome(wa, String.format(Locale.US, "Sum %d %% %d == 0", s, k));
        }
        if (!ouf.seekEoF())
            throw new Outcome(pe, "Extra data in output file");
        return s;
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        readInput(inf);
        long ja = readOut(ans, FAIL, FAIL);
        long pa = readOut(ouf, WA, PE);
        if (pa > ja)
            return new Outcome(FAIL, String.format(Locale.US, "Found better solution %d, but jury was %d", pa, ja));
        if (pa != ja)
            return new Outcome(WA, String.format(Locale.US, "Expected %d, found %d", ja, pa));
        return new Outcome(OK, String.format(Locale.US, "s=%d, k=%d", pa, k));
    }
}
