import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2015 Problem H: Hypercube.
 * This solution checks correctness of the input.
 *
 * <p>This solution approach is to list all tesseract cells with as a list of number of their vertices,
 * then assign an arbitrary starting cell to an arbitrary cell of octocube, then visit adjacent cells of octocube
 * and check that a corresponding (unique) cell of a tesseract can be assigned to it. This solution involves only
 * 3D rotations of cubic cells.
 *
 * @author Roman Elizarov
 */
public class hypercube_re {
    private static final String INPUT = "hypercube.in";
    private static final String OUTPUT = "hypercube.out";

    private static final boolean DEBUG = true;

    private static final int MAX_DIM = 8;
    private static final int[] ROT = { 1, 3, 0, 2 }; // rotation sequence for a square

    public static void main(String[] args) throws Exception {
        new hypercube_re().go();
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

    int[][] cells;

    private void initTesseractCells() {
        // describe tesseract's cells
        cells = new int[8][8]; // 8 cells of a tesseract, each having 8 points
        for (int dir = 0; dir < 4; dir++) {
            for (int j = 0; j < 2; j++) {
                int[] cell = cells[dir * 2 + j];
                int loMask = (1 << dir) - 1;
                int hiMask = ((1 << (4 - dir)) - 1) << dir;
                for (int k = 0; k < 8; k++) {
                    cell[k] = (k & loMask) | (j << dir) | ((k & hiMask) << 1);
                }
            }
        }
    }

    boolean[] u;
    boolean[][][] v;
    boolean folds;

    void solve() {
        initTesseractCells();
        // visit cells of octocube
        u = new boolean[8]; // used cells
        v = new boolean[m][n][k]; // visited
        boolean found = false;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                for (int z = 0; z < k; z++) {
                    if (v[x][y][z])
                        continue; // already visited this one
                    if (c[x][y][z]) {
                        assert !found : "adjacency graph is not connected";
                        found = true;
                        folds = visit(0, x, y, z, -1, -1, -1);
                        if (!folds)
                            return;
                    }
                }
            }
        }
        assert found;
    }

    private boolean visit(int ci, int x0, int y0, int z0, int px, int py, int pz) {
        assert !v[x0][y0][z0] : "adjacency graph is not a tree";
        v[x0][y0][z0] = true;
        assert !u[ci];
        u[ci] = true; // use this cell
        if (DEBUG)
            System.out.printf("At (%d,%d,%d) cell %d: %s%n", x0, y0, z0, ci, Arrays.toString(cells[ci]));
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
                int cj = findCell(ci, dir, dd);
                if (cj < 0)
                    return false; // no cell remaining that fits
                if (!visit(cj, x1, y1, z1, x0, y0, z0))
                    return false;
            }
        }
        return true;
    }

    private int findCell(int ci, int dir, int dd) {
        int[] side = cellSide(cells[ci], dir, dd);
        for (int cj = 0; cj < 8; cj++) {
            if (!u[cj] && adjacentCellRotate(cj, side, dir, -dd))
                return cj;
        }
        return -1;
    }

    // 4 points the represent cell's side in the given direction
    private int[] cellSide(int[] cell, int dir, int dd) {
        int[] side = new int[4];
        int t = dd < 0 ? 0 : 1;
        for (int k = 0; k < 4; k++) {
            int loMask = (1 << dir) - 1;
            int hiMask = ((1 << (3 - dir)) - 1) << dir;
            side[k] = cell[(k & loMask) | (t << dir) | ((k & hiMask) << 1)];
        }
        return side;
    }

    private boolean adjacentCellRotate(int cj, int[] side, int dir, int dd) {
        int[] cell = cells[cj];
        for (int rd = 0; rd < 2; rd++) { // full cycle of rotation over x and y
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (Arrays.equals(side, cellSide(cell, dir, dd)))
                        return true;
                    flipCell(cell, 2);
                    if (Arrays.equals(side, cellSide(cell, dir, dd)))
                        return true;
                    flipCell(cell, 2);
                    rotateCell(cell, 2);
                }
                rotateCell(cell, rd);
            }
        }
        return false;
    }

    private void rotateCell(int[] cell, int dir) {
        int loMask = (1 << dir) - 1;
        int hiMask = ((1 << (3 - dir)) - 1) << dir;
        for (int t = 0; t < 2; t++) {
            int save = cell[t << dir];
            int i = 0;
            do {
                int from = (i & loMask) | (t << dir) | ((i & hiMask) << 1);
                i = ROT[i];
                int to = (i & loMask) | (t << dir) | ((i & hiMask) << 1);
                cell[from] = i == 0 ? save : cell[to];
            } while (i != 0);
        }
    }

    private void flipCell(int[] cell, int dir) {
        int loMask = (1 << dir) - 1;
        int hiMask = ((1 << (3 - dir)) - 1) << dir;
        for (int t = 0; t < 2; t++) {
            swap(cell, t << dir, (3 & loMask) | (t << dir) | ((3 & hiMask) << 1));
        }
    }

    private void swap(int[] cell, int i, int j) {
        int save = cell[i];
        cell[i] = cell[j];
        cell[j] = save;
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
