import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.List;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class king_petr_wa {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("king.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("king.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        King solver = new King();
        solver.solve(1, in, out);
        out.close();
    }

    static class King {
        private static final String NOSOLUTION = "There is no route, Karl!";

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            Vertex[] vs = new Vertex[n];
            for (int i = 0; i < n; ++i) {
                vs[i] = new Vertex();
                vs[i].index = i + 1;
            }
            for (int i = 0; i < m; ++i) {
                Vertex a = vs[in.nextInt() - 1];
                Vertex b = vs[in.nextInt() - 1];
                a.outgo.add(b);
            }
            List<Vertex> highDeg = new ArrayList<>();
            for (Vertex v : vs) {
                if (v.outgo.size() == 0) {
                    out.println(NOSOLUTION);
                    return;
                }
                if (v.outgo.size() > 1) {
                    v.isHighDeg = true;
                    highDeg.add(v);
                }
            }
            if (highDeg.isEmpty()) {
                vs[0].isHighDeg = true;
                highDeg.add(vs[0]);
            }
            for (Vertex v : highDeg) {
                v.mark = true;
                for (Vertex vv : v.outgo) {
                    boolean any = false;
                    while (!vv.isHighDeg) {
                        any = true;
                        if (vv.mark) {
                            out.println(NOSOLUTION);
                            return;
                        }
                        vv.mark = true;
                        vv = vv.outgo.get(0);
                    }
                    v.compressed.add(vv);
                    if (any) {
                        if (v.must >= 0) {
                            out.println(NOSOLUTION);
                            return;
                        }
                        v.must = v.compressed.size() - 1;
                    }
                }
            }
            for (Vertex v : vs) {
                if (!v.mark) {
                    out.println(NOSOLUTION);
                    return;
                }
            }
            int ways = 1;
            for (Vertex v : highDeg) {
                if (v.must < 0) {
                    ways *= v.compressed.size();
                }
            }
            outer:
            for (int mask = 0; mask < ways; ++mask) {
                int tmp = mask;
                for (Vertex v : highDeg) {
                    if (v.must < 0) {
                        v.chosen = tmp % v.compressed.size();
                        tmp /= v.compressed.size();
                    } else {
                        v.chosen = v.must;
                    }
                }
                for (Vertex v : highDeg) {
                    v.mark = false;
                }
                Vertex cur = highDeg.get(0);
                while (!cur.mark) {
                    cur.mark = true;
                    cur = cur.compressed.get(cur.chosen);
                }
                if (cur != highDeg.get(0)) {
                    continue;
                }
                for (Vertex v : highDeg) {
                    if (!v.mark) {
                        continue outer;
                    }
                }
                out.print(1);
                cur = vs[0];
                do {
                    if (!cur.isHighDeg) {
                        cur = cur.outgo.get(0);
                    } else {
                        cur = cur.outgo.get(cur.chosen);
                    }
                    out.print(" ");
                    out.print(cur.index);
                } while (cur != vs[0]);
                return;
            }
            out.println(NOSOLUTION);
        }

        static class Vertex {
            int index;
            boolean mark;
            boolean isHighDeg = false;
            List<Vertex> outgo = new ArrayList<>();
            List<Vertex> compressed = new ArrayList<>();
            int must = -1;
            int chosen = -1;

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

