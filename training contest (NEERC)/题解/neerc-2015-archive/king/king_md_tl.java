import java.io.*;
import java.util.*;

public class king_md_tl {
	static final String NO_ROUTE = "There is no route, Karl!";

	public void run() {
		n = in.nextInt();
		int m = in.nextInt();
		int[] eFrom = new int[m];
		int[] eTo = new int[m];
		for (int i = 0; i < m; i++) {
			eFrom[i] = in.nextInt() - 1;
			eTo[i] = in.nextInt() - 1;
		}
		out.println(solve(n, eFrom, eTo));
	}

	public String solve(int v, int[] eFrom, int[] eTo) {
		n = v;
		for (int i = 0; i < n; i++) {
			from.add(new TreeSet<Integer>());
			to.add(new TreeSet<Integer>());
		}
		for (int i = 0; i < eTo.length; i++) {
			new Edge(eFrom[i], eTo[i]).register();
		}
		for (int i = 1; i < n; i++) {
			if (from.get(i).size() != 1 || to.get(i).size() != 1) {
				continue;
			}
			Edge head = allEdges.get(to.get(i).iterator().next());
			Edge tail = allEdges.get(from.get(i).iterator().next());
			head.unregister();
			tail.unregister();
			new Edge(head, tail).register();
		}
		
		visited = new boolean[n];
		try {
			search(0);
			throw new Done(NO_ROUTE);
		} catch (Done e) {
			return e.result;
		}
	}
	
	int n;
	List<Set<Integer>> from = new ArrayList<>();
	List<Set<Integer>> to = new ArrayList<>();
	List<Edge> allEdges = new ArrayList<>();
	boolean[] visited;
	int cumLen;
	List<Edge> routeEdges = new ArrayList<>();
	
	void search(int v) {
		visited[v] = true;
		int must = -1;
		for (int id : from.get(v)) {
			Edge edge = allEdges.get(id);
			if (edge.head != null) {
				if (must >= 0) {
					throw new Done(NO_ROUTE);
				}
				must = id;
			}
		}
		for (int id : from.get(v)) {
			Edge edge = allEdges.get(id);
			if (must >= 0 && id != must) {
				continue;
			}
			if (edge.finish == 0) {
				if (cumLen + edge.len != n) {
					continue;
				}
				routeEdges.add(edge);
				StringBuilder sb = new StringBuilder();
				sb.append(1);
				for (Edge routeEdge : routeEdges) {
					routeEdge.appendTo(sb);
				}
				throw new Done(sb.toString());
			}
			if (visited[edge.finish]) {
				continue;
			}
			routeEdges.add(edge);
			cumLen += edge.len;
			search(edge.finish);
			cumLen -= edge.len;
			routeEdges.remove(routeEdges.size() - 1);
		}
		visited[v] = false;
	}
	
	@SuppressWarnings("serial")
	class Done extends RuntimeException {
		String result;

		public Done(String result) {
			this.result = result;
		}
	}

	class Edge {
		int start, finish;
		Edge head, tail;
		int id;
		int len;

		Edge() {
			this.id = allEdges.size();
			allEdges.add(this);
		}
		
		Edge(int start, int finish) {
			this();
			this.start = start;
			this.finish = finish;
			this.len = 1;
		}
		
		Edge(Edge head, Edge tail) {
			this();
			this.start = head.start;
			this.finish = tail.finish;
			this.head = head;
			this.tail = tail;
			this.len = head.len + tail.len;
		}
		
		void register() {
			from.get(start).add(id);
			to.get(finish).add(id);
		}
		
		void unregister() {
			from.get(start).remove(id);
			to.get(finish).remove(id);
		}
		
		public void appendTo(StringBuilder sb) {
			if (head == null) {
				sb.append(" " + (finish + 1));
			} else {
				head.appendTo(sb);
				tail.appendTo(sb);
			}
		}
	}

	static Scanner in;
	static PrintWriter out;
	
	public static void main(String[] args) throws IOException {
		String fileName = king_md_tl.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
		String inputFileName = fileName + ".in";
		String outputFileName = fileName + ".out";
		
		Locale.setDefault(Locale.US);
		in = new Scanner(new File(inputFileName));
		out = new PrintWriter(outputFileName);
		new king_md_tl().run();
		in.close();
		out.close();
	}
}
