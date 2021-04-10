#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 210;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int f[N][N], ans[N * N];
pair <int, int> a[N];
pair <pair<int, int>, pair<int, int> > que[N];
int n, q;

int main() {
	int T = read(), cas = 0;
	while(T--) {
		cas++;
		n = read(), q = read();
		for(int i = 1; i <= n; ++i)
			a[i].l = read(), a[i].r = i;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				f[i][j] = read();
		for(int i = 1; i <= q; ++i)
			que[i].r.l = read(), que[i].r.r = read(), que[i].l.l = read(), que[i].l.r = i;
		sort(a + 1, a + n + 1);
		sort(que + 1, que + q + 1);
		int p = 1;
		for(int i = 1; i <= q; ++i) {
			while(p <= n && a[p].l <= que[i].l.l) {
				int t = a[p++].r;
				for(int j = 1; j <= n; ++j)
					for(int k = 1; k <= n; ++k)
						if(f[j][t] + f[t][k] < f[j][k])
							f[j][k] = f[j][t] + f[t][k];
			}
			ans[que[i].l.r] = f[que[i].r.l][que[i].r.r];
		}
		printf("Case #%d:\n", cas);
		for(int i = 1; i <= q; ++i) 
			printf("%d\n", ans[i]);
	}
	return 0;
}
