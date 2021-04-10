import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Iterator;
import java.io.BufferedWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.util.NoSuchElementException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Egor Kulikov (egor@egork.net)
 */
public class king_egor {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("king.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("king.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		King solver = new King();
		solver.solve(1, in, out);
		out.close();
	}

	static class King {
		public static final String FAIL = "There is no route, Karl!";

		public void solve(int testNumber, InputReader in, OutputWriter out) {
			int n = in.readInt();
			int m = in.readInt();
			int[] a = new int[m];
			int[] b = new int[m];
			IOUtils.readIntArrays(in, a, b);
			MiscUtils.decreaseByOne(a, b);
			Graph graph = Graph.createGraph(n, a, b);
			for (int i = 0; i < n; i++) {
				if (graph.firstInbound(i) == -1 || graph.firstOutbound(i) == -1) {
					out.printLine(FAIL);
					return;
				}
			}
			boolean[] removed = new boolean[n];
			IntList remaining = Range.range(n);
			IntList[] intermediate = new IntList[n];
			int count = n;
			while (count > 2) {
				boolean updated = false;
				for (int i : remaining) {
					if (removed[i]) {
						continue;
					}
					if (graph.firstInbound(i) == -1 || graph.firstOutbound(i) == -1) {
						out.printLine(FAIL);
						return;
					}
					final boolean singleLeft = graph.nextInbound(graph.firstInbound(i)) == -1;
					final boolean singleRight = graph.nextOutbound(graph.firstOutbound(i)) == -1;
					if (singleLeft || singleRight) {
						int left = singleLeft ? graph.source(graph.firstInbound(i)) : i;
						int right = singleLeft ? i : graph.destination(graph.firstOutbound(i));
						if (intermediate[left] == null) {
							intermediate[left] = new IntArrayList();
						}
						removed[right] = true;
						intermediate[left].add(right);
						for (int j = graph.firstOutbound(left); j != -1; j = graph.nextOutbound(j)) {
							graph.removeEdge(j);
						}
						for (int j = graph.firstInbound(right); j != -1; j = graph.nextInbound(j)) {
							graph.removeEdge(j);
						}
						for (int j = graph.firstOutbound(right); j != -1; j = graph.nextOutbound(j)) {
							if (left != graph.destination(j)) {
								graph.addSimpleEdge(left, graph.destination(j));
							}
							graph.removeEdge(j);
						}
						updated = true;
						count--;
						if (count <= 2) {
							IntList next = new IntArrayList();
							for (int j : remaining) {
								if (!removed[j]) {
									next.add(j);
								}
							}
							remaining = next;
							break;
						}
					}
				}
				IntList next = new IntArrayList();
				for (int i : remaining) {
					if (!removed[i]) {
						next.add(i);
					}
				}
				remaining = next;
				if (!updated) {
					break;
				}
			}
			int s = remaining.size();
			int[][] edges = new int[s][s];
			ArrayUtils.fill(edges, -1);
			for (int i = 0; i < s; i++) {
				for (int j = graph.firstOutbound(remaining.get(i)); j != -1; j = graph.nextOutbound(j)) {
					edges[i][remaining.find(graph.destination(j))] = j;
				}
				edges[i][i] = -2;
			}
			boolean[][] possible = new boolean[s][1 << s];
			int[][] last = new int[s][1 << s];
			possible[0][1] = true;
			for (int i = 1; i < (1 << s) - 2; i += 2) {
				for (int j = 0; j < s; j++) {
					if (!possible[j][i]) {
						continue;
					}
					for (int k = 0; k < s; k++) {
						if ((i >> k & 1) == 0 && edges[j][k] != -1) {
							possible[k][i + (1 << k)] = true;
							last[k][i + (1 << k)] = j;
						}
					}
				}
			}
			for (int i = 0; i < s; i++) {
				if (possible[i][(1 << s) - 1] && edges[i][0] != -1) {
					int current = i;
					IntList answer = new IntArrayList();
					int mask = (1 << s) - 1;
					while (current != 0) {
						go(remaining.get(current), intermediate, answer);
						int next = last[current][mask];
						mask -= 1 << current;
						current = next;
					}
					go(remaining.get(current), intermediate, answer);
					answer.inPlaceReverse();
					int index = answer.find(1);
					answer = (IntList) answer.subList(index, n).compute().addAll(answer.subList(0, index));
					out.print(answer);
					out.printLine(" 1");
					return;
				}
			}
			out.printLine(FAIL);
		}

		private void go(int current, IntList[] intermediate, IntList answer) {
			if (intermediate[current] != null) {
				intermediate[current].inPlaceReverse();
				for (int i : intermediate[current]) {
					go(i, intermediate, answer);
				}
			}
			answer.add(current + 1);
		}

	}

	static class IntArray extends IntAbstractStream implements IntList {
		private int[] data;

		public IntArray(int[] arr) {
			data = arr;
		}

		public int size() {
			return data.length;
		}

		public int get(int at) {
			return data[at];
		}

		public void addAt(int index, int value) {
			throw new UnsupportedOperationException();
		}

		public void removeAt(int index) {
			throw new UnsupportedOperationException();
		}

		public void set(int index, int value) {
			data[index] = value;
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

	static interface IntList extends IntReversableCollection {
		public abstract int get(int index);

		public abstract void set(int index, int value);

		public abstract void addAt(int index, int value);

		public abstract void removeAt(int index);

		default public void swap(int first, int second) {
			if (first == second) {
				return;
			}
			int temp = get(first);
			set(first, get(second));
			set(second, temp);
		}

		default public IntIterator intIterator() {
			return new IntIterator() {
				private int at;
				private boolean removed;

				public int value() {
					if (removed) {
						throw new IllegalStateException();
					}
					return get(at);
				}

				public boolean advance() {
					at++;
					removed = false;
					return isValid();
				}

				public boolean isValid() {
					return !removed && at < size();
				}

				public void remove() {
					removeAt(at);
					at--;
					removed = true;
				}
			};
		}


		default public void add(int value) {
			addAt(size(), value);
		}

		default public int find(int value) {
			int size = size();
			for (int i = 0; i < size; i++) {
				if (get(i) == value) {
					return i;
				}
			}
			return -1;
		}

		default public void inPlaceReverse() {
			for (int i = 0, j = size() - 1; i < j; i++, j--) {
				swap(i, j);
			}
		}

		default public IntList subList(final int from, final int to) {
			return new IntList() {
				private final int shift;
				private final int size;

				{
					if (from < 0 || from > to || to > IntList.this.size()) {
						throw new IndexOutOfBoundsException("from = " + from + ", to = " + to + ", size = " + size());
					}
					shift = from;
					size = to - from;
				}

				public int size() {
					return size;
				}

				public int get(int at) {
					if (at < 0 || at >= size) {
						throw new IndexOutOfBoundsException("at = " + at + ", size = " + size());
					}
					return IntList.this.get(at + shift);
				}

				public void addAt(int index, int value) {
					throw new UnsupportedOperationException();
				}

				public void removeAt(int index) {
					throw new UnsupportedOperationException();
				}

				public void set(int at, int value) {
					if (at < 0 || at >= size) {
						throw new IndexOutOfBoundsException("at = " + at + ", size = " + size());
					}
					IntList.this.set(at + shift, value);
				}

				public IntList compute() {
					return new IntArrayList(this);
				}
			};
		}

	}

	static interface IntCollection extends IntStream {
		public int size();

		default public void add(int value) {
			throw new UnsupportedOperationException();
		}

		default public IntCollection addAll(IntStream values) {
			for (IntIterator it = values.intIterator(); it.isValid(); it.advance()) {
				add(it.value());
			}
			return this;
		}

		default public IntCollection compute() {
			return this;
		}

	}

	static class Range {
		public static IntList range(int from, int to) {
			int[] result = new int[Math.abs(from - to)];
			int current = from;
			if (from <= to) {
				for (int i = 0; i < result.length; i++) {
					result[i] = current++;
				}
			} else {
				for (int i = 0; i < result.length; i++) {
					result[i] = current--;
				}
			}
			return new IntArray(result);
		}

		public static IntList range(int n) {
			return range(0, n);
		}

	}

	static class MiscUtils {
		public static void decreaseByOne(int[]... arrays) {
			for (int[] array : arrays) {
				for (int i = 0; i < array.length; i++)
					array[i]--;
			}
		}

	}

	static interface IntIterator {
		public int value() throws NoSuchElementException;

		public boolean advance();

		public boolean isValid();

	}

	static class IntArrayList extends IntAbstractStream implements IntList {
		private int size;
		private int[] data;

		public IntArrayList() {
			this(3);
		}

		public IntArrayList(int capacity) {
			data = new int[capacity];
		}

		public IntArrayList(IntCollection c) {
			this(c.size());
			addAll(c);
		}

		public IntArrayList(IntStream c) {
			this();
			if (c instanceof IntCollection) {
				ensureCapacity(((IntCollection) c).size());
			}
			addAll(c);
		}

		public IntArrayList(IntArrayList c) {
			size = c.size();
			data = c.data.clone();
		}

		public IntArrayList(int[] arr) {
			size = arr.length;
			data = arr.clone();
		}

		public int size() {
			return size;
		}

		public int get(int at) {
			if (at >= size) {
				throw new IndexOutOfBoundsException("at = " + at + ", size = " + size);
			}
			return data[at];
		}

		private void ensureCapacity(int capacity) {
			if (data.length >= capacity) {
				return;
			}
			capacity = Math.max(2 * data.length, capacity);
			data = Arrays.copyOf(data, capacity);
		}

		public void addAt(int index, int value) {
			ensureCapacity(size + 1);
			if (index > size || index < 0) {
				throw new IndexOutOfBoundsException("at = " + index + ", size = " + size);
			}
			if (index != size) {
				System.arraycopy(data, index, data, index + 1, size - index);
			}
			data[index] = value;
			size++;
		}

		public void removeAt(int index) {
			if (index >= size || index < 0) {
				throw new IndexOutOfBoundsException("at = " + index + ", size = " + size);
			}
			if (index != size - 1) {
				System.arraycopy(data, index + 1, data, index, size - index - 1);
			}
			size--;
		}

		public void set(int index, int value) {
			if (index >= size) {
				throw new IndexOutOfBoundsException("at = " + index + ", size = " + size);
			}
			data[index] = value;
		}

	}

	static interface Edge {
	}

	static class ArrayUtils {
		public static void fill(int[][] array, int value) {
			for (int[] row : array)
				Arrays.fill(row, value);
		}

	}

	static class IOUtils {
		public static void readIntArrays(InputReader in, int[]... arrays) {
			for (int i = 0; i < arrays[0].length; i++) {
				for (int j = 0; j < arrays.length; j++)
					arrays[j][i] = in.readInt();
			}
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

		public void printLine(Object... objects) {
			print(objects);
			writer.println();
		}

		public void close() {
			writer.close();
		}

	}

	static abstract class IntAbstractStream implements IntStream {

		public String toString() {
			StringBuilder builder = new StringBuilder();
			boolean first = true;
			for (IntIterator it = intIterator(); it.isValid(); it.advance()) {
				if (first) {
					first = false;
				} else {
					builder.append(' ');
				}
				builder.append(it.value());
			}
			return builder.toString();
		}


		public boolean equals(Object o) {
			if (!(o instanceof IntStream)) {
				return false;
			}
			IntStream c = (IntStream) o;
			IntIterator it = intIterator();
			IntIterator jt = c.intIterator();
			while (it.isValid() && jt.isValid()) {
				if (it.value() != jt.value()) {
					return false;
				}
				it.advance();
				jt.advance();
			}
			return !it.isValid() && !jt.isValid();
		}


		public int hashCode() {
			int result = 0;
			for (IntIterator it = intIterator(); it.isValid(); it.advance()) {
				result *= 31;
				result += it.value();
			}
			return result;
		}

	}

	static class Graph {
		public static final int REMOVED_BIT = 0;
		protected int vertexCount;
		protected int edgeCount;
		private int[] firstOutbound;
		private int[] firstInbound;
		private Edge[] edges;
		private int[] nextInbound;
		private int[] nextOutbound;
		private int[] from;
		private int[] to;
		private long[] weight;
		public long[] capacity;
		private int[] reverseEdge;
		private int[] flags;

		public Graph(int vertexCount) {
			this(vertexCount, vertexCount);
		}

		public Graph(int vertexCount, int edgeCapacity) {
			this.vertexCount = vertexCount;
			firstOutbound = new int[vertexCount];
			Arrays.fill(firstOutbound, -1);

			from = new int[edgeCapacity];
			to = new int[edgeCapacity];
			nextOutbound = new int[edgeCapacity];
			flags = new int[edgeCapacity];
		}

		public static Graph createGraph(int vertexCount, int[] from, int[] to) {
			Graph graph = new Graph(vertexCount, from.length);
			for (int i = 0; i < from.length; i++)
				graph.addSimpleEdge(from[i], to[i]);
			return graph;
		}

		public int addEdge(int fromID, int toID, long weight, long capacity, int reverseEdge) {
			ensureEdgeCapacity(edgeCount + 1);
			if (firstOutbound[fromID] != -1)
				nextOutbound[edgeCount] = firstOutbound[fromID];
			else
				nextOutbound[edgeCount] = -1;
			firstOutbound[fromID] = edgeCount;
			if (firstInbound != null) {
				if (firstInbound[toID] != -1)
					nextInbound[edgeCount] = firstInbound[toID];
				else
					nextInbound[edgeCount] = -1;
				firstInbound[toID] = edgeCount;
			}
			this.from[edgeCount] = fromID;
			this.to[edgeCount] = toID;
			if (capacity != 0) {
				if (this.capacity == null)
					this.capacity = new long[from.length];
				this.capacity[edgeCount] = capacity;
			}
			if (weight != 0) {
				if (this.weight == null)
					this.weight = new long[from.length];
				this.weight[edgeCount] = weight;
			}
			if (reverseEdge != -1) {
				if (this.reverseEdge == null) {
					this.reverseEdge = new int[from.length];
					Arrays.fill(this.reverseEdge, 0, edgeCount, -1);
				}
				this.reverseEdge[edgeCount] = reverseEdge;
			}
			if (edges != null)
				edges[edgeCount] = createEdge(edgeCount);
			return edgeCount++;
		}

		protected final GraphEdge createEdge(int id) {
			return new GraphEdge(id);
		}

		public final int addFlowWeightedEdge(int from, int to, long weight, long capacity) {
			if (capacity == 0) {
				return addEdge(from, to, weight, 0, -1);
			} else {
				int lastEdgeCount = edgeCount;
				addEdge(to, from, -weight, 0, lastEdgeCount + entriesPerEdge());
				return addEdge(from, to, weight, capacity, lastEdgeCount);
			}
		}

		protected int entriesPerEdge() {
			return 1;
		}

		public final int addWeightedEdge(int from, int to, long weight) {
			return addFlowWeightedEdge(from, to, weight, 0);
		}

		public final int addSimpleEdge(int from, int to) {
			return addWeightedEdge(from, to, 0);
		}

		public final int firstOutbound(int vertex) {
			int id = firstOutbound[vertex];
			while (id != -1 && isRemoved(id))
				id = nextOutbound[id];
			return id;
		}

		public final int nextOutbound(int id) {
			id = nextOutbound[id];
			while (id != -1 && isRemoved(id))
				id = nextOutbound[id];
			return id;
		}

		public final int firstInbound(int vertex) {
			initInbound();
			int id = firstInbound[vertex];
			while (id != -1 && isRemoved(id))
				id = nextInbound[id];
			return id;
		}

		public final int nextInbound(int id) {
			initInbound();
			id = nextInbound[id];
			while (id != -1 && isRemoved(id))
				id = nextInbound[id];
			return id;
		}

		public final int source(int id) {
			return from[id];
		}

		public final int destination(int id) {
			return to[id];
		}

		private void initInbound() {
			if (firstInbound == null) {
				firstInbound = new int[firstOutbound.length];
				Arrays.fill(firstInbound, 0, vertexCount, -1);
				nextInbound = new int[from.length];
				for (int i = 0; i < edgeCount; i++) {
					nextInbound[i] = firstInbound[to[i]];
					firstInbound[to[i]] = i;
				}
			}
		}

		public final boolean flag(int id, int bit) {
			return (flags[id] >> bit & 1) != 0;
		}

		public final void setFlag(int id, int bit) {
			flags[id] |= 1 << bit;
		}

		public final void removeEdge(int id) {
			setFlag(id, REMOVED_BIT);
		}

		public final boolean isRemoved(int id) {
			return flag(id, REMOVED_BIT);
		}

		protected void ensureEdgeCapacity(int size) {
			if (from.length < size) {
				int newSize = Math.max(size, 2 * from.length);
				if (edges != null)
					edges = resize(edges, newSize);
				from = resize(from, newSize);
				to = resize(to, newSize);
				nextOutbound = resize(nextOutbound, newSize);
				if (nextInbound != null)
					nextInbound = resize(nextInbound, newSize);
				if (weight != null)
					weight = resize(weight, newSize);
				if (capacity != null)
					capacity = resize(capacity, newSize);
				if (reverseEdge != null)
					reverseEdge = resize(reverseEdge, newSize);
				flags = resize(flags, newSize);
			}
		}

		protected final int[] resize(int[] array, int size) {
			int[] newArray = new int[size];
			System.arraycopy(array, 0, newArray, 0, array.length);
			return newArray;
		}

		private long[] resize(long[] array, int size) {
			long[] newArray = new long[size];
			System.arraycopy(array, 0, newArray, 0, array.length);
			return newArray;
		}

		private Edge[] resize(Edge[] array, int size) {
			Edge[] newArray = new Edge[size];
			System.arraycopy(array, 0, newArray, 0, array.length);
			return newArray;
		}

		protected class GraphEdge implements Edge {
			protected int id;

			protected GraphEdge(int id) {
				this.id = id;
			}

		}

	}

	static interface IntReversableCollection extends IntCollection {
	}

	static interface IntStream extends Iterable<Integer>, Comparable<IntStream> {
		public IntIterator intIterator();

		default public Iterator<Integer> iterator() {
			return new Iterator<Integer>() {
				private IntIterator it = intIterator();

				public boolean hasNext() {
					return it.isValid();
				}

				public Integer next() {
					int result = it.value();
					it.advance();
					return result;
				}
			};
		}

		default public int compareTo(IntStream c) {
			IntIterator it = intIterator();
			IntIterator jt = c.intIterator();
			while (it.isValid() && jt.isValid()) {
				int i = it.value();
				int j = jt.value();
				if (i < j) {
					return -1;
				} else if (i > j) {
					return 1;
				}
				it.advance();
				jt.advance();
			}
			if (it.isValid()) {
				return 1;
			}
			if (jt.isValid()) {
				return -1;
			}
			return 0;
		}

	}
}

