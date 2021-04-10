import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Set;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class cactus_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("cactus.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("cactus.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Cactus solver = new Cactus();
        solver.solve(1, in, out);
        out.close();
    }

    static class Cactus {
        static int nextCycleId = 0;

        void addEdge(Vertex a, Vertex b) {
            Edge ab = new Edge();
            ab.dest = b;
            Edge ba = new Edge();
            ba.dest = a;
            ab.rev = ba;
            ba.rev = ab;
            a.outgo.add(ab);
            b.outgo.add(ba);
        }

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            int ne = 0;
            Vertex[] vs = new Vertex[n];
            for (int i = 0; i < n; ++i) {
                vs[i] = new Vertex();
            }
            for (int i = 0; i < m; ++i) {
                int len = in.nextInt();
                Vertex cur = vs[in.nextInt() - 1];
                for (int j = 1; j < len; ++j) {
                    Vertex nxt = vs[in.nextInt() - 1];
                    addEdge(cur, nxt);
                    ++ne;
                    cur = nxt;
                }
            }
            List<Edge> stack = new ArrayList<>();
            vs[0].dfs(stack);
            long sumInside = 0;
            for (Vertex v : vs)
                if (v.compSize < 0) {
                    List<Vertex> comp = new ArrayList<>();
                    v.dfsComp(comp);
                    for (Vertex vv : comp) vv.compSize = comp.size();
                    sumInside += ((comp.size() - 2) * (long) (comp.size() - 1)) / 2;
                }
            long res = 0;
            for (Vertex v : vs)
                for (Edge e : v.outgo)
                    if (e.cycleId < 0 && e.inTree) {
                        res += e.dest.subtreeSize * (long) (n - e.dest.subtreeSize);
                    }
            List<Set<Vertex>> onCycle = new ArrayList<>();
            for (int i = 0; i < nextCycleId; ++i) onCycle.add(new HashSet<Vertex>());
            for (Vertex v : vs)
                for (Edge e : v.outgo)
                    if (e.cycleId >= 0) {
                        onCycle.get(e.cycleId).add(e.dest);
                    }
            for (Set<Vertex> one : onCycle) {
                long tmp = sumInside;
                long bigComp = 0;
                for (Vertex v : one) {
                    tmp -= (v.compSize - 2) * (long) (v.compSize - 1) / 2;
                    bigComp += v.compSize;
                }
                tmp += (bigComp - 2) * (bigComp - 1) / 2;
                res += one.size() * tmp;
            }
            res -= ne;
            out.println(res);
        }

        static class Edge {
            Edge rev;
            Vertex dest;
            int cycleId = -1;
            boolean inTree;

        }

        static class Vertex {
            List<Edge> outgo = new ArrayList<>();
            int inStack = -1;
            int compSize = -1;
            int subtreeSize = -1;

            public int dfs(List<Edge> stack) {
                if (inStack >= 0) {
                    if (inStack == stack.size() - 2) return 0;
                    for (int i = inStack; i < stack.size(); ++i) {
                        Edge e = stack.get(i);
                        e.cycleId = e.rev.cycleId = nextCycleId;
                    }
                    ++nextCycleId;
                    return 0;
                }
                if (inStack == -2) return 0;
                subtreeSize = 1;
                inStack = stack.size();
                for (Edge e : outgo) {
                    stack.add(e);
                    int r = e.dest.dfs(stack);
                    subtreeSize += r;
                    if (r > 0) e.inTree = true;
                    stack.remove(inStack);
                }
                inStack = -2;
                return subtreeSize;
            }

            public void dfsComp(List<Vertex> comp) {
                if (compSize >= 0) return;
                compSize = 0;
                comp.add(this);
                for (Edge e : outgo) if (e.cycleId < 0) e.dest.dfsComp(comp);
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

