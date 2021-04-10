import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;

public class binary_gk {
    static Scanner in;
    static PrintWriter out;

    final int BITS = 20;
    final int MASK = (1 << BITS) - 1;
    final int N = 200;

    void run() {
        int n = in.nextInt();
        List<int[]> candidates = new ArrayList<>();
        candidates.add(new int[N]);
        int[] power = new int[N];
        power[0] = 1;
        for (int bit = 0; ; bit++) {
            List<int[]> zeroes = new ArrayList<>();
            List<int[]> ones = new ArrayList<>();
            for (int[] candidate : candidates) {
                if (((candidate[bit / BITS] >> (bit % BITS)) & 1) == 0) {
                    if (--n == 0) {
                        out.println(toString(add(candidate, power)));
                        return;
                    }
                    zeroes.add(candidate);
                    ones.add(add(candidate, power));
                }
            }
            power = multiply(power, 10);
            candidates.clear();
            candidates.addAll(zeroes);
            candidates.addAll(ones);
        }
    }

    private String toString(int[] a) {
        StringBuilder sb = new StringBuilder();
        for (int q = 0; q < N * BITS / 3; q++) {
            int carry = 0;
            for (int i = N - 1; i >= 0; i--) {
                carry = carry % 10 * (MASK + 1) + a[i];
                a[i] = carry / 10;
            }
            sb.append(carry % 10);
        }
        sb.reverse();
        return sb.toString().replaceAll("^0+", "");
    }

    private int[] multiply(int[] a, int b) {
        int carry = 0;
        int[] result = new int[N];
        for (int i = 0; i < N; i++) {
            carry = a[i] * b + (carry >> BITS);
            result[i] = carry & MASK;
        }
        return result;
    }

    private int[] add(int[] candidate, int[] power) {
        int carry = 0;
        int[] result = new int[N];
        for (int i = 0; i < N; i++) {
            carry = candidate[i] + power[i] + (carry >> BITS);
            result[i] = carry & MASK;
        }
        return result;
    }

    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.US);
        in = new Scanner(new File("binary.in"));
        out = new PrintWriter("binary.out");

        new binary_gk().run();

        in.close();
        out.close();
    }
}
