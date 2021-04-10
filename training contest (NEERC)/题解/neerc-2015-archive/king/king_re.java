import java.io.*;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * Solution for NEERC'2015 Problem K: King's Inspection.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class king_re {
    private static final String INPUT = "king.in";
    private static final String OUTPUT = "king.out";
    public static final int MAX_N = 100_000;
    public static final int MAX_DELTA_M = 20;
    public static final int MAX_SPECIAL_COUNT = 2 * MAX_DELTA_M + 1;
    public static final int CAPITAL = 1;
    public static final String NO_ROUTE = "There is no route, Karl!";

    public static void main(String[] args) throws Exception {
        new king_re().go();
    }

    void go() throws IOException {
        long time = System.currentTimeMillis();
        try (Scanner in = new Scanner(new File(INPUT))) {
            read(in);
        }
        solve();
        try (PrintWriter out = new PrintWriter(OUTPUT)) {
            write(out);
        }
        System.out.printf("Done in %d ms%n", System.currentTimeMillis() - time);
    }

    int n;
    int m;
    Edge[] es;

    void read(Scanner in) {
        n = in.nextInt();
        m = in.nextInt();
        in.nextLine();
        assert n >= 2 && n <= MAX_N;
        assert m >= 0 && m <= n + MAX_DELTA_M;
        es = new Edge[m];
        for (int j = 0; j < m; j++) {
            int a = in.nextInt();
            int b = in.nextInt();
            in.nextLine();
            assert a >= 1 && a <= n;
            assert b >= 1 && b <= n;
            es[j] = new Edge(a, b);
        }
    }

    Set<Edge> unique = new HashSet<>();
    int[] ci; // vertex in-degree
    int[] co; // vertex out-degree

    int sc; // no of special vertices
    int[] s; // list of special vertices
    int[] bs; // -1 if not special, or index of special vertex in "s"
    int[] soc; // out-degree of special vertices
    int[][] sol; // outgoing endges list of special vertices

    int[] hop; // shortcut to the end (special vertices) of chains
    boolean found;
    int[] next;

    void solve() {
        // drop multi-edges, loops & count in-out degrees
        ci = new int[n + 1];
        co = new int[n + 1];
        next = new int[n + 1];
        for (int j = 0; j < m; j++) {
            Edge e = es[j];
            if (e.a == e.b || !unique.add(e)) {
                es[j] = null; // drop
                continue; // multi-edge or loop
            }
            co[e.a]++;
            ci[e.b]++;
            next[e.a] = e.b;
        }
        // renumber all special vertices (not in-1, out-1 degree). Capital is considered special, too
        bs = new int[n + 1];
        s = new int[MAX_SPECIAL_COUNT];
        Arrays.fill(bs, -1);
        for (int i = 1; i <= n; i++) {
            if (co[i] == 0 || ci[i] == 0)
                return; // not found
            if (i == CAPITAL || ci[i] > 1 || co[i] > 1) {
                if (sc >= MAX_SPECIAL_COUNT || ci[i] > MAX_DELTA_M || co[i] > MAX_DELTA_M)
                    return; // not found
                int k = sc++;
                s[k] = i;
                bs[i] = k;
            }
        }
        // collect out lists from special vertices
        soc = new int[sc];
        sol = new int[sc][MAX_DELTA_M];
        for (int j = 0; j < m; j++) {
            Edge e = es[j];
            if (e == null)
                continue; // multi-edge or loop
            int k = bs[e.a];
            if (k >= 0)
                sol[k][soc[k]++] = e.b;
        }
        // pick out one path from special vertices when must go there due to in-1 degree of the next vertex
        for (int k = 0; k < sc; k++) {
            int u = s[k];
            if (co[u] == 1)
                continue; // do only for not-trivial number of outs
            int cc = 0;
            for (int t = 0; t < soc[k]; t++) {
                int v = sol[k][t];
                if (ci[v] == 1) {
                    if (cc > 0)
                        return; // not found -> more the one next vertex where "must go to"
                    next[u] = v;
                    co[u] = 1; // update out degree to 1
                    cc++;
                }
            }
            if (co[u] == 1) {
                // made a pick
                soc[k] = 1;
                sol[k][0] = next[u];
            }
        }
        // compute short-cut hops from out-1 vertices to not out-1 vertices
        // also checks if graph is connected starting from capital
        hop = new int[n + 1];
        visitHops(CAPITAL);
        for (int i = 1; i <= n; i++) {
            if (hop[i] == 0)
                return; // not connected
        }
        // start search from a capital
        found = search(CAPITAL, 0, 0);
    }

    private void visitHops(int u) {
        if (hop[u] != 0)
            return; // been there -- done
        int k = bs[u];
        if (k >= 0) {
            // expand from all special points
            hop[u] = u;
            for (int t = 0; t < soc[k]; t++) {
                visitHops(sol[k][t]);
            }
            return;
        }
        // non special point - compute shortcut "hop" to the next special
        int v = u;
        while (bs[v] < 0) {
            v = next[v];
        }
        int fin = v; // finished chain here
        v = u;
        while (bs[v] < 0) {
            hop[v] = fin;
            v = next[v];
        }
        visitHops(fin); // follow from the next special point
    }

    private boolean search(int u, int cnt, long mask) {
        if (cnt >= sc) { // visited all special points
            return u == CAPITAL; // found route when back to capital!
        }
        int k = bs[u];
        assert k >= 0;
        long kb = 1L << k;
        if ((mask & kb) != 0)
            return false; // back to prev visited
        for (int t = 0; t < soc[k]; t++) {
            int v = sol[k][t];
            if (search(hop[v], cnt + 1, mask | kb)) {
                next[u] = v; // store the path that was found
                return true;
            }
        }
        return false;
    }

    void write(PrintWriter out) {
        if (!found) {
            out.println(NO_ROUTE);
            return;
        }
        int cur = 1;
        out.print(1);
        do {
            cur = next[cur];
            out.print(' ');
            out.print(cur);
        } while (cur != 1);
        out.println();
    }

    static class Edge {
        final int a;
        final int b;

        public Edge(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Edge edge = (Edge) o;
            return a == edge.a && b == edge.b;
        }

        @Override
        public int hashCode() {
            int result = a;
            result = 31 * result + b;
            return result;
        }
    }

//----------------- just for validation ------------------

    /**
     * Strict scanner to verify 100% correspondence between input files and input file format specification.
     * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
     * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
     */
    public class Scanner implements Closeable {
        private final BufferedReader in;
        private String line = "";
        private int pos;
        private int lineNo;

        public Scanner(File source) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(source));
            nextLine();
        }

        public void close() {
            assert line == null : "Extra data at the end of file";
            try {
                in.close();
            } catch (IOException e) {
                throw new AssertionError("Failed to close with " + e);
            }
        }

        public void nextLine() {
            assert line != null : "EOF";
            assert pos == line.length() : "Extra characters on line " + lineNo;
            try {
                line = in.readLine();
            } catch (IOException e) {
                throw new AssertionError("Failed to read line with " + e);
            }
            pos = 0;
            lineNo++;
        }

        public String next() {
            assert line != null : "EOF";
            assert line.length() > 0 : "Empty line " + lineNo;
            if (pos == 0)
                assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
            else {
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
                pos++;
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) > ' ' : "Line " + lineNo + " has double whitespace";
            }
            StringBuilder sb = new StringBuilder();
            while (pos < line.length() && line.charAt(pos) > ' ')
                sb.append(line.charAt(pos++));
            return sb.toString();
        }

        public int nextInt() {
            String s = next();
            assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Integer.parseInt(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }
    }
}
