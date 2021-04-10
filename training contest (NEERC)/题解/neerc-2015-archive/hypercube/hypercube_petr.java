import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class hypercube_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("hypercube.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("hypercube.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Hypercube solver = new Hypercube();
        solver.solve(1, in, out);
        out.close();
    }

    static class Hypercube {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int mc = in.nextInt();
            int mb = in.nextInt();
            int ma = in.nextInt();
            String[][] data = new String[ma][mb];
            int total = 0;
            for (int a = 0; a < ma; ++a) {
                for (int b = 0; b < mb; ++b) {
                    data[a][b] = in.next();
                    for (int c = 0; c < mc; ++c) {
                        if (data[a][b].charAt(c) == 'x') ++total;
                    }
                }
            }
            if (total != 8) {
                out.println("No");
                return;
            }
            for (int a = 0; a < ma; ++a)
                for (int b = 0; b < mb; ++b)
                    for (int c = 0; c < mc; ++c)
                        if (data[a][b].charAt(c) == 'x') {
                            boolean[][][][] seen = new boolean[3][3][3][3];
                            boolean[][][] mark = new boolean[ma][mb][mc];
                            int[][] vecs = new int[][]{
                                    new int[]{1, 0, 0, 0},
                                    new int[]{0, 1, 0, 0},
                                    new int[]{0, 0, 1, 0},
                                    new int[]{0, 0, 0, 1},
                            };
                            if (dfs(new int[]{a, b, c}, new int[]{ma, mb, mc}, data, mark, seen, vecs)) {
                                out.println("Yes");
                            } else {
                                out.println("No");
                            }
                            return;
                        }
        }

        private boolean dfs(int[] coords, int[] maxc, String[][] data, boolean[][][] mark, boolean[][][][] seen, int[][] vecs) {
            if (mark[coords[0]][coords[1]][coords[2]]) return true;
            mark[coords[0]][coords[1]][coords[2]] = true;
            if (seen[vecs[3][0] + 1][vecs[3][1] + 1][vecs[3][2] + 1][vecs[3][3] + 1]) return false;
            seen[vecs[3][0] + 1][vecs[3][1] + 1][vecs[3][2] + 1][vecs[3][3] + 1] = true;
            for (int coord = 0; coord < 3; ++coord) {
                for (int delta = -1; delta <= 1; delta += 2) {
                    int[] nc = coords.clone();
                    nc[coord] += delta;
                    if (nc[coord] < 0 || nc[coord] >= maxc[coord]) continue;
                    if (data[nc[0]][nc[1]].charAt(nc[2]) != 'x') continue;
                    int[][] nvecs = vecs.clone();
                    nvecs[3] = mul(delta, vecs[coord]);
                    nvecs[coord] = mul(-delta, vecs[3]);
                    if (!dfs(nc, maxc, data, mark, seen, nvecs)) return false;
                }
            }
            return true;
        }

        private int[] mul(int delta, int[] vec) {
            int[] res = new int[vec.length];
            for (int i = 0; i < vec.length; ++i) res[i] = delta * vec[i];
            return res;
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

