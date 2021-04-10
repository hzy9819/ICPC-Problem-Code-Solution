import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.math.BigInteger;
import java.io.BufferedReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class binary_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("binary.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("binary.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Binary solver = new Binary();
        solver.solve(1, in, out);
        out.close();
    }

    static class Binary {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            List<State> goodNums = new ArrayList<>();
            goodNums.add(new State(BigInteger.ZERO, BigInteger.valueOf(5), BigInteger.ZERO, 1));
            goodNums.add(new State(BigInteger.ONE, BigInteger.valueOf(5), BigInteger.ZERO, 1));
            while (true) {
                List<State> withZero = new ArrayList<>();
                List<State> withOne = new ArrayList<>();
                for (State s : goodNums) {
                    if (s.u.bitLength() == s.len) {
                        --n;
                        if (n == 0) {
                            for (int i = s.len - 1; i >= 0; --i) {
                                out.print(s.u.testBit(i) ? '1' : '0');
                            }
                            out.println();
                            return;
                        }
                    }
                    State next = extendZero(s);
                    if (next != null) withZero.add(next);
                    next = extendOne(s);
                    if (next != null) withOne.add(next);
                }
                goodNums.clear();
                goodNums.addAll(withZero);
                goodNums.addAll(withOne);
            }
        }

        private State extendOne(State s) {
            if (s.num.testBit(0)) {
                return null;
            }
            return new State(s.u.add(BigInteger.ONE.shiftLeft(s.len)), s.p5.multiply(BigInteger.valueOf(5)), s.num.add(s.p5).shiftRight(1), s.len + 1);
        }

        private State extendZero(State s) {
            if (s.num.testBit(0)) {
                return null;
            }
            return new State(s.u, s.p5.multiply(BigInteger.valueOf(5)), s.num.shiftRight(1), s.len + 1);
        }

        static class State {
            BigInteger u;
            BigInteger p5;
            BigInteger num;
            int len;

            public State(BigInteger u, BigInteger p5, BigInteger num, int len) {
                this.u = u;
                this.p5 = p5;
                this.num = num;
                this.len = len;
            }

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

