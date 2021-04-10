#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int gcd(int a, int b) {
	if(a < b)
		swap(a, b);
	int c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}

int n, a[N], fa[N], to[N];
int ans[N], k;
bool vis[N];

int find_fa(int x) {
	if(x == fa[x])
		return fa[x];
	fa[x] = find_fa(fa[x]);
	return fa[x];
}

int main() {
	int T = read();
	while(T--) {
		n = read();
		for(int i = 1; i <= n; ++i)
			fa[i] = i, a[i] = read(), to[i] = i + 1, vis[i] = 1;
		to[n] = 1;
		k = 0;
		bool fg = 1;
		int p = 1, nxt, x, y;
		while(1) {
			y = find_fa(p);
			nxt = to[y];
			if(nxt <= p || y < p) {
				if(fg)
					fg = 0;
				else
					break;
			}
			p = y;
			if(!vis[p])
				break;
			if(gcd(a[p], a[nxt]) == 1) {
				ans[++k] = nxt;
				vis[nxt] = 0;
				to[p] = to[nxt];
				fg = 1;
			}
			else {
				x = find_fa(p), y = find_fa(nxt);
				fa[x] = y;
			}
			p = to[p];
		}
		printf("%d ", k);
		for(int i = 1; i <= k; ++i)
			printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}
