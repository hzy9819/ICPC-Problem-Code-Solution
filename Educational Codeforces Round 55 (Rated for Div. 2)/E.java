import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Scanner;

public class E {
	public static void main(String [] args) {
		InputStream ins = System.in;
		OutputStream outs = System.out;
		Scanner in = new Scanner(ins);
		PrintWriter out = new PrintWriter(outs);
		Solver sol = new Solver();
		sol.solve(in, out);
		out.close();
	}

	static class Solver {
		public void solve(Scanner in, PrintWriter out) {
			int n = in.nextInt(), c = in.nextInt();
			int [] a = new int[n + 10];
			int [] s = new int[500010];
			int [] s_min = new int[500010];
			int sum = 0, ans = 0;

			for(int i = 1; i <= n; ++i) {
				a[i] = in.nextInt();
				if(a[i] == c)
					sum++;
				else {
					if(s_min[a[i]] > s[a[i]] - sum)
						s_min[a[i]] = s[a[i]] - sum;
					s[a[i]]++;
					if(ans < s[a[i]] - sum - s_min[a[i]])
						ans = s[a[i]] - sum - s_min[a[i]];
				}
			}
			out.println(ans + sum);
		}
	}
}


