import ru.ifmo.validate.*;
import java.util.Arrays;
import java.util.Stack;
import java.util.HashSet;

public class Validate implements Validator {
    static final int MAXN = 50000;
    static final int MAXQ = 100000;

    private final int OPEN = 1;
    private final int CLOSE = -1;

    private class Bracket implements Comparable<Bracket> {
        int pos;
        int pair;
        int type;

        public Bracket(int pos, int pair) {
            this.pos = pos;
            this.pair = pair;
            this.type = (pos < pair ? OPEN : CLOSE);
        }

        public int compareTo(Bracket e) {
            if (pos != e.pos) {
                return pos - e.pos;
            }
            if (type != e.type) {
                return type - e.type;
            }
            return e.pair - pair;
        }
    }

    private class Edge implements Comparable<Edge> {
        int from;
        int to;

        public Edge(int from, int to) {
            if (from > to) {
                int tmp = from;
                from = to;
                to = tmp;
            }
            this.from = from;
            this.to = to;
        }

        public int compareTo(Edge e) {
            if (from != e.from) {
                return from - e.from;
            }
            return to - e.to;
        }
    }

    private void validatePolygon(int n, int[] dx, int[] dy) {
        for (int i = 0; i < n - 3; i++) {
            int diff = Math.abs(dx[i] - dy[i]);
            diff = Math.min(diff, n - diff);
            assert (diff >= 2);
        }
        
        HashSet<Edge> set = new HashSet<Edge>();
        for (int i = 0; i < n - 3; i++) {
            Edge e = new Edge(dx[i], dy[i]);
            assert (!set.contains(e));
            set.add(e);
        }

        Bracket[] brackets = new Bracket[2 * (n - 3)];
        for (int i = 0; i < n - 3; i++) {
            int x = dx[i];
            int y = dy[i];
            if (x > y) {
                int tmp = x;
                x = y;
                y = tmp;
            }
            brackets[2 * i]     = new Bracket(x, y);
            brackets[2 * i + 1] = new Bracket(y, x);
        }
        Arrays.sort(brackets);

        Stack<Bracket> stack = new Stack<Bracket>();
        for (int i = 0; i < 2 * (n - 3); i++) {
            Bracket b = brackets[i];
            if (b.type == OPEN) {
                stack.push(b);
            } else {
                assert (!stack.empty());
                Bracket top = stack.pop();
                assert (top.pos == b.pair && top.pair == b.pos);
            }
        }
        assert (stack.empty());
    }

	@Override
	public void validate(ValidatingScanner in) {
		int n = in.nextInt("n", 4, MAXN);
        in.eoln();                    
		
		int[] dx = new int[n - 3];
		int[] dy = new int[n - 3];
        
        for (int i = 0; i < n - 3; i++) {
			dx[i] = in.nextInt("dx_" + i, 1, n);
			dy[i] = in.nextInt("dy_" + i, 1, n);
            in.eoln();
		}

		validatePolygon(n, dx, dy);
		
		int q = in.nextInt("q", 1, MAXQ);
        in.eoln();                    
        
        for (int i = 0; i < q; i++) {
			in.nextInt("qx_" + i, 1, n);
			in.nextInt("qy_" + i, 1, n);
            in.eoln();
		} 
        
        in.close();
	}
}
