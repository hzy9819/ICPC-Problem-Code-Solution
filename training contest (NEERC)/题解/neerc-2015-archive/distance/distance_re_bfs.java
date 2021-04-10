import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Solution for NEERC'2015 Problem D: Distance on Triangulation.
 * This solution checks correctness of the input.
 * This solution makes preprocessing in O(n log n).
 *
 * @author Roman Elizarov
 */
public class distance_re_bfs {
    private static final String INPUT = "distance.in";
    private static final String OUTPUT = "distance.out";

    public static final int MAX_N = 50_000;
    public static final int MAX_Q = 100_000;

    public static void main(String[] args) throws Exception {
        new distance_re_bfs().go();
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

    Queue queue;

    void solve() {
        queue = new Queue(n);
        Task root = new Task(n, Stream.of(e).collect(Collectors.toList()));
        root.make(queue);
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
        Edge nextByA;
        Edge nextByB;

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

        // BFS stuff
        Edge[] firstByA;
        Edge[] firstByB;

        int depth; // debug only

        public Task(int n, List<Edge> edges) {
            this.n = n;
            this.edges = edges;
        }

        public void make(Queue queue) {
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
            if (bDist < 0)
                return;
            left = makeSubTask(b1, b2, queue);
            right = makeSubTask(b2, b1, queue);
            assert left.edges.size() + right.edges.size() + 1 == edges.size() : "edges do not intersect";
            this.b1 = b1;
            this.b2 = b2;
            left.d1 = left.computeDist(index(n, b1, b2, b1), queue);
            left.d2 = left.computeDist(index(n, b1, b2, b2), queue);
            right.d1 = right.computeDist(index(n, b2, b1, b1), queue);
            right.d2 = right.computeDist(index(n, b2, b1, b2), queue);
            depth = 1 + Math.max(left.depth, right.depth);
        }

        private int[] computeDist(int b, Queue queue) {
            if (firstByA == null) {
                assert firstByB == null;
                firstByA = new Edge[n];
                firstByB = new Edge[n];
                for (Edge e : edges) {
                    e.nextByA = firstByA[e.a];
                    firstByA[e.a] = e;
                    e.nextByB = firstByB[e.b];
                    firstByB[e.b] = e;
                }
            }
            int[] d = new int[n];
            queue.clear();
            queue.enqueue(b);
            while (!queue.isEmpty()) {
                int u = queue.dequeue();
                int d1 = d[u] + 1;
                expand((u + 1) % n, d1, d, queue);
                expand((u + n - 1) % n, d1, d, queue);
                for (Edge e = firstByA[u]; e != null; e = e.nextByA) {
                    expand(e.b, d1, d, queue);
                }
                for (Edge e = firstByB[u]; e != null; e = e.nextByB) {
                    expand(e.a, d1, d, queue);
                }
            }
            return d;
        }

        private void expand(int u, int d1, int[] d, Queue queue) {
            if (!queue.v[u]) {
                d[u] = d1;
                queue.enqueue(u);
            }
        }

        private Task makeSubTask(int b1, int b2, Queue queue) {
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
            subTask.make(queue);
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

    static class Queue {
        int[] queue;
        boolean[] v;
        int head;
        int tail;

        public Queue(int n) {
            queue = new int[n];
            v = new boolean[n];
        }

        void clear() {
            for (int i = 0; i < tail; i++) {
                v[queue[i]] = false;
            }
            head = 0;
            tail = 0;
        }

        public void enqueue(int b) {
            queue[tail++] = b;
            v[b] = true;
        }

        public boolean isEmpty() {
            return tail == head;
        }

        public int dequeue() {
            return queue[head++];
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
