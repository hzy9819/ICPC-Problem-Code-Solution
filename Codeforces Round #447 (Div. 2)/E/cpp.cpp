#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1000010;
const LL lim = 1000000;
struct Edge {
	int to, next, w;
}e[N * 2];
int lst[N], ls[N], d;
int dfn[N], cnt, low[N], color[N], sz;
bool in[N];
stack <int> s;
int indg[N];
void add(int x, int y, int w, int * lst) {
	e[d].to = y, e[d].next = lst[x], e[d].w = w, lst[x] = d++;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, st;
LL v[N], ans, f[N];
LL func(LL x) { return x * (x + 1) / 2;}
LL sum(LL x) { return (x * (x + 1) * (2LL * x + 1) / 6 + x * (x + 1) / 2) / 2;}
LL calc(LL w) {
	LL l, r, mid;
	for(l = 0, r = lim, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
		if(func(mid) <= w) l = mid + 1;
		else r = mid - 1;
	return w * l - sum(l - 1);
}
void dfs(int t) {
	dfn[t] = low[t] = ++cnt;
	s.push(t), in[t] = 1;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(!dfn[e[i].to]) {
			dfs(e[i].to);
			low[t] = min(low[t], low[e[i].to]);
		}
		else if(in[e[i].to]) low[t] = min(low[t], dfn[e[i].to]);
	if(low[t] == dfn[t]) {
		int x; ++sz;
		do {
			x = s.top(), s.pop();
			color[x] = sz, in[x] = 0;
		}while(x != t);
	}
}
bool vis[N];
void Dfs(int t) {
	vis[t] = 1;
	for(int i = ls[t]; i >= 0; i = e[i].next) if(!vis[e[i].to]) Dfs(e[i].to);
}
int main() {
	Hzy("E");
	n = read(), m = read();
	int x, y, z;
	memset(lst, -1, 4 * (n + 1)); d = 0;
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read(), z = read();
		add(x, y, z, lst);
	}
	for(int i = 1; i <= n; ++i)
		if(!dfn[i]) dfs(i);
	memset(ls, -1, 4 * (sz + 1));
	for(int t = 1; t <= n; ++t)
		for(int i = lst[t]; i >= 0; i = e[i].next)
			if(color[t] == color[e[i].to]) v[color[t]] += calc((LL) e[i].w);
			else add(color[t], color[e[i].to], e[i].w, ls), indg[color[e[i].to]]++;
	st = read();
	Dfs(color[st]);
	//bool fg = 0;
	/*for(int i = 1; i <= sz; ++i) 
		if(indg[i] == 0) 
		s.push(i), f[i] = v[i];*/
	for(int i = 1; i <= sz; ++i) {
		f[i] = v[i];
		if(!vis[i])
			for(int j = ls[i]; j >= 0; j = e[j].next) indg[e[j].to]--;
	}
	s.push(color[st]);
	ans = f[color[st]] = v[color[st]];
	while(!s.empty()) {
		x = s.top(), s.pop();
		//if(x == color[st]) fg = 1;
		for(int i = ls[x]; i >= 0; i = e[i].next) {
			indg[e[i].to]--;
			if(!indg[e[i].to]) s.push(e[i].to);
			f[e[i].to] = max(f[e[i].to], f[x] + e[i].w + v[e[i].to]);
			ans = max(ans, f[e[i].to]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
