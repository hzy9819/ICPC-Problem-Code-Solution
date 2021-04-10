import java.io.*;
import java.util.*;

/**
 * NEERC 2015 Test generator for problem C: Cactus Jubilee.
 * Based on the NEERC 2013 test generator by Roman Elizarov, based on NEERC 2010 generator by Maxim Buzdalov.
 *
 * @author Roman Elizarov
 */
public class Tests {
	static final String TEST_NAME_FORMAT = "%03d";

	static int nTests = 0;
	static int MAX_N = 50000;
	static int MAX_PATH_LENGTH = 1000;
	static int MAX_PATH_COUNT = 50000;
	static Random random = new Random(45345654);
	static final File LST_FILE = new File("tests/tests.lst");

	static class VertexWithDegree implements Comparable<VertexWithDegree> {
		final int index;
		int degree;

		public VertexWithDegree(int index, int degree) {
			this.index = index;
			this.degree = degree;
		}

		public int compareTo(VertexWithDegree vwd) {
			if (degree != vwd.degree)
				return degree - vwd.degree;
			return index - vwd.index;
		}
	}

	static class Graph {
		int next = 0; // next vertex id for autogen
		int nVertices = 1;
		List<Set<Integer>> edges = new ArrayList<>();

		{
			edges.add(new HashSet<Integer>());
		}

		public Graph() {}

		public Graph(int[]... paths) {
			for (int[] p : paths) {
				for (int i = 1; i < p.length; ++i) {
					addEdge(p[i - 1], p[i]);
				}
			}
		}

		public void addEdge(int a, int b) {
			while (edges.size() <= Math.max(a, b)) {
				edges.add(new HashSet<Integer>());
			}
			if (edges.get(a).contains(b))
				throw new AssertionError("The edge (" + a + "--" + b + ") is already contained");
			if (edges.get(b).contains(a))
				throw new AssertionError("The edge (" + a + "--" + b + ") is already contained");
			edges.get(a).add(b);
			edges.get(b).add(a);
			nVertices = Math.max(nVertices, 1 + Math.max(a, b));
		}

		void shuffle() {
			int[] rp = randomPermutation(nVertices);
			List<Set<Integer>> e0 = edges;
			edges = new ArrayList<>();
			for (int i = 0; i < nVertices; i++)
				edges.add(new HashSet<Integer>());
			for (int i = 0; i < nVertices; i++) {
				Set<Integer> set = e0.get(i);
				for (int j : set)
					edges.get(rp[i]).add(rp[j]);
			}
		}

		public void dfs(int vertex, boolean[] used) {
			used[vertex] = true;
			for (int next : edges.get(vertex)) {
				if (!used[next]) {
					dfs(next, used);
				}
			}
		}

		public boolean checkConnectivity() {
			boolean[] used = new boolean[nVertices];
			dfs(0, used);
			for (boolean t : used) {
				if (!t)
					return false;
			}
			return true;
		}

		public List<List<Integer>> extractPaths(int maxPathLength) {
			List<Set<Integer>> edgeCopy = new ArrayList<>(edges.size());
			for (Set<Integer> e : edges) {
				edgeCopy.add(new HashSet<>(e));
			}
			VertexWithDegree[] vs = new VertexWithDegree[nVertices];
			TreeSet<VertexWithDegree> vertices = new TreeSet<>();
			for (int i = 0; i < nVertices; ++i) {
				vs[i] = new VertexWithDegree(i, edgeCopy.get(i).size());
				if (vs[i].degree > 0) {
					vertices.add(vs[i]);
				}
			}
			List<List<Integer>> paths = new ArrayList<>();
			while (!vertices.isEmpty()) {
				List<Integer> curr = new ArrayList<>();
				paths.add(curr);
				int v = vertices.first().index;
				curr.add(v);
				while (curr.size() < maxPathLength && vs[v].degree > 0) {
					int next = edgeCopy.get(v).iterator().next();
					edgeCopy.get(v).remove(next);
					edgeCopy.get(next).remove(v);
					vertices.remove(vs[v]);
					vertices.remove(vs[next]);
					if (--vs[v].degree > 0) {
						vertices.add(vs[v]);
					}
					if (--vs[next].degree > 0) {
						vertices.add(vs[next]);
					}
					v = next;
					curr.add(v);
				}
			}
			return paths;
		}
	}

	static abstract class NGen {
		abstract int n(Map<String, Integer> ctx);
		void set(Map<String, Integer> ctx, int i) {}
	}

	static abstract class TGen {
		abstract void gen(Map<String, Integer> ctx, Graph g, int n0);
	}

	static abstract class CGen extends TGen {
		abstract void gen(Map<String, Integer> ctx, Graph g, int n0, int n1);

		final void gen(Map<String, Integer> ctx, Graph g, int n0) {
			gen(ctx, g, n0, g.next++);
		}
	}

	// fined number
	static NGen num(final int n) {
		return new NGen() {
			@Override
			int n(Map<String, Integer> ctx) {
				return n;
			}

			@Override
			public String toString() {
				return Integer.toString(n);
			}
		};
	}

	// var value
	static NGen var(final String name) {
		return new NGen() {
			@Override
			int n(Map<String, Integer> ctx) {
				return ctx.get(name);
			}

			@Override
			public String toString() {
				return "\"" + name + "\"";
			}
		};
	}

	// range of values for a variable
	static NGen range(final String name, final int from, final int to, final int step) {
		return new NGen() {
			@Override
			int n(Map<String, Integer> ctx) {
				return (to - from) / step + 1;
			}

			@Override
			void set(Map<String, Integer> ctx, int i) {
				ctx.put(name, from + i * step);
			}

			@Override
			public String toString() {
				return "range(\"" + name + "\"," + from + "," + to + (step == 1 ? "" : "," + step) + ")";
			}
		};
	}

	static NGen range(final String name, final int from, final int to) {
		return range(name, from, to, 1);
	}

	// chain of the length one (just one edge)
	static final CGen c = new CGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0, int n1) {
				g.addEdge(n0, n1);
			}

			@Override
			public String toString() {
				return "c";
			}
		};

	// chain n copies of c together
	static CGen c(final NGen ng, final CGen c) {
		return new CGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0, int n1) {
				int n = ng.n(ctx);
				assert n >= 1;
				int u = n0;
				for (int i = 0; i < n; i++) {
					int v = i == n - 1 ? n1 : g.next++;
					ng.set(ctx, i);
					c.gen(ctx, g, u, v);
					u = v;
				}
			}

			@Override
			public String toString() {
				if (c == Tests.c)
					return "c(" + ng + ")";
				return "c(" + ng + "," + c + ")";
			}
		};
	}

	static CGen c(final int n, final CGen c) {
		return c(num(n), c);
	}

	static CGen c(final String name, final CGen c) {
		return c(var(name), c);
	}

	// chain of the given length n, shortcut to c(n, c)
	static CGen c(final int n) {
		return c(n, c);
	}

	static CGen c(final String name) {
		return c(name, c);
	}

	// concatenate specified chains
	static CGen c(final CGen... cs) {
		assert cs.length >= 1;
		if (cs.length == 1)
			return cs[0];
		return new CGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0, int n1) {
				int u = n0;
				for (int i = 0; i < cs.length; i++) {
					int v = i == cs.length - 1 ? n1 : g.next++;
					cs[i].gen(ctx, g, u, v);
					u = v;
				}
			}

			@Override
			public String toString() {
				StringBuilder sb = new StringBuilder();
				sb.append("c(");
				for (int i = 0; i < cs.length; i++) {
					if (i > 0)
						sb.append(",");
					sb.append(cs[i]);
				}
				sb.append(")");
				return sb.toString();
			}
		};
	}

	// concat chain and tree
	static TGen ct(final CGen c, final TGen t) {
		return new TGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0) {
				int n1 = g.next++;
				c.gen(ctx, g, n0, n1);
				t.gen(ctx, g, n1);
			}

			@Override
			public String toString() {
				return "ct(" + c + "," + t + ")";
			}
		};
	}

	// loop chain n times
	static CGen loop(final NGen ng, final CGen c) {
		return new CGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0, int n1) {
				int n = ng.n(ctx);
				assert n >= 2;
				int u = n0;
				for (int i = 0; i < n; i++) {
					int v = i == 0 ? n1 : i == n - 1 ? n0 : g.next++;
					ng.set(ctx, i);
					c.gen(ctx, g, u, v);
					u = v;
				}
			}

			@Override
			public String toString() {
				if (c == Tests.c)
					return "loop(" + ng + ")";
				return "loop(" + ng + "," + c + ")";
			}
		};
	}

	static CGen loop(final int n, final CGen g) {
		return loop(num(n), g);
	}

	static CGen loop(final String name, final CGen g) {
		return loop(var(name), g);
	}

	// simple loop, shortcut to loop(n. c)
	static CGen loop(final int n) {
		return loop(n, c);
	}

	static CGen loop(final String name) {
		return loop(name, c);
	}

	// loop a list of chains
	static CGen loop(final CGen... cs) {
		assert cs.length >= 1;
		if (cs.length == 1)
			return cs[0];
		return new CGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0, int n1) {
				int u = n0;
				for (int i = 0; i < cs.length; i++) {
					int v = i == 0 ? n1 : i == cs.length - 1 ? n0 : g.next++;
					cs[i].gen(ctx, g, u, v);
					u = v;
				}
			}

			@Override
			public String toString() {
				StringBuilder sb = new StringBuilder();
				sb.append("loop(");
				for (int i = 0; i < cs.length; i++) {
					if (i > 0)
						sb.append(",");
					sb.append(cs[i]);
				}
				sb.append(")");
				return sb.toString();
			}
		};
	}

	// tree with n times branches of the given form c
	static TGen t(final NGen ng, final TGen t) {
		return new TGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0) {
				int n = ng.n(ctx);
				for (int i = 0; i < n; i++) {
					ng.set(ctx, i);
					t.gen(ctx, g, n0);
				}
			}

			@Override
			public String toString() {
				return "t(" + ng + "," + t + ")";
			}
		};
	}

	static TGen t(final int n, final TGen t) {
		return t(num(n), t);
	}

	static TGen t(final String name, final TGen t) {
		return t(var(name), t);
	}

	// tree with given branches
	static TGen t(final TGen... ts) {
		assert ts.length >= 1;
		if (ts.length == 1)
			return ts[0];
		return new TGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0) {
				for (TGen t : ts)
					t.gen(ctx, g, n0);
			}

			@Override
			public String toString() {
				StringBuilder sb = new StringBuilder();
				sb.append("t(");
				for (int i = 0; i < ts.length; i++) {
					if (i > 0)
						sb.append(",");
					sb.append(ts[i]);
				}
				sb.append(")");
				return sb.toString();
			}
		};
	}

	// chain with with given tree branches inserted to the first node
	static CGen ic(final CGen c, final TGen... ts) {
		return new CGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0, int n1) {
				c.gen(ctx, g, n0, n1);
				for (TGen t : ts)
					t.gen(ctx, g, n0);
			}

			@Override
			public String toString() {
				StringBuilder sb = new StringBuilder();
				sb.append("ic(");
				sb.append(c);
				for (TGen t : ts) {
					sb.append(",");
					sb.append(t);
				}
				sb.append(")");
				return sb.toString();
			}
		};
	}

	static TGen btRecImpl(int n, int depth, CGen edge) {
		assert depth >= 1;
		if (depth == 1)
			return t(n, edge);
		return t(n, ct(edge, bt(n, depth - 1, edge)));
	}

	// balanced tree with custom edges
	static TGen bt(final int n, final int depth, final CGen edge) {
		final TGen gen = btRecImpl(n, depth, edge);
		return new TGen() {
			@Override
			void gen(Map<String, Integer> ctx, Graph g, int n0) {
				gen.gen(ctx, g, n0);
			}

			@Override
			public String toString() {
				return "bt(" + n + "," + depth + (edge.toString().equals("c") ? "" : "," + edge) + ")";
			}
		};
	}

	// balanced tree with simple edges
	static TGen bt(int n, int depth) {
		return bt(n, depth, c);
	}

	static PrintWriter openTestFile(String desc) throws IOException {
		new File("tests").mkdir();
		PrintWriter out = new PrintWriter(String.format("tests/" + TEST_NAME_FORMAT, ++nTests));
		PrintWriter out1 = new PrintWriter(new FileWriter(LST_FILE, true));
		out1.printf(TEST_NAME_FORMAT + " %s%n", nTests, desc);
		out1.close();
		System.out.printf("Writing test " + TEST_NAME_FORMAT + ": %s%n", nTests, desc);
		return out;
	}

	static void writeGraph(String desc, Graph g, boolean checkOnly) {
		if (g.nVertices > MAX_N)
			throw new AssertionError("nVertices = " + g.nVertices + " > " + MAX_N);
		if (!g.checkConnectivity())
			throw new AssertionError("The graph is not connected");
		List<List<Integer>> paths = g.extractPaths(MAX_PATH_LENGTH);
		if (paths.size() > MAX_PATH_COUNT)
			throw new AssertionError("Path count exceeded: " + paths.size());

		if (checkOnly)
			return;

		try {
			PrintWriter out = openTestFile(desc);
			out.println(g.nVertices + " " + paths.size());
			for (List<Integer> p : paths) {
				out.print(p.size());
				for (int i : p) {
					out.print(" ");
					out.print(i + 1);
				}
				out.println();
			}
			out.close();
		} catch (IOException ex) {
			ex.printStackTrace();
			System.exit(1);
		}
	}

	static void writeExactPaths(String desc, int[]... paths) {
		Graph g = new Graph(paths);
		writeGraph("", g, true);
		try {
			PrintWriter out = openTestFile(desc);
			out.println(g.nVertices + " " + paths.length);
			for (int[] p : paths) {
				out.print(p.length);
				for (int i : p) {
					out.print(" ");
					out.print(i + 1);
				}
				out.println();
			}
			out.close();
		} catch (IOException ex) {
			ex.printStackTrace();
			System.exit(1);
		}
	}

	static void writePaths(String desc, int[]... paths) {
		Graph g = new Graph();
		for (int[] p : paths) {
			for (int i = 1; i < p.length; ++i) {
				g.addEdge(p[i - 1], p[i]);
			}
		}
		writeGraph(desc, g, false);
	}

	static int[] p(int... path) {
		return path;
	}

	static int[] randomPermutation(int n) {
		Integer[] t = new Integer[n];
		for (int i = 0; i < n; ++i) {
			t[i] = i;
		}
		Collections.shuffle(Arrays.asList(t), random);
		int[] rv = new int[n];
		for (int i = 0; i < n; ++i) {
			rv[i] = t[i];
		}
		return rv;
	}

	static void write(String desc, TGen gen) {
		Graph g = new Graph();
		gen.gen(new HashMap<String, Integer>(), g, g.next++);
		g.shuffle();
		writeGraph(desc + "; gen=" + gen, g, false);
	}

	static void writeChain(int n) {
		write(String.format("Chain n=%d", n), c(n - 1));
	}

	static void writeOneCycle(int n) {
		write(String.format("OneCycle n=%d", n), loop(n));
	}

	static void writeCycleWithRegularIcicles(int n, int step) {
		assert n % step == 0;
		write(String.format("CycleWithRegularIcicles n=%d, step=%d", n, step),
			loop(n / step, ic(c(step), c)));
	}

	static void writeCycleWithPeriodicIcicles(int n, int... def) {
		assert def.length % 2 == 0;
		List<CGen> cs = new ArrayList<>();
		int totalStep = 0;
		for (int j = 0; j < def.length; j += 2) {
			int len = def[j];
			int step = def[j + 1];
			totalStep += step;
			cs.add(ic(c(step), c(len)));
		}
		assert n % totalStep == 0;
		write(String.format("CycleWithPeriodicIcicles n=%d, totalStep=%d, def=%s",
			n, totalStep, Arrays.toString(def)), loop(n / totalStep, c(cs.toArray(new CGen[cs.size()]))));
	}

	static void writeTriangleChain(int len1, int len2) {
		Graph g = new Graph();
		for (int i = 1; i < len1; ++i) {
			g.addEdge(i - 1, i);
		}
		for (int i = 0; i < len2; ++i) {
			g.addEdge(i, len1 + i);
			g.addEdge(len1 + i, i + 1);
		}
		writeGraph(String.format("TriangleChain len1=%d, len2=%d", len1, len2), g, false);
	}

	static void randomTriangleTest(int n) {
		int x = (n - 4) / 2;
		n = 4 + 2 * x;
		Graph g = new Graph(new int[] {0, 1, 2, 0});
		for (int i = 1; i <= x; ++i) {
			int rnd = random.nextInt(2 * i + 1);
			g.addEdge(rnd, 2 * i + 1);
			g.addEdge(rnd, 2 * i + 2);
			g.addEdge(2 * i + 1, 2 * i + 2);
		}
		g.addEdge(random.nextInt(n - 1), n - 1);
		writeGraph(String.format("Triangle n=%d", n), g, false);
	}

	static void simplePenicillum(int cycleLength, int nPenicillum) {
		int[] p = randomPermutation(cycleLength + nPenicillum);
		Graph g = new Graph();
		for (int i = 0; i < cycleLength; ++i) {
			g.addEdge(p[i], p[(i + 1) % cycleLength]);
		}
		for (int i = 0; i < nPenicillum; i += 2) {
			int x = random.nextInt(cycleLength);
			g.addEdge(p[x], p[cycleLength + i]);
			g.addEdge(p[x], p[cycleLength + i + 1]);
			g.addEdge(p[cycleLength + i], p[cycleLength + i + 1]);
		}
		writeGraph(String.format("SimplePenicillum cycleLength=%d, nPencillum=%d", cycleLength, nPenicillum),
			g, false);
	}

	static void writeBigCycleAndPenicillum(int cycleLength, int nPenicillum) {
        int oldPenicillum = nPenicillum;
		int[] p = randomPermutation(cycleLength + nPenicillum);
		Graph g = new Graph();
		for (int i = 0; i < cycleLength; ++i) {
			g.addEdge(p[i], p[(i + 1) % cycleLength]);
		}
		int idx = cycleLength;
		while (nPenicillum > 0) {
			int cnt = random.nextInt(nPenicillum) + 1;
			if (cnt == 1) {
				g.addEdge(p[random.nextInt(cycleLength)], p[idx]);
			} else {
				for (int i = 1; i < cnt; ++i) {
					g.addEdge(p[idx + i - 1], p[idx + i]);
				}
				int pnt = random.nextInt(cycleLength);
				g.addEdge(p[idx], p[pnt]);
				if (random.nextBoolean()) {
					g.addEdge(p[idx + cnt - 1], p[pnt]);
				}
			}
			idx += cnt;
			nPenicillum -= cnt;
		}
		writeGraph(String.format("BigCycleAndPenicillum cycleLength=%d, nPencillum=%d", cycleLength, oldPenicillum),
			g, false);
	}

	static void generateTrickyIntervals2(int cs) {
		Graph g = new Graph();
		int prevVertex = 1;
		int xmod = random.nextInt(cs - 1) + 1;
		g.addEdge(0, 1);
		do {
			int size = random.nextInt(cs);
			int lim = size == 0 ? cs : size;
			int nextVertex = prevVertex + 1;
			for (int i = 0; i < lim - 1; ++i) {
				if (nextVertex % cs == xmod) {
					break;
				}
				g.addEdge(nextVertex - 1, nextVertex);
				++nextVertex;
			}
			if (prevVertex + 2 < nextVertex) {
				g.addEdge(nextVertex - 1, prevVertex);
			}
			if (nextVertex % cs == 0) {
				g.addEdge(prevVertex, 0);
			} else {
				g.addEdge(prevVertex, nextVertex);
			}
			prevVertex = nextVertex;
		} while (prevVertex % cs != 0);
		writeGraph(String.format("TrickyIntervals (cycles) n = %d compSize = %d", g.nVertices, cs), g, false);
	}

	static void writeDegreeExceeded(int n, int k) {
		int[] perm = randomPermutation(n);
		Graph g = new Graph();
		for (int i = 1; i < 2 * k; ++i) {
			g.addEdge(perm[0], perm[i]);
		}
		for (int i = 2 * k, j = 0; i < n; ++i) {
			g.addEdge(perm[j], perm[i]);
			j = i;
		}
		writeGraph(String.format("DegreeExceeded n = %d, k = %d", n, k), g, false);
	}

	public static void main(String[] args) throws IOException {
		LST_FILE.delete();

		writeExactPaths("first sample",
				p(0, 1, 4, 5, 1, 2, 3));

		writeExactPaths("second sample (classic Cactus)",
				p(0, 1, 2, 3, 4, 5, 6, 7, 2),
				p(1, 8, 9, 10, 11, 12, 9),
				p(1, 13, 8, 14, 9));

		writeExactPaths("third sample (two vertices 0-1)", p(0, 1));

		writeExactPaths("fourth sample (star)",
				p(0, 1, 2), p(3, 1, 4), p(5, 1, 6), p(7, 1, 8), p(9, 1, 10), p(11, 1, 12), p(13, 1, 14));

		writeExactPaths("one vertex");

		writeExactPaths("two vertices 1-0", p(1, 0));

		writeExactPaths("triangle 0-1-2-0", p(0, 1, 2, 0));

		writeExactPaths("triangle 0-2-1-0", p(0, 2, 1, 0));

		writeExactPaths("small star (second sample in 2010)", p(0, 1, 2), p(1, 3));

		writeExactPaths("hand-made fork2 (v center)", p(0, 1, 2, 3, 4), p(3, 5));
		writeExactPaths("hand-made fork3 (v center)", p(0, 1, 2, 3, 4), p(3, 5), p(3, 6));
		writeExactPaths("hand-made fork2 (e center)", p(0, 1, 2, 3, 4, 5), p(4, 6));
		writeExactPaths("hand-made fork3 (e center)", p(0, 1, 2, 3, 4, 5), p(4, 6), p(4, 7));

		writePaths("hand-made",
				p(0, 1, 2, 3, 4),
				p(5, 6, 7, 8),
				p(3, 6), p(1, 7));

		writePaths("hand-made fork2", p(0, 1, 2, 3, 8, 9, 10, 11, 12, 13, 4, 5), p(6, 5, 7));

		writePaths("hand-made line", p(0, 1, 2, 3, 4, 5), p(5, 6, 7));

		writePaths("hand-made loop", p(0, 1, 2, 3, 4, 2, 7, 5, 6, 7, 8, 0));

		writePaths("hand-made loop chain (anti-RE 2010)", p(2, 1, 0, 8, 3, 1), p(3, 4, 5, 6, 7, 4));

		writePaths("hand-made symmetric letter A", p(0, 1, 2, 3, 4), p(1, 3));

		writePaths("hand-made 2 loops + chain",
				p(2, 1, 0, 2, 3, 4, 2),
				p(4, 5, 6));

		// ----------- chains ------------

		writeChain(100);
		writeChain(MAX_N - 1);
		writeChain(MAX_N);

		// ----------- cycles ------------

		writeOneCycle(100);
		writeOneCycle(MAX_N - 1);
		writeOneCycle(MAX_N);

		// ----------- special overflow ------------

		write("Two 3-loops + long chain from one (anti-overflow)",
				loop(
						ic(c, loop(3)), // triangle
						ic(c, c(MAX_N - 5)), // long chain
						c
				));

		// ----------- cycles with special symmetry cases and algo effectiveness tests ------------

		write("One big(max) cycle with a small icicle",
				loop(
						c(MAX_N - 2),
						ic(c, c)
				));
		write("One big(max) cycle with two small icicles",
				loop(
						c(MAX_N - 4),
						ic(c, c),
						ic(c, c)
				));
		write("One big(max) cycle with two small icicles far away",
				loop(
						c((MAX_N - 4) / 2 - 1),
						ic(c, c),
						c((MAX_N - 4) / 2 + 1),
						ic(c, c)
				));
		write("One big(max) cycle with three icicle groups far away",
				loop(
						c((MAX_N - 27) / 3),
						ic(c, c(2)),
						ic(c, c),
						c((MAX_N - 27) / 3),
						ic(c, c(2)),
						ic(c, c),
						c((MAX_N - 27) / 3),
						ic(c, c(2)),
						ic(c, c)
				));
		write("One big(max) cycle with three small icicles far away",
				loop(
						c((MAX_N - 12) / 3 - 1),
						ic(c, c),
						c((MAX_N - 12) / 3 - 1),
						ic(c, c),
						c((MAX_N - 12) / 3),
						ic(c, c)
				));

		// ------- cycle with regular icicles -----

		writeCycleWithRegularIcicles(4444, 4);
		writeCycleWithRegularIcicles(MAX_N / 2, 1);
		writeCycleWithRegularIcicles(MAX_N / 2, 5);
		writeCycleWithRegularIcicles(45000, 10);

		// ------- cycle with periodic icicles -----

		writeCycleWithPeriodicIcicles(20, 1, 2, 1, 3);
		writeCycleWithPeriodicIcicles(MAX_N / 4, 1, 1, 2, 1);
		writeCycleWithPeriodicIcicles(10000, 50, 51, 50, 49);

		// ------- cycles with complex stuff handing from it -------

		write("Triangle with 3 longest icicles", loop(3, ic(c, c(16665))));
		write("Triangle with 2 longest icicles + one bit smaller", loop(c(2, ic(c, c(16666))), ic(c, c(16665))));
		write("Triangle with 3 long and different icicles", loop(ic(c, c(16666)), ic(c, c(16665)), ic(c, c(16664))));

		write("Cycle with 10000 triangles hanging", loop(10000, ic(c, loop(3))));
		write("Cycle with 10000 boxes hanging", loop(10000, ic(c, loop(4))));
		write("Cycle with 10000 pentas hanging", loop(10000, ic(c, loop(5))));
		write("Cycle with 10000 triangle pairs hanging", loop(10000, ic(c, loop(3), loop(3))));

		write("Cycle with 10000 triangles on a 2-chain", loop(10000, ic(c, c(c, c, loop(3)))));
		write("Cycle with 10000 4-chains", loop(10000, ic(c, c(4))));

		write("Cycle with 5000 triangles on a 7-chain", loop(5000, ic(c, c(c(7), loop(3)))));
		write("Cycle with 5000 boxes on a 6-chain", loop(5000, ic(c, c(c(6), loop(4)))));
		write("Cycle with 5000 pentas on a 5-chain", loop(5000, ic(c, c(c(5), loop(5)))));
		write("Cycle with 5000 triangles+3chains on a 4-chain", loop(5000, ic(c, c(c(4), loop(c, ic(c, c(3)), c)))));
		write("Cycle with 5000 fancy stars with 2 triangles", loop(5000, ic(c, c(c, ic(c, c(c, loop(3), c(c, loop(3)))), c))));

		write("Regular cycle with various stuff hanging",
				loop(1913, c(
						ic(c, c, c),                   // two short icicles hanging                (3 nodes)
						ic(c, loop(3)),                    // triangle hanging                         (3 nodes)
						ic(c, loop(3), c),               // triangle and icicle                      (4 nodes)
						ic(c, c(2), c(2)),                 // two longer icicles                       (5 nodes)
						ic(c, ct(loop(c(2), c(2)), c(2))), // box with longer icicle at the end        (6 nodes)
						ic(c, ct(loop(c, c(2)), c(2)))   // triangle with longer icicle at the end   (5 nodes)
			)));

		// ------- Balanced trees -------

		write("2^8 tree", bt(2, 8));
		write("2^14 tree", bt(2, 14));
		write("3^9 tree", bt(3, 9));
		write("4^7 tree", bt(4, 7));
		write("5^6 tree", bt(5, 6));
		write("7^5 tree", bt(7, 5));
		write("2^13 tree with c(2) edges", bt(2, 13, c(2)));
		write("2^13 tree with triangle edges", bt(2, 13, loop(c, c(2))));
		write("2^13 tree with box edges", bt(2, 13, loop(c(2), c(2))));
		write("6 x 2^12 trees hanging from a loop at 139 edge intervals", loop(6, ic(c(139), bt(2, 12))));
		write("3^6 tree with very fancy edges",
				bt(3, 6, c(
						loop(c(2), c(2)),                          // box
						ic(loop(c, c(2)), c, c, c(2), c(3),  // triangle with a lot of icicles
								c(c(5), loop(c(3), c(3)), c(5)),       // .. including some fancy ones #1
								c(c(3), loop(c(2), c(4)), c(6))        // .. including some fancy ones #2
				)
			)));

		// ------- stars -------

		write("Star with 223 small rays", t(223, c));
		write("Star with 223 rays of len 223", t(223, c(223)));
		write("Star with max small rays", t(MAX_N - 1, c));
		write("Star with 223 rays of len 221+fork3 at the end", t(223, ct(c(221), t(3, c))));
		write("Star with 222 rays of len 221+fork3 at the end + one(other) 222 ray", t(t(222, ct(c(221), t(3, c))), c(222)));
		write("Star with 107 rays of len 223 and 109 rays of len 222", t(t(107, c(223)), t(109, c(222))));
		write("Star with 20k-1 small rays and 15k len 2 rays", t(t(19999, c), t(15000, c(2))));

		write("Star with different rays lens 1-315", t(range("n", 1, 315), c("n")));
		write("Star with different rays lens 1-223 (twice each)", t(2, t(range("n", 1, 223), c("n"))));

		// ------- varying forks -------

		write("Star with different forks spans 1-314", t(range("n", 1, 314), ct(c, t("n", c))));
		write("Loop with different forks spans 1-313", loop(range("n", 1, 313), ic(c, ct(c, t("n", c)))));
		write("Loop with different forks spans 1-221 (twice each)", loop(2, c(range("n", 1, 221), ic(c, ct(c, t("n", c))))));

		// ------- Hanging loops -------

		write("223 x 223 loops hanging from loop", loop(223, ic(c, loop(223))));
		write("223 x 222 loops with sym tail hanging from loop", loop(223, ic(c, loop(c(111), ic(c(111), c)))));
		write("223 x 223 loops with asym tail hanging from loop", loop(223, ic(c, loop(c(111), ic(c(112), c)))));
		write("223 x 223 loops hanging from vertex", t(223, loop(223)));
		write("223 x 222 loops with sym tail hanging from vertex", t(223, loop(c(111), ic(c(111), c))));
		write("223 x 223 loops with asym tail hanging from vertex", t(223, loop(c(111), ic(c(112), c))));

		// ----------- other ------------

		for (int test = 56; test <= 60; ++test)
			writeDegreeExceeded((test - 10) * 1000, (test - 10) * 10);

		writeTriangleChain(100, 98);
		writeTriangleChain(101, 100);
		writeTriangleChain(MAX_N / 2 + 1, MAX_N / 2 - 1);
		writeTriangleChain(MAX_N / 2, MAX_N / 2 - 1);
		writeTriangleChain(MAX_N / 2 - 1, MAX_N / 2 - 3);

		randomTriangleTest(MAX_N);
		randomTriangleTest(MAX_N);
		randomTriangleTest(MAX_N);

		int mn = (MAX_N / 3) * 3;
		writeBigCycleAndPenicillum(3 * MAX_N / 4, MAX_N / 4);
		writeBigCycleAndPenicillum(2 * mn / 3, mn / 3);
		writeBigCycleAndPenicillum(3 * MAX_N / 4, MAX_N / 4);
		simplePenicillum(3 * MAX_N / 4, MAX_N / 4);

		long[] seeds = {
			2226861971064629152L,
			-2832785353362038500L,
			-6876602688646264131L,
			3964041828427475130L,
			7611464926608697184L,
			-7139336543207181995L,
			-624544712540808086L,
			514579434522028778L,
			-3615143344253293305L,
			-2930983803661830815L,
		};
		for (long seed : seeds) {
			random = new Random(seed);
			generateTrickyIntervals2(random.nextInt(250) + 5);
		}
	}
}
