import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Arrays;

public class E {
	public static void main(String [] args) {
		InputStream ins = System.in;
		OutputStream outs = System.out;
		Scanner in = new Scanner(ins);
		PrintWriter out = new PrintWriter(outs);
		Solver sol = new Solver();
		//out.println("ok");
		sol.solve(in, out);
		out.close();
	}
	
	static class Solver {
		int n, m, d = 0;
		long ans = 0;
		int [] dsz = new int[1000010];
		int [] lst = new int[1000010];
		int [] to = new int[1000010];
		int [] next = new int[1000010];

		public void add(int x, int y) {
			to[d] = y;
			next[d] = lst[x];
			lst[x] = d;
			d = d + 1;
		}

		public void solve(Scanner in, PrintWriter out) {
			int n = in.nextInt();
			Arrays.fill(lst, -1);
			//out.println(G.n + " " + G.m);
			//for(int i = 1; i <= n; ++i)
			//	out.println(G.lst[i]);
			int x, y;
			for(int i = 1; i < n; ++i) {
				x = in.nextInt();
				y = in.nextInt();
				//out.println(x + " " + y + " " + d);
				add(x, y);
				add(y, x);
				//e[d].to = y;
				//e[d].next = lst[x];
				//lst[x] = d;
				//d = d + 1;

			}
			Dfs_init(1, -1);
			long sum = 0;
			for(int i = 1; i <= n; ++i)
				sum = sum + dsz[i];
			Dfs_Update(1, -1, sum);
			out.println(ans);
		}
		public void Dfs_init(int t, int fa) {
			dsz[t] = 1;
			for(int i = lst[t]; i >= 0; i = next[i])
				if(to[i] != fa) {
					Dfs_init(to[i], t);
					dsz[t] = dsz[t] + dsz[to[i]];
				}
		}
		public void Dfs_Update(int t, int fa, long now_ans) {
			if(now_ans > ans)
				ans = now_ans;
			int tmp1 = dsz[t], tmp2;
			for(int i = lst[t]; i >= 0; i = next[i])
				if(to[i] != fa) {
					tmp2 = dsz[to[i]];
					dsz[t] = dsz[t] - dsz[to[i]];
					dsz[to[i]] = tmp1;
					Dfs_Update(to[i], t, now_ans + dsz[t] - tmp2);
					dsz[t] = tmp1;
					dsz[to[i]] = tmp2;
				}
		}
	}
}