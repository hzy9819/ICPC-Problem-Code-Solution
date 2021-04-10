import java.util.*;
import java.io.*;

public class easy_al {
    static final int MAXN = 10;
    static final int MINK = 8;
    static final int MAXK = 14;
    static final int MAXP = 10;

    static int rangeInt(int x, int a, int b) {
	if (x < a || x > b) throw new RuntimeException(x + " should be between " + a + " and " + b);
	return x;
    }

    public static void main(String args[]) throws Exception {
	Scanner in = new Scanner(new File("easy.in"));
	PrintWriter out = new PrintWriter("easy.out");
	
	int n = rangeInt(in.nextInt(), 2, MAXN), k = rangeInt(in.nextInt(), MINK, MAXK);
	int a[][] = new int[n][];
	for (int i = 0; i < n; i++) {
	    int p = rangeInt(in.nextInt(), 1, MAXP);
	    a[i] = new int[p];
	    for (int j = 0; j < p; j++) {
		a[i][j] = rangeInt(in.nextInt(), 0, 49);
	    }
	}
	
	if (in.hasNext()) throw new RuntimeException("Extra info in the input");
	
	int cnt = 0, tot = 0;
	
	all:
	for (int i = 0; i < MAXP; i++) {
	    for (int j = 0; j < n; j++) {
		int cur = i < a[j].length ? a[j][i] : 50;
		if (cur >= tot) {
		    //System.err.println("selected on i = " + i);
		    ++cnt;
		    tot += cur;
		    if (cnt == k) break all;
		}
	    }
	}
	
	if (cnt < k) tot += 50 * (k - cnt);
	out.println (tot);
	
	out.close();
    }
}
