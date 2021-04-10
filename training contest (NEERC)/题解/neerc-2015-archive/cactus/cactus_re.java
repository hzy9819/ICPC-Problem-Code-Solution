import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2015 Problem C: Cactus Jubilee.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class cactus_re {
    private static final String INPUT = "cactus.in";
    private static final String OUTPUT = "cactus.out";

    private static final int MAX_N = 50000;

    public static void main(String[] args) throws Exception {
        new cactus_re().go();
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
        System.out.printf("Done in %d ms with answer %d%n", System.currentTimeMillis() - time, answer);
    }

    // -------------------------- INPUT --------------------------

    int n;
    int m;

    List<List<Integer>> adj = new ArrayList<>();
    List<Set<Integer>> adjSets = new ArrayList<>(); // for validation only

    private void read(Scanner in) throws FileNotFoundException {
        n = in.nextInt();
        m = in.nextInt();
        in.nextLine();

        assert n >= 1 && n <= MAX_N;
        assert m >= 0 && m <= MAX_N;

        adj.add(null);
        adjSets.add(null);
        for (int i = 1; i <= n; i++) {
            adj.add(new ArrayList<>());
            adjSets.add(new HashSet<>());
        }

        for (int i = 0; i < m; i++) {
            int k = in.nextInt();
            assert k >= 2 && k <= 1000;
            int u = 0;
            for (int j = 0; j < k; j++) {
                int v = in.nextInt();
                assert v >= 1 && v <= n;
                if (u > 0) {
                    assert u != v;
                    add(u, v);
                    add(v, u);
                }
                u = v;
            }
            in.nextLine();
        }
    }

    void add(int a, int b) {
        assert !adjSets.get(a).contains(b);
        adj.get(a).add(b);
        adjSets.get(a).add(b);
    }

    // -------------------------- SOLUTION --------------------------

    // Cycle in Cactus. Bridges are cycles size size==2 (connect only two vertices)
    static class Cycle {
        final List<Vertex> v = new ArrayList<>(); // list of vertices in a cycle, v(0) is up, v(1) is its key in up's next map

        @Override
        public String toString() {
            return v.toString();
        }
    }

    // Vertex in Cactus.
    static class Vertex {
        final int index; // original index
        final Map<Vertex, Cycle> next = new HashMap<>(); // cycles handing at this vertex (keyed by the next vertex)

        // --- dfsBuild state ---
        int num;        // number in dfs order
        Vertex vUp;      // uplink in dfs

        // --- compute at dfsBuild exit ---
        long sizeTotal; // total number of vertices in this subtree
        long sizeBO; // total number of vertices in bridge-only subtree
        long edgeAddCntBO; // number of ways to add an edge to this subtree

        Vertex(int index) {
            this.index = index;
        }

        @Override
        public String toString() {
            return "" + index;
        }
    }

    int curNum;   // current dfs vertex number
    Vertex[] v;   // all vertices
    List<Cycle> cycles = new ArrayList<>(); // all simple cycles
    long sumEdgeAddCntBO;
    long answer;

    private void solve() {
        v = new Vertex[n + 1];
        for (int i = 1; i <= n; i++)
            v[i] = new Vertex(i);
        // start dfs at a vertex 1
        Vertex s = v[1];
        // Build cactus & compute answer for edges that are not on a cycle
        dfsBuild(s);
        // assert connected (all visited)
        for (int i = 1; i <= n; i++)
            assert v[i].num > 0;
        // Push down computed BO sizes & sum them up
        dfsPushDownBO(s, s);
        // Compute answer for all cycles
        for (Cycle c : cycles) {
            long sizeBO = 0;
            long edgeAddCnt = sumEdgeAddCntBO;
            int k = c.v.size();
            for (int i = 0; i < k; i++) {
                Vertex u = c.v.get(i);
                edgeAddCnt += sizeBO * u.sizeBO;
                sizeBO += u.sizeBO;
            }
            answer += (edgeAddCnt - k) * k;
        }
    }

    void dfsBuild(Vertex s) {
        // number new vertex
        s.num = ++curNum;
        // visit all edges
        List<Integer> sAdj = adj.get(s.index);
        for (int tIndex : sAdj) {
            Vertex t = v[tIndex];
            visitBuild(s, t);
        }
        // compute all values at vertex on dfs exit
        s.sizeTotal = 1;
        s.sizeBO = 1;
        for (Cycle c : s.next.values()) {
            int k = c.v.size();
            for (int i = 1; i < k; i++) {
                Vertex t = c.v.get(i);
                s.sizeTotal += t.sizeTotal;
            }
            if (k == 2) {
                // a bridge in the cactus
                Vertex t = c.v.get(1);
                answer += t.sizeTotal * (n - t.sizeTotal) - 1; // can drop this bridge
                s.edgeAddCntBO += t.edgeAddCntBO + s.sizeBO * t.sizeBO - 1;
                s.sizeBO += t.sizeBO;
            } else {
                // a simple cycle in the cactus
                cycles.add(c);
            }
        }
    }

    // visits edge from s to t in dfs
    void visitBuild(Vertex s, Vertex t) {
        if (t.num > 0) {
            // already visited
            if (s.num < t.num)
                return; // already processed
            if (s.vUp == t)
                return; // one back -- skip
            // cycle
            Cycle c = new Cycle();
            Vertex j = s;
            while (j != t) {
                c.v.add(j);
                j = j.vUp;
            }
            c.v.add(t);
            Collections.reverse(c.v);
            // now from t to s
            for (int i = 1; i < c.v.size(); i++) {
                Vertex p = c.v.get(i - 1);
                Vertex q = c.v.get(i);
                Cycle oldC = p.next.remove(q);
                assert oldC.v.size() == 2 : "Cactus -- at most one loop per edge";
            }
            t.next.put(c.v.get(1), c);
            return;
        }
        // store up link
        t.vUp = s;
        // create simple cycle (two vertices)
        Cycle c = new Cycle();
        c.v.add(s);
        c.v.add(t);
        s.next.put(t, c);
        // go inside
        dfsBuild(t);
    }

    private void dfsPushDownBO(Vertex s, Vertex s0) {
        s.sizeBO = s0.sizeBO;
        s.edgeAddCntBO = s0.edgeAddCntBO;
        if (s == s0)
            sumEdgeAddCntBO += s.edgeAddCntBO;
        for (Cycle c : s.next.values()) {
            int k = c.v.size();
            if (k == 2) {
                // a bridge in the cactus
                dfsPushDownBO(c.v.get(1), s0);
            } else {
                // a simple cycle in the cactus
                for (int i = 1; i < k; i++) {
                    Vertex t = c.v.get(i);
                    dfsPushDownBO(t, t);
                }
            }
        }
    }

    // -------------------------- OUTPUT --------------------------

    private void write(PrintWriter out) throws FileNotFoundException {
        out.println(answer);
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
