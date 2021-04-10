import java.io.*;
import java.util.Arrays;

/**
 * Solution for NEERC'2015 Problem H: Hypercube.
 * This solution checks correctness of the input.
 *
 * <p>This solution approach is keep track of three 4D unit vectors that define the hyperspace that
 * a cell lies and it a 4th vector -- a cell normal, that uniquely identifies it.
 * Rotations are performed in 4D.
 *
 * @author Roman Elizarov
 */
public class hypercube_re_4d {
    private static final String INPUT = "hypercube.in";
    private static final String OUTPUT = "hypercube.out";

    private static final boolean DEBUG = true;

    private static final int MAX_DIM = 8;

    public static void main(String[] args) throws Exception {
        new hypercube_re_4d().go();
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

    int m;
    int n;
    int k;
    boolean[][][] c;

    void read(Scanner in) {
        m = in.nextInt();
        n = in.nextInt();
        k = in.nextInt();
        in.nextLine();
        assert m >= 1 && m <= MAX_DIM;
        assert n >= 1 && n <= MAX_DIM;
        assert k >= 1 && k <= MAX_DIM;
        c = new boolean[m][n][k];
        int xCnt = 0;
        for (int z = 0; z < k; z++) {
            for (int y = 0; y < n; y++) {
                String s = in.next();
                in.nextLine();
                assert s.length() == m;
                for (int x = 0; x < m; x++) {
                    switch (s.charAt(x)) {
                        case '.':
                            break;
                        case 'x':
                            c[x][y][z] = true;
                            xCnt++;
                            break;
                        default: assert false : "Invalid char in line '" + s + "'";
                    }
                }
            }
        }
        assert xCnt == 8 : "Invalid number of cubes: " + xCnt;
    }

    boolean[] u;
    boolean[][][] v;
    boolean folds;

    void solve() {
        // visit cells of octocube
        u = new boolean[8]; // used cells
        v = new boolean[m][n][k]; // visited
        boolean found = false;
        int[][] vec = new int[4][4];
        // vec[0],vec[1],vec[2] -- cell space, vec[3] -- normal
        for (int i = 0; i < 4; i++)
            vec[i][i] = 1; // start with 4 unit vectors
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                for (int z = 0; z < k; z++) {
                    if (v[x][y][z])
                        continue; // already visited this one
                    if (c[x][y][z]) {
                        assert !found : "adjacency graph is not connected";
                        found = true;
                        folds = visit(vec, x, y, z, -1, -1, -1);
                        if (!folds)
                            return;
                    }
                }
            }
        }
        assert found;
    }

    private boolean visit(int[][] vec, int x0, int y0, int z0, int px, int py, int pz) {
        assert !v[x0][y0][z0] : "adjacency graph is not a tree";
        v[x0][y0][z0] = true;
        // use cell's normal vec[3] to figure out its "index" (number) among 8 cells
        int ci = cellIndex(vec[3]);
        assert !u[ci];
        u[ci] = true; // use this cell
        if (DEBUG)
            System.out.printf("At (%d,%d,%d) cell %d: %s%n", x0, y0, z0, ci, Arrays.toString(vec[3]));
        for (int dir = 0; dir < 3; dir++) {
            for (int dd = -1; dd <= 1; dd += 2) {
                int[] cur = { x0, y0, z0 };
                cur[dir] += dd;
                int x1 = cur[0];
                int y1 = cur[1];
                int z1 = cur[2];
                if (x1 == px && y1 == py && z1 == pz)
                    continue; // no going back
                if (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n || z1 < 0 || z1 >= k)
                    continue; // outside of box
                if (!c[x1][y1][z1])
                    continue; // no cube here
                // 4D-rotate into the next cell
                int[][] vec2 = new int[4][];
                for (int i = 0; i < 4; i++)
                    vec2[i] = vec[i].clone();
                vec2[3] = mul(vec[dir], dd); // direction we went to is the new normal
                vec2[dir] =mul(vec[3], -dd); // make sure it's a proper 4D rotations
                int cj = cellIndex(vec2[3]);
                if (u[cj])
                    return false; // the corresponding cell was already visited
                if (!visit(vec2, x1, y1, z1, x0, y0, z0))
                    return false;
            }
        }
        return true;
    }

    private int[] mul(int[] a, int dd) {
        int[] b = new int[4];
        for (int i = 0; i < 4; i++) {
            b[i] = a[i] * dd;
        }
        return b;
    }

    // convert cell's normal to its index from 0 to 7
    private int cellIndex(int[] normal) {
        int ci = 0;
        for (int i = 0; i < 4; i++)
            if (normal[i] != 0)
                ci = 2 * i + (normal[i] > 0 ? 1 : 0);
        return ci;
    }

    void write(PrintWriter out) {
        String answer = folds ? "Yes" : "No";
        if (DEBUG)
            System.out.println(answer);
        out.print(answer);
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
