import java.io.*;
import java.util.*;
import java.util.stream.Stream;

/**
 * Solution for NEERC'2015 Problem I: Iceberg Orders.
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class iceberg_re {
    private static final String INPUT = "iceberg.in";
    private static final String OUTPUT = "iceberg.out";

    public static final int MAX_N = 50_000;
    public static final int MAX_ID = 1_000_000;
    public static final int BUY = 1;
    public static final int SELL = 2;
    public static final int MAX_P = 100_000;
    public static final int MAX_V = 1_000_000_000;
    public static final int MAX_TRADES = 100_000;

    public static void main(String[] args) throws Exception {
        new iceberg_re().go();
    }

    void go() throws IOException {
        long time = System.currentTimeMillis();
        try (Scanner in = new Scanner(new File(INPUT))) {
            in.useLocale(Locale.US);
            read(in);
        }
        solve();
        try (PrintWriter out = new PrintWriter(OUTPUT)) {
            write(out);
        }
        System.out.printf("Done in %d ms%n", System.currentTimeMillis() - time);
    }

    int n;
    Order[] orders;

    void read(Scanner in) {
        n = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= MAX_N;
        orders = new Order[n];
        Set<Integer> ids = new HashSet<>();
        for (int i = 0; i < n; i++) {
            orders[i] = new Order(in);
            assert ids.add(orders[i].id) : "unique id";
        }
    }

    Map<Integer, Trade> ts = new TreeMap<>();
    List<Trade> trades = new ArrayList<>();
    Book[] books = new Book[3];

    void solve() {
        books[BUY] = new Book();
        books[SELL] = new Book();
        for (Order a : orders) {
            Book book = books[BUY + SELL - a.t];
            NavigableMap<Integer, Queue<Order>> map;
            switch (a.t) {
                case BUY:
                    map = book.orders;
                    break;
                case SELL:
                    map = book.orders.descendingMap();
                    break;
                default:
                    throw new AssertionError();
            }
            for (Iterator<Map.Entry<Integer, Queue<Order>>> mapIt = map.entrySet().iterator();
                 a.v > 0 && mapIt.hasNext(); )
            {
                Map.Entry<Integer, Queue<Order>> entry = mapIt.next();
                Integer bp = entry.getKey();
                boolean okPrice = a.t == SELL ? bp >= a.p : bp <= a.p;
                if (!okPrice)
                    break;
                Queue<Order> queue = entry.getValue();
                // make one pass (asymptotically efficient when order is small, queue is big)
                simulateOnePass(a, queue);
                if (a.v == 0) {
                    if (queue.isEmpty())
                        mapIt.remove();
                    break;
                }
                // check if this order completely eats all the queue (eventually),
                // removes extra log multiplier in asymptotic efficiency
                if (a.v >= sumVolume(queue, Integer.MAX_VALUE)) {
                    // eats all
                    simulateMFullPasses(a, queue, Integer.MAX_VALUE);
                    mapIt.remove();
                    continue;
                }
                // binary search for the number times queue is fully matched
                int lo = 0;
                int hi = a.v + 1;
                while (lo + 1 < hi) { // lo <= answer < hi
                    int m = (lo + hi) / 2;
                    long sum = sumVolume(queue, m);
                    if (sum > a.v)
                        hi = m;
                    else
                        lo = m;
                }
                // do m full matches through the queue
                int m = lo;
                if (m > 0) {
                    simulateMFullPasses(a, queue, m);
                }
                // simulate one remaining pass
                simulateOnePass(a, queue);
                // should be done with either a or queue
                assert a.v == 0 || queue.isEmpty();
                if (queue.isEmpty())
                    mapIt.remove();
            }
            if (a.v != 0) {
                a.cv = Math.min(a.v, a.tv);
                books[a.t].add(a);
            }
            trades.addAll(ts.values());
            ts.clear();
        }
        assert trades.size() <= MAX_TRADES;
    }

    private void simulateOnePass(Order a, Queue<Order> queue) {
        int n = queue.size();
        for (int i = 0; i < n && a.v > 0; i++) {
            Order b = queue.peek();
            int v = Math.min(a.v, b.cv);
            boolean updatePR = addTrade(a, b, v);
            if (b.v == 0) {
                queue.remove();
            } else if (updatePR) {
                queue.remove();
                queue.add(b);
            }
        }
    }

    private void simulateMFullPasses(Order a, Queue<Order> queue, int m) {
        for (Iterator<Order> queueIt = queue.iterator(); queueIt.hasNext(); ) {
            Order b = queueIt.next();
            int v = b.cv + (int)Math.min(b.v - b.cv, (long)b.tv * (m - 1));
            boolean updatePR = addTrade(a, b, v);
            assert updatePR;
            if (b.v == 0) {
                queueIt.remove();
            }
        }
    }

    private long sumVolume(Queue<Order> queue, int m) {
        long sum = 0; // total volume
        for (Order b : queue) {
            int v = b.cv + (int)Math.min(b.v - b.cv, (long)b.tv * (m - 1));
            sum += v;
        }
        return sum;
    }

    private boolean addTrade(Order a, Order b, int v) {
        Trade t = ts.get(b.id);
        if (t == null)
            ts.put(b.id, t = new Trade(a, b));
        t.v += v;
        a.v -= v;
        b.v -= v;
        b.cv -= v;
        if (b.cv <= 0) {
            b.cv = Math.min(b.v, b.tv);
            return true;
        }
        return false;
    }

    void write(PrintWriter out) {
        trades.forEach(out::println);
        out.println();
        Stream.of(books)
            .filter(b -> b != null)
            .flatMap(b -> b.orders.values().stream())
            .flatMap(Collection::stream)
            .forEach(out::println);
    }

    static class Order {
        int id;
        int t;
        int p;
        int v;
        int tv;
        int cv;

        public Order(Scanner in) {
            id = in.nextInt();
            t = in.nextInt();
            p = in.nextInt();
            v = in.nextInt();
            tv = in.nextInt();
            in.nextLine();
            assert id >= 1 && id <= MAX_ID;
            assert t == BUY || t == SELL;
            assert p >= 1 && p <= MAX_P;
            assert tv >= 1 && tv <= v && v <= MAX_V;
        }

        @Override
        public String toString() {
            return String.format("%d %d %d %d %d %d", id, t, p, v, tv, cv);
        }
    }

    static class Book {
        TreeMap<Integer, Queue<Order>> orders = new TreeMap<>();

        void add(Order a) {
            Queue<Order> queue = orders.get(a.p);
            if (queue == null)
                orders.put(a.p, queue = new LinkedList<>());
            queue.add(a);
        }
    }

    static class Trade {
        int buyId;
        int sellId;
        int p;
        int v;

        public Trade(Order a, Order b) {
            assert a.t != b.t;
            buyId = a.t == BUY ? a.id : b.id;
            sellId = a.t == SELL ? a.id : b.id;
            p = b.p;
        }

        @Override
        public String toString() {
            return String.format("%d %d %d %d", buyId, sellId, p, v);
        }
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
        private boolean localeset;

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

        public double nextDouble() {
            assert localeset : "Locale must be set with useLocale(Locale.US)";
            String s = next();
            assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Double.parseDouble(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }

        public void useLocale(Locale locale) {
            assert locale == Locale.US;
            localeset = true;
        }
    }
}
