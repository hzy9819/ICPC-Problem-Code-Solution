import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Solution for NEERC'2015 Problem D: Distance on Triangulation.
 * This solution checks correctness of the input.
 * This solution makes preprocessing in O(n log^2 n).
 *
 * @author Roman Elizarov
 */
public class distance_re {
    private static final String INPUT = "distance.in";
    private static final String OUTPUT = "distance.out";

    public static final int MAX_N = 50_000;
    public static final int MAX_Q = 100_000;

    public static void main(String[] args) throws Exception {
        new distance_re().go();
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
    Edge[] e;
    int q;
    int[] x;
    int[] y;
    int[] dist;

    void read(Scanner in) {
        n = in.nextInt();
        in.nextLine();
        assert n >= 4 && n <= MAX_N;
        m = n - 3;
        e = new Edge[m];
        for (int j = 0; j < m; j++) {
            int a = in.nextInt();
            int b = in.nextInt();
            in.nextLine();
            assert a >= 1 && a <= n;
            assert b >= 1 && b <= n;
            assert a != b;
            assert a != b % n + 1;
            assert b != a % n + 1;
            e[j] = new Edge(a - 1, b - 1);
        }
        q = in.nextInt();
        in.nextLine();
        assert q >= 1 && q <= MAX_Q;
        x = new int[q];
        y = new int[q];
        for (int k = 0; k < q; k++) {
            x[k] = in.nextInt();
            y[k] = in.nextInt();
            in.nextLine();
            assert x[k] >= 1 && x[k] <= n;
            assert y[k] >= 1 && y[k] <= n;
        }
    }

    void solve() {
        Task root = new Task(n, Stream.of(e).collect(Collectors.toList()));
        root.make();
        System.out.println("Built task tree of depth " + root.depth);
        dist = new int[q];
        for (int k = 0; k < q; k++) {
            dist[k] = root.query(x[k] - 1, y[k] - 1);
        }
    }

    void write(PrintWriter out) {
        for (int k = 0; k < q; k++) {
            out.println(dist[k]);
        }
    }

    static class Edge {
        int a;
        int b;

        public Edge(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

    static class Task {
        int n;
        List<Edge> edges;

        Task left;  // sub-task for [b1,b2]
        Task right; // sub-task for [b2,b1]
        int b1;
        int b2;
        int[] d1;
        int[] d2;

        int depth; // debug only

        public Task(int n, List<Edge> edges) {
            this.n = n;
            this.edges = edges;
        }

        public void make() {
            int b1 = -1;
            int b2 = -1;
            int bDist = -1;
            for (Edge e : edges) {
                int dist = dist(n, e.a, e.b);
                if (dist > bDist) {
                    b1 = e.a;
                    b2 = e.b;
                    bDist = dist;
                }
            }
            if (bDist < 0) {
                assert n == 3 : "terminal task w/o diagonals must be a triangle";
                return;
            }
            left = makeSubTask(b1, b2);
            right = makeSubTask(b2, b1);
            assert left.edges.size() + right.edges.size() + 1 == edges.size() : "edges do not intersect";
            this.b1 = b1;
            this.b2 = b2;
            left.d1 = left.computeDist(index(n, b1, b2, b1));
            left.d2 = left.computeDist(index(n, b1, b2, b2));
            right.d1 = right.computeDist(index(n, b2, b1, b1));
            right.d2 = right.computeDist(index(n, b2, b1, b2));
            depth = 1 + Math.max(left.depth, right.depth);
        }

        private int[] computeDist(int b) {
            int[] d = new int[n];
            for (int i = 0; i < n; i++) {
                d[i] = query(b, i);
            }
            return d;
        }

        private Task makeSubTask(int b1, int b2) {
            int n2 = b1 < b2 ? b2 - b1 + 1 : n - b1 + b2 + 1;
            List<Edge> e2 = new ArrayList<>(n2);
            boolean seenSplit = false;
            for (Edge e : this.edges) {
                if (e.a == b1 && e.b == b2 || e.a == b2 && e.b == b1) {
                    assert !seenSplit;
                    seenSplit = true;
                    continue;
                }
                int ia = index(n, b1, b2, e.a);
                int ib = index(n, b1, b2, e.b);
                if (ia >= 0 && ib >= 0) {
                    e2.add(new Edge(ia, ib));
                }
            }
            assert seenSplit;
            Task subTask = new Task(n2, e2);
            subTask.make();
            return subTask;
        }

        public int query(int x, int y) {
            assert x >= 0 && x < n;
            assert y >= 0 && y < n;
            if (left == null) {
                assert right == null;
                return dist(n, x, y);
            }
            int xl = index(n, b1, b2, x);
            int xr = index(n, b2, b1, x);
            int yl = index(n, b1, b2, y);
            int yr = index(n, b2, b1, y);
            if (xl >= 0 && xr >= 0 && yl >= 0 && yr >= 0)
                return x == y ? 0 : 1;
            if (xl >= 0 && yl >= 0)
                return left.query(xl, yl);
            if (xr >= 0 && yr >= 0)
                return right.query(xr, yr);
            int dx1;
            int dx2;
            int dy1;
            int dy2;
            if (xl >= 0) {
                assert yr >= 0;
                dx1 = left.d1[xl];
                dx2 = left.d2[xl];
                dy1 = right.d1[yr];
                dy2 = right.d2[yr];
            } else {
                assert xr >= 0;
                assert yl >= 0;
                dx1 = right.d1[xr];
                dx2 = right.d2[xr];
                dy1 = left.d1[yl];
                dy2 = left.d2[yl];
            }
            return Math.min(dx1 + dy1, dx2 + dy2);
        }
    }

    private static int dist(int n, int a, int b) {
        int dist = (b - a + n) % n;
        return Math.min(dist, n - dist);
    }

    private static int index(int n, int b1, int b2, int v) {
        if (v >= b1 && v <= b2)
            return v - b1;
        if (b2 < b1) {
            if (v >= b1)
                return v - b1;
            if (v <= b2)
                return n - b1 + v;
        }
        return -1;
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
