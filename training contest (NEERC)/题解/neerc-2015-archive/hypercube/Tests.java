import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.util.stream.Collectors;

/**
 * NEERC'2015 Test generator for problem H: Hypercube.
 *
 * @author Roman Elizarov
 */
public class Tests {
    static final String TEST_NAME_FORMAT = "%03d";
    static final File LST_FILE = new File("tests/tests.lst");
    static final Random RND = new Random(1);
    static int nTests = 0;

    static final Set<TestCase> allTestCases = new HashSet<>();

    private static final int[] ROT = { 1, 3, 0, 2 }; // rotation sequence for a square
    static final int MAX_DIM = 8;

    static PrintWriter openTestFile(String desc) throws IOException {
        new File("tests").mkdir();
        PrintWriter out = new PrintWriter(String.format("tests/" + TEST_NAME_FORMAT, ++nTests));
        try (PrintWriter out1 = new PrintWriter(new FileWriter(LST_FILE, true))) {
            out1.printf(TEST_NAME_FORMAT + " %s%n", nTests, desc);
        }
        System.out.printf("Writing test " + TEST_NAME_FORMAT + ": %s%n", nTests, desc);
        return out;
    }

    private static void write0(String desc, String[][] t) throws IOException {
        try (PrintWriter out = openTestFile(desc)) {
            int m = t[0][0].length();
            int n = t[0].length;
            int k = t.length;
            out.printf("%d %d %d%n", m, n, k);
            for (int z = 0; z < k; z++) {
                for (int y = 0; y < n; y++) {
                    assert t[z][y].length() == m;
                    out.println(t[z][y]);
                }
            }
        }
    }

    static void write(String desc, String[][] t) throws IOException {
        allTestCases.add(new TestCase(t));
        write0(desc, t);
    }

    private static boolean writeRandom(String tree, boolean foldable) throws IOException {
        long seed = nTests + 1;
        Builder builder = new Builder(seed, foldable);
        if (!buildTree(0, tree, builder))
            return false; // no more cases of this type
        allTestCases.add(new TestCase(builder.octocube.convertToTestCase(null)));
        write0("Random tree " + tree + ", seed=" + seed + (foldable ? ", foldable" : ""),
                builder.octocube.convertToTestCase(builder.rnd));
        return true;
    }

    private static boolean buildTree(int moveNo, String tree, Builder builder) {
        if (moveNo > 6) {
            String[][] t = builder.octocube.convertToTestCase(null);
            return !allTestCases.contains(new TestCase(t));
        }
        Move parent = builder.getMove(tree.charAt(moveNo) - '0');
        int d0 = builder.rnd.nextInt(6);
        for (int di = 0; di < 6; di++) {
            if (builder.tryMove(d0 + di, parent)) {
                if (buildTree(moveNo + 1, tree, builder))
                    return true;
                builder.popMove();
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        LST_FILE.delete();

        write("First sample", new String[][]{
                {"...", ".x.", "..."},
                {".x.", "xxx", ".x."},
                {"...", ".x.", "..."},
                {"...", ".x.", "..."},
        });

        write("Second sample", new String[][]{
                {"xxxxxxxx"},
        });

        write("Vertical sample", new String[][]{
                {"x"}, {"x"}, {"x"}, {"x"}, {"x"}, {"x"}, {"x"}, {"x"}
        });

        write("Deep sample", new String[][]{
                {"x", "x", "x", "x", "x", "x", "x", "x"},
        });

        // generate more chains
        for (int i = 0; i < 16; i++) {
            boolean ok = writeRandom("0123456", false);
            assert ok; // lots of different chains can be generated
        }
        // generate foldable chains
        for (int i = 0; i < 10; i++) {
            boolean ok = writeRandom("0123456", true);
            assert ok; // lots of different chains can be generated
        }
        // all other types of tree, trees are numbered per paper at http://unfolding.apperceptual.com/
        String[] trees = {
                "0123455", // 2
                "0123454", // 3
                "0123436", // 4
                "0123156", // 5
                "0123444", // 6
                "0123336", // 7
                "0121416", // 8
                "0123333", // 9
                "0111416", // 10
                "0122222", // 11
                "0123441", // 13
                "0123431", // 14
                "0123251", // 15
                "0123254", // 16
                "0123355", // 17
                "0111455", // 18
                "0122255", // 19
                "0122444", // 20
                "0113333", // 21
                "0111444", // 22
                "0113355", // 23
        };
        // generate 3 of a kind
        for (String tree : trees) {
            for (int i = 0; i < 3; i++) {
                if (!writeRandom(tree, false))
                    break; // no more cases of this kind
            }
            for (int i = 0; i < 3; i++) {
                if (!writeRandom(tree, true))
                    break; // no more cases of this kind
            }
        }
    }

    private static class Cell {
        int[] c;

        public Cell() {
            c = new int[3];
        }

        public Cell(Cell c0, int dir, int dd) {
            c = c0.c.clone();
            c[dir] += dd;
        }

        boolean adjacent(Cell c1) {
            int sum = 0;
            for (int i = 0; i < 3; i++) {
                sum += Math.abs(c[i] - c1.c[i]);
            }
            return sum == 1;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Cell)) return false;
            Cell cell = (Cell) o;
            return Arrays.equals(c, cell.c);
        }

        @Override
        public int hashCode() {
            return Arrays.hashCode(c);
        }

        int x() { return c[0]; }
        int y() { return c[1]; }
        int z() { return c[2]; }
    }

    private static class TestCase {
        final String[][] t;

        public TestCase(String[][] t) {
            this.t = t;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof TestCase)) return false;
            TestCase testCase = (TestCase) o;
            return Arrays.deepEquals(t, testCase.t);

        }

        @Override
        public int hashCode() {
            return Arrays.deepHashCode(t);
        }
    }

    private static class Octocube {
        private final List<Cell> cells = new ArrayList<>(8);

        void add(Cell c) {
            cells.add(c);
        }


        void remove(Cell c) {
            cells.remove(c);
        }

        boolean contains(Cell c) {
            return cells.contains(c);
        }

        Set<Cell> adjacent(Cell c1) {
            return cells.stream().filter(c -> c.adjacent(c1)).collect(Collectors.toSet());
        }

        String[][] convertToTestCase(Random rndPadding) {
            assert cells.size() == 8;
            Cell c0 = cells.get(0);
            int[] min = c0.c.clone();
            int[] max = c0.c.clone();
            for (int i = 1; i < cells.size(); i++) {
                Cell c = cells.get(i);
                for (int j = 0; j < 3; j++) {
                    min[j] = Math.min(min[j], c.c[j]);
                    max[j] = Math.max(max[j], c.c[j]);
                }
            }
            if (rndPadding != null) {
                for (int j = 0; j < 3; j++) {
                    int w = max[j] - min[j] + 1;
                    if (w >= MAX_DIM)
                        continue;
                    if (rndPadding.nextBoolean()) {
                        min[j] -= rndPadding.nextBoolean() ? MAX_DIM - w : rndPadding.nextInt(MAX_DIM - w);
                    }
                    w = max[j] - min[j] + 1;
                    if (w >= MAX_DIM)
                        continue;
                    if (rndPadding.nextBoolean()) {
                        max[j] += rndPadding.nextBoolean() ? MAX_DIM - w : rndPadding.nextInt(MAX_DIM - w);
                    }
                }
            }
            int m = max[0] - min[0] + 1;
            int n = max[1] - min[1] + 1;
            int k = max[2] - min[2] + 1;
            char[][][] cc = new char[k][n][m];
            for (int z = 0; z < k; z++) {
                for (int y = 0; y < n; y++) {
                    for (int x = 0; x < m; x++) {
                        cc[z][y][x] = '.';
                    }
                }
            }
            for (Cell c : cells) {
                cc[c.z() - min[2]][c.y() - min[1]][c.x() - min[0]] = 'x';
            }
            String[][] cs = new String[k][n];
            for (int z = 0; z < k; z++) {
                for (int y = 0; y < n; y++) {
                    cs[z][y] = new String(cc[z][y]);
                }
            }
            return cs;
        }
    }

    static class Tesseract {
        int[][] cells;
        boolean[] u;

        Tesseract() {
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
            // used cells
            u = new boolean[8];
        }

        void useCell(int ci) {
            assert !u[ci];
            u[ci] = true;
        }

        void undoCell(int ci) {
            assert u[ci];
            u[ci] = false;
        }

        int findCell(int ci, int dir, int dd) {
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
    }

    static class Move {
        Cell c0;
        int ci;

        public Move(Cell c0, int ci) {
            this.c0 = c0;
            this.ci = ci;
        }
    }

    static class Builder {
        final boolean foldable;
        final Random rnd;
        final Octocube octocube = new Octocube();
        final Tesseract tesseract = new Tesseract();
        final List<Move> stack = new ArrayList<>(8);

        Builder(long seed, boolean foldable) {
            this.foldable = foldable;
            rnd = new Random(seed);
            makeMove(new Move(new Cell(), 0));
        }

        void makeMove(Move move) {
            stack.add(move);
            octocube.add(move.c0);
            if (foldable)
                tesseract.useCell(move.ci);
        }

        Move getMove(int i) {
            return stack.get(i);
        }

        boolean tryMove(int di, Move move) {
            int dir = (di / 2) % 3;
            int dd = (di % 2) * 2 - 1;
            Cell c1 = new Cell(move.c0, dir, dd);
            if (octocube.contains(c1))
                return false;
            if (!octocube.adjacent(c1).equals(Collections.singleton(move.c0)))
                return false;
            int cj = 0;
            if (foldable) {
                cj = tesseract.findCell(move.ci, dir, dd);
                if (cj < 0)
                    return false;
            }
            makeMove(new Move(c1, cj));
            return true; // found
        }

        void popMove() {
            Move move = stack.get(stack.size() - 1);
            octocube.remove(move.c0);
            if (foldable) {
                tesseract.undoCell(move.ci);
            }
            stack.remove(stack.size() - 1);
        }
    }
}
