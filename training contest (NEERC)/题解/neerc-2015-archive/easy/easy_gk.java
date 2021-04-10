import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class easy_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int n = in.nextInt();
        int k = in.nextInt();
        List<List<Integer>> judges = new ArrayList<>();
        int z = 0;
        for (int i = 0; i < n; i++) {
            int p = in.nextInt();
            judges.add(Stream.generate(() -> in.nextInt()).limit(p).collect(Collectors.toList()));
            z += p;
        }
        int j = 0;
        int total = 0;
        while (k != 0 && total < 50 && z != 0) {
            int next;
            if (judges.get(j % judges.size()).isEmpty()) {
                next = 50;
            } else {
                next = judges.get(j % judges.size()).remove(0);
                z--;
            }
            if (next >= total) {
                total += next;
                k--;
            }
            j++;
        }
        out.println(total + 50 * k);
    }

    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.US);
        in = new Scanner(new File("easy.in"));
        out = new PrintWriter("easy.out");

        new easy_gk().run();

        in.close();
        out.close();
    }
}
