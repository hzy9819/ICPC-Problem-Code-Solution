import java.util.*;

import ru.ifmo.testlib.*;
import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem K: King's Inspection.
 *
 * @author Mikhail Dvorkin (reworked by Roman Elizarov)
 */
public class Check implements Checker {
	private static final String NO_ROUTE = "There is no route, Karl!";

	int n;
	int m;
	Set<Long> edges;
	String outcomePrefix;

	private void readInf(InStream inf) {
		n = inf.nextInt();
		m = inf.nextInt();
		edges = new TreeSet<>();
		for (int i = 0; i < m; i++) {
			int a = inf.nextInt() - 1;
			int b = inf.nextInt() - 1;
			edges.add((long) a * n + b);
		}
		outcomePrefix = String.format(Locale.US, "n=%d, m=%d: " , n, m);
	}

	private int[] readOuf(InStream ouf, Outcome.Type wa, Outcome.Type pe) {
		if (NO_ROUTE.equals(ouf.nextLine())) {
			if (!ouf.seekEoF())
				throw new Outcome(pe, "Extra data in output file");
			return null;
		}
		ouf.reset();
		int[] route = new int[n + 1];
		for (int i = 0; i <= n; i++) {
			route[i] = ouf.nextInt() - 1;
		}
		if (!ouf.seekEoF())
			throw new Outcome(pe, "Extra data in output file");
		for (int i = 0; i <= n; i++) {
			if (route[i] < 0 || route[i] >= n || (i == 0 || i == n) && route[i] != 0) {
				throw new Outcome(wa, String.format(Locale.US, outcomePrefix + "Invalid city #%d: %d", i + 1, route[i] + 1));
			}
		}
		boolean[] present = new boolean[n];
		for (int i = 0; i < n; i++) {
			if (!edges.contains((long) route[i] * n + route[i + 1])) {
				throw new Outcome(WA, String.format(Locale.US, outcomePrefix + "Edge #%d in not present in graph: %d -> %d", i + 1, route[i] + 1, route[i + 1] + 1));
			}
			if (present[route[i]]) {
				throw new Outcome(WA, String.format(Locale.US, outcomePrefix + "City %d visited twice", route[i] + 1));
			}
			present[route[i]] = true;
		}
		return route;
	}

	@Override
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		readInf(inf);
		int[] ja = readOuf(ans, FAIL, FAIL);
		int[] pa = readOuf(ouf, WA, PE);
		if (pa == null) {
			if (ja != null) {
				return new Outcome(WA, outcomePrefix + "Route not found, but there is one");
			}
			return new Outcome(OK, outcomePrefix + "There is no route indeed");
		}
		if (ja == null) {
			return new Outcome(FAIL, outcomePrefix + "Unexpected route found!");
		}
		return new Outcome(OK, outcomePrefix + "Correct route found");
	}
}
