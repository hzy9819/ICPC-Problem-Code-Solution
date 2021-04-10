import ru.ifmo.validate.ValidatingScanner;
import ru.ifmo.validate.Validator;

import java.util.*;

public class Validate implements Validator {
	static final int MAXQ = 50000;
	static final int MAX_ID = 1000000;
	static final int MAX_PRICE = 100000;
	static final int MAX_VOLUME = 1000000000;
	static final int MAX_GENERATED = 100000;

	@Override
	public void validate(ValidatingScanner in) {
		int q = in.nextInt("q", 1, MAXQ);
		in.eoln();
		NavigableMap<Integer, Queue<Order>> buyBook = new TreeMap<>(new ReverseComparator<>());
		NavigableMap<Integer, Queue<Order>> sellBook = new TreeMap<>();
		int totalGenerated = 0;
		Set<Integer> ids = new HashSet<>();
		for (int i = 0; i < q; i++) {
			int id = in.nextInt("id", 1, MAX_ID);
			assert !ids.contains(id) : "duplicate id " + id;
			ids.add(id);
			int type = in.nextInt("type", 1, 2);
			int price = in.nextInt("price", 1, MAX_PRICE);
			int volume = in.nextInt("volume", 1, MAX_VOLUME);
			int tipVolume = in.nextInt("tip volume", 1, volume);
			totalGenerated += getTrades(buyBook, sellBook, id, type, price, volume, tipVolume).size();
			in.eoln();
		}
		assert totalGenerated <= MAX_GENERATED : "generated to much trades";
	}

	static final int BUY = 1;
	static final int SELL = 2;

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


	static class ReverseComparator<T extends Comparable<T>> implements Comparator<T> {
	public int compare(T o1, T o2) {
		return o2.compareTo(o1);
	}

}


}
          