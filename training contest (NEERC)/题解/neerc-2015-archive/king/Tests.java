import java.io.*;
import java.util.*;

public class Tests {
	private static File dir = new File("tests");
	private static File visDir = new File("visualized");
	private int curTest = 1;
	private static boolean verbose = true;
	private static boolean visualize = true;
	private static boolean diminishedMode = false;

	private String testName;
	private PrintWriter out;
	private static PrintWriter tests;
	private Random r = new Random(5516681322906813814L);
	
	public final static int DEBUG_MAX = 100;
	public final static int MAX = diminishedMode ? DEBUG_MAX : Validate.MAX;
	public final static int EXTRA = Validate.EXTRA;
	
	int n;
	Collection<Long> edges = new TreeSet<>();

	public void run() {
		n = 4;
		useArrayList();
		e(0, 3);
		e(3, 0);
		e(3, 1);
		e(1, 0);
		e(2, 3);
		e(0, 2);
		t(true, "sample 1", false, true);
		
		n = 4;
		useArrayList();
		e(0, 3);
		e(0, 3);
		e(1, 1);
		t(false, "sample 2", false, false);
		
		n = 4;
		e(0, 1);
		e(1, 2);
		e(0, 2);
		e(2, 3);
		e(3, 0);
		t(true, "square with diagonal", false, true);
		
		n = 5;
		e(0, 1);
		e(1, 2);
		e(0, 4);
		e(4, 2);
		e(0, 2);
		e(2, 3);
		e(3, 0);
		t(false, "manual: two ways", false, true);
		
		n = 2;
		e(0, 1);
		e(1, 0);
		t(true, "min. test", false, true);
		
		n = 3;
		e(0, 1);
		e(1, 0);
		t(false, "isolated vertex", false, false);
		
		n = 3;
		e(2, 1);
		e(1, 2);
		t(false, "isolated starting vertex", false, false);
		
		tGrid(3, 3);
		tGrid(2, 3);
		tGrid(2, 4);
		
		for (n = 2; n <= 5; n++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i != j) {
						for (int k = 0; k < (n + EXTRA) / n / (n - 1); k++) {
							e(i, j);
						}
					}
				}
			}
			t(true, "full graph");
		}
		
		n = 11;
		e/*BothDir*/(0, 2);
		eBothDir(0, 4);
		eBothDir(0, 6);
		eBothDir(0, 8);
		eBothDir(1, 2);
		eBothDir(2, 3);
		eBothDir(3, 4);
		eBothDir(4, 5);
		eBothDir(5, 6);
		eBothDir(6, 7);
		//eBothDir(7, 8);
		eBothDir(8, 1);
		eBothDir(3, 9);
		eBothDir(7, 10);
		eBothDir(9, 1);
		//eBothDir(9, 5);
		eBothDir(10, 1);
		eBothDir(10, 5);
		t(false, "Herschel graph, diminished");
		
		n = 6;
		for (int i = 0; i < 4; i++) {
			eBothDir(i, (i + 1) % 4);
			eBothDir(i, 4);
			eBothDir(i, 5);
		}
		t(true, "octahedron graph");
		
		n = 20;
		addCycle();
		eBothDir(0, 13);
		eBothDir(1, 11);
		eBothDir(2, 18);
		eBothDir(3, 10);
		eBothDir(4, 17);
		eBothDir(5, 9);
		eBothDir(6, 16);
		eBothDir(7, 14);
		eBothDir(8, 12);
		eBothDir(15, 19);
		t(true, "dodecahedron graph, diminished");
		
		for (int n_ : new int[]{12, EXTRA, EXTRA / 2}) {
			n = n_;
			addCycle();
			for (int i = 0; i < n; i++) {
				e(i, (i + n / 2) ^ 1);
				if (n <= EXTRA / 2) {
					e(i, i - 1);
				}
			}
			t(true, "Franklin graph, diminished");		// n * (n - 1) <= MAX + 20
			n = (int) Math.sqrt(MAX) - 1;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) {
						continue;
					}
					e(i, j);
				}
			}
			t(true, "full graph", true, true, true);
		}
		
		for (n = 8; n <= 16; n += 8) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < 2; j++) {
					e(i, (i * 2 + j) & (n - 1));
				}
			}
			t(true, "de Bruijn graph");
		}

		// n * (n - 1) <= MAX + 20
		n = (int) Math.sqrt(MAX) - 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					continue;
				}
				e(i, j);
			}
		}
		t(true, "full graph", true, true, true);
		
		for (Generator gen : allGenerators) {
			int d = 2 + r.nextInt(4);
			n = (int) Math.sqrt(d * MAX) - 1;
			gen.generate(n * (n - 1) / d);
		}
		
		for (int t = 0; t < 2; t++) {
			int m = n / 3;
			n = 3 * m;
			for (int i = 0; i < m; i++) {
				e(i, i + 1);
				e(m, m + i);
				e(m + i, 0);
			}
			for (int i = 0; i < EXTRA * t; i++) {
				eRandom();
			}
			t(false, "many parallel 2-paths" + (t == 0 ? "" : " with noise"), true, false, false);
		}
		
		{
			int m = EXTRA + 1;
			n = m * m + 2;
			int k = 2;
			for (int i = 0; i < m; i++) {
				int prev = 0;
				for (int j = 0; j < m; j++) {
					e(prev, k);
					prev = k;
					k++;
				}
				e(prev, 1);
			}
			e(1, 0);
			t(false, "many parallel long paths");
		}
		
		n = 8;
		for (int d : new int[]{4, 3, 0}) {
			for (boolean noise: new boolean[]{false, true}) {
				boolean expected = d >= 4 || noise;
				for (;;) {
					for (int i = 0; i < n; i++) {
						e(i, i ^ 1);
						e(i, i ^ 2);
						e(i, i ^ d);
					}
					if (noise) {
						while (edges.size() < n + EXTRA) {
							eRandom();
						}
					}
					if (solve() == expected) {
						break;
					}
					clear();
				}
				t(expected, (d == 4 ? "cube" : "some") + " graph" + (noise ? " with noise" : ""));
			}
		}
		
		for (n = 10; n <= 11; n++) {
			for (int m = 4, k = m, i = 0; i < m; i++) {
				for (int j = i + 1; j < m; j++) {
					eBothDir(i, k);
					eBothDir(j, k);
					k++;
				}
			}
			if (n == 10) {
				t(false, "full graph m=4, doubled");
			} else {
				eBothDir(0, 10);
				eBothDir(1, 10);
				t(false, "envelope, doubled");
			}
		}

		for (Generator gen : allGenerators) {
			for (n = 3; n <= 21; n += 3) {
				gen.generate(false);
				gen.generate(true);
			}
		}
		
		n = 7;
		while (edges.size() < n + EXTRA) {
			e(r.nextInt(n - 1), r.nextInt(n - 1));
		}
		t(false, "random graph with isolated vertex", true, false);
		
		n = 7;
		while (edges.size() < n + EXTRA) {
			e(r.nextInt(n - 1) + 1, r.nextInt(n - 1) + 1);
		}
		t(false, "random graph with isolated vertex 0", false, false);
		
		n = EXTRA;
		for (int s : new int[]{2, 3, n / 2 - 1, n / 2, n / 2 + 1, n - 3, n - 2, n - 1}) {
			addCycle();
			for (int i = 0; i < n; i++) {
				e(i, i + s);
			}
			t(true, "cycle with all chords +" + s);
		}
		
		for (n = EXTRA - 1; n <= EXTRA; n++) {
			for (int i = 0; i < n; i++) {
				if (i > 0) {
					e(i, i + 1);
				}
				e(i, i + 2);
			}
			t(n % 2 == 1, "path with all chords +2");
		}
		
		for (n = EXTRA; n <= EXTRA + 1; n++) {
			for (int i = 0; i < n; i++) {
				if (i > 0) {
					e(i, i + 1);
				}
				if (i != EXTRA / 3) {
					e(i, i + 2);
				}
			}
			t(false, "path with almost all chords +2");
		}
		
		n = EXTRA;
		addCycle();
		for (int i = 0; i < n; i++) {
			e(i, i + r.nextInt(EXTRA - 1) + 1);
		}
		t(true, "cycle with n random chords");
		
		for (int n_ : new int[]{EXTRA, MAX}) {
			n = n_;
			addCycle();
			List<Integer> p = randomPerm(EXTRA);
			for (int i = 0; i < EXTRA; i++) {
				e(i, p.get(i));
			}
			t(true, "cycle with permutation chords");
		}
		
		for (n = EXTRA; n <= 4 * EXTRA; n += EXTRA) {
			addCycle();
			for (int i = 0; i < EXTRA; i++) {
				e(i, i * i);
			}
			t(true, "cycle with (i -> i^2) chords");

			addCycle();
			List<Integer> p = randomPerm(EXTRA);
			for (int i = 0; i < EXTRA; i++) {
				e(p.get(i), p.get(EXTRA - 1 - i));
			}
			t(true, "cycle with random distinct chords");
		}
		
		n = MAX;
		t(false, "empty graph", true, false);
		
		tRandomChords(10, 1);
		tRandomChords(EXTRA, EXTRA);
		tRandomChords(MAX, 1);
		tRandomChords(MAX, EXTRA);
		
		for (int d = 2; d <= 3; d++) {
			n = MAX;
			addCycle();
			for (int i = 0; i < EXTRA; i++) {
				int j = r.nextInt(n);
				e(j, j + d);
			}
			t(true, "cycle with few chords +" + d);
		}
		
		n = MAX;
		addCycle();
		for (int i = 0; i < EXTRA; i++) {
			int j = r.nextInt(n);
			e(i, j);
		}
		t(true, "cycle with random chords from 0.." + (EXTRA - 1));
		
		n = MAX;
		addCycle();
		for (int i = 0; i < EXTRA / 2; i++) {
			int j = r.nextInt(n);
			e(j, j + 2);
			e(j + 1, j + 3);
		}
		t(true, "cycle with few pairs of chords");
	}

	boolean solve() {
		return solveArray() != null;
	}
	
	int[] solveArray() {
		String s = solveString();
		if (s.equals(king_md.NO_ROUTE)) {
			return null;
		}
		String[] ss = s.split("\\s");
		int[] result = new int[n];
		for (int i = 0; i < n; i++) {
			result[i] = Integer.parseInt(ss[i]) - 1;
		}
		return result;
	}

	private String solveString() {
		int[][] fromAndTo = fromAndTo();
		return new king_md().solve(n, fromAndTo[0], fromAndTo[1]);
	}
	
	boolean isNice() {
		int[][] fromAndTo = fromAndTo();
		int[] from = fromAndTo[0];
		int[] to = fromAndTo[1];
		int m = from.length;
		int[] inDegree = new int[n];
		int[] outDegree = new int[n];
		for (int i = 0; i < m; i++) {
			outDegree[from[i]]++;
			inDegree[to[i]]++;
		}
		for (int i = 0; i < n; i++) {
			if (inDegree[i] == 0 || outDegree[i] == 0) {
				return false;
			}
		}
		return true;
	}
	
	int[][] fromAndTo() {
		int m = edges.size();
		int[] from = new int[m];
		int[] to = new int[m];
		int i = 0;
		for (long edge : edges) {
			from[i] = (int) (edge / MAX);
			to[i] = (int) (edge % MAX);
			i++;
		}
		return new int[][]{from, to};
	}
	
	abstract class Generator {
		boolean ok(@SuppressWarnings("unused") int a, @SuppressWarnings("unused") int b) {
			return true;
		}
		boolean possible(@SuppressWarnings("unused") boolean ans) {
			return true;
		}
		boolean mustBeNice() {
			return true;
		}
		void prepare() {}
		
		void generate(boolean ans) {
			generate(ans, n + EXTRA, false);
		}
		
		void generate(int edgesNum) {
			generate(null, edgesNum, true);
		}
		
		void generate(Boolean ans, int edgesNum, boolean addIsolated) {
			if (ans != null && !possible(ans)) {
				return;
			}
			boolean mustBeNice = mustBeNice();
			System.out.println("Will now generate " + (mustBeNice ? "nice " : "") + this + ", n=" + n + (edgesNum == n + EXTRA ? "" : ", edges=" + edgesNum) + (ans == null ? "" : ", " + ans) + "...");
			for (;;) {
				clear();
				if (n <= 6) {
					useArrayList();
				}
				prepare();
				while (edges.size() < edgesNum) {
					for (;;) {
						int a = r.nextInt(n);
						int b = r.nextInt(n);
						if (a == b) {
							continue;
						}
						if (!ok(a, b)) {
							continue;
						}
						e(a, b);
						break;
					}
				}
				if (mustBeNice && !isNice()) {
					continue;
				}
				if (ans == null || solve() == ans) {
					break;
				}
			}
			t(ans, this.toString(), true, mustBeNice, addIsolated);
		}
	}
	
	Generator randomGraph = new Generator() {
		@Override
		public String toString() {
			return "random graph";
		}
	};
	
	Generator randomBigraph = new Generator() {
		@Override
		public boolean ok(int a, int b) {
			return a % 2 != b % 2;
		}
		
		@Override
		public boolean possible(boolean ans) {
			return n % 2 == 0 || !ans;
		}
		
		@Override
		public String toString() {
			return "random bigraph";
		}
	};
	
	Generator hourglass = new Generator() {
		@Override
		public boolean ok(int a, int b) {
			return !(a < n / 2 && b > n / 2 || b < n / 2 && a > n / 2);
		}
		
		@Override
		public boolean possible(boolean ans) {
			return !ans;
		}
		
		@Override
		public String toString() {
			return "hourglass";
		}
		
		@Override
		boolean mustBeNice() {
			return n >= 6;
		}
	};

	Generator hourglassWithEdge = new Generator() {
		@Override
		public boolean ok(int a, int b) {
			return !(a < n / 2 && b > n / 2 || b < n / 2 && a > n / 2);
		}
		
		@Override
		public String toString() {
			return "hourglass with edge";
		}

		@Override
		public void prepare() {
			e(0, n - 1);
		}
		
		@Override
		boolean mustBeNice() {
			return n >= 6;
		}
	};
	
	Generator dag = new Generator() {
		@Override
		public boolean ok(int a, int b) {
			return a < b;
		}
		
		@Override
		public boolean possible(boolean ans) {
			return !ans;
		}
		
		@Override
		public String toString() {
			return "random dag";
		}
		
		@Override
		boolean mustBeNice() {
			return false;
		}
	};
	
	Generator dagWithEdge = new Generator() {
		@Override
		public boolean ok(int a, int b) {
			return a < b;
		}
		
		@Override
		boolean possible(boolean ans) {
			return ans ? n <= 12: n >= 6;
		}
		
		@Override
		public String toString() {
			return "random dag with source-sink edge";
		}
		
		@Override
		public void prepare() {
			e(n - 1, 0);
		}
	};
	
	Generator[] allGenerators = new Generator[]{
			randomGraph, randomBigraph,
			hourglass, hourglassWithEdge,
			dag, dagWithEdge
	};

	void tRandomChords(int num, int chords) {
		n = num;
		addCycle();
		while (edges.size() < n + chords) {
			eRandom();
		}
		t(true, "random chords");
	}

	void tGrid(int a, int b) {
		n = a * b;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				if (i + 1 < a) {
					eBothDir(b * i + j, b * (i + 1) + j); 
				}
				if (j + 1 < b) {
					eBothDir(b * i + j, b * i + j + 1); 
				}
			}
		}
		t(a * b % 2 == 0, "grid " + a + "x" + b);
	}
	
	void addCycle() {
		for (int i = 0; i < n; i++) {
			e(i, i + 1);
		}
	}
	
	void eRandom() {
		for (;;) {
			int a = r.nextInt(n);
			int b = r.nextInt(n);
			if (a != b) {
				e(a, b);
				return;
			}
		}
	}
	
	void eBothDir(int from, int to) {
		e(from, to);
		e(to, from);
	}

	void e(int from, int to) {
		edges.add(((from + n) % n) * 1L * MAX + ((to + n) % n));
	}
	
	void t(boolean expected, String desc) {
		t(expected, desc, true, true);
	}
	
	void t(Boolean expected, String desc, boolean shuffleAndExpand, boolean mustBeNice) {
		t(expected, desc, shuffleAndExpand, mustBeNice, false);
	}

	void t(Boolean expected, String desc, boolean shuffleAndExpand, boolean mustBeNice, boolean addIsolated) {
		int[] solveArray = null;
		if (expected != null) {
			solveArray = solveArray();
			assert (solveArray != null) == expected : "Unexpected answer " + !expected;
		}
		if (mustBeNice) {
			assert isNice() : "Not nice";
		}
		int nOrig = n;
		int nIsolated = 0;
		int nExpanded = 0;
		
		if (addIsolated) {
			assert n < MAX;
			n = edges.size() - EXTRA;
			assert n > nOrig;
			nIsolated = n - nOrig;
		} else if (shuffleAndExpand && edges.size() > 0 && n < MAX) {
			TreeSet<Long> toExpand = new TreeSet<>();
			int expanded;
			switch (r.nextInt(4)) {
			case 0: expanded = 0; break;
			case 1: expanded = 1; break;
			case 2: expanded = 2; break;
			default: expanded = r.nextInt(n + 1); break;
			}
			ArrayList<Long> edgesTemp = new ArrayList<Long>(edges);
			while (toExpand.size() < expanded) {
				if (solveArray != null) {
					int i = r.nextInt(n);
					toExpand.add(solveArray[i] * 1L * MAX + solveArray[(i + 1) % n]);
				} else {
					toExpand.add(edgesTemp.get(r.nextInt(edgesTemp.size())));
				}
			}
			int more = toExpand.size();
			for (long edge : toExpand) {
				int toAdd = (MAX - n) / more;
				n += toAdd;
				edges.remove(edge);
				int from = (int) (edge / MAX);
				int to = (int) (edge % MAX);
				for (int i = 0; i < toAdd; i++) {
					e(from, n - 1 - i);
					from = n - 1 - i;
				}
				e(from, to);
				more--;
			}
			nExpanded = n - nOrig;
		}
		
		edges = new ArrayList<Long>(edges);
		List<Integer> rename = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			rename.add(i);
		}
		if (shuffleAndExpand) {
			Collections.shuffle((List<?>) edges, r);
			Collections.shuffle(rename, r);
			if (addIsolated) {
				for (int i = 0; i < n; i++) {
					if (rename.get(i) == 0) {
						rename.set(i, rename.get(0));
						rename.set(0, 0);
						break;
					}
				}
			}
		}
		
		int m = edges.size();
		int[] from = new int[m];
		int[] to = new int[m];
		int edgeNum = 0;
		for (long edge : edges) {
			from[edgeNum] = rename.get((int) (edge / MAX));
			to[edgeNum] = rename.get((int) (edge % MAX));
			edgeNum++;
		}
		
		desc += ", n=" + nOrig;
		if (nExpanded > 0) {
			desc += "+" + nExpanded + "expanded";
		}
		if (nIsolated > 0) {
			desc += "+" + nIsolated + "isolated";
		}
		desc += ", +" + (edges.size() - n) + " edges, " + (expected == Boolean.TRUE && (nIsolated == 0) ? "YES" : "NO");
		open(desc);
		out.println(n + " " + edges.size());
		for (int i = 0; i < m; i++) {
			out.println((from[i] + 1) + " " + (to[i] + 1));
		}
		close();
		if (visualize && n <= DEBUG_MAX) {
			try {
				out = new PrintWriter(new File(visDir, testName + ".dot"));
				out.println("digraph test" + testName + " {");
				out.println("\td[label=\"" + testName + ": " + desc + "\" shape=box]");
				for (int i = 1; i <= n; i++) {
					out.println("\tv" + i);
				}
				for (int i = 0; i < m; i++) {
					out.println("\tv" + (from[i] + 1) + " -> v" + (to[i] + 1) + ";");
				}
				out.println("}");
				out.close();
			} catch (FileNotFoundException e) {
				throw new RuntimeException(e);
			}
		}
		n = nOrig;
		clear();
	}
	
	void clear() {
		edges = new TreeSet<>();
	}

	void useArrayList() {
		edges = new ArrayList<>();
	}
	
	List<Integer> randomPerm(int m) {
		List<Integer> p = new ArrayList<>();
		for (int i = 0; i < m; i++) {
			p.add(i);
		}
		Collections.shuffle(p, r);
		return p;
	}
	
	private void open(String desc) {
		try {
			testName = String.format(Locale.US, "%03d", curTest);
			out = new PrintWriter(new File(dir, testName));
			tests.println(testName + "\t" + desc);
			if (verbose) { 
				System.out.print("Generating " + testName + " {" + desc + "}");
			}
		} catch (IOException e) {
			throw new RuntimeException("Unable to open " + testName + " for writing", e);
		}
	}

	private void close() {
		out.close();
		if (verbose) {
			System.out.println(" - done.");
		}
		curTest++;
	}

	static void checkMode() {
		if (diminishedMode) {
			System.err.println("$%#$%**%^&*%^&* IMPORTANT! Turn off the diminished mode!! $^@&*^&%^&*%^&");
		}
	}
	
	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		checkMode();
		dir.mkdirs();
		tests = new PrintWriter(new File(dir, "tests.lst"));
		if (visualize) {
			visDir.mkdirs();
		}
		new Tests().run();
		tests.close();
		checkMode();
	}
}
