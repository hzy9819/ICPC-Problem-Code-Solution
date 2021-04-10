#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 100010;
struct Edge {
	int to, next, w;
}e[N * 2];
int list[N], d;
int n, p;
void add(int x, int y, int w) {
	e[d].to = y, e[d].next = list[x], e[d].w = w, list[x] = d++;
}
int fa[N];
LL f[N], s[N], ans;
void dfs(int t) {
	for(int i = list[t]; i >= 0; i = e[i].next) if(!fa[e[i].to]) {
			fa[e[i].to] = t;
			s[e[i].to] = s[t] + e[i].w;
			dfs(e[i].to);
		}
}
void Dfs(int t) {
	int w = t;
	f[t] = (1LL << 60);
	do {
		w = fa[w];
		f[t] = min(f[t], f[w] + (s[t] - s[w]) * (s[t] - s[w]) + p);
	}while(w != 1);
	if(t == 1) f[t] = 0;
	ans = max(ans, f[t]);
	for(int i = list[t]; i >= 0; i = e[i].next) if(e[i].to != fa[t]) Dfs(e[i].to);
}
int main() {

	freopen("I.in", "r", stdin), freopen("bf.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &p), ans = 0;
		memset(list, -1, sizeof list), d = 0;
		int x, y, z;
		for(int i = 1; i < n; ++i) {
			scanf("%d %d %d", &x, &y, &z);
			add(x, y, z);
			add(y, x, z);
		}
		for(int i = 1; i <= n; ++i) fa[i] = 0;
		fa[1] = 1;
		dfs(1);
		Dfs(1);
		printf("%lld\n", ans - p);
	}
	return 0;
}
