import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;
import java.util.function.DoubleUnaryOperator;
import java.util.function.IntUnaryOperator;
import java.util.stream.IntStream;

public class Tests {     
    static final int MAX_W = 100_000;
    static final int MAX_H = 100_000;
    static final int MAX_N = 1000_000_000;

    static int nTests = 0;
    static final File root = new File("tests");
    static final Random random = new Random(7458234579823234855L);

    static void write(int n, int... h) {
        assert 1 <= n && n <= MAX_N;
        assert 1 <= h.length && h.length <= MAX_W;
        for (int y : h) {
            assert 1 <= y && y <= MAX_H;
        }

        try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root.getName(), ++nTests))) {
            System.out.println("Writing test " + nTests);
            out.println(h.length + " " + n);
            Arrays.stream(h).forEach(out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static int randomInt(int min, int max) {
        return random.nextInt(max - min + 1) + min;
    }

    static void random(int w, int n, IntUnaryOperator f) {
        write(n, IntStream.range(0, w).map(f).toArray());
    }

    static void random(int w, int n, int maxH) {
        random(w, n, i -> randomInt(1, maxH));
    }

    static void approx(int w, int n, DoubleUnaryOperator f, int scale, int ds) {
        random(w, n, i -> Math.min(scale, Math.max(1, (int) Math.floor(1 + f.applyAsDouble(i / (double) (w - 1)) * scale) + randomInt(-ds, ds))));
    }

    public static void main(String[] args) {
        write(4, 3, 4, 2, 1, 3, 3, 2, 4);
        write(100, 3, 3, 3);

        for (int w = 10; w <= MAX_W; w *= 10) {
            int z = (int) (MAX_N * (long) w / MAX_W);
            random(randomInt(1, w), randomInt(1, 3), w);
            random(randomInt(1, w), randomInt(1, w), w);
            random(randomInt(1, w), randomInt(1, z), w);
            approx(randomInt(1, w), randomInt(1, z), x -> Math.sin(x * Math.PI), w, w / 10);
            approx(randomInt(1, w), randomInt(1, z), x -> Math.sin((x - 0.5) + Math.PI / 2), w, w / 10);
            approx(randomInt(1, w), randomInt(1, z), x -> (Math.cos(x * 2 * Math.PI) + 1) / 2, w, w / 10);
            approx(randomInt(1, w), randomInt(1, z), x -> 1 - Math.sin(x * Math.PI), w, w / 10);
            approx(randomInt(1, w), randomInt(1, z), x -> 1 - Math.sin((x - 0.5) + Math.PI / 2), w, w / 10);
            approx(randomInt(1, w), randomInt(1, z), x -> (1 - Math.cos(x * 2 * Math.PI)) / 2, w, w / 10);
            random(w, (int) (MAX_N * (long) w / MAX_W), w);
        }
    }
}
