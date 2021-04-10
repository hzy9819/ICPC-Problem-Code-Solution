import java.util.*;
import java.io.*;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Egor Kulikov (egor@egork.net)
 */
public class iceberg_egor {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("iceberg.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("iceberg.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		Iceberg solver = new Iceberg();
		solver.solve(1, in, out);
		out.close();
	}

	static class Iceberg {
		static final int BUY = 1;
		static final int SELL = 2;

		public void solve(int testNumber, InputReader in, OutputWriter out) {
			int q = in.readInt();
			NavigableMap<Integer, Queue<Order>> buyBook = new TreeMap<>(new ReverseComparator<>());
			NavigableMap<Integer, Queue<Order>> sellBook = new TreeMap<>();
			for (int i = 0; i < q; i++) {
				int id = in.readInt();
				int type = in.readInt();
				int price = in.readInt();
				int volume = in.readInt();
				int tipVolume = in.readInt();
				List<Trade> trades = getTrades(buyBook, sellBook, id, type, price, volume, tipVolume);
				Collections.sort(trades);
				for (Trade trade : trades) {
					out.printLine(trade.buyId, trade.sellId, trade.price, trade.volume);
				}
			}
			out.printLine();
			List<Queue<Order>> buys = new ArrayList<>();
			buys.addAll(buyBook.values());
			Collections.reverse(buys);
			for (Queue<Order> queue : buys) {
				for (Order order : queue) {
					out.printLine(order.id, order.type, order.price, order.volume, order.tipVolume, order.currentVolume);
				}
			}
			for (Queue<Order> queue : sellBook.values()) {
				for (Order order : queue) {
					out.printLine(order.id, order.type, order.price, order.volume, order.tipVolume, order.currentVolume);
				}
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

	}

	static class InputReader {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar;
		private int numChars;
		private SpaceCharFilter filter;

		public InputReader(InputStream stream) {
			this.stream = stream;
		}

		public int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		public int readInt() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public boolean isSpaceChar(int c) {
			if (filter != null)
				return filter.isSpaceChar(c);
			return isWhitespace(c);
		}

		public static boolean isWhitespace(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		public interface SpaceCharFilter {
			public boolean isSpaceChar(int ch);

		}

	}

	static class OutputWriter {
		private final PrintWriter writer;

		public OutputWriter(OutputStream outputStream) {
			writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
		}

		public OutputWriter(Writer writer) {
			this.writer = new PrintWriter(writer);
		}

		public void print(Object... objects) {
			for (int i = 0; i < objects.length; i++) {
				if (i != 0)
					writer.print(' ');
				writer.print(objects[i]);
			}
		}

		public void printLine() {
			writer.println();
		}

		public void printLine(Object... objects) {
			print(objects);
			writer.println();
		}

		public void close() {
			writer.close();
		}

	}

	static class ReverseComparator<T extends Comparable<T>> implements Comparator<T> {
		public int compare(T o1, T o2) {
			return o2.compareTo(o1);
		}

	}
}

