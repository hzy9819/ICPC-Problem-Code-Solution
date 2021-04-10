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
public class king_petr {
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
                v.anyMark = true;
                for (Vertex vv : v.outgo) {
                    for (Vertex vvv : vs) vvv.mark = false;
                    boolean any = false;
                    int cnt = 0;
                    while (!vv.isHighDeg) {
                        if (!any) {
                            vv.isTrickyLowDeg = true;
                        }
                        any = true;
                        if (vv.mark) {
                            out.println(NOSOLUTION);
                            return;
                        }
                        vv.mark = true;
                        vv.anyMark = true;
                        ++cnt;
                        vv = vv.outgo.get(0);
                    }
                    v.compressed.add(vv);
                    v.count.add(cnt);
                }
            }
            for (Vertex v : vs) {
                if (!v.anyMark) {
                    out.println(NOSOLUTION);
                    return;
                }
            }
            List<Vertex> trickyLowDeg = new ArrayList<>();
            for (Vertex v : vs) if (v.isTrickyLowDeg) trickyLowDeg.add(v);
            for (Vertex v : highDeg) {
                for (Vertex vv : v.outgo) {
                    List<Vertex> curCover = new ArrayList<>();
                    while (!vv.isHighDeg) {
                        if (vv.isTrickyLowDeg) {
                            curCover.add(vv);
                        }
                        vv = vv.outgo.get(0);
                    }
                    v.covers.add(curCover);
                }
            }
            int ways = 1;
            for (Vertex v : highDeg) {
                ways *= v.compressed.size();
            }
            outer:
            for (int mask = 0; mask < ways; ++mask) {
                int tmp = mask;
                for (Vertex v : highDeg) {
                    v.chosen = tmp % v.compressed.size();
                    tmp /= v.compressed.size();
                }
                for (Vertex v : highDeg) {
                    v.mark = false;
                }
                for (Vertex v : trickyLowDeg) {
                    v.mark = false;
                }
                Vertex cur = highDeg.get(0);
                int totalV = 0;
                while (!cur.mark) {
                    cur.mark = true;
                    int cnt = cur.count.get(cur.chosen);
                    totalV += 1 + cnt;
                    for (Vertex vvv : cur.covers.get(cur.chosen)) {
                        vvv.mark = true;
                    }
                    cur = cur.compressed.get(cur.chosen);
                }
                if (cur != highDeg.get(0)) {
                    continue;
                }
                if (totalV != n) {
                    continue;
                }
                for (Vertex v : highDeg) {
                    if (!v.mark) {
                        continue outer;
                    }
                }
                for (Vertex v : trickyLowDeg) {
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
            boolean anyMark;
            boolean isHighDeg = false;
            boolean isTrickyLowDeg = false;
            List<Vertex> outgo = new ArrayList<>();
            List<Vertex> compressed = new ArrayList<>();
            List<Integer> count = new ArrayList<>();
            List<List<Vertex>> covers = new ArrayList<>();
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

