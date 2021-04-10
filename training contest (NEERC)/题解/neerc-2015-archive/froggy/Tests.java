import java.io.*;
import java.util.*;
import java.util.function.DoubleUnaryOperator;
import java.util.function.IntUnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.DoubleStream;
import java.util.stream.IntStream;

public class Tests {
    static final int MAX_C = 1000_000_000;
    static final int MAX_N = 1_000;

    static int nTests = 0;
    static final File root = new File("tests");
    static final Random random = new Random(5138740147081374083L);

    static class Point {
        final int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int hashCode() {
            return x * MAX_N + y;
        }

        @Override
        public boolean equals(Object o) {
            if (o instanceof Point) {
                Point that = (Point) o;
                return this.x == that.x && this.y == that.y;
            }
            return false;
        }
    }

    static void write(int w, Point... points) {
        write(w, Arrays.asList(points));
    }

    static void write(int w, Collection<Point> points) {
        assert points.size() <= MAX_N;
        assert 1 <= w && w <= MAX_C;
        for (Point p : points) {
            assert 0 < p.x && p.x < w;
            assert -MAX_C <= p.y && p.y <= MAX_C;
        }
        assert(new HashSet<>(points).size() == points.size());

        try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root.getName(), ++nTests))) {
            System.out.println("Writing test " + nTests);
            out.println(w + " " + points.size());
            for (Point p : points) {
                out.println(p.x + " " + p.y);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static Point p(int x, int y) {
        return new Point(x, y);
    }

    static int randomInt(int min, int max) {
        return random.nextInt(max - min + 1) + min;
    }

    static void random(int w, int n, IntUnaryOperator fMinX, IntUnaryOperator fMaxX, int minY, int maxY) {
        Set<Point> points = new HashSet<>();
        int minX = fMinX.applyAsInt(w);
        int maxX = fMaxX.applyAsInt(w);
        while (points.size() != n) {
            points.add(p(randomInt(minX, maxX), randomInt(minY, maxY)));
        }
        write(w, points);
    }

    private static DoubleStream parametricStream(int n) {
        return IntStream.range(0, n).mapToDouble(t -> t / (double) (n - 1));
    }

    static void parametric(int w, int n, DoubleUnaryOperator fx, DoubleUnaryOperator fy, int del, int wobble) {
        double minX = parametricStream(n).map(fx).min().getAsDouble();
        double maxX = parametricStream(n).map(fx).max().getAsDouble();
        double scale = (w - 2) / (maxX - minX);
        List<Point> points = parametricStream(n).mapToObj(f -> new Point(
                (int) Math.round(Math.min(w - 1, Math.max(1, (fx.applyAsDouble(f) - minX) * scale + 1 + randomInt(-wobble, wobble)))),
                (int) Math.round(fy.applyAsDouble(f) * scale + randomInt(-wobble, wobble))
        )).collect(Collectors.toList());
        for (int i = 0; i < del; i++) {
            int dxJ = 0;
            double dx = Double.POSITIVE_INFINITY;
            for (int j = 1; j < points.size() - 1; j++) {
                double q = Math.signum(points.get(j + 1).x - points.get(j - 1).x) * Math.hypot(points.get(j + 1).x - points.get(j - 1).x, points.get(j + 1).y - points.get(j - 1).y);
                if (dx > q) {
                    dx = q;
                    dxJ = j;
                }
            }
            points.remove(dxJ);
        }
//        Collections.shuffle(points);

        write(w, points);
    }

    static IntUnaryOperator one = i -> 1;
    static IntUnaryOperator div(int n) {
        return i -> i / n;
    }

    public static void main(String[] args) {
        write(10, p(2, 2), p(2, 4), p(5, 1), p(5, 3), p(8, 2), p(7, 5), p(9, 4));
        write(7);
        write(10, p(5, 3));
        write(10, p(4, 3));
        write(10, p(6, 3));
        write(10, p(7, -3), p(3, 3));
        write(16, p(2, -2), p(4, 0), p(6, 0), p(8, 0), p(10, 2), p(6, 6), p(8, 8), p(10, 10), p(12, 10), p(14, 10));
        for (int n : new int[]{20, 100, 1000, MAX_N}) {
            int s = MAX_C / MAX_N * n;
            int a = randomInt(-s, s);
            random(randomInt(s / 2, s), n, one, div(1), -s, s);
            random(randomInt(s / 2, s), n, one, div(2), -s, s);
            random(randomInt(s / 2, s), n, div(2), div(1), -s, s);
            random(randomInt(s / 2, s), n, div(4), i -> i / 4 * 3, -s, s);
            random(randomInt(s / 2, s), n, one, div(1), a - n, a + n);
            random(randomInt(s / 2, s), n, one, div(1), a, a);
            random(randomInt(s / 2, s), n, one, div(1), a - 1, a + 1);
            parametric(randomInt(s / 2, s) / 3, n, t -> 1 - Math.sin(15 * t) - 3 * t, t -> 5 * t, 0, 1);
            parametric(s / 3, n, t -> 1 - Math.cos(30 * t) + 2 * t, t -> 10 * t, 1, 2);
            parametric(randomInt(s / 2, s), n, t -> Math.sin(7 * t), t -> Math.cos(60 * t), 0, 3);
            parametric(randomInt(s / 2, s), n, t -> Math.cos(60 * t), t -> Math.cos(11 * t), 1, 4);
        }

        write(MAX_C);
        random(MAX_C, MAX_N, one, div(1), -MAX_C, MAX_C);
    }
}
