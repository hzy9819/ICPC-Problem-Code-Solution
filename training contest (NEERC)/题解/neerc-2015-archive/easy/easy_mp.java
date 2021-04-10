import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.util.ArrayDeque;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class easy_mp {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("easy.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("easy.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Easy solver = new Easy();
        solver.solve(1, in, out);
        out.close();
    }

    static class Easy {
        final int HARD = 50;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt(), k = in.nextInt();
            ArrayList<ArrayDeque<Integer>> what = new ArrayList<>();
            for (int i = 0; i < n; ++i) {
                ArrayDeque<Integer> me = new ArrayDeque<>();
                int cnt = in.nextInt();
                for (int j = 0; j < cnt; ++j) {
                    me.add(in.nextInt());
                }
                for (int j = 0; j < 1000; ++j) {
                    me.add(HARD);
                }
                what.add(me);
            }
            int total = 0, cur = 0;
            for (int it = 0; (it < 1000) && (k > 0); ++it) {
                if (what.get(cur).isEmpty()) {
                    cur = (cur + 1) % n;
                    continue;
                }
                int proposed = what.get(cur).pollFirst();
                if (proposed >= total) {
                    total += proposed;
                    k--;
                }
                cur = (cur + 1) % n;
            }
            total += k * 50;
            out.println(total);
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

