#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL unsigned long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 600010;
int T, n, m;
struct eg {
	int u, v, w;
	bool operator < (const eg & p) const {
		return w < p.w;
	}
}ed[N];
struct Edge {
	int to, next;
}e[N];
int list[N], d, cnt;
void add(int x, int y) {
	e[d].to = y, e[d].next = list[x], list[x] = d++;
}
int fa[N];
LL ad[N], sz[N];
LL f[N], ans;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int find_fa(int x) {
	if(x != fa[x]) fa[x] = find_fa(fa[x]);
	return fa[x];
}
void Dfs(int t) {
	if(t <= n) sz[t] = 1;
	else sz[t] = 0;
	for(int i = list[t]; i >= 0; i = e[i].next) {
		Dfs(e[i].to);
		sz[t] += sz[e[i].to];
	}
}
void dfs(int t, LL p) {
	f[t] = p;
	for(int i = list[t]; i >= 0; i = e[i].next) 
		dfs(e[i].to, p + ad[t] * (sz[t] - sz[e[i].to]));
}
int main() {
	Hzy("G");
	T = read();
	for(int tc = 1; tc <= T; ++tc) {
		n = read(), m = read();
		for(int i = 1; i <= n; ++i) fa[i] = i, f[i] = 0, ad[i] = 0;
		for(int i = 0; i <= n + m; ++i) list[i] = -1;
		d = 0, cnt = n;
		int x, y, z;
		for(int i = 1; i <= m; ++i) {
			x = read(), y = read(), z = read();
			ed[i].u = x, ed[i].v = y, ed[i].w = z;
		}
		sort(ed + 1, ed + m + 1);
		for(int i = 1; i <= m; ++i) {
			x = ed[i].u, y = ed[i].v, z = ed[i].w;
			x = find_fa(x), y = find_fa(y);
			if(x != y) {
				cnt++;
				fa[cnt] = cnt;
				fa[x] = cnt, fa[y] = cnt;
				add(cnt, x), add(cnt, y);
				ad[cnt] = z;
			}
		}
		Dfs(cnt);
		dfs(cnt, 0);
		ans = 0;
		LL tp;
		for(int i = 1; i <= n; ++i) {
			tp = f[i] * i;
			ans ^= tp;
		}
		printf("Case #%d: %lld\n", tc, ans);
		//if(tc != T) puts("");
	}
	return 0;
}
