import ru.ifmo.validate.ValidatingScanner;
import ru.ifmo.validate.Validator;

import java.io.*;
import java.util.Arrays;
import java.util.HashSet;
import java.util.InputMismatchException;
import java.util.Set;

public class Validate implements Validator {
	@Override
	public void validate(ValidatingScanner in) {
		int n = in.nextInt("n", 1, Tests.MAX_N);
		int m = in.nextInt("m", 0, Tests.MAX_PATH_COUNT);
		in.eoln();
		Graph graph = new BidirectionalGraph(n, m);
		Set<IntIntPair> present = new HashSet<>();
		for (int i = 0; i < m; i++) {
			int k = in.nextInt("k_" + i, 2, Tests.MAX_PATH_LENGTH);
			int last = in.nextInt("v_" + i + ",0", 1, n) - 1;
			for (int j = 1; j < k; j++) {
				int current = in.nextInt("v_" + i + "," + j, 1, n) - 1;
				IntIntPair edge = new IntIntPair(Math.min(last, current), Math.max(last, current));
				assert !present.contains(edge) : "Duplicate edge " + (last + 1) + "->" + (current + 1);
				assert last != current : "Loop " + (current + 1);
				present.add(edge);
				graph.addSimpleEdge(last, current);
				last = current;
			}
			in.eoln();
		}
		in.close();
		boolean[] treeEdges = new boolean[graph.edgeCount() >> 1];
		IndependentSetSystem setSystem = new RecursiveIndependentSetSystem(n);
		Graph tree = new BidirectionalGraph(n);
		for (int i = 0; i < treeEdges.length; i++) {
			int source = graph.source(2 * i);
			int destination = graph.destination(2 * i);
			if (setSystem.join(source, destination)) {
				tree.addSimpleEdge(source, destination);
				treeEdges[i] = true;
			}
		}
		assert setSystem.getSetCount() == 1 : "Not connected";
		LCA lca = new LCA(tree);
		boolean[] onCycle = new boolean[n - 1];
		for (int i = 0; i < treeEdges.length; i++) {
			if (treeEdges[i]) {
				continue;
			}
			int first = graph.source(2 * i);
			int second = graph.source(2 * i + 1);
			int parent = lca.getLCA(first, second);
			goUp(first, parent, tree, lca, onCycle);
			goUp(second, parent, tree, lca, onCycle);
		}
	}

	private void goUp(int vertex, int parent, Graph tree, LCA lca, boolean[] onCycle) {
		while (vertex != parent) {
			for (int i = tree.firstOutbound(vertex); i != -1; i = tree.nextOutbound(i)) {
				int destination = tree.destination(i);
				if (lca.getLevel(vertex) > lca.getLevel(destination)) {
					assert !onCycle[i >> 1] : "Two cycles through same edge " + (vertex + 1) + "->" + (destination + 1);
					onCycle[i >> 1] = true;
					vertex = destination;
					break;
				}
			}
		}
	}

	static class RecursiveIndependentSetSystem implements IndependentSetSystem {
		private final int[] color;
		private final int[] rank;
		private int setCount;
		private Listener listener;

		public RecursiveIndependentSetSystem(int size) {
			color = new int[size];
			rank = new int[size];
			for (int i = 0; i < size; i++)
				color[i] = i;
			setCount = size;
		}

		public RecursiveIndependentSetSystem(RecursiveIndependentSetSystem other) {
			color = other.color.clone();
			rank = other.rank.clone();
			setCount = other.setCount;
		}

		public boolean join(int first, int second) {
			first = get(first);
			second = get(second);
			if (first == second)
				return false;
			if (rank[first] < rank[second]) {
				int temp = first;
				first = second;
				second = temp;
			} else if (rank[first] == rank[second])
				rank[first]++;
			setCount--;
			color[second] = first;
			if (listener != null)
				listener.joined(second, first);
			return true;
		}

		public int get(int index) {
			if (color[index] == index)
				return index;
			return color[index] = get(color[index]);
		}

		public int getSetCount() {
			return setCount;
		}

	}

	static interface IndependentSetSystem {
		public boolean join(int first, int second);

		public int getSetCount();

		public static interface Listener {
			public void joined(int joinedRoot, int root);

		}

	}

	static class IntIntPair implements Comparable<IntIntPair> {
		public final int first;
		public final int second;

		public IntIntPair(int first, int second) {
			this.first = first;
			this.second = second;
		}


		public boolean equals(Object o) {
			if (this == o) return true;
			if (o == null || getClass() != o.getClass()) return false;

			IntIntPair pair = (IntIntPair) o;

			return first == pair.first && second == pair.second;

		}


		public int hashCode() {
			int result = Integer.hashCode(first);
			result = 31 * result + Integer.hashCode(second);
			return result;
		}


		public String toString() {
			return "(" + first + "," + second + ")";
		}

		@SuppressWarnings({"unchecked"})
		public int compareTo(IntIntPair o) {
			int value = Integer.compare(first, o.first);
			if (value != 0) {
				return value;
			}
			return Integer.compare(second, o.second);
		}

	}

	static abstract class IntervalTree {
		protected int size;

		protected IntervalTree(int size) {
			this(size, true);
		}

		public IntervalTree(int size, boolean shouldInit) {
			this.size = size;
			int nodeCount = Math.max(1, Integer.highestOneBit(size) << 2);
			initData(size, nodeCount);
			if (shouldInit)
				init();
		}

		protected abstract void initData(int size, int nodeCount);

		protected abstract void initAfter(int root, int left, int right, int middle);

		protected abstract void initBefore(int root, int left, int right, int middle);

		protected abstract void initLeaf(int root, int index);

		protected abstract long queryPostProcess(int root, int left, int right, int from, int to, int middle, long leftResult, long rightResult);

		protected abstract void queryPreProcess(int root, int left, int right, int from, int to, int middle);

		protected abstract long queryFull(int root, int left, int right, int from, int to);

		protected abstract long emptySegmentResult();

		public void init() {
			if (size == 0)
				return;
			init(0, 0, size - 1);
		}

		private void init(int root, int left, int right) {
			if (left == right) {
				initLeaf(root, left);
			} else {
				int middle = (left + right) >> 1;
				initBefore(root, left, right, middle);
				init(2 * root + 1, left, middle);
				init(2 * root + 2, middle + 1, right);
				initAfter(root, left, right, middle);
			}
		}

		public long query(int from, int to) {
			return query(0, 0, size - 1, from, to);
		}

		protected long query(int root, int left, int right, int from, int to) {
			if (left > to || right < from)
				return emptySegmentResult();
			if (left >= from && right <= to)
				return queryFull(root, left, right, from, to);
			int middle = (left + right) >> 1;
			queryPreProcess(root, left, right, from, to, middle);
			long leftResult = query(2 * root + 1, left, middle, from, to);
			long rightResult = query(2 * root + 2, middle + 1, right, from, to);
			return queryPostProcess(root, left, right, from, to, middle, leftResult, rightResult);
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

		public void close() {
			writer.close();
		}

	}

	static interface Edge {
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

	static abstract class ReadOnlyIntervalTree extends IntervalTree {
		protected long[] value;
		protected long[] array;

		protected ReadOnlyIntervalTree(long[] array) {
			super(array.length, false);
			this.array = array;
			init();
		}


		protected void initData(int size, int nodeCount) {
			value = new long[nodeCount];
		}


		protected void initAfter(int root, int left, int right, int middle) {
			value[root] = joinValue(value[2 * root + 1], value[2 * root + 2]);
		}


		protected void initBefore(int root, int left, int right, int middle) {
		}


		protected void initLeaf(int root, int index) {
			value[root] = array[index];
		}


		protected long queryPostProcess(int root, int left, int right, int from, int to, int middle, long leftResult, long rightResult) {
			return joinValue(leftResult, rightResult);
		}


		protected void queryPreProcess(int root, int left, int right, int from, int to, int middle) {
		}


		protected long queryFull(int root, int left, int right, int from, int to) {
			return value[root];
		}


		protected long emptySegmentResult() {
			return neutralValue();
		}

		protected abstract long neutralValue();

		protected abstract long joinValue(long left, long right);

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

		public final int vertexCount() {
			return vertexCount;
		}

		public final int edgeCount() {
			return edgeCount;
		}

		protected final int edgeCapacity() {
			return from.length;
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

		public final int source(int id) {
			return from[id];
		}

		public final int destination(int id) {
			return to[id];
		}

		public final boolean flag(int id, int bit) {
			return (flags[id] >> bit & 1) != 0;
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

	static class BidirectionalGraph extends Graph {
		public int[] transposedEdge;

		public BidirectionalGraph(int vertexCount) {
			this(vertexCount, vertexCount);
		}

		public BidirectionalGraph(int vertexCount, int edgeCapacity) {
			super(vertexCount, 2 * edgeCapacity);
			transposedEdge = new int[2 * edgeCapacity];
		}


		public int addEdge(int fromID, int toID, long weight, long capacity, int reverseEdge) {
			int lastEdgeCount = edgeCount;
			super.addEdge(fromID, toID, weight, capacity, reverseEdge);
			super.addEdge(toID, fromID, weight, capacity, reverseEdge == -1 ? -1 : reverseEdge + 1);
			this.transposedEdge[lastEdgeCount] = lastEdgeCount + 1;
			this.transposedEdge[lastEdgeCount + 1] = lastEdgeCount;
			return lastEdgeCount;
		}


		protected int entriesPerEdge() {
			return 2;
		}


		protected void ensureEdgeCapacity(int size) {
			if (size > edgeCapacity()) {
				super.ensureEdgeCapacity(size);
				transposedEdge = resize(transposedEdge, edgeCapacity());
			}
		}

	}

	static class LCA {
		private final long[] order;
		private final int[] position;
		private final Graph graph;
		private final IntervalTree lcaTree;
		private final int[] level;

		public LCA(Graph graph) {
			this(graph, 0);
		}

		public LCA(Graph graph, int root) {
			this.graph = graph;
			order = new long[2 * graph.vertexCount() - 1];
			position = new int[graph.vertexCount()];
			level = new int[graph.vertexCount()];
			int[] index = new int[graph.vertexCount()];
			for (int i = 0; i < index.length; i++)
				index[i] = graph.firstOutbound(i);
			int[] last = new int[graph.vertexCount()];
			int[] stack = new int[graph.vertexCount()];
			stack[0] = root;
			int size = 1;
			int j = 0;
			last[root] = -1;
			Arrays.fill(position, -1);
			while (size > 0) {
				int vertex = stack[--size];
				if (position[vertex] == -1)
					position[vertex] = j;
				order[j++] = vertex;
				if (last[vertex] != -1)
					level[vertex] = level[last[vertex]] + 1;
				while (index[vertex] != -1 && last[vertex] == graph.destination(index[vertex]))
					index[vertex] = graph.nextOutbound(index[vertex]);
				if (index[vertex] != -1) {
					stack[size++] = vertex;
					stack[size++] = graph.destination(index[vertex]);
					last[graph.destination(index[vertex])] = vertex;
					index[vertex] = graph.nextOutbound(index[vertex]);
				}
			}
			lcaTree = new ReadOnlyIntervalTree(order) {

				protected long joinValue(long left, long right) {
					if (left == -1)
						return right;
					if (right == -1)
						return left;
					if (level[((int) left)] < level[((int) right)])
						return left;
					return right;
				}


				protected long neutralValue() {
					return -1;
				}
			};
			lcaTree.init();
		}

		public int getLCA(int first, int second) {
			return (int) lcaTree.query(Math.min(position[first], position[second]), Math.max(position[first], position[second]));
		}

		public int getLevel(int vertex) {
			return level[vertex];
		}

	}
}
          