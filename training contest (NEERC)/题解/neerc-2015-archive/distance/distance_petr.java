import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class distance_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("distance.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("distance.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Distance solver = new Distance();
        solver.solve(1, in, out);
        out.close();
    }

    static class Distance {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            Polygon p = new Polygon();
            p.n = n;
            for (int i = 0; i < n - 3; ++i) {
                int a = in.nextInt() - 1;
                int b = in.nextInt() - 1;
                if (a > b) {
                    int t = a;
                    a = b;
                    b = t;
                }
                p.diagonals.add(new Diagonal(a, b));
            }
            p.prepare();
            int q = in.nextInt();
            for (int qi = 0; qi < q; ++qi) {
                int x = in.nextInt() - 1;
                int y = in.nextInt() - 1;
                out.println(p.getAnswer(x, y));
            }
        }

        class Diagonal {
            int a;
            int b;
            Diagonal nextByA;
            Diagonal nextByB;

            public Diagonal(int a, int b) {
                this.a = a;
                this.b = b;
            }

        }

        class Polygon {
            int n;
            List<Diagonal> diagonals = new ArrayList<>(1);
            Diagonal[] firstByA;
            Diagonal[] firstByB;
            Diagonal mainDiagonal;
            int[] fromA;
            int[] fromB;
            Polygon inside;
            Polygon outside;

            public void prepare() {
                if (diagonals.isEmpty()) {
                    if (n != 3) throw new RuntimeException();
                    return;
                }
                firstByA = new Diagonal[n];
                firstByB = new Diagonal[n];
                for (Diagonal d : diagonals) {
                    d.nextByA = firstByA[d.a];
                    firstByA[d.a] = d;
                    d.nextByB = firstByB[d.b];
                    firstByB[d.b] = d;
                }
                int mainScore = -1;
                for (Diagonal d : diagonals) {
                    int score = d.b - d.a;
                    score = Math.min(score, n - score);
                    if (score > mainScore) {
                        mainScore = score;
                        mainDiagonal = d;
                    }
                }
                fromA = bfs(mainDiagonal.a);
                fromB = bfs(mainDiagonal.b);
                inside = new Polygon();
                outside = new Polygon();
                inside.n = mainDiagonal.b - mainDiagonal.a + 1;
                outside.n = mainDiagonal.a + n - mainDiagonal.b + 1;
                for (Diagonal d : diagonals) {
                    if (d == mainDiagonal) continue;
                    if (d.a >= mainDiagonal.a && d.a <= mainDiagonal.b && d.b >= mainDiagonal.a && d.b <= mainDiagonal.b) {
                        inside.diagonals.add(new Diagonal(d.a - mainDiagonal.a, d.b - mainDiagonal.a));
                    } else {
                        int ea = d.a - mainDiagonal.b;
                        int eb = d.b - mainDiagonal.b;
                        if (ea < 0) ea += n;
                        if (eb < 0) eb += n;
                        if (ea > eb) {
                            int t = ea;
                            ea = eb;
                            eb = t;
                        }
                        outside.diagonals.add(new Diagonal(ea, eb));
                    }
                }
                diagonals.clear();
                inside.prepare();
                outside.prepare();
            }

            private int[] bfs(int start) {
                int[] res = new int[n];
                Arrays.fill(res, -1);
                int[] queue = new int[n];
                int qt = 0;
                int qh = 1;
                res[start] = 0;
                queue[0] = start;
                while (qt < qh) {
                    int cur = queue[qt++];
                    int nxt = (cur + 1) % n;
                    if (res[nxt] < 0) {
                        res[nxt] = res[cur] + 1;
                        queue[qh++] = nxt;
                    }
                    nxt = (cur + n - 1) % n;
                    if (res[nxt] < 0) {
                        res[nxt] = res[cur] + 1;
                        queue[qh++] = nxt;
                    }
                    Diagonal d = firstByA[cur];
                    while (d != null) {
                        if (res[d.b] < 0) {
                            res[d.b] = res[cur] + 1;
                            queue[qh++] = d.b;
                        }
                        d = d.nextByA;
                    }
                    d = firstByB[cur];
                    while (d != null) {
                        if (res[d.a] < 0) {
                            res[d.a] = res[cur] + 1;
                            queue[qh++] = d.a;
                        }
                        d = d.nextByB;
                    }
                }
                return res;
            }

            public int getAnswer(int x, int y) {
                if (x == y) return 0;
                if (mainDiagonal == null) return 1;
                int res = Math.min(fromA[x] + fromA[y], fromB[x] + fromB[y]);
                if (res <= 1) return res;
                if (x >= mainDiagonal.a && x <= mainDiagonal.b && y >= mainDiagonal.a && y <= mainDiagonal.b) {
                    res = Math.min(res, inside.getAnswer(x - mainDiagonal.a, y - mainDiagonal.a));
                }
                if ((x <= mainDiagonal.a || x >= mainDiagonal.b) && (y <= mainDiagonal.a || y >= mainDiagonal.b)) {
                    x -= mainDiagonal.b;
                    y -= mainDiagonal.b;
                    if (x < 0) x += n;
                    if (y < 0) y += n;
                    res = Math.min(res, outside.getAnswer(x, y));
                }
                return res;
            }

        }

    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }
}

