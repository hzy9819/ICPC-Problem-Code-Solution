import java.util.*;
import java.io.*;

/**
 * NEERC 2015 Test generator for problem C: Cactus Jubilee.
 * Based on the NEERC 2013 test generator by Roman Elizarov, based on NEERC 2010 generator by Maxim Buzdalov.
 *
 * @author Roman Elizarov
 */
public class Tests {
    static final String TEST_NAME_FORMAT = "%02d";

    static int nTests = 0;
    static Random random = new Random(45345654);
    static final File LST_FILE = new File("tests/tests.lst");


    static PrintWriter openTestFile(String desc) throws IOException {
        new File("tests").mkdir();
        PrintWriter out = new PrintWriter(String.format("tests/" + TEST_NAME_FORMAT, ++nTests));
        PrintWriter out1 = new PrintWriter(new FileWriter(LST_FILE, true));
        out1.printf(TEST_NAME_FORMAT + " %s%n", nTests, desc);
        out1.close();
        System.out.printf("Writing test " + TEST_NAME_FORMAT + ": %s%n", nTests, desc);
        return out;
    }

    static void write(List<Order> orders, String desc) throws IOException {
        PrintWriter out = openTestFile(desc);
        out.println(orders.size());
        for (Order order : orders) {
            out.println(order.id + " " + order.type + " " + order.price + " " + order.volume + " " + order.tipVolume);
        }
        out.close();
    }

    static void writeRandIds(List<Order> orders, String desc) throws IOException {
        Set<Integer> ids = new HashSet<>();
        for (Order order : orders) {
            int id;
            do {
                id = random.nextInt(Validate.MAX_ID) + 1;
            } while (ids.contains(id));
            ids.add(id);
            order.id = id;
        }
        write(orders, desc);
    }

    public static void main(String[] args) throws IOException {
        LST_FILE.delete();
        write(Arrays.asList(
            new Order(42, 1, 100, 200, 20),
            new Order(239, 1, 100, 50, 50),
            new Order(1111, 1, 101, 30, 15),
            new Order(1234, 1, 100, 300, 15),
            new Order(4321, 2, 99, 125, 25),
            new Order(5678, 1, 101, 30, 30),
            new Order(8765, 2, 101, 100, 20)
        ), "sample");

        for (int n = 1; n <= 20; n++) {
            smallTest(n);
        }
        for (int i = 1; i < 10; i++) {
            smallTest(100);
        }

        writeRandIds(Arrays.asList(
            new Order(0, 1, 100, Validate.MAX_VOLUME, 1),
            new Order(0, 2, 100, Validate.MAX_VOLUME, 1)
        ), "easy anti simulation");

        antiSimulation();
        bigLevel();

        for (int i = 0; i < 5; i++) {
            bigTip();
        }

        for (int i = 0; i < 5; i++) {
            bigTest();
        }

        for (int i = 0; i < 5; i++) {
            bigTestAlmostSamePrice();
        }

        for (int i = 0; i < 5; i++) {
            bigTestAlmostSamePriceSmallTip();
        }
    }

    private static void bigTest() throws IOException {
        NavigableMap<Integer, Queue<Order>> buyBook = new TreeMap<>(Comparator.reverseOrder());
        NavigableMap<Integer, Queue<Order>> sellBook = new TreeMap<>();
        int totalGenerated = 0;
        List<Order> orders = new ArrayList<>();
        for (int i = 0; i < Validate.MAXQ; i++) {
            int volume = random.nextInt(Validate.MAX_VOLUME) + 1;
            Order order = new Order(0, random.nextInt(2) + 1, random.nextInt(Validate.MAX_PRICE) + 1, volume, random.nextInt(volume) + 1);
            totalGenerated += getTrades(buyBook, sellBook, i + 1, order.type, order.price, volume, order.tipVolume).size();
            if (totalGenerated > Validate.MAX_GENERATED) {
                break;
            }
            orders.add(order);
        }
        writeRandIds(orders, "big test");
    }

    private static void bigTestAlmostSamePrice() throws IOException {
        NavigableMap<Integer, Queue<Order>> buyBook = new TreeMap<>(Comparator.reverseOrder());
        NavigableMap<Integer, Queue<Order>> sellBook = new TreeMap<>();
        int totalGenerated = 0;
        List<Order> orders = new ArrayList<>();
        for (int i = 0; i < Validate.MAXQ; i++) {
            int volume = random.nextInt(Validate.MAX_VOLUME) + 1;
            Order order = new Order(0, random.nextInt(2) + 1, random.nextInt(10) + 100, volume, random.nextInt(volume) + 1);
            totalGenerated += getTrades(buyBook, sellBook, i + 1, order.type, order.price, volume, order.tipVolume).size();
            if (totalGenerated > Validate.MAX_GENERATED) {
                break;
            }
            orders.add(order);
        }
        writeRandIds(orders, "big test almost same price");
    }

    private static void bigTestAlmostSamePriceSmallTip() throws IOException {
        NavigableMap<Integer, Queue<Order>> buyBook = new TreeMap<>(Comparator.reverseOrder());
        NavigableMap<Integer, Queue<Order>> sellBook = new TreeMap<>();
        int totalGenerated = 0;
        List<Order> orders = new ArrayList<>();
        for (int i = 0; i < Validate.MAXQ; i++) {
            int volume = random.nextInt(Validate.MAX_VOLUME) + 1;
            Order order = new Order(0, random.nextInt(2) + 1, random.nextInt(10) + 100, volume, random.nextInt(Math.min(volume, 20)) + 1);
            totalGenerated += getTrades(buyBook, sellBook, i + 1, order.type, order.price, volume, order.tipVolume).size();
            if (totalGenerated > Validate.MAX_GENERATED) {
                break;
            }
            orders.add(order);
        }
        writeRandIds(orders, "big test almost same price small tip");
    }

    private static void smallTest(int n) throws IOException {
        List<Order> orders = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int volume = random.nextInt(100) + 1;
            orders.add(new Order(0, random.nextInt(2) + 1, random.nextInt(10) + 100, volume, random.nextInt(volume) + 1));
        }
        writeRandIds(orders, "small test n=" + n);
    }

    private static void bigTip() throws IOException {
        List<Order> orders = new ArrayList<>();
        for (int i = 0; i < Validate.MAXQ; i++) {
            int volume = random.nextInt(Validate.MAX_VOLUME) + 1;
            orders.add(new Order(0, random.nextInt(2) + 1, random.nextInt(Validate.MAX_PRICE) + 1, volume, volume / 2 + random.nextInt(volume / 2) + 1));
        }
        writeRandIds(orders, "big tip");
    }

    private static void antiSimulation() throws IOException {
        List<Order> orders = new ArrayList<>();
        for (int i = 0; i < Validate.MAX_GENERATED / 10; i++) {
            orders.add(new Order(0, 1, 100, Validate.MAX_VOLUME / 2 + random.nextInt(Validate.MAX_VOLUME / 2), random.nextInt(5) + 1));
        }
        for (int j = 0; j < 10; j++) {
            orders.add(new Order(0, 2, 100, Validate.MAX_VOLUME / 2 + random.nextInt(Validate.MAX_VOLUME / 2), random.nextInt(5) + 1));
        }
        writeRandIds(orders, "anti simulation");
    }

    private static void bigLevel() throws IOException {
        List<Order> orders = new ArrayList<>();
        for (int i = 0; i < Validate.MAXQ / 2; i++) {
            orders.add(new Order(0, 1, 100, Validate.MAX_VOLUME, Validate.MAX_VOLUME));
        }
        for (int i = 0; i < Validate.MAXQ / 2; i++) {
            orders.add(new Order(0, 2, 100, Validate.MAX_VOLUME, Validate.MAX_VOLUME));
        }
        writeRandIds(orders, "big level");
    }

    static final int BUY = 1;
    static final int SELL = 2;

    static class Order {
        int id;
        int type;
        int price;
        int volume;
        int tipVolume;
        int currentVolume;

        Order(int id, int type, int price, int volume, int tipVolume) {
            this.id = id;
            this.type = type;
            this.price = price;
            this.volume = volume;
            this.tipVolume = tipVolume;
        }

        void prepare() {
            currentVolume = Math.min(volume, tipVolume);
        }

        Collection<? extends Trade> fillAgainst(Queue<Order> orders) {
            List<Trade> trades = new ArrayList<>();
            long total = 0;
            int size = orders.size();
            for (int i = 0; i < size; i++) {
                Order order = orders.peek();
                int current = Math.min(volume, order.currentVolume);
                trades.add(new Trade(type == BUY ? id : order.id, type == SELL ? id : order.id, order.price, current));
                order.volume -= current;
                order.currentVolume -= current;
                volume -= current;
                total += order.volume;
                if (order.currentVolume == 0) {
                    orders.poll();
                    if (order.volume != 0) {
                        order.prepare();
                        orders.add(order);
                    }
                }
                if (volume == 0) {
                    return trades;
                }
            }
            if (total <= volume) {
                int at = 0;
                for (Order order : orders) {
                    Trade trade;
                    do {
                        trade = trades.get(at++);
                    } while (trade.buyId != order.id && trade.sellId != order.id);
                    trade.volume += order.volume;
                }
                volume -= total;
                orders.clear();
                return trades;
            }
            size = orders.size();
            long left = 0;
            long right = (long) size * volume;
            while (left < right) {
                long current = (left + right) >> 1;
                long vol = 0;
                int at = 0;
                for (Order order : orders) {
                    long times = (current - at + size - 1) / size;
                    long curVolume = Math.min(order.volume, order.tipVolume * times);
                    vol += curVolume;
                    at++;
                }
                if (vol >= volume) {
                    right = current;
                } else {
                    left = current + 1;
                }
            }
            Order specialOrder = null;
            Trade specialTrade = null;
            int at = 0;
            int i = 0;
            Queue<Order> before = new ArrayDeque<>();
            Queue<Order> after = new ArrayDeque<>();
            long special = left % size - 1;
            if (special == -1) {
                special += size;
            }
            for (Order order : orders) {
                Trade trade;
                do {
                    trade = trades.get(at++);
                } while (trade.buyId != order.id && trade.sellId != order.id);
                if (i == special) {
                    specialOrder = order;
                    specialTrade = trade;
                    i++;
                    continue;
                }
                long times = (left - i + size - 1) / size;
                long curVolume = Math.min(order.volume, order.tipVolume * times);
                trade.volume += curVolume;
                order.volume -= curVolume;
                volume -= curVolume;
                if (order.volume != 0) {
                    order.prepare();
                    if (i < special) {
                        before.add(order);
                    } else {
                        after.add(order);
                    }
                }
                i++;
            }
            orders.clear();
            specialTrade.volume += volume;
            specialOrder.volume -= volume;
            int lastFill = volume % specialOrder.tipVolume;
            specialOrder.currentVolume = Math.min(specialOrder.volume, specialOrder.tipVolume - lastFill);
            if (lastFill != 0 && specialOrder.volume != 0) {
                orders.add(specialOrder);
            }
            orders.addAll(after);
            orders.addAll(before);
            if (lastFill == 0 && specialOrder.volume != 0) {
                orders.add(specialOrder);
            }
            volume = 0;
            return trades;
        }

    }


    static class Trade implements Comparable<Trade> {
        int buyId;
        int sellId;
        int price;
        int volume;

        public Trade(int buyId, int sellId, int price, int volume) {
            this.buyId = buyId;
            this.sellId = sellId;
            this.price = price;
            this.volume = volume;
        }


        public int compareTo(Trade o) {
            if (buyId != o.buyId) {
                return buyId - o.buyId;
            }
            return sellId - o.sellId;
        }

    }

    static List<Trade> getTrades(NavigableMap<Integer, Queue<Order>> buyBook, NavigableMap<Integer, Queue<Order>> sellBook, int id, int type, int price, int volume, int tipVolume) {
   		Order order = new Order(id, type, price, volume, tipVolume);
   		List<Trade> trades = new ArrayList<>();
   		NavigableMap<Integer, Queue<Order>> oppositeBook = type == BUY ? sellBook : buyBook;
   		while (order.volume > 0 && !oppositeBook.isEmpty()) {
                  int curPrice = oppositeBook.firstKey();
                  if (type == BUY && curPrice > price || type == SELL && curPrice < price) {
                      break;
                  }
                  Queue<Order> queue = oppositeBook.get(curPrice);
                  trades.addAll(order.fillAgainst(queue));
                  if (queue.isEmpty()) {
                      oppositeBook.remove(curPrice);
                  }
              }
   		if (order.volume > 0) {
                  order.prepare();
                  NavigableMap<Integer, Queue<Order>> currentBook = type == BUY ? buyBook : sellBook;
                  Queue<Order> queue = currentBook.get(price);
                  if (queue == null) {
                      currentBook.put(price, queue = new ArrayDeque<>());
                  }
                  queue.add(order);
              }
   		return trades;
   	}


}
