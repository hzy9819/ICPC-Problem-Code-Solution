import java.util.Arrays;
import java.util.Random;
import java.util.stream.IntStream;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Stress {
    public static void main(String[] args) {
        final Random random = new Random();
        int s = 100;
        for (int t = 0; t < 30_000; t++) {
            int[] h = IntStream.generate(() -> random.nextInt(s) + 1).limit(random.nextInt(s) + 1).toArray();
            long n = random.nextLong() % (s * s / 4) + 1;
            int expected = new landscape_gk_tl_n2logn().solve(n, h);
            int actual = new landscape_gk().solve(n, h);
            if (expected != actual) {
                System.err.format("Expected %d, found %d\n", expected, actual);
                System.err.println(h.length + " " + n);
                Arrays.stream(h).forEach(System.err::println);
            }
        }
        System.out.println("ok");
    }
}
