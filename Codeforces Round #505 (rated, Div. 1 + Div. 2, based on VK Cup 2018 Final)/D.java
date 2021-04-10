import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Scanner;

public class D {
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
		private int gcd(int a, int b) {
			int c = 0;
			if(a < b) {
				c = a;
				a = b;
				b = c;
			}
			while(b > 0) {
				c = a % b; 
				a = b;
				b = c;
			}
			return a;
		}

		public void solve(Scanner in, PrintWriter out) {
			int n = in.nextInt();
			int [] a = new int[n + 10];
			boolean[][] g = new boolean[n + 10][n + 10];
			boolean[][] dpl = new boolean[n + 10][n + 10];
			boolean[][] dpr = new boolean[n + 10][n + 10];

			for(int i = 1; i <= n; ++i) a[i] = in.nextInt();

			for(int i = 1; i <= n; ++i)
				for(int j = i; j <= n; ++j)
					g[i][j] = g[j][i] = (gcd(a[i], a[j]) > 1);

			for(int len = 0; len < n; ++len) {
				for(int l = 1; l + len <= n; ++l) {
					int r = l + len;
					for(int i = l; i <= r; ++i) {
						boolean lg = (i == l || dpr[l][i - 1]);
						boolean rg = (i == r || dpl[i + 1][r]);
						if(!(lg && rg)) continue;
						if(g[i][l - 1]) dpl[l][r] = true;
						if(g[i][r + 1]) dpr[l][r] = true;
					}
				}
			}

			for(int i = 1; i <= n; ++i) {
				boolean lg = (i == 1 || dpr[1][i - 1]);
				boolean rg = (i == n || dpl[i + 1][n]);

				if(lg && rg) {
					out.println("Yes");
					return ;
				}
			}
			out.println("No");
		}
	}
}